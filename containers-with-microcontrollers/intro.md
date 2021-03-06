# Containers on Microcontrollers
This tutorial will introduce you to the concept of Femto-Containers. A femto-container is, just like the name says, a small container that can be used 
to isolate applications on microcontrollers.

The concept of Femto-Containers was introduced by Koen Zandberg and Emmanuel Baccelli in their paper:
[Femto-Containers: DevOps on Microcontrollers with Lightweight Virtualization & Isolation for IoT Software Modules](https://arxiv.org/pdf/2106.12553.pdf).
While it is not required for you to read it to follow along in the tutorial, it is definitely an interesting read. It will also allow you to gain a greater understanding of FemtoContainers and their use cases.

## Goal
In this tutorial, you will gain insight into why running containers on a micro-controller can be useful, and how to code, compile and run simple applications using containers on a microcontroller.

You'll also become familiar with the real-time operating system `RIOT OS`, which is specifically adapated for embedded systems and the Internet of Things (IoT).

## Why is this useful?
You might be familiar with how normal containers work, and what the benefits of them are. However, running normal containers, like docker, on a microcontroller would not be possible; they don't have nearly enough processing power or resources.  

The solution is called [Femto-Containers](https://arxiv.org/pdf/2106.12553.pdf), which are based on [Linux eBPF](https://ebpf.io/what-is-ebpf). You can see how they compare at a glance in [Figure 1](https://raw.githubusercontent.com/EdmanJohan/katacoda-scenarios/master/containers-with-microcontrollers/assets/FemtoContainer-Katacoda.png).

<img align="right" src="./assets/FemtoContainer-Katacoda.png">

What are then the additional benefits? Mainly the fact that you can start applying DevOps workflows and use-cases to embedded microcontrollers or IoT devices. You can imagine the following scenarios, 
1. A device in the field misbehaves; can test the application in a containerized and controlled environment.  
2. You can allow 3rd party code to run, by sandboxing and isolating applications.  
Only giving access to e.g. sensors to allowed applications.  
4. Deploy changes to workloads without flashing new firmware with OTA Updates.  
5. Lightweight! Virtual machines are not possible due to limited resources.  
