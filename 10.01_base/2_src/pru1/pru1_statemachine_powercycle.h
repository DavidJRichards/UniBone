/* pru1_statemachine_powercycle.h: state machine to generate an ACLO/DCLO pseudo power cycle

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
#ifndef  _PRU1_STATEMACHINE_POWERCYCLE_H_
#define  _PRU1_STATEMACHINE_POWERCYCLE_H_

#include <stdint.h>

#define POWERCYCLE_DELAY_MS	100 	// wait period in millsecs between ACLO/DCLO transitions

// execution of a state. return : 1, if statemachine stopped
typedef uint8_t (*sm_powercycle_state_func_ptr)(void);

typedef struct {
	sm_powercycle_state_func_ptr state; // current state as ptr to  "state function"
} statemachine_powercycle_t;

#ifndef  _PRU1_STATEMACHINE_POWERCYCLE_C_
extern statemachine_powercycle_t sm_powercycle;
#endif

void sm_powercycle_start();

#endif
