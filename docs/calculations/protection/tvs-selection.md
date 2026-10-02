# TVS Selection Procedure

**System Target:** 2S through 8S battery input, STM32MP257 universal robotics controller.

## TVS Candidate Template

For each Transient Voltage Suppressor (TVS) evaluated, document the following parameters:

*   **Reverse Standoff Voltage ($V_{RWM}$):**
*   **Breakdown Voltage ($V_{BR}$):**
*   **Clamping Voltage ($V_{C}$):**
*   **Peak Pulse Current ($I_{PP}$):**
*   **Peak Pulse Power ($P_{PP}$):**
*   **Dynamic Resistance ($R_{DYN}$):**
*   **Pulse Waveform:** (e.g., 10/1000 µs, 8/20 µs)
*   **Package:**
*   **Temperature derating:**
*   **Capacitance:**
*   **Leakage Current ($I_{R}$):**

## Fundamental Selection Relationship

The selection of a TVS diode must satisfy the following critical inequality:

**Normal Max Source Voltage < $V_{RWM}$ < $V_{BR}$ < $V_{C}$ (@ expected surge $I_{PP}$) < Abs Max Rating of Downstream Components**

**CRITICAL RULE:** Do NOT simply choose a "36V TVS for a 36V system." A TVS labeled as "36V" might mean its $V_{RWM}$ is 36V, but its $V_{C}$ during a surge could be over 50V. If the downstream MOSFET is rated for 40V, the TVS will fail to protect it.

## Considerations for 8S Systems

An 8S Li-ion system has a nominal voltage of ~29.6V and a maximum charge voltage of 33.6V.

When selecting $V_{RWM}$, consider:
*   **Max battery charging voltage:** 33.6V
*   **Charger tolerance:** (e.g., +1%)
*   **Regenerative braking voltage rise:** Motors acting as generators can temporarily raise the bus voltage above the battery's resting voltage. The TVS must not clamp this normal operational regeneration.

When evaluating $V_{C}$, consider the transient sources:
*   **Wiring-inductance overshoot:** ($V = L \cdot di/dt$) upon sudden current interruption.
*   **Load dump / Hot plug:** Connecting the battery with long, inductive wires.
*   **Downstream ratings:** For an 8S system, the downstream components (MOSFETs, eFuses, regulators) are typically rated for 40V, 60V, or 65V.

**CALCULATION:** You must model the actual clamp voltage at the expected pulse current. If the expected transient current is 20A, look at the $V_C$ vs. $I_{PP}$ curve (or calculate using $R_{DYN}$) to ensure $V_C$ at 20A is safely below the downstream component's absolute maximum rating.

## TVS Energy Analysis

**THEORY:** A TVS diode absorbs the energy of a transient pulse. The energy is the integral of voltage and current over the pulse duration:

$$E = \int v(t) \cdot i(t) \, dt$$

**DESIGN CHOICE:** Do NOT select a TVS from headline peak-power ratings alone (e.g., "1500W"). That power rating is strictly tied to a specific waveform (like 10/1000 µs).

For any expected transient, document:
1.  Transient source
2.  Pulse duration
3.  Expected current
4.  Resulting clamp voltage
5.  Repetition rate (Is it a one-time hot-plug or a repetitive switching spike?)
6.  Thermal recovery time

If the energy of the transient exceeds the TVS's thermal capacity, it will fail (typically failing short, which then blows the upstream fuse).

## ESD vs. Surge vs. Power TVS

**THEORY:** It is critical to distinguish between different types of transient protection. They are fundamentally different problems requiring different silicon geometries.

*   **ESD Diode:** Designed for electrostatic discharge. Very low energy (microjoules), very fast response (picoseconds), low capacitance (critical for high-speed signals like USB or Ethernet). Used on signal pins.
*   **Power TVS (Surge):** Designed for heavy inductive spikes or load dumps. Substantially higher energy (joules), slower response than ESD, high capacitance. Used on power buses.

**CRITICAL RULES:**
*   Do not use a USB ESD suppressor array as battery surge protection; it will instantly vaporize under a power transient.
*   Do not put a large, high-capacitance power TVS on a high-speed data line; the capacitance will severely distort the signal integrity.
