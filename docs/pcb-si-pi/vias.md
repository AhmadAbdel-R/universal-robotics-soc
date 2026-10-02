# Via Transitions and Parasitics

## Via Parasitics

(THEORY)
A via presents parasitic inductance and capacitance to a high-speed signal.
First-order via inductance approximation ($h$, $d$ in mm):
$$L_{via}(nH) \approx 0.2h \left[1 + \ln\left(\frac{4h}{d}\right)\right]$$
where:
- $h$ = electrical via length
- $d$ = via barrel diameter

*Note: This is an approximation. EM/field simulation is required for critical high-speed structures.*
A first-order capacitance model should also be included where applicable for full PI/SI considerations.

## Why Shorter Vias Help

(THEORY)
A longer via barrel introduces higher series inductance. If a signal changes layers but leaves a significant portion of the via barrel unused beyond the destination layer, that remaining structure becomes a stub.

## Via Stubs

(THEORY)
When a signal enters a through-hole via on one layer and exits on an inner layer, the unused portion of the barrel forms a **via stub**.
A stub acts as an unterminated transmission-line discontinuity, causing reflection, resonance, insertion loss, and eye-diagram closure. The severity depends heavily on the stub length, dielectric properties, signal edge rate, and data rate.

## Via-Stub Resonance

(THEORY)
A via stub acts as a quarter-wave resonator. The fundamental resonant frequency can be estimated by:
$$f_{quarter} \approx \frac{v_p}{4 \cdot L_{stub}}$$
where:
$$v_p \approx \frac{c}{\sqrt{\varepsilon_{effective}}}$$
*This is a screening estimate only. A 3D field solver is needed for rigorous analysis.*

## Backdrill

(FABRICATOR CONSTRAINT / DESIGN CHOICE)
Backdrilling physically removes the unused via barrel (stub) using a secondary drilling process from the bottom (or top) side.
JLCPCB supports controlled-depth backdrilling. This technique should only be specified where SI analysis justifies its cost and necessity.

## Microvia / HDI Justification

(DESIGN CHOICE)
The STM32MP257 in a TFBGA436 package (18mm x 18mm, 0.8mm pitch) may require High Density Interconnect (HDI) techniques for effective escape routing.
Document parameters:
- Microvia diameter: TBD
- Capture pad size: TBD
- Dielectric thickness: TBD
- Aspect ratio: TBD
- Sequential lamination stages: TBD
- Configuration (staggered vs. stacked): TBD
- Via-in-pad (filled/capped): TBD

*All parameters must be verified against JLCPCB manufacturing capability limits.*
