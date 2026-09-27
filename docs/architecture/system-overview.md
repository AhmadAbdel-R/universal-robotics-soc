# System Architecture Overview

## High-Level System Block Diagram

This is the broadest view of the system: the board as a universal robotics brain.

```mermaid
flowchart LR
    PWR[External Power System] --> URC[Universal Robotics Controller]
    CAM[Camera / Vision Inputs] --> URC
    SENS[Onboard + External Sensors] --> URC
    NET[Ethernet / Wi-Fi / USB / IoT] <--> URC
    ACT[Actuators / ESCs / Servo Drives / Stepper Drivers] <--> URC
    UI[Debug / Desktop / Dev Interfaces] <--> URC
    STO[Local Storage / eMMC / NVMe / SD] <--> URC
```

## Internal Architecture

```mermaid
flowchart TD
    subgraph Compute Domain
        A[Linux OS - High Level Apps]
        B[AI Accelerator / NPU]
        C[PCIe Interface]
    end

    subgraph Real-Time Domain
        D[RTOS - Motor Control]
        E[Sensor Hub / IMU]
    end

    subgraph External
        F[External GPU via PCIe]
        G[Camera / Vision]
        H[Motor Drivers / ESCs]
    end

    A <--> B
    A <--> C
    A <--> D
    C <--> F
    G --> B
    D <--> H
    E --> D
```

## PCIe Acceleration Note
As robotics applications increasingly rely on foundation models and complex 3D perception, the onboard NPU may not suffice for all use cases. Therefore, the architecture incorporates **PCIe** to allow the connection of an external GPU later for heavier acceleration workloads.

## Core Modules
- **Application Processor:** Manages ROS2, networking, and user logic.
- **Co-Processor / MCU:** Handles tight timing loops, safety overrides, and PID controllers.
- **Vision Pipeline:** Dedicated ISP and MIPI CSI lanes for camera ingestion.
