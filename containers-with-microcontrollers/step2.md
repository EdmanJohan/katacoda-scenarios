Now it is about time to create our own little container application.
To save some time, we will work upon an existing code-skeleton that you can find here: `tutorial_helloworld/main.c`{{open}}.

The only thing happening currently is, that a thread is created, that gets executed by the RIOT OS scheduler. This thread writes "Hello from thread" to stdout and then waits for 500ms before it repeats.

You can execute it and see for yourself.

```sh
make -C tutorial_helloworld all term
```{{execute interrupt}}

In the following steps, we will adjust the thread to execute a container, that runs code in an isolated environment. 

Each step holds code that needs to be inserted for the placeholder with the number of the respective step.

### 1. Add bpf library for Femto-containers

First, we need to include the header for using the bpf subsystem within RIOT OS, which implements everything needed to work with Femto-containers.

<pre class="file" data-filename="./tutorial_helloworld/main.c" data-target="insert" data-marker="//placeholder(1)">
#include "bpf.h"
</pre>

### 2. Initialize the bpf subsystem

Before we can use any functionality from the bpf subsystem, we need to initialize its infrastructure.

<pre class="file" data-filename="./tutorial_helloworld/main.c" data-target="insert" data-marker="//placeholder(2)">
bpf_init();
</pre>

### 3. Create and set up the container environment

Now we create our container environment.

<pre class="file" data-filename="./tutorial_helloworld/main.c" data-target="insert" data-marker="//placeholder(3)">
bpf_t bpf = {
        .application = helloworld_bin,
        .application_len = sizeof(helloworld_bin),
        .stack = _stack,
        .stack_size = sizeof(_stack),
    };
    bpf_setup(&bpf);
</pre>

A container has a few attributes:

- *.application* holds the binary of the code that the container shall execute. "helloworld_bin" is not yet existing. We will tackle this later when we'll create the containerized application.
- *.stack* holds a previously allocated memory space that the container will be working with. This stack will be created in the next step.

### 4. Add a pre-allocated stack for the virtual machine

Dictated by the eBPF specification, our container gets a memory space of 512 bytes.
Code that is running within the container can only use that block of memory, which assures the isolation aspect of containers.

<pre class="file" data-filename="./tutorial_helloworld/main.c" data-target="insert" data-marker="//placeholder(4)">
static uint8_t _stack[512] = { 0 };
</pre>

### 5. Add binary for executable container code

The application "helloworld_bin" must still be created.
We will later find it as a constant byte array in the following header.
This step might be confusing now, but we'll come back to this later to clear it up.

<pre class="file" data-filename="./tutorial_helloworld/main.c" data-target="insert" data-marker="//placeholder(5)">
#include "blob/container/helloworld/helloworld.bin.h"
</pre>

### 6. Get container from thread argument

We want to execute our container from within a RIOT OS thread.
Since we want to be able to assign applications that run inside containers dynamically,
we can not define them as global variables. Thus, they must be given to the thread as a parameter.

In this step, we make sure to correctly dereference the void pointer that is given to the thread function as a parameter.

<pre class="file" data-filename="./tutorial_helloworld/main.c" data-target="insert" data-marker="//placeholder(6)">
bpf_t * bpf = (bpf_t *) arg;
</pre>

Of course, we also have to make sure, that we actually pass the bpf container, when we create the thread.
For that, we need to adjust the 6th parameter of the thread_create function, as shown below.

```c
thread_create(stack, sizeof(stack),
        THREAD_PRIORITY_MAIN - 1, THREAD_CREATE_STACKTEST,
        container_thread, &bpf, "container");
```{{copy}}

### 7. Execute container

Last but not least, we add the command "bpf_execute_ctx()" to execute the container to the thread callback function body.
At the current state of the Femto-container project, it is necessary to have a variable, to store the return value of the code, 
that is executed in the container, even if it is not used.

<pre class="file" data-filename="./tutorial_helloworld/main.c" data-target="insert" data-marker="//placeholder(7)">
int64_t result;
	bpf_execute_ctx(bpf, NULL, sizeof(NULL), &result);
</pre>

Now it is time to create the program that shall run within the container
`tutorial_helloworld/container/helloworld/helloworld.c`{{open}}.

### 8. Include BPF Helper function library

Since the code that is running within the container is interpreted, we can only use functions that have already been implemented in the interpreter.
Those can be found in the following file.

<pre class="file" data-filename="./tutorial_helloworld/container/helloworld/helloworld.c" data-target="insert" data-marker="//placeholder(8)">
#include "bpf/bpfapi/helpers.h"
</pre>

### 9. Write program code using the bpf helper functions

Our program is supposed to only print a string to stdio.
Note: The "bpf_printf()" expects a string constant.

<pre class="file" data-filename="./tutorial_helloworld/container/helloworld/helloworld.c" data-target="insert" data-marker="//placeholder(9)">
const char print_str[] = "Hello from container\n";
	bpf_printf(print_str);
</pre>

Let's compile the helloworld program and look at the compiled binary file!

```sh
make -C Femto-Container_tutorials/tutorial_helloworld/container/helloworld
```{{execute interrupt}}

```sh
./Femto-Container_tutorials/RIOT/dist/tools/rbpf/gen_rbf.py dump Femto-Container_tutorials/tutorial_helloworld/container/helloworld/helloworld.bin
```{{execute interrupt}}

In the next step, those binary symbols will get transferred to the constant byte array "helloworld_bin", that we encountered in step 4.

### 10. Add program binary to the main program

This is done fully automatically by the routine in the Makefile for the main application: `tutorial_helloworld/Makefile`{{open}}.
We only have to add the respective binary as a blob to the Makefile.

<pre class="file" data-filename="./tutorial_helloworld/Makefile" data-target="insert" data-marker="#placeholder(10)">
BLOBS += container/helloworld/helloworld.bin
</pre>

## Execution

Now, that everything is set up, we can finally build the program.

```sh
make -C tutorial_helloworld all
```{{execute interrupt}}

This means we can finally see where our program is stored.
`tutorial_helloworld/bin/native/application_bpf_tutorial/blobs/blob/container/helloworld/helloworld.bin.h`{{open}}.

This byte array "helloworld_bin" can of course also be dynamically created. I. e. after fetching it from some server.

In the final step, let's confirm that our program is running correctly.

```sh
make -C Femto-Container_tutorials/tutorial_helloworld term
```{{execute interrupt}}
