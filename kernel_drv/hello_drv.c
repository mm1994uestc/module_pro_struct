#include <linux/fs.h>     /* 包含file_operation结构体 */
#include <linux/init.h>    /* 包含module_init module_exit */
#include <linux/module.h>  /* 包含LICENSE的宏 */

#include <linux/irq.h>
#include <linux/cdev.h>
#include <linux/interrupt.h>

#include <linux/io.h>
#include <asm/uaccess.h>
#include <linux/device.h>

MODULE_LICENSE("Dual BSD/GPL"); // module license:GPL and so on...
MODULE_AUTHOR("MM1994UESTC");   // module author

#define GPIO_CONF_ADDR 0xe0200240 // Hardware phy-address
#define IRQ_DEBUG 0

static char *param_str = "This is hello-drv's str param."; // string param insert
module_param(param_str, charp, S_IRUGO);

static int param_num = 666; // intger param insert
module_param(param_num, int, S_IRUGO);

static unsigned int major;            // device major id
static struct class *hello_dev_class; // device class
static struct device *hello_dev;      // device name

int a=10,b=20,hello_c=1;
static ssize_t hello_drv_write(struct file *filep, const char __user * buf,size_t len,loff_t *ppos) // Kernel basic write-func
{
	printk("hello_drv_write\n"); // use printk to print the content to /var/log/syslog
	hello_c = a + b;
	return 0;
}

// export the intger var to /proc/kallsyms which record the symbol's memory-address/
// The symbol can be used by other modules.
EXPORT_SYMBOL_GPL(hello_c);

#if IRQ_DEBUG
static irqreturn_t irq_handler(int irq, void *dev_id)
{
	printk(KERN_INFO"irq_handler %d\n",irq);
	return IRQ_HANDLED;
}
#endif

static int hello_drv_open(struct inode *inodep, struct file *filep) // Kernel basic open-func
{
	printk("hello_drv_open\n"); // printk the mesg into the kernal log(/var/log/syslog)

#if IRQ_DEBUG
	int ret = 0;
	ret = request_irq(irq_eint(2), irq_handler, IRQF_TRIGGER_RISING|IRQF_TRIGGER_FALLING, "irq-eint2",NULL);
	if(ret)
	{
		printk(KERN_ERR"request_irq IRG_EINT(2) fail!");
	}
#endif

	return 0;
}

static int hello_drv_close(struct inode *inode, struct file *file)
{
#if IRQ_DEBUG
    free_irq(irq_eint(2), NULL);
#endif
    return 0;
}

static const struct file_operations hello_drv_operation = {
	.owner = THIS_MODULE,
	.open  = hello_drv_open, // register the base kernel functions mapping to user functions:{user-open:kernel-open}
	.write = hello_drv_write,
	.release = hello_drv_close,
};

static int __init hello_init(void)
{
	major = register_chrdev(0,"hello_drv",&hello_drv_operation); // The return value is the major-id of device(if major == 0)

	// Some hardware & mem initial

	hello_dev_class = class_create(THIS_MODULE, "hello_dev_class"); // create a new class for dev
	if(!hello_dev_class) {
		if(IS_ERR(hello_dev_class))
			return PTR_ERR(hello_dev_class);
	}

	hello_dev = device_create(hello_dev_class,NULL,MKDEV(major, 0),NULL, "hello"); // create dev-point under /dev/ folder
	if(IS_ERR(hello_dev))
		return PTR_ERR(hello_dev);

        printk(KERN_ALERT "hello-drv installed!\n");
	printk(KERN_INFO"The param-str:%s\n",param_str);
	printk(KERN_INFO"The param-num:%d\n",param_num);

        return 0;
}
static void __exit hello_exit(void)
{
	unregister_chrdev(major,"hello_init");
        printk(KERN_ALERT "Goodbye,cruel world!\n");

	device_unregister(hello_dev);   // unregister the device in /dev/
	class_destroy(hello_dev_class); // destroy the dev class
}

module_init(hello_init);
module_exit(hello_exit);
