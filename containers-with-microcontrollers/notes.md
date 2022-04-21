

## Why is this useful?

- Use case: A device in the field misbehaves, can test in a containerized/controlled environment!
- 3rd party code running, can sanbdox and isolate applications
- Can modify workload without flashing new firmware / OTA Updates
- Virtual machines not possible due to resource constraints

# Step 1

Simple Case to set up containers from scratch

- Template for RIOT OS Thread
- Add bpf-header and code to main.c
- Show that main doesn't compile
- Create container hello.c and compile with llvm
- Show output as hex
- Compile and execute main

# Step 2

- Lunar Lander example for key value store

