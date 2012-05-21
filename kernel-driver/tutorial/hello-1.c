#include <linux/module.h>
#include <linux/kernel.h>

int init_module(void)
{
	printk(KERN_INFO "Hello World\n");

	return -1;
}

void cleanup_module(void)
{
	printk(KERN_INFO "Over and Out!\n");
}
