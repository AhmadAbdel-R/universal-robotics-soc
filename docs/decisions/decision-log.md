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
