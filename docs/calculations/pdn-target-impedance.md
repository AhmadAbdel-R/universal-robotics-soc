# Power Distribution Network (PDN) Target Impedance Methodology

[THEORY] A robust Power Distribution Network (PDN) must provide an impedance profile below a specific target across a broad frequency spectrum to ensure voltage variations remain within acceptable limits during load transients.

## Target Impedance

[CALCULATION] The target impedance is calculated based on the maximum allowable voltage ripple and the expected transient current:
$$Z_{TARGET} = \frac{\Delta V_{ALLOWABLE}}{\Delta I_{TRANSIENT}}$$

[THEORY] **Example (Illustrative Only - Not Project Values):** 
If a power rail is permitted to deviate by 50mV during a sudden 1A load step, the required target impedance is:
$Z_{TARGET} = 50\text{m}\Omega$. 

[TBD] Actual project target impedance calculations: TBD - REQUIRES <missing parameter> (e.g., specific load current profiles and datasheet ripple tolerances for STM32MP257 core rails).

## Frequency Range

[THEORY] A common misconception is that the PDN only needs to provide low impedance up to the clock frequency ($f_{clock}$) or the knee frequency ($f_{knee}$). In reality, the PDN must provide acceptable impedance from DC through the relevant spectral content of the load transient. The digital edge rate, rather than the clock frequency alone, determines the substantial high-frequency content.

[THEORY] Different components of the PDN dominate different frequency regions:
*   Voltage Regulator Module (VRM) -> bulk capacitance -> MLCC network -> PCB planes -> IC package -> on-die capacitance.

## Knee Frequency

[THEORY] The knee frequency defines the approximate bandwidth of the digital signal's spectrum based on its rise/fall time.
$$f_{knee} \approx \frac{0.5}{t_r}$$

[DESIGN CHOICE] This project utilizes the $0.5/t_r$ convention for calculating knee frequency to maintain conservative bandwidth estimations, as opposed to the $0.35/t_r$ convention found in some older references.

[TBD] Project specific knee frequency calculations: TBD - REQUIRES <missing parameter> (e.g., precise $t_r$ edge rates of the target interfaces/loads).

## PDN Frequency Bands

[THEORY] The PDN operates across multiple frequency bands where specific elements dominate. Note that frequency boundaries are not arbitrary; they depend strictly on VRM loop response, ESL, ESR, layout inductance, capacitor values, package inductance, and load edge rate.
*   **VERY LOW:** Dominated by the power source, battery, or external adapter.
*   **LOW:** Dominated by the VRM feedback loop bandwidth.
*   **LOW-MID:** Dominated by the VRM output capacitors.
*   **MID:** Dominated by the bulk capacitors.
*   **HIGH:** Dominated by the multi-layer ceramic capacitor (MLCC) network.
*   **VERY HIGH:** Dominated by the PCB plane capacitance, package characteristics, and on-die capacitance.

## Capacitor Impedance Model

[THEORY] An ideal capacitor's impedance decreases infinitely with frequency:
$$Z_C = \frac{1}{j2\pi f C}$$

[THEORY] However, practical MLCCs contain inherent parasitic resistance and inductance. The realistic impedance profile is modeled as:
$$Z(f) = ESR + j2\pi f \cdot ESL + \frac{1}{j2\pi f \cdot C_{EFFECTIVE}}$$
*   **Below Resonance:** The capacitor acts capacitively, and impedance drops with frequency.
*   **At Self-Resonant Frequency (SRF):** The ESL and $C_{EFFECTIVE}$ reactances cancel out perfectly. The impedance bottoms out and is exactly equal to the ESR.
*   **Above Resonance:** The capacitor acts inductively due to ESL, and impedance rises with frequency.

## Self-Resonant Frequency (SRF)

[CALCULATION] The self-resonant frequency is calculated as:
$$f_{SRF} = \frac{1}{2\pi\sqrt{ESL \cdot C_{EFFECTIVE}}}$$

[DESIGN CHOICE] Rely exclusively on manufacturer impedance-vs-frequency curves rather than assuming ideal values, as parasitics heavily dominate high-frequency performance.

## MLCC Effective Capacitance and Derating

[THEORY] The actual capacitance of an MLCC in a real circuit is heavily dependent on operational parameters, vastly differing from the nominal printed value.
$$C_{EFFECTIVE} = C_{NOMINAL} \times K_{DC\_BIAS} \times K_{TEMPERATURE} \times K_{TOLERANCE} \times K_{AGING}$$

[FABRICATOR CONSTRAINT] A nominal 10µF MLCC may provide substantially less than 10µF when biased at the actual rail voltage. It is strictly required to document and evaluate dielectric type, package size, rated voltage, applied DC voltage, DC-bias derating, tolerance, temperature coefficients, and aging metrics for every chosen component.

## Anti-Resonance

[THEORY] Paralleling multiple capacitor values (e.g., 100nF, 1µF, 10µF) can create anti-resonances. This occurs when the inductive region of a higher-value capacitor interacts with the capacitive region of a lower-value capacitor, resulting in high-impedance peaks that can violate $Z_{TARGET}$.
[DESIGN CHOICE] Utilizing more capacitor values is NOT automatically better.
[DESIGN CHOICE] Do NOT rely merely on standard "100nF + 1µF + 10µF" habit templates. 
[DESIGN CHOICE] Full PDN impedance simulation is required to verify that anti-resonance peaks remain below the target impedance.

## Plane Capacitance

[THEORY] PCB power and ground planes form a distributed capacitor, offering extremely low inductance for high-frequency transient demands.
$$C_{plane} \approx \frac{\varepsilon_0 \cdot \varepsilon_r \cdot A}{d}$$
[THEORY] Bringing power and ground planes closer together (reducing $d$) significantly increases distributed capacitance and lowers loop inductance.
[DESIGN CHOICE] Do not overstate plane capacitance relative to MLCC and on-die capacitance; it is highly effective for inductance reduction but provides limited bulk charge storage.

## Load-Step Capacitance

[CALCULATION] The minimum capacitance required to support a sudden load step before the VRM can respond is:
$$C_{REQUIRED} \geq \frac{\Delta I \cdot \Delta t}{\Delta V}$$

[THEORY] However, having enough nominal capacitance does not guarantee success due to parasitic effects:
*   Voltage drop due to ESR: $\Delta V_{ESR} = \Delta I \cdot ESR$
*   Voltage drop due to inductance: $\Delta V_L = L_{PATH} \cdot \frac{di}{dt}$

[THEORY] A capacitor with sufficient $C_{REQUIRED}$ can still fail transient requirements if ESR, ESL, or path inductance is excessively high.

## PDN Results Template

[DESIGN CHOICE] The following template must be used to track PDN validation. No result may be called "PASS" until it has been simulated or measured.

| Frequency Band | PDN Impedance | Target Impedance | Margin | Dominant Component | Resonance Peak | Antiresonance Risk | Status |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| [TBD] | [TBD] | [TBD] | [TBD] | [TBD] | [TBD] | [TBD] | [TBD] |
