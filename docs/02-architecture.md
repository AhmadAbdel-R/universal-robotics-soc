# Architecture

The Universal Robotics Controller (URC) architecture is designed to merge high-level computational tasks with low-level real-time actuation. 

## High-Level Block Diagram

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
