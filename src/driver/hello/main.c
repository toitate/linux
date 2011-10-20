#include <linux/module.h>
#include <linux/kernel.h>

MODULE_LICENSE("Dual BSD/GPL");

extern void method(void);

static int hello_init(void) {
	printk(KERN_ALERT "driver loaded\n");
	method();
	return 0;
}

static void hello_exit(void) {
	printk(KERN_ALERT "driver unloaded\n");
}

module_init(hello_init);
module_exit(hello_exit);
