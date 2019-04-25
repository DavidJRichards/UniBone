/* cpu.cpp: PDP-11/05 CPU

 Copyright (c) 2018, Angelo Papenhoff, Joerg Hoppe

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


 23-nov-2018  JH      created

 In worker() Angelos 11/05 CPU is  running.
 Can do bus amster DAGTIDATO.
 */

#include <string.h>

#include "mailbox.h"

#include "unibus.h"

#include "unibusadapter.hpp"
#include "unibusdevice.hpp"	// definition of class device_c
#include "cpu.hpp"

cpu_c::cpu_c() :
		unibusdevice_c()  // super class constructor
{
	// static config
	name.value = "CPU20";
	type_name.value = "PDP-11/20";
	log_label = "cpu";
	default_base_addr = 0777707; // none
	default_intr_vector = 0;
	default_intr_level = 0;

	// init parameters
	runmode.value = true; //false;
	init.value = false;
	del.value = 2;

	// current CPU does not publish registers to the bus
	register_count = 0;

	memset(&bus, 0, sizeof(bus)) ;
	memset(&ka11, 0, sizeof(ka11)) ;
	ka11.bus = &bus ;


	// controller has a register
	register_count = 1 ;

	reg_R7 = &(this->registers[0]); // @  base addr
	strcpy(reg_R7->name, "R7"); // R7 PC
	reg_R7->active_on_dati = true; // no controller state change
	reg_R7->active_on_dato = true;
	reg_R7->reset_value = 0;
	reg_R7->writable_bits = 0xffff;


	
}

cpu_c::~cpu_c() {

}

extern "C" {
// functions to be used by Angelos CPU emulator
// Result: 1 = OK, 0 = bus timeout
int cpu_dato(unsigned addr, unsigned data) {
	bool timeout;
	mailbox->dma.words[0] = data;
	timeout = !unibus->dma(UNIBUS_CONTROL_DATO, addr, 1);
	return !timeout;

}

int cpu_datob(unsigned addr, unsigned data) {
	// TODO DATOB als 1 byte-DMA !
	bool timeout;
	mailbox->dma.words[0] = data;
	timeout = !unibus->dma(UNIBUS_CONTROL_DATOB, addr, 1);
	return !timeout;

}

int cpu_dati(unsigned addr, unsigned *data) {
	bool timeout;

	timeout = !unibus->dma(UNIBUS_CONTROL_DATI, addr, 1);
	*data = mailbox->dma.words[0];
	return !timeout;
}
}

void cpu_c::cpu2regs (KA11 *cpu)
{
	r0.value = cpu->r[0];
	r1.value = cpu->r[1];
	r2.value = cpu->r[2];
	r3.value = cpu->r[3];
	r4.value = cpu->r[4];
	r5.value = cpu->r[5];
	r6.value = cpu->r[6];
	r7.value = cpu->r[7];
	r10.value = cpu->r[010];
	r11.value = cpu->r[011];
	r12.value = cpu->r[012];
}

void cpu_c::regs2cpu (KA11 *cpu)
{
	cpu->r[0]=r0.value;
	cpu->r[1]=r1.value;
	cpu->r[2]=r2.value;
	cpu->r[3]=r3.value;
	cpu->r[4]=r4.value;
	cpu->r[5]=r5.value;
	cpu->r[6]=r6.value;
	cpu->r[7]=r7.value;
	cpu->r[010]=r10.value;
	cpu->r[011]=r11.value;
	cpu->r[012]=r12.value;
}



// background worker.
// udpate LEDS, poll switches direct to register flipflops
void cpu_c::worker(void) {
	timeout_c timeout;
	bool nxm;
	unsigned pc = 0;
//	unsigned dr = 0760102;
//	unsigned opcode = 0;
	unsigned int buttons;
	unsigned int leds;
//	(void) opcode;

	while (!worker_terminate || (del.value == 0)) {
#if 0 // blocking cpu		
		if(ka11.r[4] == 05430) 	// forth expect, waiting for user key entry
			del.value = 2;
		else if(ka11.r[4] == 0) // init
			del.value = 3;
		else{
			cpu_dato(0760102, 010);
			del.value = 0;
//			timeout.wait_ms(del.value);
			while(del.value==0)
				condstep(&ka11);
//			condstep(&ka11); // blocking
//			return;
		}
#endif		
		timeout.wait_ms(del.value);

		if (runmode.value != (ka11.state != 0))
			ka11.state = runmode.value;
		
		if (step.value)
		{
			ka11.state = step.value;
			putchar('\n');
			printstate(&ka11);
		condstep(&ka11);
			ka11.state = 0;
#if 0 // get button			
		nxm = !cpu_dati(0776510, &buttons);
		if (nxm) {
			printf("Bus timeout at PC = %06o. HALT.\n", pc);
		}
		else
#endif		
			step.value = buttons &1;
			cpu2regs(&ka11);
			pc=r7.value;
#if 0 // show PC			
			nxm = !cpu_dato(0776512, pc);
			if (nxm) {
				printf("Bus timeout at DR = %06o. HALT.\n", pc);
				runmode.value = false;
			}
#endif			

		}

		condstep(&ka11);

		if (runmode.value != (ka11.state != 0))
			runmode.value = ka11.state != 0;

		if(runmode.value)
		{
			if(ka11.r[7]==brk.value)
				step.value=1;
		}

		
		if (init.value) {
			// user wants CPU reset
			reset(&ka11) ;
			ka11.r[6] = 0776; // Stack Pointer
//			ka11.r[7] = 05144; // PC Debug console, NO DIAGNOSTIC ENTRY POINT
			if(!bvec.value) { // boot vector not set so use user supplied PC
				ka11.r[7] = spc.value; // PC Debug console, NO DIAGNOSTIC ENTRY POINT
				ka11.r[010] = 0340; // SR
			}
			else { // use power vector 
				nxm = !cpu_dati(024, (unsigned *)&ka11.r[7]);
				if (nxm) {
					printf("Bus timeout readig PC from 024");
				}
					
				nxm = !cpu_dati(026, (unsigned *)&ka11.r[010]);
				if (nxm) {
					printf("Bus timeout reading SR from 026");
				}
			}
			cpu2regs(&ka11);
			init.value = 0 ;
			putchar('\n');
			printstate(&ka11);
     		condstep(&ka11);
		}

		leds = ka11.state;
		nxm = !cpu_dato(0760102, leds);
		if (nxm) {
			printf("Bus timeout at DR = %06o. HALT.\n", 0760102);
			runmode.value = false;
		}


#if 0
		if (runmode.value) {
			// simulate a fetch
			nxm = !cpu_dati(pc, &opcode);
			if (nxm) {
				printf("Bus timeout at PC = %06o. HALT.\n", pc);
				runmode.value = false;
			}
			pc = (pc + 2) % 0100; // loop around
			// set LEDS
			nxm = !cpu_dato(dr, pc & 0xf);
			if (nxm) {
				printf("Bus timeout at DR = %06o. HALT.\n", dr);
				runmode.value = false;
			}
		}
#endif

	}
}

// process DATI/DATO access to one of my "active" registers
// !! called asynchronuously by PRU, with SSYN asserted and blocking UNIBUS.
// The time between PRU event and program flow into this callback
// is determined by ARM Linux context switch
//
// UNIBUS DATO cycles let dati_flipflops "flicker" outside of this proc:
//      do not read back dati_flipflops.
void cpu_c::on_after_register_access(unibusdevice_register_t *device_reg,
		uint8_t unibus_control) {
	// nothing todo
//	UNUSED(device_reg);
//	UNUSED(unibus_control);
	
	
	if (unibus_control == UNIBUS_CONTROL_DATO) // bus write
		set_register_dati_value(device_reg, device_reg->active_dato_flipflops, __func__);
		
	switch (device_reg->index) {


		case 0:
			if (unibus_control == UNIBUS_CONTROL_DATO) { // bus write
				// signal data has been written to bus
				cpu2regs(&ka11);
				r7.value = reg_R7->active_dato_flipflops;
				printf("R7=%o.",r7.value);
				regs2cpu(&ka11);
			}
			
			if (unibus_control == UNIBUS_CONTROL_DATI) { // bus read
				// signal data has been read from bus
				cpu2regs(&ka11);
				printf("%o=R7,",r7.value);
				
				set_register_dati_value(reg_R7, r7.value, __func__);
				regs2cpu(&ka11);
			}
		break;

		default:
		break;
	}
	
	
}


bool cpu_c::on_param_changed(parameter_c *param) {
	UNUSED(param) ;
	return true ;
}

void cpu_c::on_power_changed(void) {
	printf("cpu_c::on_power_changed()");
	if (power_down) { // power-on defaults
		printf("cpu_c::on_power_changed()");
	}
}

// UNIBUS INIT: clear all registers
void cpu_c::on_init_changed(void) {
	// write all registers to "reset-values"
		printf("cpu_c::on_init()");
	if (init_asserted) {
		reset_unibus_registers();
		INFO("cpu_c::on_init()");
		printf("cpu_c::on_init()");
	}
}

