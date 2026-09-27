# SoC Candidates

## Current Important Candidates

### Rockchip RK3576
**Strengths:**
- excellent compute-per-dollar
- 4× Cortex-A72, 4× Cortex-A53
- 6 TOPS NPU
- GPU
- LPDDR support
- PCIe, SATA, USB 3, dual Ethernet, CAN-FD, MIPI
- large low-speed peripheral set
- approximately 0.6 mm BGA
- very inexpensive compared with alternatives

**Trade-offs:**
- weaker integrated real-time architecture
- documentation / hardware ecosystem not as strong as NXP/TI
- may require an external MCU for deterministic robotics control

### NXP i.MX 95
**Strengths:**
- heterogeneous architecture
- Cortex-A55 application cores
- Cortex-M7, Cortex-M33
- NPU
- strong networking (TSN), CAN-FD, PCIe, USB
- excellent NXP documentation
- industrial support
- 19 mm variant uses attractive ~0.7 mm pitch

**Trade-offs:**
- significantly more expensive
- lower application CPU/NPU performance-per-dollar than RK3576
- larger system BOM may result

### Rockchip RK3588
**Strengths:**
- very strong CPU (A76 + A55)
- strong GPU
- 6 TOPS NPU
- PCIe Gen3 x4
- excellent Linux / desktop-style compute

**Trade-offs:**
- more expensive
- higher power
- larger package
- weaker real-time architecture

### Renesas RZ/V2H
**Strengths:**
- Linux cores
- dual Cortex-R8, Cortex-M33
- very strong AI accelerator
- PCIe Gen3 x4
- industrial interfaces
- very strong robotics architecture

**Trade-offs:**
- 1368-ball BGA
- approximately 0.5 mm pitch
- significantly more difficult escape routing / HDI
- cost
- board manufacturing complexity

## Candidate Comparison Table

| Parameter | RK3576 | i.MX 95 | RK3588 | RZ/V2H |
|---|---|---|---|---|
| CPU architecture | ARMv8 | ARMv8 | ARMv8 | ARMv8 |
| CPU cores | 4xA72 + 4xA53 | up to 6xA55 | 4xA76 + 4xA55 | 4xA55 |
| Real-time cores | TBD | M7 + M33 | TBD | 2xR8 + M33 |
| NPU TOPS | 6 | TBD | 6 | High |
| BGA pitch | ~0.6 mm | ~0.7 mm | TBD | ~0.5 mm |
| LCSC availability | [Search](https://www.lcsc.com/) | Not currently verified | [Search](https://www.lcsc.com/) | Not currently verified |
*(Table to be expanded as evaluation continues)*
