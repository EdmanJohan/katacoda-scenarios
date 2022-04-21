## Hello World in Femto-Container in RIOT OS Thread

Now it is about time to create our own little container application.
To save you some time, we will work upon an existing code-skelleton that you can find here: `\root\Femto-Container_tutorials\tutorial_helloworld\main.c`{{open}}.

The only thing happenig currently is, that we are creating a thread, that gets executed by the RIOT OS scheduler. This thread writes "Hello from thread" to stdout and then waits for 500ms. In this tutorial we will adjust the thread to execute a container, that runs code in an isolated environment.

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
        .application = helloworld_bin,              /* The system.bin content */
        .application_len = sizeof(helloworld_bin),  /* Length of the application */
        .stack = _stack,                            /* Preallocated stack */
        .stack_size = sizeof(_stack),               /* And the length */
    };
bpf_setup(&bpf_system);
```{{copy}}