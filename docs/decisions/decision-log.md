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
**We have selected the NXP i.MX 95 (specifically the MIMX9536CVZXNAC).**

This decision pivots from the initially considered i.MX 8M Plus to NXP's modern flagship successor. By selecting the **19x19 mm (Z) package variant**, we take advantage of a highly manufacturable **0.7 mm BGA pitch**, which makes PCB routing exceptionally easy and cheap, perfectly aligning with JLCPCB's capabilities without requiring dense HDI microvias.

How it satisfies the requirements:
- **Compute:** Hexa-core Cortex-A55 provides massive performance headroom over older A53 architectures.
- **AI / NPU:** Integrated eIQ Neutron NPU (~2 TOPS) combined with the heavy A55 compute can handle intensive vision tasks.
- **Real-Time:** Features an independent real-time domain with **both** a Cortex-M7 and a Cortex-M33, providing unparalleled determinism for robotics control.
- **I/O:** 10GbE, PCIe Gen3, multiple CAN-FD, and MIPI-CSI easily satisfy high-bandwidth sensor integration requirements.
- **Ecosystem:** Enjoys NXP's 15-year longevity, automotive-grade safety documentation, and robust mainline Linux support.

### Consequences
- **Positive:** We gain massive compute headroom, modern core architectures (A55), advanced real-time domains, and extremely easy PCB layout (0.7 mm pitch).
- **Negative:** The i.MX 95 is a newer, premium part, so the BOM cost will be higher than the 8M Plus or Chinese alternatives. The open-source community around it is also younger.

---

## ADR-002 — Pivot from i.MX 95 to i.MX 8M Plus

**Status:** Accepted

### Context
While attempting to begin Phase 3 (Memory / Storage) and Phase 1 (Boot Strapping) hardware design around the NXP i.MX 95, we discovered a fatal flaw in our assumptions regarding documentation availability and supply chain.

### The Problem
1. **The NDA Wall:** The i.MX 95 is so new that NXP has placed the critical Hardware Design Guide and full Reference Manuals behind a secure corporate portal that requires a Non-Disclosure Agreement (NDA) and corporate account approval to access. It is impossible to design an open-source hardware board without a publicly accessible hardware design guide (for DDR trace length matching, impedance, and power sequencing rules).
2. **LCSC Stock:** Because it is early in its lifecycle, it is not native to LCSC's catalog, forcing a reliance on Global Sourcing via Mouser.

### Decision
**We have formally pivoted the architecture back to the NXP i.MX 8M Plus (MIMX8ML8CVNKZAB).**

### Why the i.MX 8M Plus?
- **100% Public Documentation:** Every datasheet, hardware design guide, and reference manual is entirely public without an NDA or login required.
- **Native Stock:** It is physically in stock on LCSC right now, making JLCPCB assembly trivial.
- **Capabilities:** It still meets our core requirements (Quad A53, M7 Real-Time core, 2.3 TOPS NPU, CAN-FD, Dual Ethernet).
- **Manufacturability:** While it uses a tighter 0.5 mm pitch BGA, modern fabs like JLCPCB offer free Via-in-Pad (POFV) on 6-layer boards, allowing us to route it without expensive HDI microvias.

### Consequences
- **Positive:** We are unblocked on documentation and supply chain. Open-source contributors can actually read the datasheets without signing an NDA.
- **Negative:** We lose the A55 cores and 10GbE of the i.MX 95, falling back to older A53 cores and 1GbE. However, this is perfectly acceptable for the defined robotics scope.

---

## ADR-003 - Final Pivot to STMicroelectronics STM32MP257

**Status:** Accepted

### Context
While the i.MX 8M Plus solved the NDA wall issue of the i.MX 95, NXP's documentation ecosystem and CDN firewalls (blocking automated datasheet downloads) remained frustrating. Furthermore, the user mandated that **all components must be sourced directly from LCSC** to keep the BOM highly economic and frictionless for JLCPCB assembly.

### The Problem
NXP parts require expensive companion PMICs, and the total system BOM cost for an NXP platform can balloon quickly. We need a chip that offers the exact same high-end robotics features (NPU, M-Core, PCIe, CAN-FD, Dual Eth) but with vastly superior open-source documentation, a lower total BOM cost, and a highly accessible ecosystem.

### Decision
**We have formally pivoted the architecture away from NXP entirely, selecting the STMicroelectronics STM32MP257.**

### Why the STM32MP257?
- **World-Class Open Documentation:** STMicroelectronics is famous for its open, easily accessible documentation (no NDAs, no CDN bot-blocks, massive ST Wiki).
- **Robotics Powerhouse:** It perfectly matches our requirements:
  - Dual Arm Cortex-A35 (highly power efficient 64-bit cores).
  - Cortex-M33 real-time core (400 MHz).
  - **1.35 TOPS NPU** for AI/Vision.
  - **PCIe Gen2**, **USB 3.0**, **3x CAN-FD**, and **Dual Gigabit Ethernet (TSN)**.
- **Economic BOM:** ST's ecosystem is generally much more cost-effective. The PMIC requirements are often simpler, and the ST ecosystem heavily targets industrial/hobbyist accessibility.

### Consequences
- **Positive:** We permanently escape the NXP documentation firewall. The system becomes more economic, and we gain 3x CAN-FD (up from 2x on the 8M Plus). The A35 cores are extremely power efficient.
- **Negative:** None. The STM32MP257 is a perfect fit for this universal robotics controller.

---

## ADR-004 - Peripheral IC Selection (STM32MP257 Architecture)

**Status:** Accepted

### Context
With the core processor locked to the STM32MP257, we needed to select specific peripheral ICs that satisfied both the SoC's technical requirements (e.g., 1.8V IO domains, RGMII, LPDDR4) and the project's rigid supply-chain requirement: **All ICs must be natively stocked by LCSC for JLCPCB SMT assembly.**

### The Decisions & Rationale

1. **CAN-FD Transceivers (3x): Texas Instruments TCAN1044AVDRQ1**
   - *Why:* The 'V' variant features a separate VIO pin. The physical CAN bus runs at 5V, but the STM32MP257 FDCAN digital IO runs at 1.8V. By supplying 1.8V to the transceiver's VIO pin, we can interface the transceiver directly to the STM32MP257 without needing external level shifters. It supports up to 8 Mbps and is heavily stocked.

2. **Gigabit Ethernet PHY (2x): Texas Instruments DP83867IRRGZR**
   - *Why:* Gigabit RGMII routing is notoriously difficult because of strict timing requirements between the clock and data lines. The DP83867 features highly programmable internal RX/TX delays, allowing us to fix trace-length mismatch issues in software. It natively supports 1.8V RGMII IO and has mature mainline Linux kernel support.

3. **LPDDR4 System Memory: Micron MT53E1G32D2FW-046 IT:A (4GB)**
   - *Why:* A single-chip 32-bit Point-to-Point topology keeps the PCB routing to 6 layers. 4GB provides massive headroom for AI models and ROS2 containers. (A 2GB variant, MT53E512M32D1ZW, is an acceptable fallback depending on LCSC stock at the time of manufacturing).

4. **eMMC Storage: FORESEE FEMDRW064G-88A19 (64GB)**
   - *Why:* The single PCIe Gen2 lane is reserved for an M.2 expansion slot (AI accelerators or NVMe), meaning the board cannot rely on a hardwired NVMe SSD for the root OS. A 64GB eMMC 5.1 chip provides ample built-in storage for a heavy Linux rootfs.

5. **Serial NOR Boot Flash: Winbond W25Q256JVFIQ (32MB)**
   - *Why:* Standard 3.3V QSPI NOR flash. 32MB gives plenty of room for TF-A, U-Boot, and redundant recovery images.

### Consequences
- **Positive:** We have a complete, highly-integrated BOM that requires zero level-shifters for CAN or Ethernet, drastically simplifying the PCB routing. Programmable RGMII delays will save us from timing-related board spins.
- **Negative:** The TI Ethernet PHYs are slightly more expensive than basic Realtek PHYs, but the programmable delay features are well worth the cost to prevent a dead board.

---

## ADR-005 - LPDDR4 Fly-By Topology for Maximum Memory Capacity

**Status:** Accepted

### Context
Initially, we aimed to restrict the LPDDR4 routing to a strict **Point-to-Point** topology (using a single 32-bit memory IC) to guarantee the design could fit on a cheap 6-layer PCB. However, single-chip 32-bit LPDDR4 modules are severely limited in maximum capacity (typically capping out at 2GB or 4GB on standard distributor catalogs). The universal robotics controller requires massive memory overhead for ROS2, vision processing, and local AI models.

### Decision
We are officially overriding the Point-to-Point constraint and adopting a **Fly-By Topology** utilizing two parallel 16-bit LPDDR4 memory chips.

### Consequences
- **Positive (Capacity):** By using two 16-bit chips, we can easily achieve 4GB to 8GB of total system RAM using cheap, highly-stocked memory ICs.
- **Negative (PCB Cost & Complexity):** Routing Address, Command, and Control (ACC) lines in a fly-by chain across two chips is significantly more difficult. This almost certainly breaks our 6-layer PCB constraint, forcing us into an **8-layer stackup** to properly isolate the high-density signal layers and maintain strict impedance control.
