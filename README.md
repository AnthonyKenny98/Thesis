# if goingToCrash: Don't
> RISC-V Architecture for Motion Planning Algorithms in Autonomous UAVs

This repository holds the working files of my Senior Thesis, submitted in partial fulfillment of the requirements for the degree of Bachelor of Science in Electrical Engineering at Harvard University.

![ifgoingtocrash](Writeups/4_Report/chapters/chapter1/img/ifgoingtocrash.png)

This thesis aims to design RISC-V computer architecture that supports the fast execution of motion planning algorithms for drone applications. First, the computation of sampling-based motion planning algorithms commonly used in autonomous drones (such as RRT, RRT, PRM) will be profiled on an unmodified RISC-V processor. From this profiling, common bottlenecks and hotspots in execution will be identified. Based on these results, this project will extend the RISC-V ISA and design a modified processor to support the extensions.

## Table of Contents
+ [Repository Structure](#structure)
	
## <a name=#structure></a>Repository Structure
+ [Research](#research)
+ [Writeups](#writeups)
+ [RRT](#rrt)
+ [PhilosophyV](#phil_v)
+ [HoneyBee](#honeybee)


### <a name=#research></a>Research
This folder holds the academic papers that constitute the background research of this Thesis.

### <a name=#writeups></a>Writeups
This folder holds the writeups required for this Thesis.
- Includes checkpoints in fulfillment of Harvard's ES100hf class.
- Includes Final Report

### <a name=#rrt></a>RRT
This subrepository holds:
	- 3D capable Rapidly Exploring Random Tree implementation in C.
	- Python implemented analysis tool for running Top Down Analysis of CPU performance.

### <a name=#phil_v></a>PhilosophyV
This subrepository holds the PhilosophyV RISCV chip

### <a name=honeybee></a>HoneyBee
This subrepository holds the HoneyBee functional unit, a hardware implementation of collision detection.
