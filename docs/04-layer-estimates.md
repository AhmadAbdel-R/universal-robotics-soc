# PCB Layer Count Estimation

When selecting the SoC for the Universal Robotics Controller, package complexity directly impacts the required PCB layer count. This affects manufacturing cost and board thickness.

## Manufacturer Recommended Formula

A common industry standard formula used by manufacturers for estimating the signal layers required to escape a BGA package is based on the number of pin rows:

```text
Signal Layers = (Number of BGA Rows / 2) - 1
```
*(Assumes standard routing capabilities and via-in-pad/dog-bone structures depending on pitch).*

### Total Layer Estimation Formula

To find the total number of layers, we must add power and ground planes. A reliable formula is:

```text
Total Layers ≈ Signal Layers + Power Planes + Ground Planes
```
*(Typically, each signal layer is paired with at least one reference plane for high-speed impedance control).*

## Examples by Package Complexity

### Example 1: Medium Complexity SoC (e.g., 400 pins, 20x20 grid)
- **Rows:** 20
- **Signal Layers:** (20 / 2) - 1 = 9
- **Required Signal Layers:** 9 (rounded up to nearest even layer stackup, likely 10)
- **Estimated Total Layers:** 10 Signal + 4 GND + 2 Power = **~16 Layers**

### Example 2: Compact Edge AI SoC (e.g., 144 pins, 12x12 grid)
- **Rows:** 12
- **Signal Layers:** (12 / 2) - 1 = 5
- **Required Signal Layers:** 6
- **Estimated Total Layers:** 6 Signal + 2 GND + 2 Power = **~10 Layers**

## Impact on URC Design
To keep the board cost-effective, we should aim for an SoC that allows a **6 to 10 layer** stackup. High pin-count memory interfaces (like LPDDR4/5) and PCIe routing will dominate these signal layers.
