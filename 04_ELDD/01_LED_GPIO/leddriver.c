/*
*                   CDAC HYDERABAD LAB EXAM, JULY 2022
*           **************************************************
*
*1. LED OPERATION USING GPIO & TIMERS
*
*@ Write a Character Driver using ioctl & Kernel Timer functionality.
*@ Use GPIO_23 to interface LED on RaspberryPi and blink the LED Periodically using Kernel Timer.
*@ Use ioctl functionality to change the periodicity of LED Blinking. 
*
*   AUTHOR      - Abhinav Tyagi
*   EMAIL ID    - erabhinavtyagi@gmail.com
*  
*/

#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/cdev.h>
#include <linux/kdev_t.h>
#include <linux/jiffies.h>
#include <linux/timer.h>
#include <linux/gpio.h>

//#include <asm-generic/ioctl.h>
#include "ioctl_led.h"

/**************** METADATA ***********************/

MODULE_LICENSE("GPL");
MODULE_AUTHOR("ABHINAV")
MODULE_DESCRIPTION("LED Blinking using using Timer on GPIO_23");

/*********** FUNCTION DECLARATIONS ***************/

// Init & Exit functions
static int  __init gpio_init(void);
static void __exit gpio_exit(void);

// File Operations
int gpio_open (struct inode *node, struct file *filp);
ssize_t gpio_read (struct file *filp, char __user *buff, size_t count, loff_t *offset);
ssize_t gpio_write (struct file *filp, const char __user *buff, size_t count, loff_t *offset);
int gpio_release (struct inode *node, struct file *filp);
long gpio_ioctl(struct file *filep, unsigned int cmd, unsigned long arg);

static struct file_operations *fops =
{
    .owner          = THIS_MODULE;
    .open           = gpio_open;
    .read           = gpio_close;
    .write          = gpio_write;
    .release        = gpio_release;
    .unlocked_ioctl = gpio_release;         // To Enable ioctl Functionality for the module
}

// Timer Function Declarations
void ledTimer (struct timer_list *timer);
void init_timers(void);
int mod_timer(struct timer_list *timer, unsigned long expires);
int del_timer(struct timer_list * timer);

/**************** GLOBAL DECLARATIONS ******************/
dev_t dev;
struct cdev chardev;

#define LED 23      // LED GPIO Pin = 23 


/**************** FUNCTION DEFINATION ******************/

static int gpio_open (struct inode *node, struct file *filp)
{
    pr_info("\nOpening Device File.....\n");
    return 0;
}

static ssize_t gpio_read (struct file *filp, char __user *buff, size_t count, loff_t *offset)
{
    pr_info("\nReading Device File.....\n");
    return 0;           // End of file (EOF)
}

static ssize_t gpio_write (struct file *filp, const char __user *buff, size_t count, loff_t *offset)
{
    pr_info("\nWriting Device File.....\n");
    return count;       // Number of bytes written
}

static int gpio_release (struct inode *node, struct file *filp)
{
    pr_info("\nClosing Device File.....\n");
    return 0;
}


//---------- Timer module---------
static void ledTimer (struct timer_list *timer)
{
    static int count;

    pr_info(KERN_INFO " Timer Function \n");
    pr_info(KERN_INFO " HZ: %d \n", HZ);

    mod_timer(&timer, jiffies + (msecs_to_jiffies(300)));
    if (count)
    {
        gpio_direction_output(LED_PIN, 1);
        count = 0;
    }
    else
    {
        gpio_direction_output(LED_PIN, 0);
        count = 1;
    }
}

// ------------IOCTL ---------------

static long gpio_ioctl(struct file *filep, unsigned int cmd, unsigned long arg)
{
    pr_info("GPIO_ioctl Invoked.\n");
    switch(cmd)
    {
        case LED_ON: __putusr(LED) = 1 ;
                    break;

        case LED_OFF:__putusr(LED) = 0;
                    break;
        default:
                pr_err("INVALID COMMAND\n");
    }

return 0;
}

// ----------INIT MODULE-------------------------
static int  __init gpio_init(void);
{
    pr_info("INSIDE %s MODULE\n", __FUNCTION__);
    
    // Registering Character driver
   
    if(alloc_chrdev_region(mydev, 0, 1, "ledGPIO")<0)
    {
        pr_err("Error in Allocating Device Number\n");
    }
    
    pr_info("Allocated Major Number: %d \t Minor Number: %d\n", MAJOR(dev), MINOR(dev));
    
    dev = cdev_alloc();
	dev->ops = &fops;

    if(cdev_add(struct cdev chardev, dev, 1)<0)
    {
        pr_err("Error in Adding Device to system \n");
    }
        
    return 0;
}

//----------EXIT MODULE-------------------------
static void __exit gpio_exit(void);
{
    pr_info("EXITING %s MODULE\n", __FUNCTION__);
    
    cdev_del(&chardev);                     // Remove Character Driver 
    unregister_chrdev_region(dev,1);        // Unregister Device File 
    del_timer(timer);                       // Remove Timer Functionality
}

//****************** END OF MODULE !! HAVE A NICE DAY *******************************