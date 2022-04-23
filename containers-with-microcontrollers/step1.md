In this first step, you'll learn the fundamentals of the development enviroment, including the toolchain; the commands used to compile and run code using RIOT-OS.

We'll start by running a very simple containered application.

The RIOT-OS ecosystem provides a very handy `native` mode, which allows you to emulate a microcontroller on your PC. This allows for very rapid development and prototyping, without any actual hardware! 

Let's move into the proper directory shall we?
```sh
cd Femto-Container_tutorials
```{{execute}}

*Note:* If you cannot continue immediately, this is because the installation of the dependencies has not yet finished.
Try again, once you see new files in the code editor.

## 1. Compiling the Code
RIOT-OS uses a Makefile and the `make` system to define tasks that can be run, and much more. Let's dive into what makes up the basic structure of a RIOT-OS project.

There are mainly two files of interest here, for starters the Makefile,
`tutorial_1/Makefile`{{open}}

and of course, the `main.c` which is at the heart of the project,
`tutorial_1/main.c`{{open}}

Let's also take a look at the container workload that we will be running. This is defined in a subdirectory of our application.
`tutorial_1/fc/increment.c`{{open}}

But enough of staring at code, let's compile the project! 

### 1.1. Compile the container application
First, we must compile our container application. Run the following command to compile the container:
```sh
make all -C tutorial_1/fc
```{{execute}}

This produces a separate binary blob that we can link with our main application/firmware.

### 1.2. Compile the firmware
We will now compile the entire project. This will produce a firmware binary that is possible to flash to a microcontroller.
```sh
make all -C tutorial_1
```{{execute}}

But, since we are running this in an emulated environment we don't have to flash the actual firmware. Instead, we can jump directly to "running" the code.
We will open an emulated terminal session to our "microcontroller" with the `make term` command.
```sh
make term -C tutorial_1
```{{execute}}

**Note:** You might have to scroll down in the terminal to see the output.

This should show you a simple containered application running, that does nothing more exciting than take an input, increment it, and return the value.
Let's move on to something more a bit more thrilling shall we?
