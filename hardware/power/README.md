# Power Subsystem

## Power Philosophy

Power can both:
- constrain the processor choice, and
- be created as a requirement by the processor choice.

For example:
Application Power Budget → Allowable SoC

But also:
Selected SoC → Core Rails → PMIC → Sequencing → Power-Good / Reset → Decoupling → PCB Current Distribution

Potential SoC rails may include:
- CPU
- GPU
- NPU
- SoC core
- DDR
- PLL / analog
- 1.8 V I/O
- 3.3 V I/O

## Requirements

| ID | Requirement | Priority | Verification | Status |
|---|---|---|---|---|
| PWR-001 | TBD | MUST | TBD | Open |

## Constraints
- TBD

## Open Details (To Be Defined)
- rail voltage
- current
- peak current
- sequencing
- startup timing
- PMIC channel
- switching frequency
- transient requirements
- decoupling
- power state
