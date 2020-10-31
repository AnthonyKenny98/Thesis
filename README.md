# if goingToCrash: Don't
> RISC-V Architecture for Motion Planning Algorithms in Autonomous UAVs

This repository holds the working files of my Senior Thesis, submitted in partial fulfillment of the requirements for the degree of Bachelor of Science in Electrical Engineering at Harvard University.

![ifgoingtocrash](Writeups/4_Report/chapters/chapter1/img/ifgoingtocrash.png)

This thesis presents an extension for the RISC-V Instruction Set Architecture (ISA) for the purpose of faster motion planning in autonomous Unmanned Aerial Vehicles (UAVs). Fully autonomous UAVs have the potential to change the world in which we live, but they are currently unable to pilot themselves in high-complexity, obstacle-dense environments; The processors that they employ cannot execute motion planning software quickly enough. RISC-V is a relatively new ISA that is founded on the principles of open-source and extendibility, making it an excellent ecosystem for designing application specific processors. However, as of April 2020, no attempts had been made to develop motion planning archi- tecture within the RISC-V ecosystem.
This thesis serves as a proof-of-concept for accelerating motion planning with RISC-V architecture. It presents the implementation of “HoneyBee”, a microarchitectural unit that can compute collision detection over 5 times faster than a general-purpose Intel CPU. More significantly, it defines a motion planning extension for RISC-V that simplifies the number of instructions required to detect an edge collision from hundreds of thousands to only one. These promising results demonstrate the viability of the approach, and should en- courage developers to embrace RISC-V in the development of motion planning processors for autonomous drones.

The final report can be found [here](Writeups/4_Report/obj/report.pdf)

## Table of Contents
+ [Repository Structure](#structure)
	
## <a name=#structure></a>Repository Structure
+ Research: This folder holds the academic papers that constitute the background research of this Thesis.
+ Writeups: This folder holds the writeups required for this Thesis.
+ [RRT](https://github.com/AnthonyKenny98/RRT): Subrepository holding the C implementation of RRT
+ [PhilosophyV](https://github.com/AnthonyKenny98/PhilosophyV): Subrepository holding Verilog implementation of PhilosophyV RISC-V Processor 
+ [HoneyBee](https://github.com/AnthonyKenny98/HoneyBee): Subrepository holding High-Level Synthesis implementation of edge collision detection unit.

