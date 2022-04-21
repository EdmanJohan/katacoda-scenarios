#include <stdio.h>

/* (1) Add bpf libary header */

//placeholder

/* (4) Add binary for executable container code

//placeholder

#include "sched.h"
#include "thread.h"
#include "ztimer.h"

/* (3) Add pre-allocated stack for the virtual machine */

//placeholder

static void *container_thread(void *arg) {

    /* (5) Get container from thread argument */

    //placeholder

    while (1) {
	  printf("Hello from thread\n");
        ztimer_sleep(ZTIMER_USEC, 500000);

	  /* (6) Execute container */

	  //placeholder

    }
    
    return arg;
}

int main(void) {
     /* (5) Initialize the bpf subsystem */

    //placeholder

    puts("All up, running the Femto-Container application now");

    /* (2) Define the container */

    //placeholder

    /* Create threads for containers */
    static char stack[THREAD_STACKSIZE_DEFAULT+THREAD_EXTRA_STACKSIZE_PRINTF];
    thread_create(stack, sizeof(stack),
                THREAD_PRIORITY_MAIN - 1, THREAD_CREATE_STACKTEST,
                container_thread, NULL, "container");

    return 0;
}