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

#include <asm/current.h>
#include <asm/uaccess.h>

MODULE_LICENSE("Dual BSD/GPL");

#define DRIVER_NAME "devone"

static int d_devs = 1;
static int d_major = 0;
//static int devone_minor = 0;
module_param(d_major, uint, 0);

static struct cdev c_dev;

struct data {
	unsigned char value;
	rwlock_t lock;
};

static int d_open(struct inode *inode, struct file *file) {

	struct data *p;

	printk("%s: major %d minor %d (pid %d)\n", __func__, 
				imajor(inode),
				iminor(inode),
				current->pid
			);
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
				imajor(inode),
				iminor(inode),
				current->pid
			);

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
		ret = count;
	}
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
	dev_t dev = MKDEV(d_major, 0);
	int alloc_ret = 0;
	int major;
	int cdev_err = 0;

	alloc_ret = alloc_chrdev_region(&dev, 0, d_devs, DRIVER_NAME);
	if (alloc_ret)
		goto error;
	d_major = major = MAJOR(dev);

	cdev_init(&c_dev, &devone_fops);
	c_dev.owner = THIS_MODULE;
	c_dev.ops = &devone_fops;
	cdev_err = cdev_add(&c_dev, MKDEV(d_major, 0), d_devs);
	if (cdev_err) 
		goto error;

	printk(KERN_ALERT "%s driver(major %d) installed.\n", DRIVER_NAME, major);

	return 0;

error:
	if (cdev_err == 0)
		cdev_del(&c_dev);
	if (alloc_ret == 0)
		unregister_chrdev_region(dev, d_devs);

	return -1;
}

static void d_exit(void) {
	dev_t dev = MKDEV(d_major, 0);

	cdev_del(&c_dev);
	unregister_chrdev_region(dev, d_devs);
	printk(KERN_ALERT "devone driver uninstalled.\n");
}

module_init(d_init);
module_exit(d_exit);
