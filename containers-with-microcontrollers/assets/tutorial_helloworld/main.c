#include <stdio.h>

/* (1) Add bpf libary header */

//placeholder(1)

/* (5) Add binary for executable container code */

//placeholder(5)

#include "sched.h"
#include "thread.h"
#include "ztimer.h"

/* (4) Add pre-allocated stack for the virtual machine */

//placeholder(4)

static void *container_thread(void *arg) {

    /* (6) Get container from thread argument */
    
    //placeholder(6)

    while (1) {
	    printf("Hello from thread\n");
        ztimer_sleep(ZTIMER_USEC, 500000);
        
        /* (7) Execute container */

	    //placeholder(7)
    }
    
    return arg;
}

int main(void) {
    /* (2) Initialize the bpf subsystem */

    //placeholder(2)

    puts("All up, running the Femto-Container application now");

    /* (3) Define the container */

    //placeholder(3)

    /* Create threads for containers */
    static char stack[THREAD_STACKSIZE_DEFAULT+THREAD_EXTRA_STACKSIZE_PRINTF];

    thread_create(stack, sizeof(stack),
                THREAD_PRIORITY_MAIN - 1, THREAD_CREATE_STACKTEST,
                container_thread, NULL, "container");

    return 0;
}