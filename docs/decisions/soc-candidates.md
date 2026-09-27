# SoC Candidates

## PCB Manufacturing Context (JLCPCB)
Recent updates to JLCPCB's manufacturing capabilities include **free Via-in-Pad (POFV)** for 6 to 10-layer boards. This is a game-changer for BGA escape routing. It allows high-density 0.5 mm pitch BGAs to be escaped internally without requiring expensive HDI (High Density Interconnect) laser microvias. As a result, powerful 0.5 mm pitch SoCs like the NXP i.MX 8M Plus, RK3588, and Renesas RZ/V2H are much more viable candidates for cost-effective manufacturing.

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

### STM32MP257
**Strengths:**
- excellent real-time integration (Cortex-M33, Cortex-M0+)
- 0.8 mm pitch (TFBGA 436, 18x18 mm) simplifies PCB layout, no HDI required
- 1.35 TOPS NPU and 3D GPU
- excellent ST documentation and long-term industrial support
- 3x FD-CAN and 3x Gigabit Ethernet (with TSN)

**Trade-offs:**
- Dual-core Cortex-A35 is relatively low performance for heavy Linux/vision tasks
- NPU is smaller (1.35 TOPS) than Rockchip alternatives
- higher cost per compute than Chinese SoCs

### Texas Instruments AM68A
**Strengths:**
- 0.8 mm pitch (FCBGA 770, 23x23 mm) simplifies PCB layout, no HDI required
- high performance vision/AI (8 TOPS NPU, integrated ISP)
- dual-core Cortex-A72 for heavy applications
- excellent real-time safety architecture (dual Cortex-R5F)
- exceptional industrial documentation and support

**Trade-offs:**
- very large footprint (23x23 mm)
- likely expensive
- higher power consumption

### Texas Instruments AM62A
**Strengths:**
- 0.8 mm pitch (FCBGA 484, 18x18 mm) simplifies PCB layout, no HDI required
- 2 TOPS NPU
- Quad-core Cortex-A53
- single Cortex-R5F for real-time
- balanced power/performance/cost for mid-tier robotics

**Trade-offs:**
- lower compute performance than RK3576 or AM68A
- still slightly more expensive than Rockchip options

### NXP i.MX 8M Plus
**Strengths:**
- 2.3 TOPS NPU
- Quad Cortex-A53 + Cortex-M7 real-time core
- 0.5 mm pitch (15x15 mm), which is now highly viable with free JLCPCB via-in-pad for 6-10 layers
- dual Gigabit Ethernet (one with TSN), dual CAN-FD, PCIe Gen3
- excellent NXP industrial documentation, mainline Linux support, and 15-year longevity
- extremely proven ecosystem with many open-source reference boards

**Trade-offs:**
- **Compute ceiling:** Cortex-A53 cores are getting older and offer lower single-thread performance than A55/A72/A76 cores.
- **AI limitations:** 2.3 TOPS is excellent for standard vision (YOLO, object detection), but may struggle with very heavy models compared to 6-8 TOPS chips.
- **Cost:** Significantly higher chip cost compared to alternatives like Rockchip or Allwinner.
- **Power consumption:** Manufactured on 14nm FinFET; highly efficient but older node compared to modern 8nm chips, meaning it can run warmer under full load.
- **RAM Routing:** While VIP (via-in-pad) solves escape routing, strict length-matched LPDDR4 routing is still required, keeping PCB layout complex.

## Candidate Comparison Table

| SoC | CPU cores | Real-time cores | NPU TOPS | BGA pitch | Availability |
|---|---|---|---|---|---|
| **RK3576** | 4xA72 + 4xA53 | TBD | 6 | ~0.6 mm | [LCSC](https://www.lcsc.com/) |
| **i.MX 95** | up to 6xA55 | M7 + M33 | TBD | ~0.7 mm | Unverified |
| **RK3588** | 4xA76 + 4xA55 | TBD | 6 | 0.55 mm | [LCSC](https://www.lcsc.com/) |
| **RZ/V2H** | 4xA55 | 2xR8 + M33 | High | ~0.5 mm | Unverified |
| **STM32MP257** | 2xA35 | M33 + M0+ | 1.35 | 0.8 mm | Unverified |
| **TI AM68A** | 2xA72 | 2xR5F | 8 | 0.8 mm | Unverified |
| **TI AM62A** | 4xA53 | 1xR5F | 2 | 0.8 mm | Unverified |
| **i.MX 8M Plus** | 4xA53 | M7 | 2.3 | 0.5 mm | Verified |

*(Table to be expanded as evaluation continues)*
