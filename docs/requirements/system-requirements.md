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
| MEM-001 | System shall support ≥512 MB RAM | MUST | Inspection / Boot Test | Open |
| PWR-001 | Low-power and high-performance operating modes desirable | SHOULD | Measurement | Open |
| HSI-001 | At least one PCIe interface strongly preferred | SHOULD | Inspection | Open |
| RIO-001 | CAN-FD strongly preferred | SHOULD | Test | Open |
| PCB-001 | Initial target approximately 6–10 layers | MUST | Inspection | Open |

*(More to be added as architecture solidifies)*

## Open Numerical Requirements

- **maximum board dimensions**: TBD
- **standardized mounting-hole pattern**: TBD
- **maximum processor cost**: TBD
- **maximum complete BOM**: TBD
- **maximum power consumption**: TBD
- **idle power target**: TBD
- **maximum component height**: TBD
- **target operating temperature**: TBD
- **number of camera interfaces**: TBD
- **minimum PCIe lane count**: TBD
- **minimum USB count**: TBD
- **minimum CAN count**: TBD
- **target RAM**: TBD
- **target storage**: TBD
- **thermal limits**: TBD
