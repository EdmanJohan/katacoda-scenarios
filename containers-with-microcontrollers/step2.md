## Hello World in Femto-Container in RIOT OS Thread

Now it is about time to create our own little container application.
To save some time, we will work upon an existing code-skelleton that you can find here: `tutorial_helloworld/main.c`{{open}}.

The only thing happening currently is, that a thread is created, that gets executed by the RIOT OS scheduler. This thread writes "Hello from thread" to stdout and then waits for 500ms. 

You can execute it and see for yourself.

```c
cd Femto-Container_tutorials/tutorial_helloworld 
make all term
```{{execute interrupt}}

In the following steps we will adjust the thread to execute a container, that runs code in an isolated environment. 

Each step holds holds code that needs to be inserted for the placeholder with the respective steps number.

### 1. Add bpf library for femto-containers

First, we need to include the header for using the bpf subsystem within RIOT OS, which implements everything needed to work with femto-containers.

```c
#include "bpf.h"
```{{copy}}

### 2. Initialize the bpf subsystem

Before we can use any functionality from the bpf subsystem, we need to initialize its infrastructure.

```c
bpf_init();
```{{copy}}

### 3. Create and setup the container environment

Now we create our container environment.

```c
bpf_t bpf = {
        .application = helloworld_bin,
        .application_len = sizeof(helloworld_bin),
        .stack = _stack,
        .stack_size = sizeof(_stack),
};
bpf_setup(&bpf);
```{{copy}}

A container has a few attributes.

- *.application* holds the binary of the code that the container shall execute. "helloworld_bin" is not yet existing. We will tackle this later when we'll create the containerized application.
- *.stack* holds a previously allocated memory space that the container will be working with. This stack will be created in the next step.

### 4. Add pre-allocated stack for the virtual machine

Just as in the tutorials by Koen Zandberg, our container gets a memory space of 512 bytes.
Code that is running within the container can only use that block of memory, which assures the isolation aspect of containers.

```c
static uint8_t _stack[512] = { 0 };
```{{copy}}

### 5. Add binary for executable container code

This step might be a bit confusing at this moment. 

```c
#include "blob/container/helloworld/helloworld.bin.h"
```{{copy}}

### 6. Get container from thread argument

```c
bpf_t * bpf = (bpf_t *) arg;
```{{copy}}

```c
thread_create(stack, sizeof(stack),
        THREAD_PRIORITY_MAIN - 1, THREAD_CREATE_STACKTEST,
        container_thread, &bpf, "container");
```{{copy}}

### 7. Execute container

```c
int64_t result;
bpf_execute_ctx(bpf, NULL, sizeof(NULL), &result);
```{{copy}}

Now it is time to create the program that shall run within the container
`tutorial_helloworld/container/helloworld/helloworld.c`{{open}}.

### 8. Inclue BPF Helper function library

```c
#include "bpf/bpfapi/helpers.h"
```{{copy}}

### 9. Write program code using the bpf helper functions

```c
const char print_str[] = "Hello from container\n";
bpf_printf(print_str);
```{{copy}}

### 10. Add program binary to main program

Finally we need to add the compiled binary to the main program by specifying it as blob in our Makefile. `tutorial_helloworld/Makefile`{{open}}.

```
BLOBS += container/helloworld/helloworld.bin
```{{copy}}