# PCB Stackup & Impedance Strategy

## The "Common Ground" Challenge
To keep manufacturing costs low and avoid exotic HDI PCB fabrication, we are targeting a standard **6-layer or 8-layer** stackup at JLCPCB.

However, the STM32MP257 system requires multiple high-speed interfaces, each with different controlled impedance targets:
- **LPDDR4:** 40-ohm Single-Ended (SE), 80-ohm Differential (Diff)
- **PCIe Gen2:** 85-ohm or 100-ohm Diff
- **USB 3.0 / USB 2.0:** 90-ohm Diff
- **Ethernet (RGMII):** 50-ohm SE
- **MIPI CSI/DSI:** 100-ohm Diff

Because trace impedance is determined by trace width, trace spacing, and the distance to the reference plane (dielectric thickness), a standard PCB stackup cannot mathematically hit all these targets perfectly without making some traces microscopic or massive.

## Mitigating Trade-offs via Tolerances
As established in our design philosophy, we must find the "spec common ground". 
1. **LPDDR4 is King:** The 3200 MT/s LPDDR4 interface has the strictest tolerances. The stackup dielectric thickness will be explicitly chosen to optimize for the 40-ohm SE / 80-ohm Diff DDR traces.
2. **Leveraging Tolerances for I/O:** Most peripheral specs allow a **±10% to ±15% tolerance**. 
   - If we design the stackup to hit 90-ohm differential for USB, we can often squeak by with that exact same trace geometry for PCIe (which wants 85 ohms) because 90 ohms is well within the ±10% tolerance window of 85 ohms. 
   - This "common ground" geometry prevents us from having to calculate 5 different differential pair constraints.

## Memory Topology Decision
To further simplify the stackup and Signal Integrity (SI) constraints:
- **Topology:** We will use a **Point-to-Point** topology. 
- **Component:** We will select a **single, 32-bit LPDDR4 package** (e.g., a 200-ball dual-channel chip) rather than two 16-bit chips.
- **Why:** Routing a single RAM chip point-to-point is drastically simpler than calculating fly-by or T-branch routing for two separate RAM chips, heavily reducing cross-talk and reflection risks. Final layer count remains subject to comprehensive SI analysis and overall routing density.
