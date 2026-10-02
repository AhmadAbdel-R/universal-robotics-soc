# Connector Architecture

The Universal Robotics Controller avoids using a single ubiquitous connector type for all signals. Instead, connector classes are selected based on the specific mechanical, electrical, and environmental demands of the interface. 

*Exact part numbers and SKUs will be finalized during the mechanical design phase.*

## 1. Internal Compact Robotics / UAV Signals
For lightweight, low-current signals routed internally within a robot chassis or drone frame.
- **Preferred Families:** JST-GH (1.25mm) or JST-SH (1.0mm).
- **Use Cases:** ESC telemetry/control, GNSS/GPS, ExpressLRS (CRSF), lightweight sensor ports, and internal I2C/SPI expansions.

## 2. Internal Power Distribution
For routing primary power from the battery or between power distribution boards and the motherboard.
- **Preferred Family:** Molex Micro-Fit 3.0.
- **Use Cases:** Main board power input, high-current internal power distribution, actuator daughterboard power.

## 3. High-Reliability Internal Signals
For vibration-prone systems (e.g., heavy AMRs, flight controllers) where standard friction-lock connectors may fail.
- **Preferred Family:** Harwin Gecko.
- **Use Cases:** High-reliability board-to-board connections, critical sensor harnesses.

## 4. Industrial External Sensor & Actuator
For field-wiring to industrial sensors, PLCs, and robust actuators that exit the main controller enclosure.
- **Preferred Families:** M12 A-coded (standard industrial) or M8 (space-constrained).
- **Use Cases:** IO-Link, 24-V digital inputs/outputs, RS-485/Modbus, industrial sensor buses.

## 5. Industrial Ethernet
- **Preferred Families:** M12 D-coded (100-Mbit class) or M12 X-coded (Gigabit class).
- **Use Cases:** Ruggedized industrial Ethernet connections where standard RJ45 is unsuitable. *(Note: These are optional variants; standard RJ45 is used for typical development/protected environments).*

## 6. Development & High-Speed
- **Preferred Families:** USB Type-C, RJ45 (with integrated magnetics), standard 0.1" debug headers, M.2 Key-M (PCIe).
- **Use Cases:** Flashing (STM32CubeProgrammer), standard networking, JTAG/UART debugging, NVMe/AI expansion.
