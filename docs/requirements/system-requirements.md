# System Requirements

## External Peripherals & Protocol Influence

The choice of external peripherals directly dictates the necessary on-board protocols, which in turn influences the SoC selection. For example:
- **LiDAR / High-bandwidth Sensors:** May require Gigabit Ethernet or PCIe.
- **Machine Vision / Cameras:** Necessitates multiple MIPI CSI lanes and potentially an onboard ISP.
- **Motor Controllers / Actuators:** Demand robust real-time buses like CAN-FD or EtherCAT.
- **IMUs and Low-level Sensors:** Require low-latency SPI or I2C/I3C interfaces.

These external demands act as strict constraints on the central processing architecture.

## Formal Requirements


| ID | Requirement | Priority | Verification | Status |
|---|---|---|---|---|
| SYS-001 | Platform shall support Linux | MUST | Boot Test | Open |
| SYS-002 | All BOM components MUST be natively sourced from the LCSC catalog to ensure low-cost JLCPCB assembly | MUST | BOM Review | Open |
| MEM-001 | Target 4 GB LPDDR4 | MUST | Inspection | Open |
| PCB-001 | Initial target approximately 6–10 layers | MUST | Inspection | Open |
| **SENSOR** | | | | |
| SEN-001 | Onboard IMU | MUST | Inspection | Open |
| SEN-002 | Onboard Magnetometer | MUST | Inspection | Open |
| SEN-003 | External Magnetometer Option | MUST | Inspection | Open |
| SEN-004 | Onboard Barometer | MUST | Inspection | Open |
| SEN-005 | Optional Shock Sensor (High-G) | SHOULD | Inspection | Open |
| SEN-006 | Clean Sensor Power Rail (LDO) | MUST | Inspection | Open |
| **MOTOR** | | | | |
| MOT-001 | Four deterministic motor outputs (PWM / DShot / bidirectional) | MUST | Test | Open |
| MOT-002 | ESC telemetry input | MUST | Test | Open |
| MOT-003 | Battery voltage monitoring | MUST | Test | Open |
| MOT-004 | Current monitoring | MUST | Test | Open |
| **ACTUATOR** | | | | |
| ACT-001 | Incremental encoder interface (A/B/Z) | MUST | Test | Open |
| ACT-002 | Absolute encoder support | MUST | Test | Open |
| ACT-003 | STEP / DIR interface | MUST | Test | Open |
| ACT-004 | Resolver expansion support | SHOULD | Inspection | Open |
| ACT-005 | Load-cell expansion support | SHOULD | Inspection | Open |
| ACT-006 | Drive fault / enable support | MUST | Test | Open |
| **INDUSTRIAL** | | | | |
| IND-001 | RS-485 interface | MUST | Test | Open |
| IND-002 | IO-Link Master port | MUST | Test | Open |
| IND-003 | Isolated CAN-FD option | SHOULD | Inspection | Open |
| IND-004 | 24-V industrial digital input | MUST | Test | Open |
| IND-005 | Protected 24-V output | MUST | Test | Open |
| IND-006 | Optional ±10 V / 4–20 mA expansion | SHOULD | Inspection | Open |
| **WIRELESS** | | | | |
| WIR-001 | Integrated Wi-Fi (Dual-Band) | MUST | Test | Open |
| WIR-002 | Integrated Bluetooth | MUST | Test | Open |
| WIR-003 | PCB / external antenna development path | MUST | Inspection | Open |
| **NAVIGATION** | | | | |
| NAV-001 | GNSS / GPS UART interface | MUST | Test | Open |
| NAV-002 | PPS timing input | MUST | Test | Open |
| NAV-003 | ELRS / CRSF UART interface | MUST | Test | Open |
| **DISPLAY/CAM** | | | | |
| DIS-001 | MIPI DSI Display | MUST | Inspection | Open |
| DIS-002 | HDMI output (via Bridge) | MUST | Inspection | Open |
| CAM-001 | MIPI CSI Camera interface | MUST | Inspection | Open |
| **USB** | | | | |
| USB-001 | USB 2.0 High-Speed Recovery / Device | MUST | Test | Open |
| USB-002 | USB 2.0 High-Speed Host | MUST | Test | Open |
| USB-003 | PCIe / USB3 COMBOPHY shared constraint | MUST | Inspection | Open |
| **EXPANSION** | | | | |
| EXP-001 | External I2C/I3C | MUST | Test | Open |
| EXP-002 | External SPI | MUST | Test | Open |
| EXP-003 | Environmental / CO2 expansion | SHOULD | Inspection | Open |
| EXP-004 | Rugged industrial connector variants | MUST | Inspection | Open |

## Open Numerical Requirements

- **maximum board dimensions**: TBD
- **standardized mounting-hole pattern**: TBD
- **maximum power consumption**: TBD
- **maximum component height**: TBD
