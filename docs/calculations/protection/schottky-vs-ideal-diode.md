# Schottky vs. Ideal Diode Trade Study

**System Target:** 2S through 8S battery input, STM32MP257 universal robotics controller.

This document evaluates the trade-offs between using a static Schottky diode versus a MOSFET-based ideal diode controller for reverse polarity protection and reverse current blocking.

## The Schottky Diode

**THEORY:** A Schottky diode is a semiconductor device that naturally permits current flow in one direction and blocks it in the other.

### When Schottky IS Useful
*   Simple reverse-current blocking.
*   Low component count (single part).
*   Low-power auxiliary rails (e.g., RTC battery backup, low-current logic supplies).
*   Applications with modest currents where thermal management is not an issue.

### Disadvantages
*   **Forward Voltage Loss:** A continuous voltage drop ($V_F$), typically between 0.3V and 0.6V depending on current and temperature. This directly reduces the voltage headroom available to downstream regulators.
*   **Efficiency Loss:** Power is wasted as heat.
*   **Thermal Expense:** At high currents, this heat becomes a significant problem requiring large copper pours or heatsinks.

**CALCULATION:** (Thermal Expense Example)
$$P_{DIODE} = I_{FORWARD} \cdot V_F$$

*Example methodology ONLY:* If the controller draws 10A continuously, and the Schottky diode has a $V_F$ of 0.4V at 10A:
$P_{DIODE} = 10\text{A} \cdot 0.4\text{V} = 4\text{W}$
Dissipating 4W in a surface-mount component on a densely packed robotics board is a major thermal challenge and highly undesirable.

## The MOSFET Ideal Diode

**THEORY:** An ideal diode uses an N-channel (or P-channel) MOSFET driven by a dedicated controller IC. When forward-biased, the FET is turned fully on, acting like a very low-value resistor. When reverse-biased, the controller turns the FET off, blocking current.

### Advantages
*   **Drastically Reduced Power Loss:** The power dissipation is defined by the MOSFET's on-resistance.
$$P_{MOSFET} = I^2 \cdot R_{DS(ON),HOT}$$
For a typical modern power MOSFET, $R_{DS(ON)}$ might be $2\text{m}\Omega$.
At 10A: $P_{MOSFET} = (10\text{A})^2 \cdot 0.002\Omega = 0.2\text{W}$.
This is a 20x reduction in heat compared to the Schottky example.
*   **Negligible Voltage Drop:** Preserves maximum voltage headroom for the system.

### Disadvantages and Design Considerations
*   **Controller Complexity:** Requires a specialized IC (often with a charge pump for N-FETs), increasing BOM count and cost.
*   **Active Reverse Operation:** Unlike a Schottky, an ideal diode relies on the active controller to detect a reverse voltage condition and actively discharge the MOSFET gate to turn it off.
*   **Transient Stress:** The speed at which the controller can turn off the FET dictates how much reverse current flows before blocking occurs. Fast reverse transients can stress the system.
*   **Failure Modes:** If the controller fails, or the FET fails short, reverse protection is lost.
*   **Safe Operating Area (SOA):** During turn-on or fault conditions, the controller may operate the FET in its linear region to regulate current. The FET's SOA must be carefully evaluated to ensure it can survive the thermal stress of linear operation.
