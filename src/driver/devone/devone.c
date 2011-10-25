/*
 * device one
 *
*/

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/types.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/sched.h>
#include <linux/slab.h>
#include <linux/device.h>

#include <asm/current.h>
#include <asm/uaccess.h>

MODULE_LICENSE("Dual BSD/GPL");

#define DRIVER_NAME "devone"

static int d_devs = 1;
static int d_major = 0;
static int d_minor = 0;
module_param(d_major, uint, 0);

static struct cdev c_dev;
static struct class *dev_class = NULL;
static dev_t d_dev;

struct data {
	unsigned char value;
	rwlock_t lock;
};

static int d_open(struct inode *inode, struct file *file) {

	struct data *p;

	printk("%s: major %d minor %d (pid %d)\n", __func__, 
				imajor(inode), iminor(inode), current->pid);

	p = kmalloc(sizeof(struct data), GFP_KERNEL);
	if (p == NULL) {
		printk("%s: Not memory\n", __func__);
		return 1;//-ENOMEN;
	}

	p->value = 0xff;
	rwlock_init(&p->lock);

	file->private_data = p;
	return 0;
}

static int d_close(struct inode *inode, struct file *file) {
	
	printk("%s: major %d minor %d (pid %d)\n", __func__, 
				imajor(inode), iminor(inode), current->pid);

	if (file->private_data) {
		kfree(file->private_data);
		file->private_data = NULL;
	}

	return 0;
}

ssize_t d_write(struct file *file, const char __user *buf, size_t count, loff_t *f_pos) {

	struct data *p = file->private_data;
	unsigned char value;
	int ret = 0;

	printk("%s: count %d pos %lld\n", __func__, count, *f_pos);

	if (count >= 1) {
		if (copy_from_user(&value, &buf[0], 1)) {
			ret = -EFAULT;
			goto out;
		}
		write_lock(&p->lock);
		p->value = value;
		write_unlock(&p->lock);
	}
	ret = count;

out:
	return (ret);
}

ssize_t d_read(struct file *fp, char __user *buf, size_t count, loff_t *f_pos) {
	struct data *p = fp->private_data;
	int i;
	unsigned char value;
	int ret;
	
	read_lock(&p->lock);
	value = p->value;
	read_unlock(&p->lock);

	printk("%s: count %d pos %lld\n", __func__, count, *f_pos);

	for (i=0; i<count; i++) {
		if (copy_to_user(&buf[i], &value, 1)) {
			ret = -EFAULT;
			goto out;
		}
	}
	ret = count;

out:
	return (ret);
}

struct file_operations devone_fops = {
	.open = d_open,
	.release = d_close,
	.read = d_read,
	.write = d_write,
};

static int d_init(void) {

	dev_t dev = MKDEV(d_major, d_minor);
	int a_ret = 0;
	int cdev_err = 0;
	struct class_device *d_class = NULL;

	//Get Major No.
	a_ret = alloc_chrdev_region(&dev, 0, d_devs, DRIVER_NAME);
	if (a_ret) goto error;
	d_major = MAJOR(dev);
	
	//Register handler of system call.
	cdev_init(&c_dev, &devone_fops);
	c_dev.owner = THIS_MODULE;
	c_dev.ops = &devone_fops;
	
	//Register driver to Kernel.
	cdev_err = cdev_add(&c_dev, MKDEV(d_major, d_minor), d_devs);
	if (cdev_err) goto error;

	//Register class
/*	d_class = class_create(THIS_MODULE, DRIVER_NAME);
	if (IS_ERR(d_class)) goto error;
	d_dev = MKDEV(d_major, d_minor);
	dev_class = device_create(
		d_class, NULL, d_dev, NULL, DRIVER_NAME" %d", d_minor);
*/
	printk(KERN_ALERT "%s driver(major %d) installed.\n", DRIVER_NAME, d_major);

	return 0;

error:
	if (cdev_err == 0)
		cdev_del(&c_dev);
	if (a_ret == 0)
		unregister_chrdev_region(dev, d_devs);

	return -1;
}

static void d_exit(void) {
	dev_t dev = MKDEV(d_major, d_minor);
	
/*	device_destroy(dev_class, d_dev);
	class_destroy(dev_class);
*/	
	cdev_del(&c_dev);
	unregister_chrdev_region(dev, d_devs);

	printk(KERN_ALERT "devone driver uninstalled.\n");
}

module_init(d_init);
module_exit(d_exit);
