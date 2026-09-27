# Universal Robotics Controller (URC)

A compact, reusable robotics compute platform intended to unify:

- Linux application processing
- Real-time control
- Onboard AI / vision
- Robotics I/O
- Integrated sensing
- High-speed connectivity
- Wireless / IoT capability

The goal is to create a **single reusable controller platform** that can support:

- Drones
- Rovers
- Robotic arms
- Quadrupeds
- Vision systems
- General embedded Linux / edge AI applications

---

## Why this project exists

Most robotics systems are built from multiple disconnected modules:

- SBC / compute board
- MCU / flight controller
- sensor breakout boards
- motor-control boards
- camera modules
- communication modules
- external accelerators

This project aims to reduce that fragmentation by exploring a **unified robotics controller architecture** that combines these functions into one compact platform.

---

## High-Level Questions

This repository starts with the system-definition phase. Before committing to a specific SoC or hardware architecture, the following questions need to be answered.

### 1) Project Scope
- What does “universal” mean in practice?
- Should the same board work across drones, rovers, quadrupeds, and robotic arms?
- What functions must always be present on-board?
- What functions should remain external?

### 2) Core Compute
- Which SoC best balances:
  - Linux capability
  - AI / ML acceleration
  - real-time support
  - documentation quality
  - package size / pitch
  - power consumption
  - cost
- Is PCIe a hard requirement?
- Is external hardware acceleration a must-have?

### 3) Robotics Features
- Which actuator interfaces should be supported directly?
- Which motor power stages should stay external?
- Should encoder interfaces be integrated on-board?
- Should CAN-FD become the main robotics bus?

### 4) Vision / AI
- How many camera interfaces are needed?
- Is onboard ISP required?
- What AI performance target is necessary?
- What memory size is required for practical ML workloads?

### 5) Connectivity
- Which interfaces are mandatory?
  - Ethernet
  - USB-C
  - High-speed USB
  - Wi-Fi / Bluetooth
  - CAN-FD
  - UART / SPI / I2C
  - PWM / GPIO
- Should M.2 / NVMe support be included?

### 6) Constraints
- Max board size: <= Raspberry Pi 5 footprint (ideally smaller)
- Cost target?
- Layer count target?
- Manufacturing constraints?
- Package pitch constraints?
- Thermal constraints?
- Power budget?

### 7) Novelty / Value
- What makes this architecture meaningfully different from:
  - Raspberry Pi
  - Jetson
  - traditional flight controllers
  - MCU + SBC stacks
- What is the strongest novel contribution?

---

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