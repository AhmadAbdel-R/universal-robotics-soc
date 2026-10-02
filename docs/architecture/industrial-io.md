# Industrial I/O Architecture

In addition to lightweight robotics interfaces (PWM, I2C), the Universal Robotics Controller provides a robust, protected suite of industrial interfaces intended for factory automation, PLC integration, and harsh environments.

## 24-V Digital Inputs
- **Count:** 2 to 4 inputs (Motherboard Rev A).
- **Reference IC:** TI ISO1212 or ADI/Maxim MAX22190.
- **Purpose:** Interface with inductive proximity sensors, limit switches, photoelectric sensors, and PLC outputs.
- **Requirements:** 24-V tolerance, surge protection, ESD protection, and IEC 61131-2 compatible behavior. Raw 24V is strictly isolated from STM32 GPIOs.

## 24-V Actuator Outputs
- **Count:** 2 outputs (Motherboard Rev A).
- **Reference IC:** TI TPS272C45 or ST IPS2050H.
- **Purpose:** Driving solenoids, pneumatic valves, relays, contactors, and small industrial actuators.
- **Requirements:** High-side drive, short-circuit protection, current limiting, thermal shutdown, inductive-load tolerance, and open-load diagnostics. 

## IO-Link Master
- **Count:** 1 port (Preferred).
- **Reference PHY:** ST L6360.
- **Architecture:** STM32MP257 (UART/Control) -> L6360 -> M12 A-coded Connector -> Smart Sensor/Actuator.
- **Purpose:** Communication with intelligent industrial sensors (pressure, distance, flow) and smart valves.

## RS-485 / Modbus
- **Count:** 1 interface.
- **Reference Transceiver:** TI THVD1450.
- **Purpose:** Modbus RTU communication, smart grippers, industrial motor drives, and PLC peripherals.
- **Requirements:** UART (TX/RX, DE/RE), termination footprint, TVS/ESD protection, and proper biasing provisions.

## CAN-FD Strategy
The baseline architecture features 3x CAN-FD using TI TCAN1044A transceivers. 
- **Isolated CAN Option:** One of these channels may optionally be populated with an isolated transceiver (e.g., TI ISO1042) to support long robot harnesses, ground potential differences, or separate actuator supplies.

## Encoders & Analog
- **Differential Encoders:** Utilizing proper differential receivers (A+, A-, B+, B-, Z+, Z-) feeding into STM32 hardware timers.
- **Industrial Analog (±10V / 4-20mA):** Offloaded to an isolated daughterboard utilizing an AFE like the AD4111.
- **Force/Torque/Load Cells:** Offloaded to a daughterboard utilizing a 24-bit programmable gain AFE like the ADS1235.
- **Resolver:** Offloaded to a daughterboard utilizing the AD2S1210.

## Safety & Servo Drive Signals
A connector architecture will reserve pins for interfacing to external safety hardware and servo drives (e.g., ESTOP_CH1, ESTOP_CH2, STO1, STO2, DRIVE_ENABLE, BRAKE_OUT). 
> **CRITICAL WARNING:** Exposing these signals **DOES NOT** make the board functionally safe or safety-certified (SIL/PL). Actual functional safety loops must be implemented in external, certified hardware architectures.

## Noise & EMC Mitigation
All industrial interfaces must incorporate TVS diodes, ESD protection, surge protection, and differential signaling where appropriate to survive harsh electrical environments.
