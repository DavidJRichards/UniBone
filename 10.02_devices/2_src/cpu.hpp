/* cpu.hpp: PDP-11/05 CPU

 Copyright (c) 2018, Angelo Papenhoff, Joerg Hoppe
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


23-nov-2018  JH      created
 */
#ifndef _CPU_HPP_
#define _CPU_HPP_

using namespace std;

#include "utils.hpp"
#include "unibusdevice.hpp"
extern "C" {
#include "cpu20/11.h"
#include "cpu20/ka11.h"
}

class cpu_c: public unibusdevice_c {
private:

	unibusdevice_register_t *reg_R7;
	//unibusdevice_register_t *switch_reg;
	//unibusdevice_register_t *display_reg;
	void regs2cpu(KA11 *cpu);
	void cpu2regs(KA11 *cpu);
	

public:

	cpu_c();
	~cpu_c() ;

	parameter_bool_c runmode = parameter_bool_c(this, "run", "r",/*readonly*/
	false, "1 = CPU running, 0 = halt");
	parameter_bool_c init = parameter_bool_c(this, "init", "i",/*readonly*/
	false, "1 = CPU initalizing");
	parameter_bool_c step = parameter_bool_c(this, "step", "s",/*readonly*/
	false, "1 = CPU single step");
	
	parameter_unsigned_c del = parameter_unsigned_c(this, "CPU step delay", "del", /*readonly*/	false, "", "%o", "CPU step delay", 32, 8);
	parameter_bool_c bvec = parameter_bool_c(this, "bvec", "s",/*readonly*/ false, "1 = boot using vector 024");
	parameter_unsigned_c spc = parameter_unsigned_c(this, "starting addr", "spc", /*readonly*/	false, "", "%o", "Internal state", 32, 8);	
	parameter_unsigned_c brk = parameter_unsigned_c(this, "breakpoint addr", "brk", /*readonly*/	false, "", "%o", "Internal state", 32, 8);
	
	parameter_unsigned_c r0 = parameter_unsigned_c(this, "CPU Register R0", "r0", /*readonly*/	false, "", "%o", "Internal state", 32, 8);
	parameter_unsigned_c r1 = parameter_unsigned_c(this, "CPU Register R1", "r1", /*readonly*/	false, "", "%o", "Internal state", 32, 8);
	parameter_unsigned_c r2 = parameter_unsigned_c(this, "CPU Register R2", "r2", /*readonly*/	false, "", "%o", "Internal state", 32, 8);
	parameter_unsigned_c r3 = parameter_unsigned_c(this, "CPU Register R3", "r3", /*readonly*/	false, "", "%o", "Internal state", 32, 8);
	parameter_unsigned_c r4 = parameter_unsigned_c(this, "CPU Register R4", "r4", /*readonly*/	false, "", "%o", "Internal state", 32, 8);
	parameter_unsigned_c r5 = parameter_unsigned_c(this, "CPU Register R5", "r5", /*readonly*/	false, "", "%o", "Internal state", 32, 8);
	parameter_unsigned_c r6 = parameter_unsigned_c(this, "CPU Register R6/SP", "r6", /*readonly*/	false, "", "%o", "Internal state", 32, 8);
	parameter_unsigned_c r7 = parameter_unsigned_c(this, "CPU Register R7/PC", "r7", /*readonly*/	false, "", "%o", "Internal state", 32, 8);
	parameter_unsigned_c r10 = parameter_unsigned_c(this, "CPU Register R010/SR", "r10", /*readonly*/	false, "", "%o", "Internal state", 32, 8);
	parameter_unsigned_c r11 = parameter_unsigned_c(this, "CPU Register R011/DR", "r11", /*readonly*/	false, "", "%o", "Internal state", 32, 8);
	parameter_unsigned_c r12 = parameter_unsigned_c(this, "CPU Register R012/TV", "r12", /*readonly*/	false, "", "%o", "Internal state", 32, 8);


	struct Bus bus ; // UNIBU Sinterface of CPU
	struct KA11 ka11 ; // Angelos CPU state


	// background worker function
	void worker(void) override;

	// called by unibusadapter on emulated register access
	void on_after_register_access(unibusdevice_register_t *device_reg, uint8_t unibus_control)
			override;

	bool on_param_changed(parameter_c *param) override;  // must implement
	void on_power_changed(void) override;
	void on_init_changed(void) override;
};

#endif
