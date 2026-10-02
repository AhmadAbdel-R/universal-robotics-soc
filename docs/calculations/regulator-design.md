# VRM / Regulator Design Calculations

## Regulator Design Worksheet Template

For every regulator designed in the system, fill out this worksheet:
- **Controller/IC:** TBD - REQUIRES DATASHEET
- **Topology:** TBD - REQUIRES DATASHEET
- **VIN min/nom/max:** TBD - REQUIRES DATASHEET
- **VOUT:** TBD - REQUIRES DATASHEET
- **IOUT typ/max:** TBD - REQUIRES DATASHEET
- **Transient current:** TBD - REQUIRES SIMULATION
- **Switching frequency ($f_{SW}$):** TBD - REQUIRES DATASHEET
- **Inductor:** TBD - REQUIRES DATASHEET
- **Output capacitance:** TBD - REQUIRES SIMULATION
- **Input capacitance:** TBD - REQUIRES SIMULATION
- **Compensation:** TBD - REQUIRES SIMULATION
- **Efficiency:** TBD - REQUIRES MEASUREMENT
- **Thermal loss:** TBD - REQUIRES SIMULATION
- **Ripple:** TBD - REQUIRES MEASUREMENT
- **Transient response:** TBD - REQUIRES MEASUREMENT
- **Startup:** TBD - REQUIRES MEASUREMENT
- **Sequencing:** TBD - REQUIRES DATASHEET
- **Enable dependencies:** TBD - REQUIRES DATASHEET
- **PGOOD dependencies:** TBD - REQUIRES DATASHEET
- **Soft start:** TBD - REQUIRES DATASHEET
- **Current limit:** TBD - REQUIRES DATASHEET
- **UVLO:** TBD - REQUIRES DATASHEET
- **OVP:** TBD - REQUIRES DATASHEET

## Buck Converter Calculations

### Duty Cycle

**INPUTS:** $V_{OUT}$ (TBD), $V_{IN}$ (TBD)
**ASSUMPTIONS:** Ideal switching components. Note corrections for nonidealities (dead-time, switch $R_{DS(ON)}$, DCR) will increase duty cycle slightly to compensate for losses.
**EQUATION:** 
$$D \approx \frac{V_{OUT}}{V_{IN}}$$
**SUBSTITUTION:** TBD
**RESULT:** TBD - REQUIRES DATASHEET
**MARGIN:** N/A
**SOURCE:** Standard Buck Topology Equations
**STATUS:** NEEDS DATASHEET

### Inductor Ripple

**INPUTS:** $V_{OUT}$ (TBD), $V_{IN}$ (TBD), $D$ (TBD), $f_{SW}$ (TBD), $L$ (TBD)
**ASSUMPTIONS:** Continuous Conduction Mode (CCM).
**EQUATION:**
$$\Delta I_L = \frac{V_{OUT}(1-D)}{L \cdot f_{SW}}$$
**SUBSTITUTION:** TBD
**RESULT:** TBD - REQUIRES DATASHEET
**MARGIN:** N/A
**SOURCE:** Standard Buck Topology Equations
**STATUS:** NEEDS DATASHEET

### Peak / Valley Inductor Current

**INPUTS:** $I_{OUT}$ (TBD), $\Delta I_L$ (TBD)
**ASSUMPTIONS:** Stable CCM operation.
**EQUATION:**
$$I_{L,PEAK} = I_{OUT} + \frac{\Delta I_L}{2}$$
$$I_{L,VALLEY} = I_{OUT} - \frac{\Delta I_L}{2}$$
**SUBSTITUTION:** TBD
**RESULT:** TBD - REQUIRES DATASHEET
**MARGIN:** N/A
**SOURCE:** Standard Buck Topology Equations
**STATUS:** NEEDS DATASHEET

### Inductor Selection Checks
- **Ripple ratio:** $r = \Delta I_L / I_{OUT}$ (TBD - REQUIRES DATASHEET)
- **Saturation Margin:** $I_{SAT}$ must be > $I_{L,PEAK}$ (TBD - REQUIRES DATASHEET)
- **Other Checks:** $I_{RMS}$, DCR, core loss, temperature rise, tolerance, DC-bias.

### Inductor Losses

**INPUTS:** $I_{L,RMS}$ (TBD), $DCR_{HOT}$ (TBD)
**ASSUMPTIONS:** Includes DC conduction losses. Core loss from manufacturer data must be added.
**EQUATION:**
$$P_{DCR} = I_{L,RMS}^2 \cdot DCR_{HOT}$$
**SUBSTITUTION:** TBD
**RESULT:** TBD - REQUIRES DATASHEET
**MARGIN:** N/A
**SOURCE:** Inductor Power Loss Models
**STATUS:** NEEDS DATASHEET

### Output Ripple

**INPUTS:** $\Delta I_L$ (TBD), $f_{SW}$ (TBD), $C_{OUT}$ (TBD), $ESR$ (TBD)
**ASSUMPTIONS:** $ESL$ effect omitted for basic sizing; assumes ideal placement. Control topology and switching-node coupling will affect real-world values.
**EQUATION:**
$$\Delta V_{OUT} \approx \frac{\Delta I_L}{8 \cdot f_{SW} \cdot C_{OUT}} + \Delta I_L \cdot ESR$$
**SUBSTITUTION:** TBD
**RESULT:** TBD - REQUIRES DATASHEET
**MARGIN:** N/A
**SOURCE:** Output Ripple Fundamental Equations
**STATUS:** NEEDS DATASHEET

### Input Capacitor

**INPUTS:** $I_{OUT}$ (TBD), $D$ (TBD)
**ASSUMPTIONS:** Requires evaluating ripple current rating, ESR heating, placement, voltage derating, and hot-plug stress.
**EQUATION:**
$$I_{CIN,RMS} \approx I_{OUT} \sqrt{D(1-D)}$$
**SUBSTITUTION:** TBD
**RESULT:** TBD - REQUIRES DATASHEET
**MARGIN:** N/A
**SOURCE:** Input Ripple RMS Models
**STATUS:** NEEDS DATASHEET

### Switching MOSFET Losses

**INPUTS:** $I_{RMS}$ (TBD), $R_{DS(ON),HOT}$ (TBD), $V_{IN}$ (TBD), $I_{SWITCH}$ (TBD), $t_r$ (TBD), $t_f$ (TBD), $f_{SW}$ (TBD), $Q_G$ (TBD), $V_{GS}$ (TBD)
**ASSUMPTIONS:** Additional losses to consider: dead-time loss, body-diode conduction, reverse recovery, $C_{OSS}$ discharge, and controller quiescent current.
**EQUATION:**
$$P_{COND} = I_{RMS}^2 \cdot R_{DS(ON),HOT}$$
$$P_{SW} \approx 0.5 \cdot V_{IN} \cdot I_{SWITCH} \cdot (t_r + t_f) \cdot f_{SW}$$
$$P_{GATE} \approx Q_G \cdot V_{GS} \cdot f_{SW}$$
**SUBSTITUTION:** TBD
**RESULT:** TBD - REQUIRES DATASHEET
**MARGIN:** N/A
**SOURCE:** MOSFET Switching Loss Models
**STATUS:** NEEDS DATASHEET

### Efficiency

**INPUTS:** $P_{OUT}$ (TBD), $P_{IN}$ (TBD)
**ASSUMPTIONS:** Loss distribution broken into: MOSFET, inductor, controller, capacitor ESR, gate drive, switching, PCB conduction.
**EQUATION:**
$$\eta = \frac{P_{OUT}}{P_{IN}}$$
$$P_{LOSS} = P_{IN} - P_{OUT}$$
**SUBSTITUTION:** TBD
**RESULT:** TBD - REQUIRES MEASUREMENT
**MARGIN:** N/A
**SOURCE:** Power Efficiency Calculation
**STATUS:** NEEDS MEASUREMENT

### Switch-Node Edge Rate / EMI

**INPUTS:** $\Delta V$ (TBD), $\Delta I$ (TBD), $t_r$ (TBD)
**ASSUMPTIONS:** Faster edges: reduce switching loss, increase EMI/ringing/coupling. Slower edges: reduce EMI, increase switching loss. Tuning via gate-drive/gate-resistor.
**EQUATION:**
$$\frac{dv}{dt} \approx \frac{\Delta V}{t_r}$$
$$\frac{di}{dt} \approx \frac{\Delta I}{t_r}$$
**SUBSTITUTION:** TBD
**RESULT:** TBD - REQUIRES MEASUREMENT
**MARGIN:** N/A
**SOURCE:** Edge Rate Approximations
**STATUS:** NEEDS MEASUREMENT

### Switch-Node Ringing

**INPUTS:** $L_{PARASITIC}$ (TBD), $C_{PARASITIC}$ (TBD)
**ASSUMPTIONS:** Placeholder for measurement. Do NOT pick snubber values without measurement and tuning.
**EQUATION:**
$$f_{RING} \approx \frac{1}{2\pi\sqrt{L_{PARASITIC} \cdot C_{PARASITIC}}}$$
**SUBSTITUTION:** TBD
**RESULT:** TBD - REQUIRES MEASUREMENT
**MARGIN:** N/A
**SOURCE:** LC Resonance Formula
**STATUS:** NEEDS MEASUREMENT

### Control-Loop Bandwidth
For each regulator:
- **Switching frequency:** TBD - REQUIRES DATASHEET
- **Crossover frequency:** TBD - REQUIRES SIMULATION
- **Phase margin:** TBD - REQUIRES SIMULATION
- **Gain margin:** TBD - REQUIRES SIMULATION
- *Note:* Do NOT invent values. Use datasheet/manufacturer tool/SPICE/measurement. VRM feedback bandwidth limits transient response.

### Regulator Thermal Estimate
**DESIGN CHOICE / ASSUMPTION:** Do NOT blindly use $T_J = T_A + P \cdot \theta_{JA}$. Note that $\theta_{JA}$ depends heavily on the JEDEC test PCB.
**METHOD:** Prefer using $\Psi_{JT}$, thermal characterization parameters, manufacturer tools, simulation, and measurement to estimate junction temperatures.
