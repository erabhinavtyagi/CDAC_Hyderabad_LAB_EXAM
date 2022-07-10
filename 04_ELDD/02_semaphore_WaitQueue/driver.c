#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/kdev_t.h>
#include <linux/cdev.h>
#include <linux/fs.h>
#include <linux/semaphore.h>
#include <linux/uaccess.h>
#include <linux/wait.h>

dev_t dev = 0;
struct cdev *my_cdev;
struct semaphore my_sema;
wait_queue_head_t wq;

DECLARE_WAIT_QUEUE_HEAD(wq);

static int flag = 0;

unsigned char kbuff[50];

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Abhinav Tyagi");
MODULE_DESCRIPTION("Module to perform Synchronization Mechanism");


static int 	__init chardriver_init(void);
static void 	__exit chardriver_exit(void);

/*********** File Operations *****************/
static int	char_open(struct inode *inode, struct file *file);
static int	char_release(struct inode *inode,struct file *file);
static ssize_t 	char_read(struct file *file, char __user *buff, size_t len, loff_t *off);
static ssize_t	char_write(struct file *file, const char __user *buff, size_t len, loff_t *off);

static struct file_operations fops =
{
	.owner	  =	THIS_MODULE,
	.open	  =	char_open,
	.read	  = 	char_read,
	.write	  = 	char_write,
	.release  =	char_release,
};

static int char_open(struct inode *inode, struct file *file)
{
	printk(KERN_INFO "Driver Opened\n");
	return 0;
}

static int char_release(struct inode *inode, struct file *file)
{
	printk(KERN_INFO "Driver Closed\n");
	return 0;
}

static ssize_t char_read(struct file *file, char __user *buff, size_t len, loff_t *off)
{
	if((copy_to_user((char *)buff, (char *)kbuff, sizeof(kbuff))) == 0)
	{
		printk(KERN_INFO "Data Read Successfull...\n");
	}
	else
	{
		printk(KERN_ERR "Error in reading\n");
	}
	up(&my_sema);
	flag = 1;
	wake_up_interruptible(&wq);
	return 0;
}	

static ssize_t char_write(struct file *file, const char __user *buff, size_t len, loff_t *off)
{
	down_interruptible(&my_sema);
	if((copy_from_user((char *)kbuff, (char *)buff, sizeof(kbuff))) == 0)
	{
		printk(KERN_INFO "Data Write Successfull...\n");
		printk(KERN_INFO "Received Data from User = %s\n", kbuff);
	}
	else
	{
		printk(KERN_ERR "Error in writing\n");
	}
	wait_event_interruptible(wq, flag!=0);
	printk(KERN_INFO "Process went into Sleep\n");
	if(flag ==2)
	{
		printk(KERN_INFO "Wake up Successfull...\n");
	}
	flag= 0;
	return len;

}

static int __init chardriver_init(void)
{
	alloc_chrdev_region(&dev, 0 , 2, "chardriver");
	printk(KERN_INFO "Major Number = %d\nMinor Number = %d\n", MAJOR(dev), MINOR(dev));
	my_cdev = cdev_alloc();
	my_cdev -> ops = &fops;
	cdev_add(my_cdev, dev, 2);
	sema_init(&my_sema, 1);
	printk(KERN_INFO "Driver Inserted Successfully\n");
	return 0;
}

static void __exit chardriver_exit(void)
{
	cdev_del(my_cdev);
	unregister_chrdev_region(dev, 2);
	printk(KERN_INFO "Driver removed Successfully\n");
}
module_init(chardriver_init);
module_exit(chardriver_exit);
