# Fuse Selection Calculations

**System Target:** 2S through 8S battery input, STM32MP257 universal robotics controller.

## Fuse Candidate Template

For every fuse candidate evaluated for the main input, the following parameters MUST be documented:

*   **Fuse technology:** (e.g., Ceramic surface mount, Glass tube, Blade)
*   **Rated voltage ($V_{RATED}$):**
*   **Rated current ($I_{RATED}$):**
*   **Breaking/interrupt rating ($I_{BREAKING}$):**
*   **Hold current ($I_{HOLD}$):**
*   **Trip current ($I_{TRIP}$):**
*   **Cold resistance ($R_{COLD}$):**
*   **Hot resistance ($R_{HOT}$):**
*   **Temperature derating:** (Curve or specific %/°C)
*   **Time-current curve:** (Reference to datasheet figure)
*   **$I^2t$ (Melting Integral):**
*   **Package:**
*   **PCB heating:** (Calculated at normal operating current)
*   **Fault-energy capability:**

## Required Reasoning for Selection

Fuses are non-ideal components. The selected fuse must satisfy multiple, often conflicting, criteria:

1.  **Operating Current Margin:** **THEORY:** The normal operating current must NOT sit too close to the fuse rating. Most fuses will degrade, suffer nuisance tripping, or run excessively hot if operated continuously at $>70-80\%$ of their rated current.
2.  **Environmental Factors:** **THEORY:** Ambient temperature and enclosed-board temperature significantly affect the fuse's hold current. A fuse rated for 10A at 25°C may only hold 7A at 85°C.
3.  **Transient Loading:** The fuse must survive normal operational transients without fatigue:
    *   Startup inrush current (capacitors)
    *   Wi-Fi/M.2/compute burst peaks
    *   Actuator startup and servo stall currents
    *   Motor-controller capacitor charging

### $I^2t$ Integration and Time-Current Curves

**THEORY:** A fuse does not blow instantly at its rated current. It blows based on thermal energy accumulation, characterized by the melting integral $I^2t$:

$$I^2t = \int i^2 \, dt$$

**DATASHEET REQUIREMENT:** We MUST use the manufacturer's time-current curves for transient analysis. Do NOT infer trip time from the rated current alone. For a motor stall lasting 50ms, we must check the fuse curve to ensure the stall current is safely below the minimum melting curve at $t=50ms$.

### Downstream Component Protection

**THEORY:** To protect downstream components (like MOSFETs or traces), the total clearing $I^2t$ of the fuse must be less than the fault-energy capability of the component being protected.

*   $I^2t_{FUSE\_CLEARING} < I^2t_{MOSFET\_DESTRUCTION}$
*   If this is not satisfied, the MOSFET will explode before the fuse blows, rendering the fuse largely ineffective for component protection (though it may still prevent a fire).

## Interrupt Rating Analysis ($I_{BREAKING}$)

**CRITICAL:** A fuse with an adequate continuous current rating but an inadequate breaking capability is NOT acceptable and constitutes a severe fire hazard.

When a hard short circuit occurs across a high-discharge lithium battery (e.g., a LiPo used in robotics), the prospective fault current is extremely high.

**CALCULATION:** (First-order approximation)
$$I_{SHORT} \approx \frac{V_{BAT}}{R_{TOTAL\_FAULT\_PATH}}$$

Where $R_{TOTAL\_FAULT\_PATH}$ includes:
*   Battery internal resistance ($R_{i}$)
*   Wiring resistance
*   Connector contact resistance
*   PCB trace resistance
*   Fuse $R_{COLD}$

**THEORY:** High-discharge LiPo batteries can deliver hundreds or thousands of amps into a dead short. If the prospective $I_{SHORT}$ exceeds the fuse's $I_{BREAKING}$ rating, the fuse may arc internally when it blows, failing to interrupt the current and potentially catching fire or shattering.

## Fuse Technologies

### Fast Blow vs. Slow Blow (Time-Delay)
*   **Fast Blow:** Low thermal mass. Blows quickly on overcurrent. Good for protecting sensitive electronics but susceptible to nuisance tripping from inrush currents.
*   **Slow Blow:** Higher thermal mass or specialized construction. Designed to survive temporary surges (like motor startup) while still protecting against sustained overcurrent. Often preferred for robotics.

### Resettable PTC (Polymeric Positive Temperature Coefficient)
*   **THEORY:** A PTC increases its resistance dramatically as it heats up due to overcurrent, limiting the current. When power is removed, it cools and "resets".
*   **DESIGN CHOICE:** While convenient, PTCs are generally **inappropriate** for the main battery input of high-power robotics.
    *   They have high intrinsic resistance, causing unacceptable voltage drop and $I^2R$ heating at high normal currents.
    *   They have a relatively slow trip time.
    *   They often have low maximum voltage ratings (e.g., 16V, 24V) which are incompatible with 6S or 8S systems.
    *   They have limited breaking capacity compared to true fuses.

### Electronic Fuse (eFuse)
*   **THEORY:** An active silicon device (MOSFET + Controller) that measures current and shuts off the FET when a limit is exceeded.
*   **DESIGN CHOICE:** Excellent for precise overcurrent protection, fast response, and telemetry. However, standard practice still dictates a physical, traditional fuse upstream of an eFuse to handle catastrophic silicon failures (e.g., the eFuse FET failing short).
