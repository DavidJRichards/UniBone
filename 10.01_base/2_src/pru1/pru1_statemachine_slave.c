/* pru1_statemachine_slave.c: state machine for execution of slave DATO* or DATI* cycles

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

   Statemachine for execution of slave DATO* or DATI* cycles.
   All references "PDP11BUS handbook 1979"

   Slave reponds not to INIT on this level, master must stop bus transactions.

   - Slave waits for MSYN L->H
   - slaves fetches address and control lines
   - address is evaluated, ggf mem access
 */

#define _PRU1_STATEMACHINE_SLAVE_C_

#include <stdint.h>

#include "pru1_utils.h"

#include "mailbox.h"
#include "ddrmem.h"
#include "iopageregister.h"

#include "pru1_buslatches.h"
#include "pru1_statemachine_slave.h"

statemachine_slave_t sm_slave;

// forwards ;
static uint8_t sm_slave_state_1(void);
static uint8_t sm_slave_state_10(void);
static uint8_t sm_slave_state_20(void);
static uint8_t sm_slave_state_99(void);

// setup with
void sm_slave_start() {
	sm_slave.state = &sm_slave_state_1;
	// next call to sm_slave.state() starts state machine
}

// check for MSYN active
static uint8_t sm_slave_state_1() {
	uint8_t latch2val, latch3val, latch4val;
	// uint8_t iopage;
	uint32_t addr;
	uint8_t control;
	uint16_t data;
	// uint8_t	page_table_entry ;
	uint16_t w;
	uint8_t b;

	// fast sample of busstate, should be atomic
	latch4val = buslatches_get(4); // MSYN first

	// MSYN active ?
	if (!(latch4val & BIT(4)))
		return 1; // still idle
	if (latch4val & BIT(5))
		// SSYN active: cycle answered by other bus slave
		return 1; // still idle
	// checking against SSYN guarantees address if valid if fetched now.
	// However, another Bus slave can SSYN immediately

	latch2val = buslatches_get(2); // A0..7
	latch3val = buslatches_get(3); // A8..15

	// decode address and control
	// addr0..7 = latch[2]
	// addr8..15 = latch[3]
	// addr 16,17 = latch[4].0,1
	addr = latch2val | ((uint32_t) latch3val << 8) | ((uint32_t) (latch4val & 3) << 16);

	// make bool of a17..a13. iopage, if a17..a13 all 1's
	// iopage = ((latch3val & 0xe0) | (latch4val & 3)) == 0xe3;
	// 2 statements above = 12 cycles = 60ns

	// C0 = latch[4], bit 2
	// C1 = latch[4], bit 3
	control = (latch4val >> 2) & 3;
	// !!! Attention: on fast UNIBUS cycles to other devices,
	// !!! SSYN may already be asserted. Or MSYN may even be inactive again !!!

	// page_table_entry = PAGE_TABLE_ENTRY(deviceregisters,addr) ; // is addr ignored,memory,iopage?
//	if (addr >= 0x8000 && addr < 0x10000)
//		page_table_entry = PAGE_MEMORY ;
	switch (control) {
	case UNIBUS_CONTROL_DATI: // fast cases first
	case UNIBUS_CONTROL_DATIP:
		// DATI: get data from memory or registers onto BUS, then SSYN
		if (iopageregisters_read(addr, &data)) {

			// DATA[0..7] = latch[5]
			buslatches_setbyte(5, data & 0xff);
			// DATA[8..15] = latch[6]
			buslatches_setbyte(6, data >> 8);
			//DEBUG_PIN_PULSE ; // trigger scope/LA. auto cleared on next reg_sel
			// set SSYN = latch[4], bit 5
			buslatches_setbits(4, BIT(5), BIT(5));
			sm_slave.state = &sm_slave_state_20;
			// perhaps PRU2ARM_INTERRUPT now active
		} else
			// no address match: wait for MSYN to go inactive
			sm_slave.state = &sm_slave_state_99;
		break;
	case UNIBUS_CONTROL_DATO:
		// fetch data in any case
		// DATA[0..7] = latch[5]
		w = buslatches_get(5);
		// DATA[8..15] = latch[6]
		w |= (uint16_t) buslatches_get(6) << 8;
		if (iopageregisters_write_w(addr, w)) {
			//DEBUG_PIN_PULSE ; // trigger scope/LA. auto cleared on next reg_sel

			// SSYN = latch[4], bit 5
			buslatches_setbits(4, BIT(5), BIT(5));
			// wait for MSYN to go inactive, then SSYN inactive
			sm_slave.state = &sm_slave_state_10;
			// perhaps PRU2ARM_INTERRUPT now active
		} else
			// no address match: wait for MSYN to go inactive
			sm_slave.state = &sm_slave_state_99;
		break;
	case UNIBUS_CONTROL_DATOB:
		// A00 = 1, odd address: get upper byte
		// A00 = 0: even address, get lower byte
		// fetch data
		if (addr & 1) {
			// DATA[8..15] = latch[6]
			b = buslatches_get(6);
		} else {
			// DATA[0..7] = latch[5]
			b = buslatches_get(5);
		}
		if (iopageregisters_write_b(addr, b)) { // always sucessful, addr already tested
			// SSYN = latch[4], bit 5
			buslatches_setbits(4, BIT(5), BIT(5));
			// wait for MSYN to go inactive, then SSYN inactive
			sm_slave.state = &sm_slave_state_10;
			// perhaps PRU2ARM_INTERRUPT now active
		} else
			// no address match: wait for MSYN to go inactive
			sm_slave.state = &sm_slave_state_99;
		break;
	}
	return 0; // busy
}

// End DATO: wait for MSYN to go inactive, then SSYN inactive
// also wait for EVENT ACK
static uint8_t sm_slave_state_10() {
	// MSYN = latch[4], bit 4
	if (buslatches_get(4) & BIT(4))
		return 0; // MSYN still active
	if (mailbox.events.eventmask)
		return 0; // long SSYN delay until ARM acknowledges all events
	// if ARM was triggered by event and changed the device state,
	// now an Interrupt arbitration may be pending!

	// clear SSYN = latch[4], bit 5
	buslatches_setbits(4, BIT(5), 0);

	sm_slave.state = &sm_slave_state_1;
	return 1; // ready }
}

// End DATI: wait for MSYN to go inactive, then SSYN and DATA inactive
// also wait for EVENT ACK
static uint8_t sm_slave_state_20() {
	// MSYN = latch[4], bit 4
	if (buslatches_get(4) & BIT(4))
		return 0; // MSYN still active
	if (mailbox.events.eventmask)
		return 0; // long SSYN delay until ARM acknowledges event
	// if ARM was triggered by event and changed the device state,
	// now an Interrupt arbitration may be pending!

	// clear first data, then SSYN
	// DATA[0..7] = latch[5]
	buslatches_setbyte(5, 0);
	// DATA[8..15] = latch[6]
	buslatches_setbyte(6, 0);
	// clear SSYN = latch[4], bit 5
	buslatches_setbits(4, BIT(5), 0);
	sm_slave.state = &sm_slave_state_1;
	return 1; // ready }
}

// end of inactive cycle: wait for MSYN to go inactive
static uint8_t sm_slave_state_99() {
	// MSYN = latch[4], bit 4
	if (buslatches_get(4) & BIT(4))
		return 0; // MSYN still active

	sm_slave.state = &sm_slave_state_1;
	return 1; // ready }
}
