/*
 * bootinfo.c
 * Copyright (C) 2017 XiaoMi, Inc.
 * Copyright (C) 2020 Iscle
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/module.h>
#include <asm/bootinfo.h>

static unsigned int hw_version = 0;

unsigned int get_hw_version(void)
{
	return hw_version;
}
EXPORT_SYMBOL(get_hw_version);

void set_hw_version(unsigned int __hw_version)
{
	hw_version = __hw_version;
}
EXPORT_SYMBOL(set_hw_version);

unsigned int get_hw_version_devid(void)
{
	return (get_hw_version() & HW_DEVID_VERSION_MASK) >> HW_DEVID_VERSION_SHIFT;
}
EXPORT_SYMBOL(get_hw_version_devid);

unsigned int get_hw_version_major(void)
{
	return (get_hw_version() & HW_MAJOR_VERSION_MASK) >> HW_MAJOR_VERSION_SHIFT;
}
EXPORT_SYMBOL(get_hw_version_major);

unsigned int get_hw_version_minor(void)
{
	return (get_hw_version() & HW_MINOR_VERSION_MASK) >> HW_MINOR_VERSION_SHIFT;
}
EXPORT_SYMBOL(get_hw_version_minor);
