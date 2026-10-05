# Engineering Decision Log

## ADR-001 — Main Processor Selection

**Status:** Superseded by ADR-002

### Context
*(Historical)* The project requires a central compute architecture to unify application processing, real-time control, AI inference, and robotics I/O.

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

**Status:** Superseded by ADR-003

### Context
*(Historical)* While attempting to begin Phase 3 (Memory / Storage) and Phase 1 (Boot Strapping) hardware design around the NXP i.MX 95, we discovered a fatal flaw in our assumptions regarding documentation availability and supply chain.

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
- **Negative:** None. The STM32MP257 is a suitable choice for this universal robotics controller.

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
   - *Why:* A single-chip 32-bit Point-to-Point topology minimizes PCB routing complexity. 4GB provides significant headroom for AI models and ROS2 containers. (A 2GB variant, MT53E512M32D1ZW, is an acceptable fallback depending on LCSC stock at the time of manufacturing).

4. **eMMC Storage: FORESEE FEMDRW064G-88A19 (64GB)**
   - *Why:* The single PCIe Gen2 lane is reserved for an M.2 expansion slot (AI accelerators or NVMe), meaning the board cannot rely on a hardwired NVMe SSD for the root OS. A 64GB eMMC 5.1 chip provides ample built-in storage for a heavy Linux rootfs.

5. **Serial NOR Boot Flash: Winbond W25Q256JVFIQ (32MB)**
   - *Why:* Standard 3.3V QSPI NOR flash. 32MB gives plenty of room for TF-A, U-Boot, and redundant recovery images.

### Consequences
- **Positive:** We have a complete, highly-integrated BOM that requires zero level-shifters for CAN or Ethernet, drastically simplifying the PCB routing. Programmable RGMII delays will save us from timing-related board spins.
- **Negative:** The TI Ethernet PHYs are slightly more expensive than basic Realtek PHYs, but the programmable delay features are well worth the cost to prevent a dead board.

---

## ADR-005 - LPDDR4 Fly-By Topology and Temperature Grade Trade-Offs

**Status:** Superseded by ADR-006

### Context
*(Historical)* Initially, it was believed a single 4GB 32-bit memory module was unavailable or too expensive, leading to a proposed dual-chip fly-by topology.

### Decision
*(Superseded)* This decision proposed a fly-by topology using two 16-bit memory chips, claiming it would force an 8-layer PCB.

---

## ADR-006 - LPDDR4 Point-to-Point Architecture

**Status:** Accepted

### Context
ADR-005 proposed a dual-chip fly-by topology for the LPDDR4 memory. However, the STM32MP257 architecture supports a simplified, high-speed point-to-point interface. A dual-device fly-by topology adds unnecessary routing complexity, signal integrity risks, and unsupported claims about mandatory 8-layer PCBs. 

### Decision
**We are formally locking the LPDDR4 architecture to a single-device, 32-bit point-to-point topology.**

The target memory configuration is:
- **Topology:** Point-to-point (single-device)
- **Interface:** 32-bit, single-rank
- **Target Part:** Micron MT53E1G32D2FW (or exact 32-bit 4 GB equivalent)
- **Capacity:** 32 Gbit (4 GB total)
- **Temperature Grade:** Industrial Grade (-40C to +95C) is still targeted due to thermal requirements.

### Consequences
- **Positive:** Point-to-point routing drastically simplifies the PCB layout and improves signal integrity. We avoid the complex length-matching required for a dual-device fly-by topology on the Address/Command (ACC) bus.
- **Positive:** We eliminate the false constraint that memory alone forces an 8-layer PCB. Final layer count will be determined by comprehensive SI analysis and routing density, not an incorrect memory topology.
- **Negative:** Reliance on a single 32-bit 4GB package limits fallback options if the specific package faces supply chain shortages.

---

## ADR-007 - Robotics and Industrial I/O Architecture

**Status:** Accepted

### Context
To elevate the board from a generic SBC to a Universal Robotics Controller, a comprehensive set of deterministic I/O, environmental sensors, and rugged industrial interfaces must be defined and carefully partitioned between the Linux application domain and the real-time microcontroller domain.

### Decisions

1. **Onboard Sensors & Clean Power:**
   - **IMU:** TDK InvenSense ICM-42688-P, communicating over a dedicated SPI bus to avoid latency from high-traffic peripherals.
   - **Magnetometer:** MEMSIC MMC5983MA on a secondary SPI bus. An external magnetometer option is also provided for high-interference environments (e.g., UAVs).
   - **Barometer:** Bosch BMP581 on the secondary SPI bus.
   - **Clean Sensor Power:** A dedicated 3.3V LDO (TI TPS7A2033PDBVR) generates `3V3_SENSOR` exclusively for sensitive low-power sensors, heavily isolated from PMIC and actuator noise.

2. **Cortex-M33 Real-Time Ownership:**
   The Cortex-M33 real-time core will natively own latency-critical interfaces, explicitly including:
   - IMU and secondary sensor SPI buses
   - Four deterministic motor outputs (PWM/DShot)
   - Incremental encoder inputs (A/B/Z) and STEP/DIR interfaces
   - ExpressLRS (CRSF) UART receiver
   - ESC telemetry and analog motor/battery monitoring
   - Real-time CAN-FD

3. **Actuator & Motor Control:**
   - The board will supply four M33-controlled motor outputs (M1-M4) compatible with PWM and DShot.
   - High-power 3-phase inverters (e.g., DRV8353) and resolver analog front-ends (e.g., AD2S1210) will be offloaded to optional daughterboards to keep the compute PCB manageable.

4. **Industrial I/O:**
   - The board will feature ruggedized RS-485 (via TI THVD1450) and a protected 24-V digital I/O philosophy (IEC 61131-2 compatible inputs/outputs) for field wiring.
   - We prefer daughterboards for specialized isolated analog requirements (e.g., ±10 V / 4–20 mA via AD4111).

### Consequences
- **Positive:** By deliberately offloading high-power electronics and specialized analog front-ends to daughterboards while retaining the fundamental real-time logic and sensors on the motherboard, we achieve a compact, robust, and highly scalable universal controller.
- **Negative:** Increased layout complexity to isolate the `3V3_SENSOR` rail and carefully route SPI buses away from the RF and PMIC zones.

---

## Active / Proposed Evaluations (Not Yet Locked)

The following architectures and components are currently under evaluation and are **NOT** yet marked as Accepted:

- **Exact Wi-Fi Module:** Murata Type 2AE (LBEE5PK2AE-564) is preferred, but final lock depends on LCSC stock and lifecycle verification.
- **Exact HDMI Bridge:** Evaluating Analog Devices ADV7535 vs. Lontium LT8912B vs. Sil9022A.
- **Exact IO-Link PHY:** ST L6360 is preferred but subject to verification.
- **Exact Resolver AFE:** AD2S1210 daughterboard interface proposed.
- **Exact Industrial ADC:** AD4111 daughterboard interface proposed.
- **Exact Rugged Connector SKUs:** JST-GH, M12, Molex Micro-Fit, and Harwin Gecko are preferred families, but exact SKUs are pending mechanical constraints.
- **Exact Isolated CAN Implementation:** TI ISO1042 proposed for the optional isolated channel.
- **Exact 24-V I/O Count:** Target is 2-4 inputs and 2 outputs, subject to final board space.
- **Exact STM32 Peripheral Instances:** Base allocation frozen in ADR-008; ~74 unassigned GPIOs pending Phase 10 voltage domain review.
- **Exact Antenna Geometry:** Pending PCB outline, stackup, and enclosure definition.

---

## ADR-008 — STM32MP257 Platform Pinout & Peripheral Mapping Freeze (CubeMX Pass 1)

### Status: Accepted
**Date:** 2026-10-03  
**Deciders:** Lead Systems Architect

### Context
Following the architecture lock of the STM32MP257FAIx (TFBGA436), a comprehensive alternate-function multiplexing and context-isolation pass was completed in STM32CubeMX (`cubemx.ioc`). The board requires concurrent operation of high-bandwidth Linux OS peripherals (Dual GbE RGMII, PCIe Gen2, USB2 OTG & Host, CSI-2, DSI/LTDC, Wi-Fi SDIO) alongside hard real-time robotics peripherals owned by the Cortex-M33 (3x CAN-FD, 3x SPI, 4x Timers/DShot, 6x UARTs, UCPD1, ICACHE).

### Decisions
1. **Dual Independent RGMII:** ETH1 and ETH2 are pinned out with 14 dedicated lines each (PA/PC/PF/PH for ETH1; PC/PF/PG for ETH2). ETHSW is disabled. Both MACs operate with independent MDC/MDIO lines. PHY interrupts are handled via external GPIOs.
2. **COMBOPHY Exclusivity:** The shared 5 Gbps COMBOPHY is allocated exclusively to PCIe Gen2 x1 Root Complex (M.2 Key-M). USB3DR is constrained to USB 2.0 High-Speed mode, preventing hardware pin conflicts.
3. **Display & Camera Pipelines:** LTDC is configured in RGB888 mode feeding internal DSIHOST (4 data lanes, Video Mode) targeting an off-chip DSI-to-HDMI bridge. CSI-2 feeds DCMIPP with Pipe 1 active.
4. **M33 Real-Time Peripheral Freeze:**
   - SPI1: Dedicated IMU (ICM-42688-P) on PE0/PF12/PI5.
   - SPI2: Sensor bus (MMC5983MA, BMP581) on PB0/PB6/PB2.
   - SPI3: Expansion SPI on PB7/PB10/PE2.
   - FDCAN1, 2, 3: Pinned out for 3x TCAN1044A transceivers.
   - TIM1: 4-channel ESC/DShot output engine (PD8-PD11).
   - TIM2: Quadrature encoder A/B input (PH5/PF15).
   - TIM3: 4-channel auxiliary PWM output (PI6/PI7/PF13/PF14).
   - TIM4: Industrial STEP pulse generator (PI10).
   - USART6: RS-485 with hardware DE (PJ5/PJ8/PG5).
   - UART4 (GNSS on PK4/PI15), UART5 (CRSF/ELRS on PG9/PG10), UART7 (Expansion on PD3/PH3).
5. **Cortex-M33 ICACHE:** Enabled in 2-way set associative mode for deterministic execution.
6. **Unassigned GPIOs (~74 pins):** Signals including `STEP_DIR`, `ENCODER_Z`, `GNSS_PPS`, `INA229_ALERT`, `CAN_STB`, `BMS_FAULT/ENABLE`, and Wi-Fi/BT/HDMI control pins remain unassigned until power bank voltages (VDDIO1-4) are verified.

### Consequences
- **Positive:** Full peripheral pin mapping established without resource collisions; dual independent GbE confirmed viable; M33 real-time determinism secured.
- **Negative:** ~74 GPIOs require ball assignment in Phase 10 after voltage domain verification.

---

## ADR-009 — A35-TD Boot Architecture: Primary eMMC Boot with Secondary OCTOSPI1 Storage

### Status: Accepted
**Date:** 2026-10-03  
**Deciders:** Lead Systems Architect

### Context
The platform implements an A35 Trusted Domain (A35-TD) boot hierarchy. The physical board incorporates a soldered 64 GB eMMC 5.1 (SDMMC2) and a 32 MB Quad-SPI NOR Flash (OCTOSPI1). We evaluated whether TF-A BL2 should boot from NOR or eMMC.

### Decisions
1. **Primary Boot Device Lock:** Primary boot is formally locked to soldered eMMC (`BOOTDEVICE_LABELS = "emmc"`). The platform does not use an SD card socket.
2. **TF-A & Device Tree Reconciliation:** To prevent build/runtime failures where TF-A is compiled for eMMC while lacking the `&sdmmc2` node, the TF-A device tree (`tf-a/stm32mp257f-cubemx-mx.dts`) is patched in its protected USER CODE sections with SDMMC2 pinctrl and device node.
3. **OCTOSPI1 Role:** OCTOSPI1 remains available as secondary non-volatile storage for bootloader recovery, board calibration, and fail-safe firmware.

### Consequences
- **Positive:** Single, coherent, high-speed primary boot path from soldered eMMC; no external SD card dependency; NOR preserved for recovery.
- **Action Item:** Next CubeMX GUI pass will check `Cortex-A35 Secure FSBL` under SDMMC2 Context Management to synchronize `.ioc` metadata natively.

---

## ADR-010 — Battery Management (BMS) Strategy & Digital Telemetry Architecture

### Status: Accepted
**Date:** 2026-10-03  
**Deciders:** Lead Systems Architect

### Context
The system supports 2S through 8S battery packs (up to ~34 V steady state). High-current battery systems pose extreme thermal and safety challenges if cell balancing is placed on a compact compute motherboard.

### Decisions
1. **External Pack BMS:** Full multi-cell balancing and high-current protection switches remain on the external smart battery pack or dedicated power daughterboard.
2. **Motherboard Ingress Protection:** Motherboard implements primary fusing, solid-state ideal-diode reverse polarity protection, surge clamping, and inrush control.
3. **Digital Telemetry via INA229:** Battery voltage, current, and power monitoring are assigned to a dedicated Texas Instruments INA229 (85 V, 20-bit delta-sigma monitor) communicating via SPI/I2C to the Cortex-M33, with an `INA229_ALERT` interrupt line. Internal STM32 ADCs are intentionally not committed to primary power monitoring.
4. **BMS Supervisory Interface:** M33 manages `BMS_FAULT` (input) and `BMS_ENABLE` (output), plus optional smart pack communications over FDCAN3 or UART7.
5. **Actuator Current Isolation:** The high-current actuator bus (`ACT_PWR_RAW`) is strictly separated from compute PMIC input (`VIN_SYS`).

### Consequences
- **Positive:** Protects compute electronics from motor back-EMF; eliminates thermal dissipation of balancing circuits on compute PCB; provides microsecond digital fault detection.

---

## ADR-011 - Universal Buck Regulator IC Selection

### Status: Accepted
**Date:** 2026-10-05
**Deciders:** Lead Systems Architect

### Context
The initial power architecture proposed using the MPS MP2315S as a universal switching regulator across all rails for extreme BOM consolidation. However, we need robust design documentation, predictable loop compensation parameters, and verifiable sizing references for all corner cases.

### Decisions
1. **IC Selection:** The primary buck regulator IC is formally changed from MP2315S to **Texas Instruments TPS54561DPRR** (LCSC C180369).
2. **Reference Design:** All power stage calculations will follow the **TI SLVA477C** Application Note.
3. **Pending Verification:** While the IC is selected for its superior documentation and design support, individual rail suitability, loop compensation, and the goal of extreme BOM consolidation (identical inductors/capacitors across all rails) remain subject to rigorous engineering verification and calculation. They are not final until explicitly proven.

### Consequences
- **Positive:** We gain access to high-quality, comprehensive TI documentation and well-defined equations for stability and power-stage calculations.
- **Action Item:** Recalculate every voltage rail strictly against the new SLVA477C-based calculation guide to verify component selections.
