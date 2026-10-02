# System Block Diagram

This document illustrates the comprehensive block diagram for the universal robotics controller based on the STM32MP257.

```mermaid
flowchart TD
    %% Power Subsystem
    subgraph Power
        BAT[2S-8S Battery Input] --> PROT[Protection]
        PROT --> COMP_PATH[Compute Power Path]
        PROT --> ACT_PATH[Actuator Power Path]
        COMP_PATH --> VIN_SYS[VIN_SYS]
        VIN_SYS --> PMIC[PMICs]
        PMIC --> SOC_PWR[Compute Power]
        ACT_PATH --> ACT_PWR_RAW[ACT_PWR_RAW]
    end

    %% STM32MP257 SoC
    subgraph STM32MP257
        SOC_PWR --> A35[Cortex-A35 Linux]
        SOC_PWR --> M33[Cortex-M33 Real-Time]
    end

    %% Peripherals & Memory
    subgraph Memories and High Speed
        A35 <--> LPDDR4[LPDDR4]
        A35 <--> EMMC[eMMC]
        A35 <--> NOR[NOR Flash]
        A35 <--> M2[M.2 Interface]
        A35 <--> ETH1[Ethernet 1]
        A35 <--> ETH2[Ethernet 2]
        A35 <--> USB[USB Interfaces]
        A35 <--> CSI[Camera CSI]
        A35 <--> DSI[Display DSI/HDMI]
        A35 <--> WIFI_BT[Wi-Fi / BT]
    end

    %% Real-Time & Sensors
    subgraph Real-Time & Industrial IO
        M33 <--> IMU[IMU]
        M33 <--> MAG[Magnetometer]
        M33 <--> BARO[Barometer]
        M33 <--> CAN1[CAN FD 1]
        M33 <--> CAN2[CAN FD 2]
        M33 <--> CAN3[CAN FD 3]
        M33 <--> ELRS[ELRS RC]
        M33 <--> GNSS[GNSS Receiver]
        M33 <--> ENC[Encoders]
        M33 <--> IND_IO[Industrial I/O]
    end

    %% Actuation
    subgraph Actuators
        ACT_PWR_RAW --> SERVOS[Servos]
        ACT_PWR_RAW --> ESC[ESC / Motor Controllers]
        ACT_PWR_RAW --> OTHER_ACT[Other Actuators]
    end

    M33 -.-> SERVOS
    M33 -.-> ESC
```

**THEORY**: The compute and actuator power paths must remain physically and logically separated until the point of main distribution to prevent actuator noise from compromising compute stability.
