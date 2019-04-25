CPU20 additions
D. RIchards, 25 April 2019

Some additional features added to aid use of the cpu20 device
These features allow execution and debugging of code loaded in the demo application.

* Condition code bits N,Z,V,C decoded in register display
* Register read/write as device parameters
* Execution start address parameter
* execution run control parameter
* CPU init stimulus
* CPU single step stimulus
* CPU breakpoint address
* CPU reset vector override
* CPU emulation speed

Sample hello world application load example:

tm		# test memory
sz		# size memory
m		# allocate memory
i		# report memory
		# load linker format program
ll /root/10.02_devices/3_test/slu/hello2.lst 
q		# quit from memory test
td		# test devices
m i		# ?
sd cpu20	# select cpu device
p spc 2000	# set starting address
p i 1		# initialise cpu
p r 1		# run cpu (at starting address)
