Unibone SLU and LTC device
D.Richards, 25 April 2019

Simple demo of serial device driver for unibus with serial in/out to second uart of Beaglebone.

Modified files:
C:\GitHub\UniBone\10.03_app_demo\2_src\makefile
C:\GitHub\UniBone\10.03_app_demo\2_src\menu_devices.cpp

New files:
C:\GitHub\UniBone\10.02_devices\2_src\DL11W.cpp
C:\GitHub\UniBone\10.02_devices\2_src\DL11W.hpp
C:\GitHub\UniBone\10.02_devices\2_src\rs232.cpp
C:\GitHub\UniBone\10.02_devices\2_src\rs232.hpp

Configuration:
Serial settings are set in file DL11W.cpp
default device is Unibone UART2 Beaglebone /dev/ttyS2
default setting is 9600 8,N,1,0

Unibus settings are set in file DL11W.hpp
SLU base address 0777550
LTC base address 0777544

Operation:
The Linux shell need to be disabled on the serial port used for the SLU.
Disable UART2 /dev/ttyS2 with this command "systemctl mask getty@ttyS2.service"

The SLU and LTC devices have been added to the Unibone demo driver.
The SLU device is initialised when the td command is issued.
At this time a message is sent to the derial port to show it has been activated.
"Comport opened" is sent to the UART

To use the device from the demo console it needs to be selected, this is done with the command "sd SLU"
the registers can be examined and deposited e.g.

>>>e 777550
EXAM 777550 -> 000000
>>>e 777552
EXAM 777552 -> 000000
>>>e 777554
EXAM 777554 -> 000200
>>>e 777556
EXAM 777556 -> 000000
>>>d 777556 66			'6' appears on the terminal
DEPOSIT 777556 <- 000066

Press key '1' in terminal session
>>>e 777550
EXAM 777550 -> 000200		Character is available
>>>e 777552
EXAM 777552 -> 000061		'1'
>>>e 777550
EXAM 777550 -> 000000
