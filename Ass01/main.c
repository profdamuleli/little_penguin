#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Lutendo Damuleli");
MODULE_DESCRIPTION("hello world module");

static int start_line(void)
{
    printk(KERN_INFO "Hello world!\n");
    return 0;
}

static  void finish_line(void)
{
    printk(KERN_INFO "Cleaning up module.\n");
}

module_init(start_line);
module_exit(finish_line);
