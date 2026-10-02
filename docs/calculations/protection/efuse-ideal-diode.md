# eFuse and Ideal-Diode Engineering

**System Target:** 2S through 8S battery input, STM32MP257 universal robotics controller.

This document details the concepts and engineering parameters for active power protection using eFuses and Ideal Diodes.

## Core Concepts

*   **Electronic Fuse (eFuse):** An active integrated circuit that drives a pass MOSFET to provide controlled power delivery. It typically offers:
    *   **Controlled Inrush (Soft Start):** Limits the surge current into empty capacitors by regulating the dV/dt of the output voltage.
    *   **Overcurrent Protection:** Actively monitors current and limits it to a set threshold.
    *   **Short-Circuit Protection:** Fast-trip response to rapidly shut off the MOSFET during a hard short to prevent damage.
*   **Ideal Diode:** A MOSFET-based circuit that emulates a diode with near-zero forward voltage drop, used for low-loss reverse polarity protection and ORing supplies.
*   **Combined Architectures:** Many modern power management ICs combine ideal diode controllers with eFuse capabilities, driving back-to-back N-channel MOSFETs. This provides comprehensive protection: reverse polarity, inrush control, and overcurrent fault clearing in a single subsystem.

## Key Engineering Parameters

When evaluating an eFuse/Ideal Diode controller, the following parameters must be analyzed:

1.  **Operating Voltage Range:** Must comfortably support the max voltage of an 8S battery (33.6V) plus operational margins. Controllers rated for 40V, 60V, or 65V are typical candidates.
2.  **Current Limit Accuracy:** How precisely can the overcurrent threshold be set? This determines how closely the system can operate to its maximum limits without nuisance tripping.
3.  **Response Time:**
    *   *Reverse Current Response:* Time to turn off the ideal diode FET when current reverses. Must be fast (microseconds) to prevent system brownout or battery damage.
    *   *Short-Circuit Response:* Time to detect a hard short and pull down the eFuse gate. Must be extremely fast to protect the FETs.
4.  **Safe Operating Area (SOA) Management:** During fault handling or inrush, the MOSFET operates in its linear region, dissipating immense power. The controller must ensure the FET stays within its thermal SOA.
5.  **Inrush Capacitance Limit:** The maximum downstream capacitance the eFuse can charge without tripping its own thermal or timeout protections.
6.  **Fault Behavior:** Does the controller latch off after a fault, requiring a power cycle or MCU reset? Or does it auto-retry (hiccup mode)? **DESIGN CHOICE:** For robotics, MCU-controlled latch-off or careful hiccup modes are usually preferred to prevent continuous hammering into a dead short.

## Controller Evaluation context

This protection architecture relates directly to the evaluation of controllers like the **LM7480** (Ideal Diode Controller) and **TPS4811-Q1** (Smart High-Side Driver / eFuse) mentioned in the broader power architecture.

*   *LM7480-x:* Focuses on ideal diode ORing and reverse battery protection, driving external N-FETs.
*   *TPS4811-Q1:* Focuses on robust eFuse capabilities, inrush control, and load diagnostics.

The final design will utilize such controllers to implement the active protection chain defined in the [README](file:///c:/Users/ahmad/OneDrive/Documents/GitHub/universal-robotics-soc/docs/calculations/protection/README.md).
