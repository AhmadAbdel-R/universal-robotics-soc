# Decoupling Capacitor Engineering

[THEORY] Proper decoupling ensures that transient current demands from digital loads are supplied locally, minimizing voltage droop, reducing ground bounce, and constraining electromagnetic emissions.

## Decoupling Hierarchy

[THEORY] Decoupling spans multiple scales of integration, forming a hierarchical network where different elements service transient energy at different time scales. Frequency boundaries are not hard stops; they overlap significantly.

*   **VRM (Voltage Regulator Module):** Supplies the average current and manages low-frequency energy variations.
*   **VRM OUTPUT CAPS:** Handle the immediate energy needs that the VRM feedback loop is too slow to compensate for.
*   **BULK CAPACITORS:** Handle slower transient loads that the local high-frequency decoupling network cannot sustain, but before the VRM fully responds.
*   **LOCAL MLCCs:** Service the faster, localized transient current spikes (e.g., logic switching) right next to the load pins.
*   **PCB PLANES:** Distribute current broadly and act as ultra-low inductance, high-frequency energy storage (plane capacitance).
*   **IC PACKAGE:** Bridges the PCB to the die at very high frequencies; its internal inductance plays a critical role in peak performance.
*   **ON-DIE CAPACITANCE:** Services the fastest possible switching events directly on the silicon.

## Capacitor Selection Methodology

[DESIGN CHOICE] Do NOT select capacitors merely because "0.1µF is high-frequency and 10µF is low-frequency." Capacitor effectiveness at high frequencies is dictated by package inductance, ESL, and mounting geometry, not strictly the capacitance value. Smaller packages (e.g., 0402, 0201) often perform better at high frequencies explicitly due to their lower ESL.

### Selection Template per Power Rail

[TBD] Specific values are strictly TBD until detailed simulation and design are finalized.

*   **Rail Name:** [TBD]
*   **Load Profile:** [TBD - REQUIRES Load Current Profile]
*   **Transient Profile ($\Delta I$, $di/dt$):** [TBD - REQUIRES Silicon characterization or app note]
*   **Target Impedance ($Z_{TARGET}$):** [TBD - REQUIRES allowable voltage ripple calculation]
*   **Capacitor Value:** [TBD]
*   **Package Size:** [TBD]
*   **Voltage Rating:** [TBD]
*   **Dielectric (e.g., X7R, C0G):** [TBD]
*   **ESR / ESL:** [TBD - REQUIRES Manufacturer Datasheet]
*   **Effective Capacitance (accounting for derating):** [TBD - REQUIRES Derating calculation]
*   **SRF:** [TBD - REQUIRES Impedance Curve]
*   **Placement & Quantity:** [TBD - REQUIRES PCB Floorplanning and Simulation]

## Mounting Inductance

[THEORY] The theoretical high-frequency performance of a capacitor is only one piece of the puzzle. The true effective high-frequency performance includes the physical layout parasitics:
$$L_{EFFECTIVE} = L_{ESL} + L_{PAD} + L_{VIA} + L_{PLANE\_SPREADING}$$

[DESIGN CHOICE] A theoretically excellent capacitor placed badly performs poorly. Careful attention must be paid to the physical mounting geometry to minimize the total loop inductance.

## Capacitor Nonidealities

[THEORY] Real-world capacitors are not ideal. Every critical capacitor must be modeled as a series RLC circuit:
$$ESR + ESL + C_{EFFECTIVE}$$

[FABRICATOR CONSTRAINT] For all critical decoupling components, the following nonidealities must be documented:
*   Tolerance
*   DC Bias Derating
*   Aging characteristics
*   Temperature coefficient
*   ESR (Equivalent Series Resistance)
*   ESL (Equivalent Series Inductance)
*   SRF (Self-Resonant Frequency)

[DESIGN CHOICE] It is mandatory to use the manufacturer's provided impedance-vs-frequency curves for modeling and selection, rather than static nominal datasheet numbers.

## Via Transitions for Decoupling

[THEORY] When a decoupling capacitor connects to power and ground planes, the current must flow through vias. The path typically looks like:
`CAP PAD -> PCB TRACE -> VIA -> POWER PLANE` and `CAP GND PAD -> PCB TRACE -> VIA -> GROUND PLANE`.

[THEORY] Via geometry introduces significant parasitic inductance into the decoupling loop, often dwarfing the ESL of the capacitor itself.

[DESIGN CHOICE] To mitigate via inductance, the following routing rules are required:
1.  Place vias immediately adjacent to the capacitor pads.
2.  Minimize the trace length between the pad and the via to absolute zero where possible.
3.  Consider utilizing multiple vias per pad for high-frequency or high-current decoupling to parallelize and reduce inductance.
4.  Utilize via-in-pad technology when justified by extreme high-frequency requirements and authorized by manufacturing capabilities.
