/* pru1_statemachine_dma.c: state machine for bus master DMA

   Copyright (c) 2018, Joerg Hoppe
   j_hoppe@t-online.de, www.retrocmp.com

   Permission is hereby granted, free of charge, to any person obtaining a
   copy of this software and associated documentation files (the "Software"),
   to deal in the Software without restriction, including without limitation
   the rights to use, copy, modify, merge, publish, distribute, sublicense,
   and/or sell copies of the Software, and to permit persons to whom the
   Software is furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in
   all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
   JOERG HOPPE BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
   IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
   CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.


   12-nov-2018  JH      entered beta phase


   Statemachines to execute multiple masterr DATO or DATI cycles.
   All references "PDP11BUS handbook 1979"
   Precondition: BBSY already asserted (arbitration got)

    Master reponds to INIT by stopping transactions.
   new state

   Start: setup dma mailbox setup with
  	startaddr, wordcount, cycle, words[]
  	Then sm_dma_init() ;
  	sm_dma_state = DMA_STATE_RUNNING ;
  	while(sm_dma_state != DMA_STATE_READY)
  		sm_dma_service() ;
  	state is 0 for OK, or 2 for timeout error.
  	mailbox.dma.cur_addr is error location

  	Speed: (clpru 2.2, -O3:
   	Example: DATI, time SSYN- active -> (processing) -> MSYN inactive
  	a) 2 states, buslatch_set/get function calls, TIMEOUT_SET/REACHED(75) -> 700ns
  	b) 2 states, buslatch_set/get macro, TIMEOUT_SET/REACHED(75) -> 605ns
  	c) 2 states, no TIMEOUT (75 already met) -> 430ns
  	d) 1 marged state, no TIMEOUT  ca. 350ns

   ! Uses single global timeout, don't run in parallel with other statemachines using timeout  !
 */
#define _PRU1_STATEMACHINE_DMA_C_

#include <stdint.h>
#include <stdbool.h>

#include "iopageregister.h"
#include "mailbox.h"
#include "pru1_buslatches.h"
#include "pru1_utils.h"

#include "pru1_statemachine_arbitration.h"
#include "pru1_statemachine_dma.h"

/* sometimes short timeout of 75 and 150ns are required
 * 75ns between state changes is not necessary, code runs longer
 * 150ns between state changes is necessary
 * Overhead for extra state and TIEOUTSET/REACHED is 100ns
 */

statemachine_dma_t sm_dma;

/********** Master DATA cycles **************/
// forwards ;
static uint8_t sm_dma_state_1(void);
static uint8_t sm_dma_state_11(void);
static uint8_t sm_dma_state_21(void);
static uint8_t sm_dma_state_99(void);

// dma mailbox setup with
// startaddr, wordcount, cycle, words[]   ?
// "cycle" must be UNIBUS_CONTROL_DATI or UNIBUS_CONTROL_DATO
// BBSY already set, SACK held asserted
void sm_dma_start() {
	// assert BBSY: latch[1], bit 6
	// buslatches_setbits(1, BIT(6), BIT(6));

	mailbox.dma.cur_addr = mailbox.dma.startaddr;
	sm_dma.dataptr = (uint16_t *) mailbox.dma.words; // point to start of data buffer
	sm_dma.state = &sm_dma_state_1;
	sm_dma.cur_wordsleft = mailbox.dma.wordcount;
	mailbox.dma.cur_status = DMA_STATE_RUNNING;
	// next call to sm_dma.state() starts state machine
}

// place address and control bits onto bus, also data for DATO
// If slave address is internal (= implemented by UniBone),
// fast UNIBUS slave protocoll is generated on the bus.
static uint8_t sm_dma_state_1() {
	uint32_t tmpval;
	uint32_t addr = mailbox.dma.cur_addr; // non-volatile snapshot
	uint16_t data;
	uint8_t control = mailbox.dma.control;
	// uint8_t page_table_entry;
	uint8_t b;
	bool internal;

	if (mailbox.dma.cur_status != DMA_STATE_RUNNING || mailbox.dma.wordcount == 0)
		return 1; // still stopped

	if (sm_dma.cur_wordsleft == 1) {
		// deassert SACK, enable next arbitration cycle
		// deassert SACK before deassert BBSY
		// parallel to last word data transfer
		buslatches_setbits(1, BIT(5), 0); // SACK = latch[1], bit 5
	}

	sm_dma.state_timeout = 0;

	// addr0..7 = latch[2]
	buslatches_setbyte(2, addr & 0xff);
	// addr8..15 = latch[3]
	buslatches_setbyte(3, (addr >> 8));
	// addr 16,17 = latch[4].0,1
	// C0 = latch[4], bit 2
	// C1 = latch[4], bit 3
	// MSYN = latch[4], bit 4
	// SSYN = latch[4], bit 5
	if (UNIBUS_CONTROL_ISDATO(control)) {
		tmpval = (addr >> 16) & 3;
		tmpval |= BIT(3); // DATO: c1=1, c0=0
		// bit 2,4,5 == 0  -> C0,MSYN,SSYN not asserted
		buslatches_setbits(4, 0x3f, tmpval);
		// write data. SSYN may still be active???
//		data = mailbox.dma.words[sm_dma.cur_wordidx];
		data = *sm_dma.dataptr;
		buslatches_setbyte(5, data & 0xff); // DATA[0..7] = latch[5]
		buslatches_setbyte(6, data >> 8); // DATA[8..15] = latch[6]
		// wait 150ns, but guaranteed to wait 150ns after SSYN inactive
		// prev SSYN & DATA may be still on bus, disturbes DATA
		while (buslatches_get(4) & BIT(5))
			;	// wait for SSYN inactive
		__delay_cycles(NANOSECS(150) - 10);
		// assume 10 cycles for buslatches_get and address test
		// ADDR, CONTROL (and DATA) stable since 150ns, set MSYN

		// use 150ns delay to check for internal address
		// page_table_entry = PAGE_TABLE_ENTRY(deviceregisters,addr);
		// !!! optimizer may not move this around !!!
		// try "volatile internal_addr" (__asm(";---") may be rearanged)

		// MSYN = latch[4], bit 4
		buslatches_setbits(4, BIT(4), BIT(4)); // master assert MSYN

		// DATO to internal slave (fast test).
		// write data into slave (
		switch (control) {
		case UNIBUS_CONTROL_DATO:
			internal = iopageregisters_write_w(addr, data);
			break;
		case UNIBUS_CONTROL_DATOB:
			// A00=1: upper byte, A00=0: lower byte
			b = (addr & 1) ? (data >> 8) : (data & 0xff);
			internal = iopageregisters_write_b(addr, b); // always sucessful, addr already tested
			break;
		default:
			internal = false; // not reached
		}
		if (internal) {
			buslatches_setbits(4, BIT(5), BIT(5)); // slave assert SSYN
			buslatches_setbits(4, BIT(4), 0); // master deassert MSYN
			buslatches_setbyte(5, 0); // master removes data
			buslatches_setbyte(6, 0);
			// perhaps PRU2ARM_INTERRUPT now active,
			// assert SSYN after ARM completes "active" register logic and INIT
			while (mailbox.events.eventmask) ;

			buslatches_setbits(4, BIT(5), 0); // slave deassert SSYN
			sm_dma.state = &sm_dma_state_99; // next word
		} else {
			// DATO to external slave
			// wait for a slave SSYN
			TIMEOUT_SET(NANOSECS(1000*UNIBUS_TIMEOUT_PERIOD_US));
			sm_dma.state = &sm_dma_state_21; // wait SSYN DATAO
		}
	} else {
		// DATI or DATIP
		tmpval = (addr >> 16) & 3;
		// bit 2,3,4,5 == 0  -> C0,C1,MSYN,SSYN not asserted
		buslatches_setbits(4, 0x3f, tmpval);

		// wait 150ns after MSYN, no distance to SSYN required
		__delay_cycles(NANOSECS(150) - 10);
		// assume 10 cycles for buslatches_get and address test
		// ADDR, CONTROL (and DATA) stable since 150ns, set MSYN next

		// use 150ns delay to check for internal address
		// page_table_entry = PAGE_TABLE_ENTRY(deviceregisters,addr);
		// !!! optimizer may not move this around !!!

		// MSYN = latch[4], bit 4
		buslatches_setbits(4, BIT(4), BIT(4)); // master assert MSYN

		if (iopageregisters_read(addr, &data)) {
			// DATI to internal slave: put MSYN/SSYN/DATA protocol onto bus,
			// slave puts data onto bus
			// DATA[0..7] = latch[5]
			buslatches_setbyte(5, data & 0xff);
			// DATA[8..15] = latch[6]
			buslatches_setbyte(6, data >> 8);
			// theoretically another bus member could set bits in bus addr & data ...
			// if yes, we would have to read back the bus lines
			*sm_dma.dataptr = data;
//			mailbox.dma.words[sm_dma.cur_wordidx] = data;

			buslatches_setbits(4, BIT(5), BIT(5)); // slave assert SSYN
			buslatches_setbits(4, BIT(4), 0); // master deassert MSYN
			buslatches_setbyte(5, 0); // slave removes data
			buslatches_setbyte(6, 0);
			// perhaps PRU2ARM_INTERRUPT now active,
			// assert SSYN after ARM completes "active" register logic and INIT
			while (mailbox.events.eventmask) ;

			buslatches_setbits(4, BIT(5), 0); // slave deassert SSYN
			sm_dma.state = &sm_dma_state_99; // next word
		} else {
			// DATI to external slave
			// wait for a slave SSYN
			TIMEOUT_SET(NANOSECS(1000*UNIBUS_TIMEOUT_PERIOD_US));
			sm_dma.state = &sm_dma_state_11; // wait SSYN DATI
		}
	}

	return 0; // still running
}

// DATI to external slave: MSYN set, wait for SSYN or timeout
static uint8_t sm_dma_state_11() {
	uint16_t tmpval;
	sm_dma.state_timeout = TIMEOUT_REACHED;
	// SSYN = latch[4], bit 5
	if (!sm_dma.state_timeout && !(buslatches_get(4) & BIT(5)))
		return 0; // no SSYN yet: wait
	// SSYN set by slave (or timeout). read data
	__delay_cycles(NANOSECS(75) - 6); // assume 2*3 cycles for buslatches_get

	// DATA[0..7] = latch[5]
	tmpval = buslatches_get(5);
	// DATA[8..15] = latch[6]
	tmpval |= (buslatches_get(6) << 8);
	// save in buffer
	*sm_dma.dataptr = tmpval;
	// mailbox.dma.words[sm_dma.cur_wordidx] = tmpval;
	// negate MSYN
	buslatches_setbits(4, BIT(4), 0);
	// DATI: remove address,control, MSYN,SSYN from bus, 75ns after MSYN inactive
	__delay_cycles(NANOSECS(75) - 8); // assume 8 cycles for state change
	sm_dma.state = &sm_dma_state_99;
	return 0; // still running
}

// DATO to external slave: wait for SSYN or timeout
static uint8_t sm_dma_state_21() {
	sm_dma.state_timeout = TIMEOUT_REACHED; // SSYN timeout?
	// SSYN = latch[4], bit 5
	if (!sm_dma.state_timeout && !(buslatches_get(4) & BIT(5)))
		return 0; // no SSYN yet: wait

	// SSYN set by slave (or timeout): negate MSYN, remove DATA from bus
	buslatches_setbits(4, BIT(4), 0); // deassert MSYN
	buslatches_setbyte(5, 0);
	buslatches_setbyte(6, 0);
	// DATO: remove address,control, MSYN,SSYN from bus, 75ns after MSYN inactive
	__delay_cycles(NANOSECS(75) - 8); // assume 8 cycles for state change
	sm_dma.state = &sm_dma_state_99;
	return 0; // still running
}

// word is transfered, or timeout.
static uint8_t sm_dma_state_99() {
	uint8_t final_dma_state;
	// from state_12, state_21

	// 2 reasons to terminate transfer
	// - BUS timeout at curent address
	// - last word transferred
	if (sm_dma.state_timeout) {
		final_dma_state = DMA_STATE_TIMEOUTSTOP;
		// deassert SACK after timeout, independent of remaining word count
		buslatches_setbits(1, BIT(5), 0); // deassert SACK = latch[1], bit 5
	} else {
		sm_dma.dataptr++;  // point to next word in buffer
		sm_dma.cur_wordsleft--;
		if (sm_dma.cur_wordsleft == 0)
			final_dma_state = DMA_STATE_READY; // last word: stop
		else if (buslatches_get(7) & BIT(3)) { // INIT stops transaction: latch[7], bit 3
			// only bus master (=we!) can issue INIT, so this should never be reached
			final_dma_state = DMA_STATE_INITSTOP;
			// deassert SACK after INIT, independent of remaining word count
			buslatches_setbits(1, BIT(5), 0); // deassert SACK = latch[1], bit 5
		} else
			final_dma_state = DMA_STATE_RUNNING; // more words:  continue

	}
	sm_dma.state = &sm_dma_state_1; // in any case, reloop

	if (final_dma_state == DMA_STATE_RUNNING) {
		// dataptr and wordsleft already incremented
		mailbox.dma.cur_addr += 2; // signal progress to ARM
		return 0;
	} else {
		// remove addr and control from bus
		buslatches_setbyte(2, 0);
		buslatches_setbyte(3, 0);
		buslatches_setbits(4, 0x3f, 0);
		// remove BBSY: latch[1], bit 6
		buslatches_setbits(1, BIT(6), 0);
		// terminate arbitration state
		sm_arb.state = &sm_arb_state_idle;
		mailbox.dma.cur_status = final_dma_state; // signal to ARM
		return 1; // now stopped
	}
}

