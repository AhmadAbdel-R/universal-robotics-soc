# Protection Engineering Overview

**System Target:** 2S through 8S battery input, STM32MP257 processor-based universal robotics controller.

This directory contains the engineering analysis, component selection, and design justification for the power protection architecture of the controller. The protection system is crucial to ensure that faults, transient events, or user errors (like reverse polarity) do not permanently damage the board or connected peripherals.

## The Protection Chain

The typical protection chain, moving from the external connector inward, is structured as follows:

**BATTERY CONNECTOR $\rightarrow$ FUSE $\rightarrow$ TVS/TRANSIENT CLAMP $\rightarrow$ REVERSE-POLARITY/IDEAL DIODE $\rightarrow$ EFUSE/INRUSH CONTROL $\rightarrow$ PROTECTED BATTERY BUS**

### Interaction and Ordering Constraints

While the above is a typical order, the precise ordering is highly dependent on system requirements and the characteristics of specific components.

1.  **Fuse placement:** Typically placed as close to the connector as possible. **THEORY:** Its purpose is to physically break the circuit in the event of a catastrophic short circuit that other protection mechanisms cannot clear, preventing fire or severe board damage. It MUST be placed before bulk capacitance.
2.  **TVS placement:** Usually placed near the connector, often after the fuse. **THEORY:** Placing the TVS after the fuse allows the fuse to blow if the TVS fails short due to a massive sustained overvoltage. However, if the fuse is slow, the TVS might safely absorb a transient without blowing the fuse.
3.  **Reverse Polarity vs. TVS:** If the TVS is placed before reverse polarity protection, a reverse connection might forward-bias the TVS. Standard unidirectional TVS diodes will conduct heavily in reverse, essentially shorting the battery. **DESIGN CHOICE:** For systems with high-current batteries, reverse polarity protection (or a bidirectional TVS, though less optimal for clamping margin) must often precede the unidirectional TVS, or the fuse must be relied upon to clear a reverse-polarity event.
4.  **eFuse and Inrush:** The eFuse handles controlled turn-on (inrush limiting) and active overcurrent/short-circuit protection. It is typically the final stage before the main protected bus, protecting upstream components from downstream faults.

## Sub-Documents

The following documents detail specific aspects of the protection architecture:

*   [Fuse Selection](file:///c:/Users/ahmad/OneDrive/Documents/GitHub/universal-robotics-soc/docs/calculations/protection/fuse-selection.md) - Detailed analysis of fuse parameters, $I^2t$ ratings, and interrupt capabilities.
*   [TVS Selection](file:///c:/Users/ahmad/OneDrive/Documents/GitHub/universal-robotics-soc/docs/calculations/protection/tvs-selection.md) - Transient Voltage Suppressor selection, clamping voltages, and energy limits.
*   [Reverse Polarity Protection](file:///c:/Users/ahmad/OneDrive/Documents/GitHub/universal-robotics-soc/docs/calculations/protection/reverse-polarity.md) - Comparison of series diodes, P-FETs, and N-FETs.
*   [Schottky vs. Ideal Diode](file:///c:/Users/ahmad/OneDrive/Documents/GitHub/universal-robotics-soc/docs/calculations/protection/schottky-vs-ideal-diode.md) - Trade study on static vs. active diode topologies.
*   [Surge and Hot-Plug Analysis](file:///c:/Users/ahmad/OneDrive/Documents/GitHub/universal-robotics-soc/docs/calculations/protection/surge-hotplug.md) - Analysis of inductive spikes, connector arcing, and load dumps.
*   [eFuse and Ideal-Diode Engineering](file:///c:/Users/ahmad/OneDrive/Documents/GitHub/universal-robotics-soc/docs/calculations/protection/efuse-ideal-diode.md) - Active protection architectures and controller evaluation.
