/* mailbox.cpp: datastructs common to ARM and PRU

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


#define _MAILBOX_CPP_

#include <stdio.h>
#include "prussdrv.h"

#include "logger.hpp"
#include "ddrmem.h"
#include "mailbox.h"

#include "pru1_config.h"

// is located in PRU 12kb shared memory.
// address symbol "" fetched from linker map
volatile mailbox_t *mailbox;

int mailbox_connect(void) {
	void *pru_shared_dataram;
	// get pointer to RAM
	if (prussdrv_map_prumem(PRU_MAILBOX_RAM_ID, &pru_shared_dataram)) {
		printf("ERROR: prussdrv_map_prumem() failed\n");
		return -1;

	}
	// prussdrv_map_prumem( PRU_MAILBOX_RAM_ID, &pru_shared_dataram) ;
	// point to struct inside RAM
	mailbox = (mailbox_t *) ((char *) pru_shared_dataram + PRU_MAILBOX_RAM_OFFSET);

	// now ARM and PRU can access the mailbox

	// tell PRU location of shared DDR RAM
	mailbox->ddrmem_base_physical = (ddrmem_t *) ddrmem->base_physical;

	return 0;
}

void mailbox_print(void) {
	printf("INFO: Content of mailbox to PRU:\n"
	"arm2pru: req=0x%x, resp=0x%x\n", mailbox->arm2pru_req, mailbox->arm2pru_resp);
}

/* simulate simple register accesses:
 * write test_addr + OP,
 * result in "val"
 */
static unsigned n = 0;
void mailbox_test1() {
	unsigned reg_sel = 0;
	for (reg_sel = 0; reg_sel < 8; reg_sel++) {
		//TODO: memory barrier??
//		__sync_synchronize() ;
		mailbox->mailbox_test.addr = n & 0xff;
//		__sync_synchronize() ;
		while (mailbox->mailbox_test.addr != (n & 0xff))
			; // cache ?
		__sync_synchronize(); // write to arm2pru_req must be last operation
		mailbox->arm2pru_req = ARM2PRU_MAILBOXTEST1; // go!
		while (mailbox->arm2pru_req)
			; // wait until processed
//		__sync_synchronize() ;
		n++;
		// PRU copies addr to val and may output on GPIOs
		/*
		 if (mailbox->mailbox_test.val != mailbox->mailbox_test.addr) {
		 printf("?");
		 fflush(stdout);
		 }
		 */
	}
}

/* start cmd to PRU via mailbox. Wait until ready
 * mailbox union members must have been filled
 */
void mailbox_execute(uint8_t request, uint8_t stopcode) {
// write to arm2pru_req must be last memory operation
	__sync_synchronize();
	mailbox->arm2pru_req = request; // go!
	while (mailbox->arm2pru_req != stopcode)
		; // wait until processed
}
