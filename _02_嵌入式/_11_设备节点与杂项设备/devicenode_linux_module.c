#include <linux/init.h>
#include <linux/module.h>


#include <linux/platform_device.h> /*驱动注册的头文件，包含驱动的结构体和注册和卸载的函数*/
#include <linux/miscdevice.h> /*注册杂项设备头文件*/
#include <linux/fs.h> /*注册设备节点的文件结构体*/

#define DRIVER_NAME "hello_ctl"
#define DEVICE_NAME "hello_ctl123"
MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("Wind");

static long hello_ioctl( struct file *files, unsigned int cmd, unsigned long arg)
{

	
	printk("cmd is %d,arg is %d\n",cmd,arg);
	return 0;
}

static int hello_release(struct inode *inode, struct file *file)
{
	printk(KERN_EMERG "hello release\n");
	return 0;
}

static int hello_open(struct inode *inode, struct file *file)
{
	printk(KERN_EMERG "hello open\n");
	return 0;
}

static struct file_operations hello_ops = //文件操作相关的函数填写
{
	.owner = THIS_MODULE,
	.open = hello_open,
	.release = hello_release,
	.unlocked_ioctl = hello_ioctl,
};

static  struct miscdevice hello_dev = //杂项设备的相关信息
{
	.minor = MISC_DYNAMIC_MINOR,
	.name = DEVICE_NAME,
	.fops = &hello_ops,
};

//注册hello_driver驱动之后运行这个
static int hello_probe(struct platform_device *pdv)
{
	
	printk(KERN_EMERG "\tinitialized\n");
	misc_register(&hello_dev);//注册杂项设备
	
	return 0;
}

static int hello_remove(struct platform_device *pdv)
{
	
	printk(KERN_EMERG "\tremove\n");
	misc_deregister(&hello_dev);
	return 0;
}

static void hello_shutdown(struct platform_device *pdv)
{
	
	;
}

static int hello_suspend(struct platform_device *pdv,pm_message_t pmt)
{
	
	return 0;
}

static int hello_resume(struct platform_device *pdv)
{
	
	return 0;
}

struct platform_driver hello_driver =
{
    .probe = hello_probe,//初始化时运行的程序
    .remove = hello_remove,//移除驱动时运行的程序
    .shutdown = hello_shutdown,//关机时运行的程序
    .suspend = hello_suspend,//挂起（休眠）时运行的程序
    .resume = hello_resume,//唤醒时运行的程序
    .driver =
    {
        .name = DRIVER_NAME,//驱动的名字
        .owner = THIS_MODULE,
    }
};


static int hello_init(void)//驱动初始化时运行这个
{
    int DriverState;

    printk(KERN_EMERG "\n this hello_init code! \n");
    DriverState = platform_driver_register( & hello_driver);//注册hello_driver驱动

    printk(KERN_EMERG "\tDriverState is %d\n", DriverState);
    return 0;
}

static void hello_exit(void)
{
    printk(KERN_EMERG "this hello_exit code !\n");

    platform_driver_unregister( & hello_driver);
}

module_init(hello_init);
module_exit(hello_exit);

