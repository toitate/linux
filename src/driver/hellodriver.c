//#include <linux/module.h>
#include <linux/kernel.h>

#include <linux/module.h>
int
init_module(void) {
	return 0;
}

void
cleanup_module() {
}
