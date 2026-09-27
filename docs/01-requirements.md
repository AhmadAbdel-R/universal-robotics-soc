# Requirements

## 1. Universal Capability
- Must function as the core compute and control node for diverse robotics platforms including:
  - Aerial systems (Drones)
  - Ground vehicles (Rovers, Quadrupeds)
  - Robotic manipulation arms
  - Edge AI and vision-based systems

## 2. Core Compute
- **Linux Compatibility:** Required for ROS2 and high-level application processing.
- **AI/ML Acceleration:** Sufficient onboard compute (NPU/TPU/GPU) to handle real-time vision inference.
- **Real-Time Control:** Must include RTOS-capable cores (e.g., Cortex-R or Cortex-M) for deterministic actuator control.

## 3. Robotics Features
- Direct interfacing with motor controllers and ESCs.
- Integrated IMU and sensor inputs.
- Hardware-assisted encoder reading.

## 4. Interfaces & Connectivity
- Ethernet and Wi-Fi/Bluetooth for high-bandwidth communication and IoT.
- CAN-FD for robust intra-robot networking.
- **PCIe Support:** PCIe must be included for expanding the system to connect external GPUs or high-speed hardware accelerators later.

## 5. Constraints
- **Footprint:** Less than or equal to the Raspberry Pi 5 footprint.
- **Power Budget:** Balanced between passive and active cooling requirements based on use case.
