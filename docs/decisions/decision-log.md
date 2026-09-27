# Engineering Decision Log

## ADR-001 — Main Processor Selection

**Status:** Accepted

### Context
The project requires a central compute architecture to unify application processing, real-time control, AI inference, and robotics I/O.

### Requirements
- Linux support
- AI / NPU accelerator
- Real-time capabilities (integrated or external)
- Specific IO: PCIe, CAN-FD, MIPI CSI, Ethernet

### Candidates
- Rockchip RK3576, RK3588
- NXP i.MX 95, i.MX 8M Plus
- Renesas RZ/V2H
- TI AM68A, AM62A
- STM32MP257

### Trade-Offs
*(See `hardware/processing/soc-candidates.md` for full breakdown)*

### Decision
**We have selected the NXP i.MX 8M Plus.**

This decision was heavily driven by JLCPCB offering free Via-in-Pad (POFV) for 6 to 10-layer boards, which completely mitigates the traditional manufacturing barrier of routing a 0.5 mm BGA. 

The i.MX 8M Plus offers a perfect feature set for this robotics platform:
- Excellent documentation and a massive ecosystem of open-source reference boards.
- 15-year industrial longevity and mainline Linux support.
- 2.3 TOPS NPU, dual Gigabit Ethernet (with TSN), CAN-FD, and a Cortex-M7 real-time core.

### Consequences
- **Positive:** We get an extremely stable software ecosystem, reducing firmware development time. The 6-10 layer free via-in-pad offering enables routing the 0.5 mm pitch BGA affordably without HDI.
- **Negative:** Hardware cost per compute unit is higher than Chinese alternatives (like Rockchip). Cortex-A53 cores are slightly aging, which imposes a performance ceiling on the primary application cores compared to modern A55/A72 chips. Strict LPDDR4 routing is still required.
