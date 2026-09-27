# Subsystem Templates

This document provides the standard template to be used when detailing individual hardware and software subsystems within the URC project.

## Template Structure

### 1. Subsystem Name & Overview
- **Description:** Brief summary of the subsystem's purpose.
- **Key Components:** Primary ICs, connectors, or software modules involved.

### 2. Interfaces
- **Inputs:** Upstream data/power sources.
- **Outputs:** Downstream data/power sinks.
- **Protocols:** (e.g., I2C, SPI, CAN-FD, MIPI).

### 3. Constraints & Requirements
- **Power:** Voltage levels, expected current draw.
- **Physical:** Placement constraints, thermal considerations.
- **Signal Integrity:** Impedance matching, length matching rules.

### 4. Risk Assessment
- Potential failure points.
- Mitigation strategies (e.g., ESD protection, fallback states).

---

*Example Subsystems to be defined using this template:*
- Power Delivery & Management
- Vision & Image Signal Processing (ISP)
- Real-Time Actuator Control
- High-Speed Communications (PCIe, Ethernet)
