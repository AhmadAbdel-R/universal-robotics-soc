# Engineering Decision Log

## ADR-001 — Main Processor Selection

**Status:** Open

### Context
The project requires a central compute architecture to unify application processing, real-time control, AI inference, and robotics I/O.

### Requirements
- Linux support
- AI / NPU accelerator
- Real-time capabilities (integrated or external)
- Specific IO: PCIe, CAN-FD, MIPI CSI, Ethernet

### Candidates
- Rockchip RK3576
- NXP i.MX 95
- Rockchip RK3588
- Renesas RZ/V2H
- TI AM67A, TI AM62A7, NXP i.MX 8M Plus, Allwinner T527M02

### Trade-Offs
*(See `hardware/processing/soc-candidates.md` for full breakdown)*

### Decision
TBD

### Consequences
TBD
