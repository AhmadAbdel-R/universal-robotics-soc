# Power Routing and Thermal Constraints

## PCB Current-Carrying Methodology

(THEORY)
Power routing and trace width for current-carrying capability are based on **IPC-2152** methodology.

**IPC-2221 vs IPC-2152:**
Older IPC-2221 calculators are useful for rough, conservative estimates but are NOT sufficient for final verification of a compact, high-density robotics PCB. IPC-2152 incorporates extensive thermal testing. Design validation should use IPC-2152-style temperature-rise analysis, manufacturer data, numerical analysis, and physical thermal validation.

## PCB Trace Resistance

(THEORY)
The DC resistance of a trace is given by:
$$R_{DC} = \frac{\rho \cdot L}{W \cdot T}$$
*Note: Real finished copper thickness ($T$) may differ significantly from the nominal starting oz values due to plating processes.*

## Trace Current / Temperature Rise

(CALCULATION / TBD)
For critical power paths, document the following parameters:
- Current requirement
- Trace width and length
- Finished copper thickness
- Internal vs External layer location
- Maximum ambient temperature
- Allowable temperature rise ($\Delta T$)
- Proximity of nearby large copper pours or adjacent planes (which act as heatsinks)
- Airflow / Enclosure constraints
- Duty cycle of the current

*Designs must check BOTH the thermal limit (heating) AND the voltage drop ($I \cdot R$) to ensure functionality.*

## High-di/dt Power Loops

(THEORY / DESIGN CHOICE)
For every switching buck converter, the critical loops must be identified and minimized:
- **INPUT HOT LOOP**: High-side switch $\rightarrow$ low-side switch $\rightarrow$ input ceramic bypass capacitor $\rightarrow$ back to source.
- **OUTPUT LOOP**: Inductor $\rightarrow$ output capacitors $\rightarrow$ load/return.

The input hot loop has the highest $di/dt$ and must be physically routed as compactly as possible to minimize loop inductance and EMI.

## Switch-Node Parasitic Capacitance

(THEORY)
Increasing the copper area of a switch-node (SW) polygon reduces thermal resistance and DC resistance but increases parasitic capacitance to nearby reference planes.
$$i = C_{parasitic} \cdot \frac{dv}{dt}$$
Because the SW node experiences huge $dv/dt$ swings, large parasitic capacitance drives significant common-mode noise and EMI. The designer must balance thermal/resistance needs against EMI/capacitance limits.

## Tool Reference Table

(DESIGN CHOICE)
No single calculator is unquestionable truth. Below is a reference for the tools used in this design:

| Tool | Useful For | Not Sufficient For | Inputs Required | Outputs | Limitations |
| :--- | :--- | :--- | :--- | :--- | :--- |
| **JLCPCB Impedance Calculator** | Fabrication verification | Complex structures, frequency-dependent loss | Stackup, trace geom | Impedance | Limited material selection visibility |
| **KiCad PCB Calculator** | Quick estimates (track width, via, spacing) | Final thermal validation | Trace geom, current | Rise, $R$, Drop | Relies on simplified IPC models |
| **Saturn PCB Design Toolkit** | IPC-2152 temp rise, via current, basic SI | 3D EM, full board PI | Geom, currents, stackup | Temp rise, $Z$, delay | 2D analytical approximations |
| **IPC-2152 calculators** | Baseline trace sizing | Coupled thermal interaction | Geom, $\Delta T$ | Current cap | Doesn't know adjacent heat sources |
| **Manufacturer Regulator Tools** | Compensation, efficiency | Board-level parasitics | $V_{in}, V_{out}, I, L, C$ | Bode, losses | Assumes ideal layout |
| **LTspice / ngspice / PSpice** | Circuit-level transient & AC analysis | 3D layout parasitics | SPICE netlist | V/I waveforms | Depends on accurate parasitic models |
| **Python Notebooks** | Custom PDN impedance calculations | Unmodeled EM effects | Stackup math | Graphs, Data | Model accuracy limit |
| **Field Solvers** | Final 3D EM validation | Quick iterative routing | Full 3D layout | S-params, Z | High setup/run time cost |
