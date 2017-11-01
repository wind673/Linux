#include <linux/init.h>
#include <linux/module.h>

/*驱动注册的头文件，包含驱动的结构体和注册和卸载的函数*/
#include <linux/platform_device.h>

#define DRIVER_NAME "hello_ctl"

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("Wind");


//注册hello_driver之后运行这个
static int hello_probe(struct platform_device *pdv)
{

    printk(KERN_EMERG "this hello_probe code !\n");

    return 0;
}

static int hello_remove(struct platform_device *pdv)
{
	printk(KERN_EMERG "this hello_remove code!\n");
    return 0;
}

static void hello_shutdown(struct platform_device *pdv)
{

    ;
}

static int hello_suspend(struct platform_device *pdv)
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
    DriverState = platform_driver_register( & hello_driver);//注册hello_driver

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



