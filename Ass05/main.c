#include <linux/init.h> 
#include <linux/miscdevice.h>
#include <linux/fs.h>
#include <linux/kernel.h>
#include <linux/uaccess.h>
#include <linux/module.h>

#define USERNAME "ldamulel"
#define LEN 8


char kbuff[LEN];
int ret;

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Lutendo Damuleli <profdamuleli@gmail.com>");
MODULE_DESCRIPTION("username module");

static ssize_t ft_read(struct file *f, char __user *buffer, size_t length, loff_t *offset)
{
    char *read_from = USERNAME + *offset;
    size_t read_num = length < (LEN - *offset) ? length : (LEN - *offset);

    if (read_num == 0)
        return (0);
    ret = copy_to_user(buffer, read_from, read_num);
    if (ret == read_num) {
        ret = -EIO;
    } else {
        *offset = LEN - ret;
        ret = read_num - ret;
    }
    return ret;
}

static ssize_t ft_write(struct file *f, const char __user *buf, size_t len, loff_t *offset)
{
    if (len != LEN) {
        ret = -EINVAL;
        return (ret);
    }
    ret = copy_from_user(kbuff, buf, LEN);
    if (strncmp(kbuff, USERNAME, LEN) == 0)
        ret = LEN;
    else
        ret = -EINVAL;
    return (ret);
}

static int ft_open(struct inode *inode, struct file *file)
{
    printk(KERN_INFO "Opened the device.\n");
    return 0;
}

static int ft_close(struct inode *inodep, struct file *filp)
{
    printk(KERN_INFO "Closed the device.\n");
    return 0;
}

static struct file_operations devfops = {
    .owner = THIS_MODULE,
    .open = ft_open,
    .read = ft_read,
    .write = ft_write,
    .release = ft_close,
    .llseek = no_llseek,
};

struct miscdevice ldamulel_device = {
    .name = "fortytwo",
    .minor = MISC_DYNAMIC_MINOR,
    .fops = &devfops,
    .mode = 0666,
};

static int init_point(void)
{
    printk(KERN_INFO "Hello world!\n");
    return misc_register(&ldamulel_device);
}

static void exit_point(void)
{
    printk(KERN_INFO "Cleaning up module.\n");
    misc_deregister(&ldamulel_device);
}
module_init(init_point);
module_exit(exit_point);
