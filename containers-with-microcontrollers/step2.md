## Hello World in Femto-Container in RIOT OS Thread

Now it is about time to create our own little container application.
To save you some time, we will work upon an existing code-skelleton that you can find here: `tutorial_helloworld/main.c`{{open}}.

The only thing happenig currently is, that we are creating a thread, that gets executed by the RIOT OS scheduler. This thread writes "Hello from thread" to stdout and then waits for 500ms. 

You can execute it by running:

```sh
cd Femto-Container_tutorials/tutorial_helloworld 
make all term
```{{execute interrupt}}

In this tutorial we will adjust the thread to execute a container, that runs code in an isolated environment.

### 1. Add bpf library for femto-containers

```c
#include "bpf.h"
```{{copy}}

### 2. Initialize the bpf subsystem

```c
bpf_init();
```{{copy}}

### 3. Create and setup the container environment

```c
bpf_t bpf_system = {
        .application = helloworld_bin,
        .application_len = sizeof(helloworld_bin),
        .stack = _stack,
        .stack_size = sizeof(_stack),
    };
bpf_setup(&bpf_system);
```{{copy}}

### 4. Add binary for executable container code

```c
#include "blob/container/helloworld/helloworld.bin.h"
```{{copy}}

### 5. Add pre-allocated stack for the virtual machine

```c
static uint8_t _stack[512] = { 0 };
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