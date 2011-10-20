#include <linux/module.h>
#include <linux/kernel.h>


void method(void) {
	printk("%s: method() called\n", __func__);
}

