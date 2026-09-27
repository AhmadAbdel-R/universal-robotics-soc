# PCB & Signal Integrity Philosophy

## Interfaces Impact on PCB

Interfaces such as LPDDR, DDR, PCIe, USB 3.x, Ethernet, HDMI, DisplayPort, MIPI CSI, and MIPI DSI create their own PCB constraints.
Requirements include:
- controlled impedance
- differential impedance
- return paths
- reference planes
- loss, skew, propagation delay, crosstalk
- via transitions, via stubs, back-drilling where appropriate
- termination, stitching, stackup, material selection

**Do not blindly assign one universal impedance value.** Each interface should later use the requirements specified by the relevant SoC/vendor/interface standard and the actual fabricated stackup.

## BGA Pitch / Manufacturing Constraints

BGA pitch is a system-level constraint.

| Pitch | General Impact |
|---|---|
| ≥0.80 mm | relatively comfortable |
| ~0.70 mm | attractive for complex SoC |
| ~0.65 mm | manageable with careful fanout |
| ~0.60 mm | increased density / fabrication constraints |
| ~0.50 mm | HDI/microvia/via-in-pad increasingly likely |
| ≤0.40 mm | significant manufacturing complexity |

**Chain of Influence:**
BGA pitch → escape routing → via technology → stackup → layer count → fabrication capability → yield / cost

These pitch categories are not absolute manufacturing laws. Actual feasibility depends on pad diameter, solder mask, neck-down rules, trace/space, via diameter, via type, escape topology, PCB vendor capabilities, layer count, and pin assignment. Treat them as early architectural guidance.

## Manufacturer Layer Estimation Formula

Signal Layers = (Number of BGA Rows / 2) - 1
Total Layers ≈ Signal Layers + Power Planes + Ground Planes
