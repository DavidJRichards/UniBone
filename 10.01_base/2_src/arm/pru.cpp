/* pru.cpp: Management interface to PRU0 & PRU1.

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

 Management interface to PRU0 & 1:
 - setup interrupt
 - download code from arrays in pru0/1_config.c

 Partly copyright (c) 2014 dhenke@mythopoeic.org

 usage: sudo ./example
 ***/
#define _PRU_CPP_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>

#include <fcntl.h>

#include "logger.hpp"
#include "prussdrv.h"
#include "pruss_intc_mapping.h"
#include "mailbox.h"
#include "ddrmem.h"
#include "iopageregister.h"

#include "pru.hpp"

#define PRUSS_MAX_IRAM_SIZE 8192

// Array with program code for PRU
// generated by 'hexpru --array'
#include "pru0_config.h"
#include "pru1_config.h"
#define  PRU0_CODE_IMAGE  pru0_image_0   // name of bianry array in include
#define  PRU1_CODE_IMAGE  pru1_image_0   // name of bianry array in include

// Singleton
pru_c	*pru ;

pru_c::pru_c() {
	log_label = "PRU" ;
}


/*** pru_setup() -- initialize PRU and interrupt handler

 Initializes both PRUs and sets up PRU_EVTOUT_0 handler.

 The argument is a pointer to a null-terminated string containing the path
 to the file containing the PRU program binary.

 Returns 0 on success, non-0 on error.
 ***/
int pru_c::setup() {
	int rtn;
	tpruss_intc_initdata intc = PRUSS_INTC_INITDATA;

	/* initialize PRU */
	if ((rtn = prussdrv_init()) != 0) {
		ERROR("prussdrv_init() failed");
		return rtn;
	}

	/* open the interrupt */
	if ((rtn = prussdrv_open(PRU_EVTOUT_0)) != 0) {
		ERROR("prussdrv_open() failed");
		return rtn;
	}

	/* initialize interrupt */
	if ((rtn = prussdrv_pruintc_init(&intc)) != 0) {
		ERROR("prussdrv_pruintc_init() failed");
		return rtn;
	}

	/*
	 http://credentiality2.blogspot.com/2015/09/beaglebone-pru-ddr-memory-access.html
	 * get pointer to shared DDR
	 */
	// Pointer into the DDR RAM mapped by the uio_pruss kernel module.
	ddrmem->base_virtual = NULL;
	prussdrv_map_extmem((void **) &(ddrmem->base_virtual));
	ddrmem->len = prussdrv_extmem_size();
//	INFO("Shared DDR memory: %u bytes available.", ddrmem.len);

	ddrmem->base_physical = prussdrv_get_phys_addr((void *) (ddrmem->base_virtual));
	ddrmem->info(); // may abort program

	/* load code from arrays PRU*_code[] into  PRU and start at 0
	 */
	if (pru0_sizeof_code() > PRUSS_MAX_IRAM_SIZE) {
		FATAL("PRU0 code too large. Closing program");
	}
	if ((rtn = prussdrv_exec_code_at(0, PRU0_CODE_IMAGE, pru0_sizeof_code(), PRU0_ENTRY_ADDR))
			!= 0) {
		ERROR("prussdrv_exec_program() failed");
		return rtn;
	}

	if (pru1_sizeof_code() > PRUSS_MAX_IRAM_SIZE) {
		FATAL("PRU1 code too large. Closing program");
		exit(1);
	}
	if ((rtn = prussdrv_exec_code_at(1, PRU1_CODE_IMAGE, pru1_sizeof_code(), PRU1_ENTRY_ADDR))
			!= 0) {
		ERROR("prussdrv_exec_program() failed");
		return rtn;
	}

	sleep(1); // wait for PRU to come up, much too long

	// get address of mail box struct in PRU
	mailbox_connect();

	// get address of device register descriptor struct in PRU
	iopageregisters_connect();

	return rtn;
}

/*** pru_cleanup() -- halt PRU and release driver

 Performs all necessary de-initialization tasks for the prussdrv library.

 Returns 0 on success, non-0 on error.
 ***/
int pru_c::cleanup(void) {
	int rtn = 0;

	/* clear the event (if asserted) */
	if (prussdrv_pru_clear_event(PRU_EVTOUT_0, PRU0_ARM_INTERRUPT)) {
		ERROR("prussdrv_pru_clear_event() failed");
		rtn = -1;
	}

	/* halt and disable the PRU (if running) */
	if ((rtn = prussdrv_pru_disable(0)) != 0) {
		ERROR("prussdrv_pru_disable(0) failed");
		rtn = -1;
	}

	if ((rtn = prussdrv_pru_disable(1)) != 0) {
		ERROR("prussdrv_pru_disable(1) failed");
		rtn = -1;
	}

	/* release the PRU clocks and disable prussdrv module */
	if ((rtn = prussdrv_exit()) != 0) {
		ERROR("prussdrv_exit() failed");
		rtn = -1;
	}

	return rtn;
}
