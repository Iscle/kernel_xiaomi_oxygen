/*
 * bootinfo.h
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#ifndef __ASMARM_BOOTINFO_H
#define __ASMARM_BOOTINFO_H

#define HW_DEVID_VERSION_SHIFT 8
#define HW_DEVID_VERSION_MASK  0xF00UL
#define HW_MAJOR_VERSION_SHIFT 4
#define HW_MAJOR_VERSION_MASK  0xF0
#define HW_MINOR_VERSION_SHIFT 0
#define HW_MINOR_VERSION_MASK  0x0F

unsigned int get_hw_version(void);
void set_hw_version(unsigned int hw_version);
unsigned int get_hw_version_devid(void);
unsigned int get_hw_version_major(void);
unsigned int get_hw_version_minor(void);
#endif
