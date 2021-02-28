---
title: Introduction to Linux Kernel Modules
author: Rahul
tags: Linux
aside:
  toc: true
sidebar:
  nav: layouts
mathjax: false
mathjax_autoNumber: false
mermaid: false
chart: false
excerpt_separator: <!--more-->
key: lkm0001
---
In this post, we will introduce the reader to writing Kernel Modules for Linux.

## What are Kernel Modules?
Kernel Modules are pieces of code that can be loaded into the kernel while the kernel is already running. Modules extend the functionality of the kernel. Many modules are already loaded into the kernel by default (built-in modules) (eg. mouse and keyboard drivers). But what if we need some functionality that is not already built-in? This is where loading new modules without rebooting the system comes in handy (loadable modules) (eg. you plug in a printer whose driver was not already present). The examples provided mostly focus on device drivers but we can do pretty much anything with kernel modules. It is literally adding your code to the kernel which implies that these modules run with kernel privileges (ring 0) (In later posts we will write some rootkits as well :) ).

It is advised to build these modules in a virtual machine to prevent corruption and to revert back to previous states of the operating system without much trouble.
Now let's begin.

## Writing a Simple Module
Kernel modules are written in C. As always let's start with writing Hello World!. The code for this is:

```C
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Rahul");

static int __init hello_init(void)
{
    printk(KERN_ALERT "Hello World!\n");
    return 0;
}

static void __exit hello_exit(void)
{
    printk(KERN_ALERT "Module Removed!\n");
}

module_init(hello_init);
module_exit(hello_exit);
 ```

 We will walk through the above code line by line. Firstly we have few ```#include``` statements that include some macros that we have used in the program. Next we define the macros ```MODULE_LICENSE``` and ```MODULE_AUTHOR```. Defining the license macro is important as without it, the kernel will complain while loading the module. GPL is the General Public License and if you do not have ````MODULE_LICENSE("GPL")```` then symbols that are exported via ``EXPORT_SYMBOL_GPL()`` will not be visible to your module. This is how Linux enforces what code is considered to be a derivative work of Linux.

 Next we have the init and exit functions that all modules MUST have. The init function ```hello_init``` in our case runs when the module is loaded into the kernel and the exit function ```hello_exit``` is called when the module is removed from the kernel. The init function is used to initialize variables and get information about hardware and other devices but here we just print "Hello World!". The exit function is used to free memory and is used as a clean-up function (The kernel runs along with all user-space programs and does not have a lot memory. That is why freeing space is very important while working with the kernel) (On 32-bit systems the entire Linux kernel has only 1 GB of virtual memory). Notice the use ```__init``` and ```__exit``` macros while defining the function. These tell the kernel that these functions are used only while the module is loading and being removed respectively. The kernel can then allocate memory for these functions only while loading and unloading the module.

 Finally notice how we use ```printk``` instead of the usual ```printf```. ```printk``` is the print utility function defined in the kernel. When the kernel is built there are no standard C libraries (glibc) in memory and hence the kernel needs it's own printing function. Also, here we have the ```KERN_ALERT``` macro that sets the "level" of the message to be printed. Here, we use the high "alert" indicator so that our string is printed almost everywhere the kernel displays messages. We can also use lower levels by using ```KERN_INFO``` or ```KERN_DEBUG```.

## Building Kernel Modules
Now that we have written our module, it is time to build it. For that we use the ``make`` utility.

Here is the Makefile.

```
obj-m += hello.o

all:
    make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
    make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
```

This is different from the usual Makefile. Here, the Kernel's build utility takes care of the rest. Assuming your file is called hello.c running ```make``` will give you many intermediate files but also a hello.ko file. This is a kernel object file. To load it into the kernel, run ```insmod hello.ko``` (You will have to switch to root to do this). Now if you run ```dmesg``` which displays kernel messages you should find our message "Hello World!" at the bottom. It will probably be highlighted because we used ```1KERN_ALERT```. Now if you run ```rmmod hello``` you will find our exit message in the output of ```dmesg```. You can list all loaded modules using ```lsmod```.

Finally, we have built our first module that does nothing :P. In later posts we will try to do something useful with our modules.

For more resources on Linux and Kernel Modules: <br>
[Linux Device Drivers Book](https://lwn.net/Kernel/LDD3/) <br>
[LiveOverflow Linux Device Drivers Video](https://www.youtube.com/watch?v=juGNPLdjLH4) <br>
{:.info}
