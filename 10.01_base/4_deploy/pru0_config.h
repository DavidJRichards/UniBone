/*** Following code generated by "/home/joerg/retrocmp/dec/UniBone/10.01_base/2_src/shared/update_pru_config.sh 0 pru0_array.c /home/joerg/retrocmp/dec/UniBone/10.01_base/4_deploy/pru0_config /home/joerg/retrocmp/dec/UniBone/10.01_base/4_deploy/pru0.map" ***/

#ifndef _PRU0_CONFIG_H_
#define _PRU0_CONFIG_H_

#include <stdint.h>

#ifndef _PRU0_CONFIG_C_
// extern const uint32_t pru0_image_0[] ;
extern uint32_t pru0_image_0[] ;
#endif

unsigned pru0_sizeof_code(void) ;

// code entry point "_c_int00_noinit_noargs" from linker map file:
#define PRU0_ENTRY_ADDR	0x00000000

// Mailbox page & offset in PRU internal shared 12 KB RAM
// Accessible by both PRUs, must be located in shared RAM
// offset 0 == addr 0x10000 in linker cmd files for PRU0 AND PRU1 projects.
// For use with prussdrv_map_prumem()
#ifndef PRU_MAILBOX_RAM_ID
  #define PRU_MAILBOX_RAM_ID	PRUSS0_SHARED_DATARAM
  #define PRU_MAILBOX_RAM_OFFSET	0
#endif

// Device register page & offset in PRU0 8KB RAM mapped into PRU1 space
// offset 0 == addr 0x2000 in linker cmd files for PRU1 projects.
// For use with prussdrv_map_prumem()
#ifndef PRU_DEVICEREGISTER_RAM_ID
  #define PRU_DEVICEREGISTER_RAM_ID	PRUSS0_PRU0_DATARAM
  #define PRU_DEVICEREGISTER_RAM_OFFSET	0
#endif

#endif