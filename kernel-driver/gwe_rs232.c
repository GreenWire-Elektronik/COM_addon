#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/stat.h>
#include <linux/fs.h>
#include <linux/serial_core.h>

#define DEVICE_NAME "ttyS42"
#define MODUL_NAME "gwe_rs232"
#define MAJOR_START 142

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Jonas Arndt, GreenWire-Elektronik, support@greenwire-elektronik.de");
MODULE_DESCRIPTION("%s - driver to support full featured RS232 on R-PI using GPIOs for sideband and flow control signals" MODUL_NAME);
MODULE_SUPPORTED_DEVICE("bcmrpi COM_addon");

static int __init gwe_rs232_init(void);
static void __exit gwe_rs232_exit(void);
static int device_open(struct inode *, struct file *);
static int device_release(struct inode *, struct file *);
static ssize_t device_read(struct file *, char *, size_t, loff_t *);
static ssize_t device_write(struct file *, const char *, size_t, loff_t *);


static long int baudrate = 9600;
static char *parity = "none";
static char *flow_ctrl = "none";
static short int stopbit = 1;
static short int databit = 8;

static int major_number = 0;
static struct file_operations fops = {
	.read = device_read,
	.write = device_write,
	.open = device_open,
	.release = device_release
};
static struct uart_driver gwe_rs232_reg = {
	.owner = THIS_MODULE,
	.driver_name = MODUL_NAME,
#ifdef CONFIG_DEVFS_FS
	.dev_name = DEVICE_NAME+"%d",
#else
	.dev_name = DEVICE_NAME,
#endif
	.major = MAJOR_START, //dummy, will be overwritten during initialization
	.minor = 0,
	.nr = 1,
	.cons = NULL //atm no console support - has to be done later on
};


static int __init gwe_rs232_init(void)
{
	int major_temp = MAJOR_START;
	printk(KERN_INFO "blub: %d", major_temp);
	int i = 0;
	for (i = 0; i <= 10; i++) {
		major_temp = major_temp + i;
		printk(KERN_INFO "A: %d", major_temp);
		major_number = register_chrdev(major_temp, DEVICE_NAME, &fops);
		printk(KERN_INFO " B: %d\n", major_number);
		if (major_number == 0) {
			major_number = major_temp;
			break;
		}
	}

	/*getting major number for this module driver*/
	if (major_number < 0) {
		printk(KERN_ALERT "%s could not be loaded: error code %d", MODUL_NAME, major_number);
		return major_number;
	}
	printk(KERN_INFO "%s loaded sucessfully MAJOR: %d\n", MODUL_NAME, major_number);

	/*registering uart driver*/
	gwe_rs232_reg.major = major_number;
	uart_register_driver(&gwe_rs232_reg);


	return 0;
}

static void __exit gwe_rs232_exit(void)
{
	unregister_chrdev(major_number, DEVICE_NAME);
	printk(KERN_INFO "%s sucessfully unloaded\n", MODUL_NAME);
}


static int device_open(struct inode *inode, struct file *file) {
	return 0;
}

static int device_release(struct inode *inode, struct file *file) {
	return 0;
}

static ssize_t device_read(struct file *filp, char *buffer, size_t length, loff_t *offset) {
	return 0;
}

static ssize_t device_write(struct file *filp, const char *buffer, size_t length, loff_t *offest) {
	return 0;
}

module_init(gwe_rs232_init);
module_exit(gwe_rs232_exit);
