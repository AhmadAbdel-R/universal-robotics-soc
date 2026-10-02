# Surge and Hot-Plug Analysis

**System Target:** 2S through 8S battery input, STM32MP257 universal robotics controller.

This document outlines the analysis required to ensure the system survives transient voltage events, particularly those associated with high-current robotics environments.

## Documented Transient Sources

Robotics power systems are electrically noisy and subject to severe transients:

*   **Battery Hot Plug with Wiring Inductance:** When a low-impedance battery is plugged into the system, the sudden rush of current into the input capacitors interacts with the inductance of the battery wires, creating a severe $LC$ ringing voltage spike. This voltage can easily double the nominal battery voltage.
*   **External Supply Connection:** Similar to hot-plugging, but power supplies may also introduce their own startup transients.
*   **Motor Braking / Regeneration:** When heavy motors decelerate rapidly, they act as generators, pumping energy back into the power bus. This causes the bus voltage to rise unless clamped or absorbed by a braking resistor.
*   **Load Dump:** If a heavy load (e.g., a large motor) is suddenly disconnected while drawing high current, the inductive energy in the wiring forces a voltage spike.
*   **Connector Arcing:** Making or breaking connections under load can cause high-frequency arcing, injecting severe EMI and voltage spikes into the system.
*   **Inductive Switching:** Actuators, relays, or long wiring harnesses switched on/off will generate $L \cdot di/dt$ transients.

## Protection Coordination

**CRITICAL RULE:** Do not independently select protection parts and assume the entire chain is coordinated. They interact tightly.

A robust system requires coordinated defense:

1.  **TVS Clamp + MOSFET Voltage Rating:** The TVS diode must clamp the transient voltage to a level safely below the absolute maximum $V_{DS}$ rating of the downstream protection MOSFETs.
    *   *Example:* For an 8S system (33.6V max), if an inductive spike occurs, a TVS with a $V_C$ of 55V at peak current protects a MOSFET rated for 60V.
2.  **eFuse Response Time:** The electronic fuse must detect an overcurrent or short-circuit fault and turn off its MOSFETs *before* downstream components are destroyed or the upstream physical fuse blows.
3.  **Physical Fuse Clearing:** The upstream physical fuse exists to protect against catastrophic failures that the semiconductor protection (eFuse/Ideal Diode) cannot safely clear (e.g., if the eFuse MOSFET fails short, or if a dead short occurs directly at the TVS).
4.  **Bulk Capacitance vs. Source Impedance:** Local bulk capacitance (electrolytics) helps dampen $LC$ ringing during hot-plug events by lowering the characteristic impedance of the input filter, but it also increases the initial inrush current.

### Coordinated Event Example: Hot Plug

1.  User plugs in 8S battery.
2.  Inrush current spikes due to wire inductance and board capacitance.
3.  Voltage rings up.
4.  TVS absorbs the ringing energy, clamping the peak voltage below 60V.
5.  Ideal diode controller starts up.
6.  eFuse controller begins controlled dV/dt turn-on (inrush limiting), slowly charging the main protected bus.
7.  System is now safely powered.
