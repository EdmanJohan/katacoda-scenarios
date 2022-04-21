In this first step, you'll learn the fundamentals of the development enviroment,  
including the toolchain; the commands used to compile and run code.  

We'll start by running a very simple containered application.

RIOT-OS provides a very handy `native` mode, which allows you to emulate a microcontroller  
on your PC. This allows for very rapid development and prototyping, without any actual hardware!  

We'll being by compiling the code.  
To compile the code, run the following command:  
```sh
make all -C tutorial_1
```{{execute}}

Then we'll execute the code in our emulated environment.  
We do this by executing the `make term` command, which will open an emulated terminal session.
Run the following command:  
```sh
make term -C tutorial_1
```{{execute}}
