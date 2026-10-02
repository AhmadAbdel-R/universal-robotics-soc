# High-Current Path Calculations

This document details calculations regarding power delivery structure and high current flows.

### PCB Copper Resistance

**INPUTS:** $\rho$ (Copper resistivity $\approx 1.724 \times 10^{-8} \Omega\cdot m$ at 20°C), $L$ (length, TBD), $W$ (width, TBD), $T$ (thickness, TBD), $I$ (Current, TBD)
**ASSUMPTIONS:** Requires actual copper thickness from selected fab stackup.
**EQUATION:**
$$R = \frac{\rho \cdot L}{W \cdot T}$$
$$V_{DROP} = I \cdot R$$
$$P_{LOSS} = I^2 \cdot R$$
**SUBSTITUTION:** TBD
**RESULT:** TBD - REQUIRES DATASHEET / FABRICATOR CONSTRAINT
**MARGIN:** TBD
**SOURCE:** Basic DC Resistance Law
**STATUS:** NEEDS DATASHEET

### Trace Temperature Rise
**DESIGN CHOICE / METHODOLOGY:** Reference IPC-2152 methodology. Note IPC-2221 calculators are rough estimates only.
**FACTORS TO DOCUMENT:** current, width, copper thickness, length, internal vs external routing, ambient temp, allowable rise, nearby copper pouring, planes, airflow, enclosure restrictions, duty cycle.
**STATUS:** TBD - REQUIRES SIMULATION / CALCULATION

### Via Current
**FABRICATOR CONSTRAINT:** Do NOT use folklore like "one via = one amp". 
**EVALUATION REQUIREMENTS:** 
- Via resistance
- Via count
- Current per via
- Thermal rise
- Layer-to-layer transfer constraints
**INPUTS REQUIRED:** Drill diameter, finished hole diameter, plating thickness, barrel length, copper temperature.
**STATUS:** TBD - REQUIRES DATASHEET

### Connector Power Loss

**INPUTS:** $I$ (TBD), $R_{CONTACT}$ (TBD - Worst-case contact resistance)
**ASSUMPTIONS:** Consider voltage drop, localized heating, and derating curves.
**EQUATION:**
$$P_{CONTACT} = I^2 \cdot R_{CONTACT}$$
**SUBSTITUTION:** TBD
**RESULT:** TBD - REQUIRES DATASHEET
**MARGIN:** TBD
**SOURCE:** Joule Heating Calculation
**STATUS:** NEEDS DATASHEET

### MOSFET Loss

**INPUTS:** $I_{RMS}$ (TBD), $R_{DS(ON),HOT}$ (TBD)
**ASSUMPTIONS:** Use $R_{DS(on)}$ at the actual junction temperature, NOT 25°C typical. Consider startup SOA, inrush, reverse conduction, avalanche energy, and parallel sharing derating.
**EQUATION:**
$$P_{CONDUCTION} = I_{RMS}^2 \cdot R_{DS(ON),HOT}$$
**SUBSTITUTION:** TBD
**RESULT:** TBD - REQUIRES DATASHEET
**MARGIN:** TBD
**SOURCE:** MOSFET Conduction Model
**STATUS:** NEEDS DATASHEET

### Current Shunt

**INPUTS:** $I$ (TBD), $R_{SHUNT}$ (TBD)
**ASSUMPTIONS:** Evaluate resolution limits, power loss heating, Kelvin routing accuracy, TCR (Temperature Coefficient of Resistance), amplifier CMR, and ADC range.
**EQUATION:**
$$V_{SHUNT} = I \cdot R_{SHUNT}$$
$$P_{SHUNT} = I^2 \cdot R_{SHUNT}$$
**SUBSTITUTION:** TBD
**RESULT:** TBD - REQUIRES DATASHEET
**MARGIN:** TBD
**SOURCE:** Ohm's Law and Power Law
**STATUS:** NEEDS DATASHEET

### Inrush

**INPUTS:** $C$ (TBD), $dV/dt$ (TBD)
**ASSUMPTIONS:** Models must incorporate input bulk caps, actuator caps, M.2 loads, external peripherals, and power daughterboards.
**EQUATION:**
$$I = C \cdot \frac{dV}{dt}$$
**SUBSTITUTION:** TBD
**RESULT:** TBD - REQUIRES SIMULATION
**MARGIN:** TBD
**SOURCE:** Capacitor Voltage-Current Relationship
**STATUS:** NEEDS SIMULATION

### Hold-Up Time

**INPUTS:** $I_{LOAD}$ (TBD), $\Delta t$ (TBD), $\Delta V_{ALLOWABLE}$ (TBD)
**ASSUMPTIONS:** Must use real parameters: PowerPath switchover time, actual input capacitance (derated), PMIC UVLO thresholds, and max compute load.
**EQUATION:**
$$C_{HOLDUP} \geq \frac{I_{LOAD} \cdot \Delta t}{\Delta V_{ALLOWABLE}}$$
**SUBSTITUTION:** TBD
**RESULT:** TBD - REQUIRES SIMULATION
**MARGIN:** TBD
**SOURCE:** Charge Conservation
**STATUS:** NEEDS SIMULATION

### Skin Effect

**INPUTS:** $\rho$ (TBD), $\omega = 2\pi f$ (TBD), $\mu$ (TBD)
**ASSUMPTIONS:** Note the difference between DC distribution and high-frequency current distribution. For DC actuator power distribution, DC resistance usually dominates. Skin depth applies to high-frequency harmonic content.
**EQUATION:**
$$\delta = \sqrt{\frac{2\rho}{\omega \mu}}$$
**SUBSTITUTION:** TBD
**RESULT:** TBD - REQUIRES CALCULATION
**MARGIN:** TBD
**SOURCE:** Electromagnetic Skin Depth
**STATUS:** CALCULATED / ESTIMATED
