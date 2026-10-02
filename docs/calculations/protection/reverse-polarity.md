# Reverse Polarity Protection Comparison

**System Target:** 2S through 8S battery input, STM32MP257 universal robotics controller.

Reverse polarity protection ensures that if a user connects the battery backwards, the reverse voltage is blocked and does not destroy the board's components.

## Topologies Evaluated

### 1. Series Schottky Diode
*   **Operation:** A diode placed in series with the positive input. It naturally blocks current when reverse-biased.
*   **Voltage Drop:** High ($V_F \approx 0.3V - 0.6V$).
*   **Current:** Modest. Impractical for high currents due to thermal dissipation.
*   **Reverse Blocking:** Passive, intrinsic.
*   **Source Orientation:** High side.
*   **Fault Behavior:** Safe.
*   **Gate Limits:** N/A.
*   **Startup / Transient:** Instantaneous.
*   **Cost / Area:** Low cost, but requires significant copper area for heat sinking at higher currents.
*   **Thermal:** Poor. $P = I \cdot V_F$.

### 2. P-Channel MOSFET
*   **Operation:** A P-FET placed in the positive path. Gate is tied to ground (often through a resistor and Zener for protection). Conducts when correctly biased, blocks when reversed via the body diode and lack of $V_{GS}$.
*   **Voltage Drop:** Low ($I \cdot R_{DS(ON)}$).
*   **Current:** High.
*   **Reverse Blocking:** Passive.
*   **Source Orientation:** High side.
*   **Fault Behavior:** Safe blocking.
*   **Gate Limits:** Requires Zener diode to protect $V_{GS}$ limits (typically $\pm 20V$) on high-voltage (e.g., 8S) systems.
*   **Startup / Transient:** Fast. Can have issues with fast transients pulling the gate around.
*   **Cost / Area:** P-FETs have higher $R_{DS(ON)}$ for a given die area than N-FETs, making them more expensive and larger for high-current applications.
*   **Thermal:** Good. $P = I^2 \cdot R_{DS(ON)}$.

### 3. N-Channel MOSFET + Controller (Ideal Diode)
*   **Operation:** An N-FET in the positive path, driven by a dedicated charge-pump controller to generate a gate voltage higher than the supply.
*   **Voltage Drop:** Very Low ($I \cdot R_{DS(ON)}$ of N-FET).
*   **Current:** Very High.
*   **Reverse Blocking:** Active. Controller must detect reverse voltage and quickly discharge the gate.
*   **Source Orientation:** High side.
*   **Fault Behavior:** Relies on controller speed. If controller fails or is slow, reverse current flows.
*   **Gate Limits:** Managed by the controller.
*   **Startup / Transient:** Slower startup (charge pump time). Must evaluate transient response time of the controller during a reverse fault.
*   **Cost / Area:** Higher cost (FET + IC). N-FET is smaller than equivalent P-FET.
*   **Thermal:** Excellent.

### 4. Back-to-Back N-MOSFETs
*   **Operation:** Two N-FETs in series with opposed body diodes, driven by a controller. Allows bidirectional blocking.
*   **Voltage Drop:** Moderate (2 $\times$ $I \cdot R_{DS(ON)}$).
*   **Current:** High.
*   **Reverse Blocking:** Active, highly controlled.
*   **Source Orientation:** High side.
*   **Fault Behavior:** Can isolate the load entirely. Often used to combine reverse polarity protection with eFuse overcurrent protection.
*   **Gate Limits:** Managed by controller.
*   **Startup / Transient:** Highly configurable via controller (inrush control).
*   **Cost / Area:** Highest cost and largest area.
*   **Thermal:** Good, but losses are doubled compared to a single FET.

## Comparison Summary

| Parameter | Series Diode | P-Channel MOSFET | N-Channel + IC | Back-to-Back N-FETs + IC |
| :--- | :--- | :--- | :--- | :--- |
| **Voltage Drop** | High (~0.5V) | Low | Lowest | Low |
| **Current Capability** | Low/Medium | High | Very High | High |
| **Thermal Dissipation** | High ($I \cdot V_F$) | Low ($I^2R$) | Lowest ($I^2R$) | Low ($2 \cdot I^2R$) |
| **Reverse Blocking** | Intrinsic | Intrinsic | Active (needs fast IC) | Active (highly controlled) |
| **Complexity/Parts** | Lowest | Low (FET, Zener, Resistor) | Medium (FET, IC, caps) | High (2x FET, IC, passives) |
| **Cost** | Low | Medium | High | Highest |
| **Best For:** | Low-power logic | Medium power, 2S-4S | High power, high efficiency | Complete protection (eFuse) |
