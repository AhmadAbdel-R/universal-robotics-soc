# Controlled Impedance Theory & Specifications

## Microstrip Theory

(THEORY)
A signal trace on an outer layer with a continuous reference plane below. The electromagnetic fields propagate partly in the dielectric and partly in the air/soldermask above.
Effective dielectric constant: 
$\varepsilon_{effective} < \varepsilon_r$

Propagation velocity:
$$v_p \approx \frac{c}{\sqrt{\varepsilon_{effective}}}$$

Propagation delay per unit length:
$$t_{pd} \approx \frac{\sqrt{\varepsilon_{effective}}}{c}$$
*A field solver must be used for final impedance calculations.*

## Stripline Theory

(THEORY)
A signal trace embedded completely within a dielectric, sandwiched between two reference planes. The vast majority of field energy is contained within the uniform dielectric.

Propagation velocity:
$$v_p \approx \frac{c}{\sqrt{\varepsilon_r}}$$
Stripline traces generally have a slower propagation velocity compared to a microstrip with the same base dielectric.

## Microstrip vs Stripline Comparison

| Feature | Microstrip | Stripline |
| :--- | :--- | :--- |
| **Advantages** | Easier probing, lower dielectric participation, faster propagation, lower dielectric loss, easy outer-layer fanout. | Fields contained, improved EM shielding, lower radiation/EMI. |
| **Disadvantages** | More radiated fields, sensitive to soldermask thickness, more crosstalk/EMI. | Greater propagation delay, often higher dielectric loss, requires via transitions, harder to probe. |

## Symmetric vs Asymmetric Stripline

(THEORY)
- **Symmetric**: The trace is perfectly centered between the two reference planes. Benefits include symmetric field distribution and simpler, predictable impedance.
- **Asymmetric**: Unequal spacing to the two reference planes. Valid, but impedance depends on BOTH distances. Symmetric equations must NOT be applied to asymmetric geometry.

## Differential Pair Theory

(THEORY)
Differential impedance is strongly influenced by the odd-mode impedance of a single trace:
$$Z_{DIFF} \approx 2 \cdot Z_{ODD}$$
Coupling depends on trace width, pair spacing, distance to reference plane, copper thickness, dielectric constant, and soldermask. Simply doubling the single-ended impedance target does NOT yield the correct differential geometry due to mutual coupling.

## Impedance Table

(DESIGN CHOICE / TBD)

| Interface | Mode | Target Z ($\Omega$) | Tolerance | Layer | Geometry | Ref Plane | Width (mm) | Spacing (mm) | Dk | Calculator Result | Status | Source |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| LPDDR4 | Diff | TBD | TBD | TBD | TBD | TBD | TBD | TBD | TBD | TBD | TBD | TBD |
| PCIe Gen2 | Diff | TBD | TBD | TBD | TBD | TBD | TBD | TBD | TBD | TBD | TBD | TBD |
| USB2 HS | Diff | TBD | TBD | TBD | TBD | TBD | TBD | TBD | TBD | TBD | TBD | TBD |
| RGMII | SE | TBD | TBD | TBD | TBD | TBD | TBD | TBD | TBD | TBD | TBD | TBD |
| MIPI CSI | Diff | TBD | TBD | TBD | TBD | TBD | TBD | TBD | TBD | TBD | TBD | TBD |
| MIPI DSI | Diff | TBD | TBD | TBD | TBD | TBD | TBD | TBD | TBD | TBD | TBD | TBD |
| Wi-Fi RF | SE | TBD | TBD | TBD | TBD | TBD | TBD | TBD | TBD | TBD | TBD | TBD |
| HDMI | Diff | TBD | TBD | TBD | TBD | TBD | TBD | TBD | TBD | TBD | TBD | TBD |

## Edge Rate vs Clock Frequency

(THEORY)
SI bandwidth is strongly driven by the EDGE RATE (rise/fall time), not merely the fundamental clock frequency. 
The knee frequency is approximated as:
$$f_{knee} \propto \frac{1}{t_r}$$
Even with a slow clock frequency, a fast driver with short transition times can require high-frequency SI treatments.
