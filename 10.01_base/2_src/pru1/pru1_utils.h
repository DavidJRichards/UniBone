/* pru1_utils.h:  misc. utilities

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
*/
#ifndef _PRU1_UTILS_H_
#define _PRU1_UTILS_H_


#include <stdint.h>

#include <pru_cfg.h>
#include <pru_ctrl.h>

/* R30,R31 declaration for all modules*/
volatile register uint32_t __R30;
volatile register uint32_t __R31;




#define MILLION 1000000L
#define BILLION (1000L * MILLION)


// SSYN timeout after 20 milliseconds
#define	UNIBUS_TIMEOUT_PERIOD_US	20

// cycles equivalent to given amount of nano seconds
#define NANOSECS(n) ( (n) / 5)
#define MICROSECS(n) ( (n) * 1000 / 5)
#define MILLISECS(n) ( (n) * 1000000 / 5)

#define BIT(n) (1 << (n))

/* The single global timeout uses the CYCLECOUNT counter
 * cycle is counting upward at 200MHz, stopps at 0xff.fff
 * CTR_EN must be 1. clearing only if CTR_EN = 0
 * can only by reset when  CTR_EN = 0
 * TIMEOUT_INTERNAL_CYCLES counts cycles to process
 * both TIMEOUT_SET and _REACHED.
 * Translated with "clpru 2.2, -O3"
 *
 * Test setup:
while (1) {
	__R30 |= (1 << 8);
		TIMEOUT_SET(NANOSECS(1000)) ; // 1 usec / level
		while (!TIMEOUT_REACHED) ;
		__R30 &= ~(1 << 8);
		TIMEOUT_SET(NANOSECS(1000)) ;
		while (!TIMEOUT_REACHED) ;
}
*
* Enhancement: save address of CYLCE in cosntant btabel C28, see
http://theembeddedkitchen.net/beaglelogic-building-a-logic-analyzer-with-the-prus-part-1/449
* ALTERNATIVE 1:
 * The Industrial Ethernet module has a general purpose time and compare registers:
 * 32 bit Counter is permanetly running cyclic through overlfow
 * TIMEOUT_SET:  compare0 = counter + delay, clear compare0 flag
 *	Error, if rollaround: Compare0 < counter    !!!!
 * TIMEOUT_REACHED: test CMP_HIT0 flag set in IEP_TMR_CMP_STS
 * reset counter on match
 * This way 8 differnet timeouts could be programmed
 * COUNTER reset on start of statemachine??
 * dann nur compare0 nutzbar
 * counter overflow auf 2^32 5ns =  21 sek

* ALTERNATIVE 2:
* PRU0 decrements a mailbox value until it is 0.
* introduces delay in PRU0 outputs!

 */
#define TIMEOUT_INTERNAL_CYCLES	24
#define TIMEOUT_SET(cycles)	do {	\
	PRU1_CTRL.CTRL_bit.CTR_EN = 0;	\
	PRU1_CTRL.CYCLE = 0 ;		\
	timeout_target = ((cycles) > TIMEOUT_INTERNAL_CYCLES) ? ((cycles) - TIMEOUT_INTERNAL_CYCLES) : 0 ; /* 4 cycle used in TIMEOUT_REACHED */	\
	PRU1_CTRL.CTRL_bit.CTR_EN = 1;	\
} while(0)

#define TIMEOUT_REACHED 	\
	( (PRU1_CTRL.CYCLE >= timeout_target))


// set PRU1_12 to 0 or 1
#define DEBUG_PIN_SET(val) ( (val) ? (__R30 |= (1 << 12) ) : (__R30 &= ~(1<< 12)) )

// 20ns pulse an PRU1_12
#define DEBUG_PIN_PULSE do {	\
		__R30 |= (1 << 12) ;	\
		__delay_cycles(4-1) ; \
		__R30 &= ~(1 << 12) ;	\
	} while(0)


#define DEBUG_PIN_PULSE_100NS	do {	\
		__R30 |= (1 << 12) ;	\
		__delay_cycles(18) ;	\
		__R30 &= ~(1 << 12) ;	\
} while(0)


// To signal the host that we're done, we set bit 5 in our R31
// simultaneously with putting the number of the signal we want
// into R31 bits 0-3. See 5.2.2.2 in AM335x PRU-ICSS Reference Guide.
// http://mythopoeic.org/BBB-PRU/pru-helloworld/example.p
// and http://www.righto.com/2016/09/how-to-run-c-programs-on-beaglebones.html

#define PRU2ARM_INTERRUPT_PRU0_R31_VEC_VALID (1<<5)
#define PRU2ARM_INTERRUPT_SIGNUM 3 // corresponds to PRU_EVTOUT_0
#define PRU2ARM_INTERRUPT do {		\
	/* is Interrupt "level" or "edge"??? */					\
	__R31 = PRU2ARM_INTERRUPT_PRU0_R31_VEC_VALID |PRU2ARM_INTERRUPT_SIGNUM ; /* 35 */ \
DEBUG_PIN_PULSE	; 	\
	} while(0)


#ifndef _PRU1_UTILS_C_
extern uint32_t timeout_target ;
#endif


#endif
