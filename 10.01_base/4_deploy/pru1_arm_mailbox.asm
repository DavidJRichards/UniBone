;******************************************************************************
;* PRU C/C++ Codegen                                              Unix v2.3.1 *
;* Date/Time created: Sun Mar 31 20:55:29 2019                                *
;******************************************************************************
	.compiler_opts --abi=eabi --endian=little --hll_source=on --object_format=elf --silicon_version=3 --symdebug:dwarf --symdebug:dwarf_version=3 

$C$DW$CU	.dwtag  DW_TAG_compile_unit
	.dwattr $C$DW$CU, DW_AT_name("pru1_arm_mailbox.c")
	.dwattr $C$DW$CU, DW_AT_producer("TI PRU C/C++ Codegen Unix v2.3.1 Copyright (c) 2012-2017 Texas Instruments Incorporated")
	.dwattr $C$DW$CU, DW_AT_TI_version(0x01)
	.dwattr $C$DW$CU, DW_AT_comp_dir("/home/joerg/retrocmp/dec/UniBone/10.01_base/2_src/pru1")
	.global	||mailbox||
||mailbox||:	.usect	".mailbox_arm_sec",1060,1
$C$DW$1	.dwtag  DW_TAG_variable
	.dwattr $C$DW$1, DW_AT_name("mailbox")
	.dwattr $C$DW$1, DW_AT_TI_symbol_name("mailbox")
	.dwattr $C$DW$1, DW_AT_location[DW_OP_addr ||mailbox||]
	.dwattr $C$DW$1, DW_AT_type(*$C$DW$T$47)
	.dwattr $C$DW$1, DW_AT_external
	.dwattr $C$DW$1, DW_AT_decl_file("pru1_arm_mailbox.c")
	.dwattr $C$DW$1, DW_AT_decl_line(0x25)
	.dwattr $C$DW$1, DW_AT_decl_column(0x18)

;	/home/joerg/retrocmp/dec/UniBone/91_3rd_party/pru-c-compile/ti-cgt-pru_2.3.1//bin/optpru --gen_opt_info=2 /tmp/TI1iUvMTKLB /tmp/TI1iUx89pCn --opt_info_filename=/home/joerg/retrocmp/dec/UniBone/10.01_base/4_deploy/pru1_arm_mailbox.nfo 
;	/home/joerg/retrocmp/dec/UniBone/91_3rd_party/pru-c-compile/ti-cgt-pru_2.3.1//bin/acpiapru -@/tmp/TI1iUn9E65z 

;******************************************************************************
;* TYPE INFORMATION                                                           *
;******************************************************************************

$C$DW$T$19	.dwtag  DW_TAG_structure_type
	.dwattr $C$DW$T$19, DW_AT_byte_size(0x40000)
$C$DW$2	.dwtag  DW_TAG_member
	.dwattr $C$DW$2, DW_AT_type(*$C$DW$T$39)
	.dwattr $C$DW$2, DW_AT_name("$P$T0")
	.dwattr $C$DW$2, DW_AT_TI_symbol_name("$P$T0")
	.dwattr $C$DW$2, DW_AT_data_member_location[DW_OP_plus_uconst 0x0]
	.dwattr $C$DW$2, DW_AT_accessibility(DW_ACCESS_public)
	.dwattr $C$DW$2, DW_AT_decl_file("/home/joerg/retrocmp/dec/UniBone/10.01_base/2_src/shared/unibus.h")
	.dwattr $C$DW$2, DW_AT_decl_line(0x34)
	.dwattr $C$DW$2, DW_AT_decl_column(0x02)

	.dwattr $C$DW$T$19, DW_AT_decl_file("/home/joerg/retrocmp/dec/UniBone/10.01_base/2_src/shared/unibus.h")
	.dwattr $C$DW$T$19, DW_AT_decl_line(0x33)
	.dwattr $C$DW$T$19, DW_AT_decl_column(0x10)
	.dwendtag $C$DW$T$19

$C$DW$T$20	.dwtag  DW_TAG_typedef
	.dwattr $C$DW$T$20, DW_AT_name("unibus_memory_t")
	.dwattr $C$DW$T$20, DW_AT_type(*$C$DW$T$19)
	.dwattr $C$DW$T$20, DW_AT_language(DW_LANG_C)
	.dwattr $C$DW$T$20, DW_AT_decl_file("/home/joerg/retrocmp/dec/UniBone/10.01_base/2_src/shared/unibus.h")
	.dwattr $C$DW$T$20, DW_AT_decl_line(0x38)
	.dwattr $C$DW$T$20, DW_AT_decl_column(0x03)


$C$DW$T$21	.dwtag  DW_TAG_structure_type
	.dwattr $C$DW$T$21, DW_AT_byte_size(0x40000)
$C$DW$3	.dwtag  DW_TAG_member
	.dwattr $C$DW$3, DW_AT_type(*$C$DW$T$20)
	.dwattr $C$DW$3, DW_AT_name("memory")
	.dwattr $C$DW$3, DW_AT_TI_symbol_name("memory")
	.dwattr $C$DW$3, DW_AT_data_member_location[DW_OP_plus_uconst 0x0]
	.dwattr $C$DW$3, DW_AT_accessibility(DW_ACCESS_public)
	.dwattr $C$DW$3, DW_AT_decl_file("/home/joerg/retrocmp/dec/UniBone/10.01_base/2_src/shared/ddrmem.h")
	.dwattr $C$DW$3, DW_AT_decl_line(0x17)
	.dwattr $C$DW$3, DW_AT_decl_column(0x12)

	.dwattr $C$DW$T$21, DW_AT_decl_file("/home/joerg/retrocmp/dec/UniBone/10.01_base/2_src/shared/ddrmem.h")
	.dwattr $C$DW$T$21, DW_AT_decl_line(0x14)
	.dwattr $C$DW$T$21, DW_AT_decl_column(0x10)
	.dwendtag $C$DW$T$21

$C$DW$T$32	.dwtag  DW_TAG_typedef
	.dwattr $C$DW$T$32, DW_AT_name("ddrmem_t")
	.dwattr $C$DW$T$32, DW_AT_type(*$C$DW$T$21)
	.dwattr $C$DW$T$32, DW_AT_language(DW_LANG_C)
	.dwattr $C$DW$T$32, DW_AT_decl_file("/home/joerg/retrocmp/dec/UniBone/10.01_base/2_src/shared/ddrmem.h")
	.dwattr $C$DW$T$32, DW_AT_decl_line(0x18)
	.dwattr $C$DW$T$32, DW_AT_decl_column(0x03)

$C$DW$T$33	.dwtag  DW_TAG_volatile_type
	.dwattr $C$DW$T$33, DW_AT_type(*$C$DW$T$32)

$C$DW$T$34	.dwtag  DW_TAG_pointer_type
	.dwattr $C$DW$T$34, DW_AT_type(*$C$DW$T$33)
	.dwattr $C$DW$T$34, DW_AT_address_class(0x20)


$C$DW$T$25	.dwtag  DW_TAG_structure_type
	.dwattr $C$DW$T$25, DW_AT_byte_size(0x0c)
$C$DW$4	.dwtag  DW_TAG_member
	.dwattr $C$DW$4, DW_AT_type(*$C$DW$T$22)
	.dwattr $C$DW$4, DW_AT_name("eventmask")
	.dwattr $C$DW$4, DW_AT_TI_symbol_name("eventmask")
	.dwattr $C$DW$4, DW_AT_data_member_location[DW_OP_plus_uconst 0x0]
	.dwattr $C$DW$4, DW_AT_accessibility(DW_ACCESS_public)
	.dwattr $C$DW$4, DW_AT_decl_file("/home/joerg/retrocmp/dec/UniBone/10.01_base/2_src/shared/mailbox.h")
	.dwattr $C$DW$4, DW_AT_decl_line(0x7a)
	.dwattr $C$DW$4, DW_AT_decl_column(0x0a)

$C$DW$5	.dwtag  DW_TAG_member
	.dwattr $C$DW$5, DW_AT_type(*$C$DW$T$22)
	.dwattr $C$DW$5, DW_AT_name("unibus_control")
	.dwattr $C$DW$5, DW_AT_TI_symbol_name("unibus_control")
	.dwattr $C$DW$5, DW_AT_data_member_location[DW_OP_plus_uconst 0x1]
	.dwattr $C$DW$5, DW_AT_accessibility(DW_ACCESS_public)
	.dwattr $C$DW$5, DW_AT_decl_file("/home/joerg/retrocmp/dec/UniBone/10.01_base/2_src/shared/mailbox.h")
	.dwattr $C$DW$5, DW_AT_decl_line(0x7d)
	.dwattr $C$DW$5, DW_AT_decl_column(0x0a)

$C$DW$6	.dwtag  DW_TAG_member
	.dwattr $C$DW$6, DW_AT_type(*$C$DW$T$22)
	.dwattr $C$DW$6, DW_AT_name("device_handle")
	.dwattr $C$DW$6, DW_AT_TI_symbol_name("device_handle")
	.dwattr $C$DW$6, DW_AT_data_member_location[DW_OP_plus_uconst 0x2]
	.dwattr $C$DW$6, DW_AT_accessibility(DW_ACCESS_public)
	.dwattr $C$DW$6, DW_AT_decl_file("/home/joerg/retrocmp/dec/UniBone/10.01_base/2_src/shared/mailbox.h")
	.dwattr $C$DW$6, DW_AT_decl_line(0x7f)
	.dwattr $C$DW$6, DW_AT_decl_column(0x0a)

$C$DW$7	.dwtag  DW_TAG_member
	.dwattr $C$DW$7, DW_AT_type(*$C$DW$T$22)
	.dwattr $C$DW$7, DW_AT_name("device_register_idx")
	.dwattr $C$DW$7, DW_AT_TI_symbol_name("device_register_idx")
	.dwattr $C$DW$7, DW_AT_data_member_location[DW_OP_plus_uconst 0x3]
	.dwattr $C$DW$7, DW_AT_accessibility(DW_ACCESS_public)
	.dwattr $C$DW$7, DW_AT_decl_file("/home/joerg/retrocmp/dec/UniBone/10.01_base/2_src/shared/mailbox.h")
	.dwattr $C$DW$7, DW_AT_decl_line(0x81)
	.dwattr $C$DW$7, DW_AT_decl_column(0x0a)

$C$DW$8	.dwtag  DW_TAG_member
	.dwattr $C$DW$8, DW_AT_type(*$C$DW$T$23)
	.dwattr $C$DW$8, DW_AT_name("addr")
	.dwattr $C$DW$8, DW_AT_TI_symbol_name("addr")
	.dwattr $C$DW$8, DW_AT_data_member_location[DW_OP_plus_uconst 0x4]
	.dwattr $C$DW$8, DW_AT_accessibility(DW_ACCESS_public)
	.dwattr $C$DW$8, DW_AT_decl_file("/home/joerg/retrocmp/dec/UniBone/10.01_base/2_src/shared/mailbox.h")
	.dwattr $C$DW$8, DW_AT_decl_line(0x83)
	.dwattr $C$DW$8, DW_AT_decl_column(0x0b)

$C$DW$9	.dwtag  DW_TAG_member
	.dwattr $C$DW$9, DW_AT_type(*$C$DW$T$24)
	.dwattr $C$DW$9, DW_AT_name("data")
	.dwattr $C$DW$9, DW_AT_TI_symbol_name("data")
	.dwattr $C$DW$9, DW_AT_data_member_location[DW_OP_plus_uconst 0x8]
	.dwattr $C$DW$9, DW_AT_accessibility(DW_ACCESS_public)
	.dwattr $C$DW$9, DW_AT_decl_file("/home/joerg/retrocmp/dec/UniBone/10.01_base/2_src/shared/mailbox.h")
	.dwattr $C$DW$9, DW_AT_decl_line(0x84)
	.dwattr $C$DW$9, DW_AT_decl_column(0x0b)

$C$DW$10	.dwtag  DW_TAG_member
	.dwattr $C$DW$10, DW_AT_type(*$C$DW$T$22)
	.dwattr $C$DW$10, DW_AT_name("initialization_signals_prev")
	.dwattr $C$DW$10, DW_AT_TI_symbol_name("initialization_signals_prev")
	.dwattr $C$DW$10, DW_AT_data_member_location[DW_OP_plus_uconst 0xa]
	.dwattr $C$DW$10, DW_AT_accessibility(DW_ACCESS_public)
	.dwattr $C$DW$10, DW_AT_decl_file("/home/joerg/retrocmp/dec/UniBone/10.01_base/2_src/shared/mailbox.h")
	.dwattr $C$DW$10, DW_AT_decl_line(0x87)
	.dwattr $C$DW$10, DW_AT_decl_column(0x0a)

$C$DW$11	.dwtag  DW_TAG_member
	.dwattr $C$DW$11, DW_AT_type(*$C$DW$T$22)
	.dwattr $C$DW$11, DW_AT_name("initialization_signals_cur")
	.dwattr $C$DW$11, DW_AT_TI_symbol_name("initialization_signals_cur")
	.dwattr $C$DW$11, DW_AT_data_member_location[DW_OP_plus_uconst 0xb]
	.dwattr $C$DW$11, DW_AT_accessibility(DW_ACCESS_public)
	.dwattr $C$DW$11, DW_AT_decl_file("/home/joerg/retrocmp/dec/UniBone/10.01_base/2_src/shared/mailbox.h")
	.dwattr $C$DW$11, DW_AT_decl_line(0x88)
	.dwattr $C$DW$11, DW_AT_decl_column(0x0a)

	.dwattr $C$DW$T$25, DW_AT_decl_file("/home/joerg/retrocmp/dec/UniBone/10.01_base/2_src/shared/mailbox.h")
	.dwattr $C$DW$T$25, DW_AT_decl_line(0x79)
	.dwattr $C$DW$T$25, DW_AT_decl_column(0x10)
	.dwendtag $C$DW$T$25

$C$DW$T$35	.dwtag  DW_TAG_typedef
	.dwattr $C$DW$T$35, DW_AT_name("mailbox_events_t")
	.dwattr $C$DW$T$35, DW_AT_type(*$C$DW$T$25)
	.dwattr $C$DW$T$35, DW_AT_language(DW_LANG_C)
	.dwattr $C$DW$T$35, DW_AT_decl_file("/home/joerg/retrocmp/dec/UniBone/10.01_base/2_src/shared/mailbox.h")
	.dwattr $C$DW$T$35, DW_AT_decl_line(0x8b)
	.dwattr $C$DW$T$35, DW_AT_decl_column(0x03)


$C$DW$T$26	.dwtag  DW_TAG_structure_type
	.dwattr $C$DW$T$26, DW_AT_byte_size(0x08)
$C$DW$12	.dwtag  DW_TAG_member
	.dwattr $C$DW$12, DW_AT_type(*$C$DW$T$23)
	.dwattr $C$DW$12, DW_AT_name("addr")
	.dwattr $C$DW$12, DW_AT_TI_symbol_name("addr")
	.dwattr $C$DW$12, DW_AT_data_member_location[DW_OP_plus_uconst 0x0]
	.dwattr $C$DW$12, DW_AT_accessibility(DW_ACCESS_public)
	.dwattr $C$DW$12, DW_AT_decl_file("/home/joerg/retrocmp/dec/UniBone/10.01_base/2_src/shared/mailbox.h")
	.dwattr $C$DW$12, DW_AT_decl_line(0x4c)
	.dwattr $C$DW$12, DW_AT_decl_column(0x0b)

$C$DW$13	.dwtag  DW_TAG_member
	.dwattr $C$DW$13, DW_AT_type(*$C$DW$T$23)
	.dwattr $C$DW$13, DW_AT_name("val")
	.dwattr $C$DW$13, DW_AT_TI_symbol_name("val")
	.dwattr $C$DW$13, DW_AT_data_member_location[DW_OP_plus_uconst 0x4]
	.dwattr $C$DW$13, DW_AT_accessibility(DW_ACCESS_public)
	.dwattr $C$DW$13, DW_AT_decl_file("/home/joerg/retrocmp/dec/UniBone/10.01_base/2_src/shared/mailbox.h")
	.dwattr $C$DW$13, DW_AT_decl_line(0x4d)
	.dwattr $C$DW$13, DW_AT_decl_column(0x0b)

	.dwattr $C$DW$T$26, DW_AT_decl_file("/home/joerg/retrocmp/dec/UniBone/10.01_base/2_src/shared/mailbox.h")
	.dwattr $C$DW$T$26, DW_AT_decl_line(0x4b)
	.dwattr $C$DW$T$26, DW_AT_decl_column(0x10)
	.dwendtag $C$DW$T$26

$C$DW$T$40	.dwtag  DW_TAG_typedef
	.dwattr $C$DW$T$40, DW_AT_name("mailbox_test_t")
	.dwattr $C$DW$T$40, DW_AT_type(*$C$DW$T$26)
	.dwattr $C$DW$T$40, DW_AT_language(DW_LANG_C)
	.dwattr $C$DW$T$40, DW_AT_decl_file("/home/joerg/retrocmp/dec/UniBone/10.01_base/2_src/shared/mailbox.h")
	.dwattr $C$DW$T$40, DW_AT_decl_line(0x4e)
	.dwattr $C$DW$T$40, DW_AT_decl_column(0x03)


$C$DW$T$27	.dwtag  DW_TAG_structure_type
	.dwattr $C$DW$T$27, DW_AT_byte_size(0x0c)
$C$DW$14	.dwtag  DW_TAG_member
	.dwattr $C$DW$14, DW_AT_type(*$C$DW$T$23)
	.dwattr $C$DW$14, DW_AT_name("addr")
	.dwattr $C$DW$14, DW_AT_TI_symbol_name("addr")
	.dwattr $C$DW$14, DW_AT_data_member_location[DW_OP_plus_uconst 0x0]
	.dwattr $C$DW$14, DW_AT_accessibility(DW_ACCESS_public)
	.dwattr $C$DW$14, DW_AT_decl_file("/home/joerg/retrocmp/dec/UniBone/10.01_base/2_src/shared/mailbox.h")
	.dwattr $C$DW$14, DW_AT_decl_line(0x51)
	.dwattr $C$DW$14, DW_AT_decl_column(0x0b)

$C$DW$15	.dwtag  DW_TAG_member
	.dwattr $C$DW$15, DW_AT_type(*$C$DW$T$23)
	.dwattr $C$DW$15, DW_AT_name("bitmask")
	.dwattr $C$DW$15, DW_AT_TI_symbol_name("bitmask")
	.dwattr $C$DW$15, DW_AT_data_member_location[DW_OP_plus_uconst 0x4]
	.dwattr $C$DW$15, DW_AT_accessibility(DW_ACCESS_public)
	.dwattr $C$DW$15, DW_AT_decl_file("/home/joerg/retrocmp/dec/UniBone/10.01_base/2_src/shared/mailbox.h")
	.dwattr $C$DW$15, DW_AT_decl_line(0x52)
	.dwattr $C$DW$15, DW_AT_decl_column(0x0b)

$C$DW$16	.dwtag  DW_TAG_member
	.dwattr $C$DW$16, DW_AT_type(*$C$DW$T$23)
	.dwattr $C$DW$16, DW_AT_name("val")
	.dwattr $C$DW$16, DW_AT_TI_symbol_name("val")
	.dwattr $C$DW$16, DW_AT_data_member_location[DW_OP_plus_uconst 0x8]
	.dwattr $C$DW$16, DW_AT_accessibility(DW_ACCESS_public)
	.dwattr $C$DW$16, DW_AT_decl_file("/home/joerg/retrocmp/dec/UniBone/10.01_base/2_src/shared/mailbox.h")
	.dwattr $C$DW$16, DW_AT_decl_line(0x53)
	.dwattr $C$DW$16, DW_AT_decl_column(0x0b)

	.dwattr $C$DW$T$27, DW_AT_decl_file("/home/joerg/retrocmp/dec/UniBone/10.01_base/2_src/shared/mailbox.h")
	.dwattr $C$DW$T$27, DW_AT_decl_line(0x50)
	.dwattr $C$DW$T$27, DW_AT_decl_column(0x10)
	.dwendtag $C$DW$T$27

$C$DW$T$41	.dwtag  DW_TAG_typedef
	.dwattr $C$DW$T$41, DW_AT_name("mailbox_buslatch_t")
	.dwattr $C$DW$T$41, DW_AT_type(*$C$DW$T$27)
	.dwattr $C$DW$T$41, DW_AT_language(DW_LANG_C)
	.dwattr $C$DW$T$41, DW_AT_decl_file("/home/joerg/retrocmp/dec/UniBone/10.01_base/2_src/shared/mailbox.h")
	.dwattr $C$DW$T$41, DW_AT_decl_line(0x54)
	.dwattr $C$DW$T$41, DW_AT_decl_column(0x03)


$C$DW$T$28	.dwtag  DW_TAG_structure_type
	.dwattr $C$DW$T$28, DW_AT_byte_size(0x04)
$C$DW$17	.dwtag  DW_TAG_member
	.dwattr $C$DW$17, DW_AT_type(*$C$DW$T$22)
	.dwattr $C$DW$17, DW_AT_name("addr_0_7")
	.dwattr $C$DW$17, DW_AT_TI_symbol_name("addr_0_7")
	.dwattr $C$DW$17, DW_AT_data_member_location[DW_OP_plus_uconst 0x0]
	.dwattr $C$DW$17, DW_AT_accessibility(DW_ACCESS_public)
	.dwattr $C$DW$17, DW_AT_decl_file("/home/joerg/retrocmp/dec/UniBone/10.01_base/2_src/shared/mailbox.h")
	.dwattr $C$DW$17, DW_AT_decl_line(0x57)
	.dwattr $C$DW$17, DW_AT_decl_column(0x0a)

$C$DW$18	.dwtag  DW_TAG_member
	.dwattr $C$DW$18, DW_AT_type(*$C$DW$T$22)
	.dwattr $C$DW$18, DW_AT_name("addr_8_15")
	.dwattr $C$DW$18, DW_AT_TI_symbol_name("addr_8_15")
	.dwattr $C$DW$18, DW_AT_data_member_location[DW_OP_plus_uconst 0x1]
	.dwattr $C$DW$18, DW_AT_accessibility(DW_ACCESS_public)
	.dwattr $C$DW$18, DW_AT_decl_file("/home/joerg/retrocmp/dec/UniBone/10.01_base/2_src/shared/mailbox.h")
	.dwattr $C$DW$18, DW_AT_decl_line(0x58)
	.dwattr $C$DW$18, DW_AT_decl_column(0x0a)

$C$DW$19	.dwtag  DW_TAG_member
	.dwattr $C$DW$19, DW_AT_type(*$C$DW$T$22)
	.dwattr $C$DW$19, DW_AT_name("data_0_7")
	.dwattr $C$DW$19, DW_AT_TI_symbol_name("data_0_7")
	.dwattr $C$DW$19, DW_AT_data_member_location[DW_OP_plus_uconst 0x2]
	.dwattr $C$DW$19, DW_AT_accessibility(DW_ACCESS_public)
	.dwattr $C$DW$19, DW_AT_decl_file("/home/joerg/retrocmp/dec/UniBone/10.01_base/2_src/shared/mailbox.h")
	.dwattr $C$DW$19, DW_AT_decl_line(0x59)
	.dwattr $C$DW$19, DW_AT_decl_column(0x0a)

$C$DW$20	.dwtag  DW_TAG_member
	.dwattr $C$DW$20, DW_AT_type(*$C$DW$T$22)
	.dwattr $C$DW$20, DW_AT_name("data_8_15")
	.dwattr $C$DW$20, DW_AT_TI_symbol_name("data_8_15")
	.dwattr $C$DW$20, DW_AT_data_member_location[DW_OP_plus_uconst 0x3]
	.dwattr $C$DW$20, DW_AT_accessibility(DW_ACCESS_public)
	.dwattr $C$DW$20, DW_AT_decl_file("/home/joerg/retrocmp/dec/UniBone/10.01_base/2_src/shared/mailbox.h")
	.dwattr $C$DW$20, DW_AT_decl_line(0x5a)
	.dwattr $C$DW$20, DW_AT_decl_column(0x0a)

	.dwattr $C$DW$T$28, DW_AT_decl_file("/home/joerg/retrocmp/dec/UniBone/10.01_base/2_src/shared/mailbox.h")
	.dwattr $C$DW$T$28, DW_AT_decl_line(0x56)
	.dwattr $C$DW$T$28, DW_AT_decl_column(0x10)
	.dwendtag $C$DW$T$28

$C$DW$T$42	.dwtag  DW_TAG_typedef
	.dwattr $C$DW$T$42, DW_AT_name("mailbox_buslatch_test_t")
	.dwattr $C$DW$T$42, DW_AT_type(*$C$DW$T$28)
	.dwattr $C$DW$T$42, DW_AT_language(DW_LANG_C)
	.dwattr $C$DW$T$42, DW_AT_decl_file("/home/joerg/retrocmp/dec/UniBone/10.01_base/2_src/shared/mailbox.h")
	.dwattr $C$DW$T$42, DW_AT_decl_line(0x5b)
	.dwattr $C$DW$T$42, DW_AT_decl_column(0x03)


$C$DW$T$30	.dwtag  DW_TAG_structure_type
	.dwattr $C$DW$T$30, DW_AT_byte_size(0x40c)
$C$DW$21	.dwtag  DW_TAG_member
	.dwattr $C$DW$21, DW_AT_type(*$C$DW$T$22)
	.dwattr $C$DW$21, DW_AT_name("cur_status")
	.dwattr $C$DW$21, DW_AT_TI_symbol_name("cur_status")
	.dwattr $C$DW$21, DW_AT_data_member_location[DW_OP_plus_uconst 0x0]
	.dwattr $C$DW$21, DW_AT_accessibility(DW_ACCESS_public)
	.dwattr $C$DW$21, DW_AT_decl_file("/home/joerg/retrocmp/dec/UniBone/10.01_base/2_src/shared/mailbox.h")
	.dwattr $C$DW$21, DW_AT_decl_line(0x61)
	.dwattr $C$DW$21, DW_AT_decl_column(0x0a)

$C$DW$22	.dwtag  DW_TAG_member
	.dwattr $C$DW$22, DW_AT_type(*$C$DW$T$22)
	.dwattr $C$DW$22, DW_AT_name("control")
	.dwattr $C$DW$22, DW_AT_TI_symbol_name("control")
	.dwattr $C$DW$22, DW_AT_data_member_location[DW_OP_plus_uconst 0x1]
	.dwattr $C$DW$22, DW_AT_accessibility(DW_ACCESS_public)
	.dwattr $C$DW$22, DW_AT_decl_file("/home/joerg/retrocmp/dec/UniBone/10.01_base/2_src/shared/mailbox.h")
	.dwattr $C$DW$22, DW_AT_decl_line(0x62)
	.dwattr $C$DW$22, DW_AT_decl_column(0x0a)

$C$DW$23	.dwtag  DW_TAG_member
	.dwattr $C$DW$23, DW_AT_type(*$C$DW$T$24)
	.dwattr $C$DW$23, DW_AT_name("wordcount")
	.dwattr $C$DW$23, DW_AT_TI_symbol_name("wordcount")
	.dwattr $C$DW$23, DW_AT_data_member_location[DW_OP_plus_uconst 0x2]
	.dwattr $C$DW$23, DW_AT_accessibility(DW_ACCESS_public)
	.dwattr $C$DW$23, DW_AT_decl_file("/home/joerg/retrocmp/dec/UniBone/10.01_base/2_src/shared/mailbox.h")
	.dwattr $C$DW$23, DW_AT_decl_line(0x63)
	.dwattr $C$DW$23, DW_AT_decl_column(0x0b)

$C$DW$24	.dwtag  DW_TAG_member
	.dwattr $C$DW$24, DW_AT_type(*$C$DW$T$23)
	.dwattr $C$DW$24, DW_AT_name("cur_addr")
	.dwattr $C$DW$24, DW_AT_TI_symbol_name("cur_addr")
	.dwattr $C$DW$24, DW_AT_data_member_location[DW_OP_plus_uconst 0x4]
	.dwattr $C$DW$24, DW_AT_accessibility(DW_ACCESS_public)
	.dwattr $C$DW$24, DW_AT_decl_file("/home/joerg/retrocmp/dec/UniBone/10.01_base/2_src/shared/mailbox.h")
	.dwattr $C$DW$24, DW_AT_decl_line(0x64)
	.dwattr $C$DW$24, DW_AT_decl_column(0x0b)

$C$DW$25	.dwtag  DW_TAG_member
	.dwattr $C$DW$25, DW_AT_type(*$C$DW$T$23)
	.dwattr $C$DW$25, DW_AT_name("startaddr")
	.dwattr $C$DW$25, DW_AT_TI_symbol_name("startaddr")
	.dwattr $C$DW$25, DW_AT_data_member_location[DW_OP_plus_uconst 0x8]
	.dwattr $C$DW$25, DW_AT_accessibility(DW_ACCESS_public)
	.dwattr $C$DW$25, DW_AT_decl_file("/home/joerg/retrocmp/dec/UniBone/10.01_base/2_src/shared/mailbox.h")
	.dwattr $C$DW$25, DW_AT_decl_line(0x65)
	.dwattr $C$DW$25, DW_AT_decl_column(0x0b)

$C$DW$26	.dwtag  DW_TAG_member
	.dwattr $C$DW$26, DW_AT_type(*$C$DW$T$29)
	.dwattr $C$DW$26, DW_AT_name("words")
	.dwattr $C$DW$26, DW_AT_TI_symbol_name("words")
	.dwattr $C$DW$26, DW_AT_data_member_location[DW_OP_plus_uconst 0xc]
	.dwattr $C$DW$26, DW_AT_accessibility(DW_ACCESS_public)
	.dwattr $C$DW$26, DW_AT_decl_file("/home/joerg/retrocmp/dec/UniBone/10.01_base/2_src/shared/mailbox.h")
	.dwattr $C$DW$26, DW_AT_decl_line(0x66)
	.dwattr $C$DW$26, DW_AT_decl_column(0x0b)

	.dwattr $C$DW$T$30, DW_AT_decl_file("/home/joerg/retrocmp/dec/UniBone/10.01_base/2_src/shared/mailbox.h")
	.dwattr $C$DW$T$30, DW_AT_decl_line(0x5f)
	.dwattr $C$DW$T$30, DW_AT_decl_column(0x10)
	.dwendtag $C$DW$T$30

$C$DW$T$43	.dwtag  DW_TAG_typedef
	.dwattr $C$DW$T$43, DW_AT_name("mailbox_dma_t")
	.dwattr $C$DW$T$43, DW_AT_type(*$C$DW$T$30)
	.dwattr $C$DW$T$43, DW_AT_language(DW_LANG_C)
	.dwattr $C$DW$T$43, DW_AT_decl_file("/home/joerg/retrocmp/dec/UniBone/10.01_base/2_src/shared/mailbox.h")
	.dwattr $C$DW$T$43, DW_AT_decl_line(0x67)
	.dwattr $C$DW$T$43, DW_AT_decl_column(0x03)


$C$DW$T$31	.dwtag  DW_TAG_structure_type
	.dwattr $C$DW$T$31, DW_AT_byte_size(0x03)
$C$DW$27	.dwtag  DW_TAG_member
	.dwattr $C$DW$27, DW_AT_type(*$C$DW$T$24)
	.dwattr $C$DW$27, DW_AT_name("vector")
	.dwattr $C$DW$27, DW_AT_TI_symbol_name("vector")
	.dwattr $C$DW$27, DW_AT_data_member_location[DW_OP_plus_uconst 0x0]
	.dwattr $C$DW$27, DW_AT_accessibility(DW_ACCESS_public)
	.dwattr $C$DW$27, DW_AT_decl_file("/home/joerg/retrocmp/dec/UniBone/10.01_base/2_src/shared/mailbox.h")
	.dwattr $C$DW$27, DW_AT_decl_line(0x6b)
	.dwattr $C$DW$27, DW_AT_decl_column(0x0b)

$C$DW$28	.dwtag  DW_TAG_member
	.dwattr $C$DW$28, DW_AT_type(*$C$DW$T$22)
	.dwattr $C$DW$28, DW_AT_name("priority_bit")
	.dwattr $C$DW$28, DW_AT_TI_symbol_name("priority_bit")
	.dwattr $C$DW$28, DW_AT_data_member_location[DW_OP_plus_uconst 0x2]
	.dwattr $C$DW$28, DW_AT_accessibility(DW_ACCESS_public)
	.dwattr $C$DW$28, DW_AT_decl_file("/home/joerg/retrocmp/dec/UniBone/10.01_base/2_src/shared/mailbox.h")
	.dwattr $C$DW$28, DW_AT_decl_line(0x6c)
	.dwattr $C$DW$28, DW_AT_decl_column(0x0a)

	.dwattr $C$DW$T$31, DW_AT_decl_file("/home/joerg/retrocmp/dec/UniBone/10.01_base/2_src/shared/mailbox.h")
	.dwattr $C$DW$T$31, DW_AT_decl_line(0x6a)
	.dwattr $C$DW$T$31, DW_AT_decl_column(0x10)
	.dwendtag $C$DW$T$31

$C$DW$T$44	.dwtag  DW_TAG_typedef
	.dwattr $C$DW$T$44, DW_AT_name("mailbox_intr_t")
	.dwattr $C$DW$T$44, DW_AT_type(*$C$DW$T$31)
	.dwattr $C$DW$T$44, DW_AT_language(DW_LANG_C)
	.dwattr $C$DW$T$44, DW_AT_decl_file("/home/joerg/retrocmp/dec/UniBone/10.01_base/2_src/shared/mailbox.h")
	.dwattr $C$DW$T$44, DW_AT_decl_line(0x6d)
	.dwattr $C$DW$T$44, DW_AT_decl_column(0x03)


$C$DW$T$36	.dwtag  DW_TAG_structure_type
	.dwattr $C$DW$T$36, DW_AT_byte_size(0x424)
$C$DW$29	.dwtag  DW_TAG_member
	.dwattr $C$DW$29, DW_AT_type(*$C$DW$T$23)
	.dwattr $C$DW$29, DW_AT_name("arm2pru_req")
	.dwattr $C$DW$29, DW_AT_TI_symbol_name("arm2pru_req")
	.dwattr $C$DW$29, DW_AT_data_member_location[DW_OP_plus_uconst 0x0]
	.dwattr $C$DW$29, DW_AT_accessibility(DW_ACCESS_public)
	.dwattr $C$DW$29, DW_AT_decl_file("/home/joerg/retrocmp/dec/UniBone/10.01_base/2_src/shared/mailbox.h")
	.dwattr $C$DW$29, DW_AT_decl_line(0x90)
	.dwattr $C$DW$29, DW_AT_decl_column(0x0b)

$C$DW$30	.dwtag  DW_TAG_member
	.dwattr $C$DW$30, DW_AT_type(*$C$DW$T$23)
	.dwattr $C$DW$30, DW_AT_name("arm2pru_resp")
	.dwattr $C$DW$30, DW_AT_TI_symbol_name("arm2pru_resp")
	.dwattr $C$DW$30, DW_AT_data_member_location[DW_OP_plus_uconst 0x4]
	.dwattr $C$DW$30, DW_AT_accessibility(DW_ACCESS_public)
	.dwattr $C$DW$30, DW_AT_decl_file("/home/joerg/retrocmp/dec/UniBone/10.01_base/2_src/shared/mailbox.h")
	.dwattr $C$DW$30, DW_AT_decl_line(0x91)
	.dwattr $C$DW$30, DW_AT_decl_column(0x0b)

$C$DW$31	.dwtag  DW_TAG_member
	.dwattr $C$DW$31, DW_AT_type(*$C$DW$T$34)
	.dwattr $C$DW$31, DW_AT_name("ddrmem_base_physical")
	.dwattr $C$DW$31, DW_AT_TI_symbol_name("ddrmem_base_physical")
	.dwattr $C$DW$31, DW_AT_data_member_location[DW_OP_plus_uconst 0x8]
	.dwattr $C$DW$31, DW_AT_accessibility(DW_ACCESS_public)
	.dwattr $C$DW$31, DW_AT_decl_file("/home/joerg/retrocmp/dec/UniBone/10.01_base/2_src/shared/mailbox.h")
	.dwattr $C$DW$31, DW_AT_decl_line(0x94)
	.dwattr $C$DW$31, DW_AT_decl_column(0x15)

$C$DW$32	.dwtag  DW_TAG_member
	.dwattr $C$DW$32, DW_AT_type(*$C$DW$T$35)
	.dwattr $C$DW$32, DW_AT_name("events")
	.dwattr $C$DW$32, DW_AT_TI_symbol_name("events")
	.dwattr $C$DW$32, DW_AT_data_member_location[DW_OP_plus_uconst 0xc]
	.dwattr $C$DW$32, DW_AT_accessibility(DW_ACCESS_public)
	.dwattr $C$DW$32, DW_AT_decl_file("/home/joerg/retrocmp/dec/UniBone/10.01_base/2_src/shared/mailbox.h")
	.dwattr $C$DW$32, DW_AT_decl_line(0x97)
	.dwattr $C$DW$32, DW_AT_decl_column(0x13)

$C$DW$33	.dwtag  DW_TAG_member
	.dwattr $C$DW$33, DW_AT_type(*$C$DW$T$45)
	.dwattr $C$DW$33, DW_AT_name("$P$T1")
	.dwattr $C$DW$33, DW_AT_TI_symbol_name("$P$T1")
	.dwattr $C$DW$33, DW_AT_data_member_location[DW_OP_plus_uconst 0x18]
	.dwattr $C$DW$33, DW_AT_accessibility(DW_ACCESS_public)
	.dwattr $C$DW$33, DW_AT_decl_file("/home/joerg/retrocmp/dec/UniBone/10.01_base/2_src/shared/mailbox.h")
	.dwattr $C$DW$33, DW_AT_decl_line(0x9a)
	.dwattr $C$DW$33, DW_AT_decl_column(0x02)

	.dwattr $C$DW$T$36, DW_AT_decl_file("/home/joerg/retrocmp/dec/UniBone/10.01_base/2_src/shared/mailbox.h")
	.dwattr $C$DW$T$36, DW_AT_decl_line(0x8d)
	.dwattr $C$DW$T$36, DW_AT_decl_column(0x10)
	.dwendtag $C$DW$T$36

$C$DW$T$46	.dwtag  DW_TAG_typedef
	.dwattr $C$DW$T$46, DW_AT_name("mailbox_t")
	.dwattr $C$DW$T$46, DW_AT_type(*$C$DW$T$36)
	.dwattr $C$DW$T$46, DW_AT_language(DW_LANG_C)
	.dwattr $C$DW$T$46, DW_AT_decl_file("/home/joerg/retrocmp/dec/UniBone/10.01_base/2_src/shared/mailbox.h")
	.dwattr $C$DW$T$46, DW_AT_decl_line(0xa1)
	.dwattr $C$DW$T$46, DW_AT_decl_column(0x03)

$C$DW$T$47	.dwtag  DW_TAG_volatile_type
	.dwattr $C$DW$T$47, DW_AT_type(*$C$DW$T$46)


$C$DW$T$39	.dwtag  DW_TAG_union_type
	.dwattr $C$DW$T$39, DW_AT_byte_size(0x40000)
$C$DW$34	.dwtag  DW_TAG_member
	.dwattr $C$DW$34, DW_AT_type(*$C$DW$T$37)
	.dwattr $C$DW$34, DW_AT_name("words")
	.dwattr $C$DW$34, DW_AT_TI_symbol_name("words")
	.dwattr $C$DW$34, DW_AT_data_member_location[DW_OP_plus_uconst 0x0]
	.dwattr $C$DW$34, DW_AT_accessibility(DW_ACCESS_public)
	.dwattr $C$DW$34, DW_AT_decl_file("/home/joerg/retrocmp/dec/UniBone/10.01_base/2_src/shared/unibus.h")
	.dwattr $C$DW$34, DW_AT_decl_line(0x35)
	.dwattr $C$DW$34, DW_AT_decl_column(0x0b)

$C$DW$35	.dwtag  DW_TAG_member
	.dwattr $C$DW$35, DW_AT_type(*$C$DW$T$38)
	.dwattr $C$DW$35, DW_AT_name("bytes")
	.dwattr $C$DW$35, DW_AT_TI_symbol_name("bytes")
	.dwattr $C$DW$35, DW_AT_data_member_location[DW_OP_plus_uconst 0x0]
	.dwattr $C$DW$35, DW_AT_accessibility(DW_ACCESS_public)
	.dwattr $C$DW$35, DW_AT_decl_file("/home/joerg/retrocmp/dec/UniBone/10.01_base/2_src/shared/unibus.h")
	.dwattr $C$DW$35, DW_AT_decl_line(0x36)
	.dwattr $C$DW$35, DW_AT_decl_column(0x0b)

	.dwattr $C$DW$T$39, DW_AT_decl_file("/home/joerg/retrocmp/dec/UniBone/10.01_base/2_src/shared/unibus.h")
	.dwattr $C$DW$T$39, DW_AT_decl_line(0x34)
	.dwattr $C$DW$T$39, DW_AT_decl_column(0x08)
	.dwendtag $C$DW$T$39


$C$DW$T$45	.dwtag  DW_TAG_union_type
	.dwattr $C$DW$T$45, DW_AT_byte_size(0x40c)
$C$DW$36	.dwtag  DW_TAG_member
	.dwattr $C$DW$36, DW_AT_type(*$C$DW$T$40)
	.dwattr $C$DW$36, DW_AT_name("mailbox_test")
	.dwattr $C$DW$36, DW_AT_TI_symbol_name("mailbox_test")
	.dwattr $C$DW$36, DW_AT_data_member_location[DW_OP_plus_uconst 0x0]
	.dwattr $C$DW$36, DW_AT_accessibility(DW_ACCESS_public)
	.dwattr $C$DW$36, DW_AT_decl_file("/home/joerg/retrocmp/dec/UniBone/10.01_base/2_src/shared/mailbox.h")
	.dwattr $C$DW$36, DW_AT_decl_line(0x9b)
	.dwattr $C$DW$36, DW_AT_decl_column(0x12)

$C$DW$37	.dwtag  DW_TAG_member
	.dwattr $C$DW$37, DW_AT_type(*$C$DW$T$41)
	.dwattr $C$DW$37, DW_AT_name("buslatch")
	.dwattr $C$DW$37, DW_AT_TI_symbol_name("buslatch")
	.dwattr $C$DW$37, DW_AT_data_member_location[DW_OP_plus_uconst 0x0]
	.dwattr $C$DW$37, DW_AT_accessibility(DW_ACCESS_public)
	.dwattr $C$DW$37, DW_AT_decl_file("/home/joerg/retrocmp/dec/UniBone/10.01_base/2_src/shared/mailbox.h")
	.dwattr $C$DW$37, DW_AT_decl_line(0x9c)
	.dwattr $C$DW$37, DW_AT_decl_column(0x16)

$C$DW$38	.dwtag  DW_TAG_member
	.dwattr $C$DW$38, DW_AT_type(*$C$DW$T$42)
	.dwattr $C$DW$38, DW_AT_name("buslatch_test")
	.dwattr $C$DW$38, DW_AT_TI_symbol_name("buslatch_test")
	.dwattr $C$DW$38, DW_AT_data_member_location[DW_OP_plus_uconst 0x0]
	.dwattr $C$DW$38, DW_AT_accessibility(DW_ACCESS_public)
	.dwattr $C$DW$38, DW_AT_decl_file("/home/joerg/retrocmp/dec/UniBone/10.01_base/2_src/shared/mailbox.h")
	.dwattr $C$DW$38, DW_AT_decl_line(0x9d)
	.dwattr $C$DW$38, DW_AT_decl_column(0x1b)

$C$DW$39	.dwtag  DW_TAG_member
	.dwattr $C$DW$39, DW_AT_type(*$C$DW$T$43)
	.dwattr $C$DW$39, DW_AT_name("dma")
	.dwattr $C$DW$39, DW_AT_TI_symbol_name("dma")
	.dwattr $C$DW$39, DW_AT_data_member_location[DW_OP_plus_uconst 0x0]
	.dwattr $C$DW$39, DW_AT_accessibility(DW_ACCESS_public)
	.dwattr $C$DW$39, DW_AT_decl_file("/home/joerg/retrocmp/dec/UniBone/10.01_base/2_src/shared/mailbox.h")
	.dwattr $C$DW$39, DW_AT_decl_line(0x9e)
	.dwattr $C$DW$39, DW_AT_decl_column(0x11)

$C$DW$40	.dwtag  DW_TAG_member
	.dwattr $C$DW$40, DW_AT_type(*$C$DW$T$44)
	.dwattr $C$DW$40, DW_AT_name("intr")
	.dwattr $C$DW$40, DW_AT_TI_symbol_name("intr")
	.dwattr $C$DW$40, DW_AT_data_member_location[DW_OP_plus_uconst 0x0]
	.dwattr $C$DW$40, DW_AT_accessibility(DW_ACCESS_public)
	.dwattr $C$DW$40, DW_AT_decl_file("/home/joerg/retrocmp/dec/UniBone/10.01_base/2_src/shared/mailbox.h")
	.dwattr $C$DW$40, DW_AT_decl_line(0x9f)
	.dwattr $C$DW$40, DW_AT_decl_column(0x12)

	.dwattr $C$DW$T$45, DW_AT_decl_file("/home/joerg/retrocmp/dec/UniBone/10.01_base/2_src/shared/mailbox.h")
	.dwattr $C$DW$T$45, DW_AT_decl_line(0x9a)
	.dwattr $C$DW$T$45, DW_AT_decl_column(0x08)
	.dwendtag $C$DW$T$45

$C$DW$T$2	.dwtag  DW_TAG_unspecified_type
	.dwattr $C$DW$T$2, DW_AT_name("void")

$C$DW$T$4	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$4, DW_AT_encoding(DW_ATE_boolean)
	.dwattr $C$DW$T$4, DW_AT_name("bool")
	.dwattr $C$DW$T$4, DW_AT_byte_size(0x01)

$C$DW$T$5	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$5, DW_AT_encoding(DW_ATE_signed_char)
	.dwattr $C$DW$T$5, DW_AT_name("signed char")
	.dwattr $C$DW$T$5, DW_AT_byte_size(0x01)

$C$DW$T$6	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$6, DW_AT_encoding(DW_ATE_unsigned_char)
	.dwattr $C$DW$T$6, DW_AT_name("unsigned char")
	.dwattr $C$DW$T$6, DW_AT_byte_size(0x01)

$C$DW$T$22	.dwtag  DW_TAG_typedef
	.dwattr $C$DW$T$22, DW_AT_name("uint8_t")
	.dwattr $C$DW$T$22, DW_AT_type(*$C$DW$T$6)
	.dwattr $C$DW$T$22, DW_AT_language(DW_LANG_C)
	.dwattr $C$DW$T$22, DW_AT_decl_file("/home/joerg/retrocmp/dec/UniBone/91_3rd_party/pru-c-compile/ti-cgt-pru_2.3.1//include/stdint.h")
	.dwattr $C$DW$T$22, DW_AT_decl_line(0x3d)
	.dwattr $C$DW$T$22, DW_AT_decl_column(0x1c)


$C$DW$T$38	.dwtag  DW_TAG_array_type
	.dwattr $C$DW$T$38, DW_AT_type(*$C$DW$T$22)
	.dwattr $C$DW$T$38, DW_AT_language(DW_LANG_C)
	.dwattr $C$DW$T$38, DW_AT_byte_size(0x40000)
$C$DW$41	.dwtag  DW_TAG_subrange_type
	.dwattr $C$DW$41, DW_AT_upper_bound(0x3ffff)

	.dwendtag $C$DW$T$38

$C$DW$T$7	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$7, DW_AT_encoding(DW_ATE_signed_char)
	.dwattr $C$DW$T$7, DW_AT_name("wchar_t")
	.dwattr $C$DW$T$7, DW_AT_byte_size(0x04)

$C$DW$T$8	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$8, DW_AT_encoding(DW_ATE_signed)
	.dwattr $C$DW$T$8, DW_AT_name("short")
	.dwattr $C$DW$T$8, DW_AT_byte_size(0x02)

$C$DW$T$9	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$9, DW_AT_encoding(DW_ATE_unsigned)
	.dwattr $C$DW$T$9, DW_AT_name("unsigned short")
	.dwattr $C$DW$T$9, DW_AT_byte_size(0x02)

$C$DW$T$24	.dwtag  DW_TAG_typedef
	.dwattr $C$DW$T$24, DW_AT_name("uint16_t")
	.dwattr $C$DW$T$24, DW_AT_type(*$C$DW$T$9)
	.dwattr $C$DW$T$24, DW_AT_language(DW_LANG_C)
	.dwattr $C$DW$T$24, DW_AT_decl_file("/home/joerg/retrocmp/dec/UniBone/91_3rd_party/pru-c-compile/ti-cgt-pru_2.3.1//include/stdint.h")
	.dwattr $C$DW$T$24, DW_AT_decl_line(0x3f)
	.dwattr $C$DW$T$24, DW_AT_decl_column(0x1c)


$C$DW$T$29	.dwtag  DW_TAG_array_type
	.dwattr $C$DW$T$29, DW_AT_type(*$C$DW$T$24)
	.dwattr $C$DW$T$29, DW_AT_language(DW_LANG_C)
	.dwattr $C$DW$T$29, DW_AT_byte_size(0x400)
$C$DW$42	.dwtag  DW_TAG_subrange_type
	.dwattr $C$DW$42, DW_AT_upper_bound(0x1ff)

	.dwendtag $C$DW$T$29


$C$DW$T$37	.dwtag  DW_TAG_array_type
	.dwattr $C$DW$T$37, DW_AT_type(*$C$DW$T$24)
	.dwattr $C$DW$T$37, DW_AT_language(DW_LANG_C)
	.dwattr $C$DW$T$37, DW_AT_byte_size(0x40000)
$C$DW$43	.dwtag  DW_TAG_subrange_type
	.dwattr $C$DW$43, DW_AT_upper_bound(0x1ffff)

	.dwendtag $C$DW$T$37

$C$DW$T$10	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$10, DW_AT_encoding(DW_ATE_signed)
	.dwattr $C$DW$T$10, DW_AT_name("int")
	.dwattr $C$DW$T$10, DW_AT_byte_size(0x04)

$C$DW$T$11	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$11, DW_AT_encoding(DW_ATE_unsigned)
	.dwattr $C$DW$T$11, DW_AT_name("unsigned int")
	.dwattr $C$DW$T$11, DW_AT_byte_size(0x04)

$C$DW$T$23	.dwtag  DW_TAG_typedef
	.dwattr $C$DW$T$23, DW_AT_name("uint32_t")
	.dwattr $C$DW$T$23, DW_AT_type(*$C$DW$T$11)
	.dwattr $C$DW$T$23, DW_AT_language(DW_LANG_C)
	.dwattr $C$DW$T$23, DW_AT_decl_file("/home/joerg/retrocmp/dec/UniBone/91_3rd_party/pru-c-compile/ti-cgt-pru_2.3.1//include/stdint.h")
	.dwattr $C$DW$T$23, DW_AT_decl_line(0x41)
	.dwattr $C$DW$T$23, DW_AT_decl_column(0x1c)

$C$DW$T$12	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$12, DW_AT_encoding(DW_ATE_signed)
	.dwattr $C$DW$T$12, DW_AT_name("long")
	.dwattr $C$DW$T$12, DW_AT_byte_size(0x04)

$C$DW$T$13	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$13, DW_AT_encoding(DW_ATE_unsigned)
	.dwattr $C$DW$T$13, DW_AT_name("unsigned long")
	.dwattr $C$DW$T$13, DW_AT_byte_size(0x04)

$C$DW$T$14	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$14, DW_AT_encoding(DW_ATE_signed)
	.dwattr $C$DW$T$14, DW_AT_name("long long")
	.dwattr $C$DW$T$14, DW_AT_byte_size(0x08)

$C$DW$T$15	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$15, DW_AT_encoding(DW_ATE_unsigned)
	.dwattr $C$DW$T$15, DW_AT_name("unsigned long long")
	.dwattr $C$DW$T$15, DW_AT_byte_size(0x08)

$C$DW$T$16	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$16, DW_AT_encoding(DW_ATE_float)
	.dwattr $C$DW$T$16, DW_AT_name("float")
	.dwattr $C$DW$T$16, DW_AT_byte_size(0x04)

$C$DW$T$17	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$17, DW_AT_encoding(DW_ATE_float)
	.dwattr $C$DW$T$17, DW_AT_name("double")
	.dwattr $C$DW$T$17, DW_AT_byte_size(0x08)

$C$DW$T$18	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$18, DW_AT_encoding(DW_ATE_float)
	.dwattr $C$DW$T$18, DW_AT_name("long double")
	.dwattr $C$DW$T$18, DW_AT_byte_size(0x08)

	.dwattr $C$DW$CU, DW_AT_language(DW_LANG_C)
	.dwendtag $C$DW$CU
