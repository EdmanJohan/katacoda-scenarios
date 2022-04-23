After understanding how to basically set up femto-containers on microcontrollers,
we now want to touch on a more advanced topic.

Since each container has an individual memory space to operate on, we can not use global variables from within them.
However, we still want to have the capability of sharing information between them.

Let's say we have i. e. a sensor driver running inside a container. We need a possibility to make the sensor measurements usable also outside the container. Femto containers offer a concept called: *key-value store* to solve this problem.

Using reference keys, container-hosted applications can load and store simple values in persistent storage. Those read and write commands are implemented via a set of system calls.

For globally shared values:
- int bpf_store_update_global(uint32_t key, uint32_t value) 
- int bpf_store_fetch_global(uint32_t key, uint32_t *value)

For locally shared values:
- int bpf_store_update_local(uint32_t key, uint32_t value)
- int bpf_store_fetch_local(uint32_t key, uint32_t *value)

We will investigate how the key-value store can be used, with a little example application.

## Main program

`tutorial_lunarlander/main.c`{{open}}

This opens two threads, that run a Femto-container each. 
Let's check out the applications that get hosted in them.

## System container

`tutorial_lunarlander/container/system/system.c`{{open}}

This containerized application emulates a rocket that is 64000m above the surface of the moon.
The rocket has 7200l of fuel to ensure a safe landing. The parameter fuel_rate which gets fetched
in line 67 from the key-value store specifies the amount of fuel that should be used to slow down the rocket.

```c
bpf_fetch_global(FUEL_RATE, &fuel_rate);
```

## Fuel control container

`tutorial_lunarlander/container/fuel/fuel.c`{{open}}

The fuel_rate gets set, by another containerized application. 

```c
bpf_store_global(FUEL_RATE, (fuel_rate << REF_FACT));
```

Note, that we bitshift the fuel_rate to the left, to store its value in the key-value storage with higher resolution.
This is because the current implementation doesn't allow storing floating-point numbers.

## Key values

`tutorial_lunarlander/container/key_value_store.h`{{open}}

The reference key for the fuel_rate is specified as a preprocessor define. This way, we can have a good overview of which keys are used for what.

## Execution

Let's execute to see the program's behavior.

```sh
make -C tutorial_lunarlander/container/system
make -C tutorial_lunarlander/container/fuel
make -C tutorial_lunarlander/ all term
```{{execute interrupt}}

Can you land on the moon safely?
