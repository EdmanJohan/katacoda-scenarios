## Hello World in Femto-Container in RIOT OS Thread

Now it is about time to create our own little container application.
To save some time, we will work upon an existing code-skelleton that you can find here: `tutorial_helloworld/main.c`{{open}}.

The only thing happening currently is, that a thread is created, that gets executed by the RIOT OS scheduler. This thread writes "Hello from thread" to stdout and then waits for 500ms. 

You can execute it and see for yourself.

```sh
make -C Femto-Container_tutorials/tutorial_helloworld  all term
```{{execute interrupt}}

In the following steps we will adjust the thread to execute a container, that runs code in an isolated environment. 

Each step holds holds code that needs to be inserted for the placeholder with the respective steps number.

### 1. Add bpf library for femto-containers

First, we need to include the header for using the bpf subsystem within RIOT OS, which implements everything needed to work with femto-containers.

<pre class="file" data-filename="./tutorial_helloworld/main.c" data-target="insert" data-marker="//placeholder(1)">
#include "bpf.h"
</pre>

### 2. Initialize the bpf subsystem

Before we can use any functionality from the bpf subsystem, we need to initialize its infrastructure.

<pre class="file" data-filename="./tutorial_helloworld/main.c" data-target="insert" data-marker="//placeholder(2)">
bpf_init();
</pre>

### 3. Create and setup the container environment

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

### 4. Add pre-allocated stack for the virtual machine

Just as in the tutorials by Koen Zandberg, our container gets a memory space of 512 bytes.
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
Since we want to be able to assign applications that run inside containers dynamicly,
we can not define them as global variables. Thus, they must be given to the thread as parameter.

In this step we make sure to correctly dereference the void pointer that is given to the thread function as parameter.

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
At the current state of the femto container project it is necessary to have a variable, to store the return value of the code, 
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

Let's compile the helloworld program!

```sh
make -C Femto-Container_tutorials/tutorial_helloworld/container/helloworld
```{{execute interrupt}}

### 10. Add program binary to main program

Finally we need to add the compiled binary to the main program by specifying it as blob in our Makefile. `tutorial_helloworld/Makefile`{{open}}.

<pre class="file" data-filename="./tutorial_helloworld/Makefile" data-target="insert" data-marker="#placeholder(10)">
BLOBS += container/helloworld/helloworld.bin
</pre>

```sh
make -C Femto-Container_tutorials/tutorial_helloworld all term
```{{execute interrupt}}