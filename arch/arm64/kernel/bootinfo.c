/*
 * bootinfo.c
 * Copyright (C) 2017 XiaoMi, Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/string.h>
#include <asm/setup.h>
#include <asm/bootinfo.h>
#include <linux/bitops.h>
#include <linux/qpnp/power-on.h>

static struct kobject *bootinfo_kobj;
static unsigned int hw_version;

#define bootinfo_attr(_name) \
static struct kobj_attribute _name##_attr = {	\
	.attr	= {				\
		.name = __stringify(_name),	\
		.mode = 0644,			\
	},					\
	.show	= _name##_show,			\
	.store	= NULL,				\
}

#define bootinfo_func_init(type, name, initval)		\
	static type name = (initval);		\
	type get_##name(void)			\
	{					\
		return name;			\
	}					\
	void set_##name(type __##name)		\
	{					\
		name = __##name;		\
	}					\
	EXPORT_SYMBOL(set_##name);		\
	EXPORT_SYMBOL(get_##name);

bootinfo_attr(hw_version);
bootinfo_func_init(u32, hw_version, 0);

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

static struct attribute *g[] = {
	&hw_version_attr.attr,
	NULL,
};

static struct attribute_group attr_group = {
	.attrs = g,
};

static int __init bootinfo_init(void)
{
	int ret = -ENOMEM;

	bootinfo_kobj = kobject_create_and_add("bootinfo", NULL);
	if (bootinfo_kobj == NULL) {
		printk("bootinfo_init: subsystem_register failed\n");
		goto fail;
	}

	ret = sysfs_create_group(bootinfo_kobj, &attr_group);
	if (ret) {
		printk("bootinfo_init: subsystem_register failed\n");
		goto sys_fail;
	}

	return ret;

sys_fail:
	kobject_del(bootinfo_kobj);
fail:
	return ret;

}

static void __exit bootinfo_exit(void)
{
	if (bootinfo_kobj) {
		sysfs_remove_group(bootinfo_kobj, &attr_group);
		kobject_del(bootinfo_kobj);
	}
}

core_initcall(bootinfo_init);
module_exit(bootinfo_exit);

