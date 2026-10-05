# Buck Power-Stage Calculations - TI SLVA477C

## Source and scope

Based on **Basic Calculation of a Buck Converter's Power Stage**, Brigitte Hauke, Texas Instruments, application note **SLVA477C**.

- [Included SLVA477C PDF](../../references/application-notes/slva477c.pdf)
- [Included TPS54561 datasheet](../../references/datasheets/TPS54561.pdf)
- [TI application note (PDF)](https://www.ti.com/lit/an/slva477c/slva477c.pdf)
- [TPS54561 datasheet (PDF)](https://www.ti.com/lit/ds/symlink/tps54561.pdf)
- [TPS54561DPRR purchase link - LCSC C180369](https://www.lcsc.com/product-detail/C180369.html)
- [Regulator design worksheet](regulator-design.md)
- [Rail-by-rail power budget](power-budget.md)

This is an original project summary and calculation worksheet, not a verbatim reproduction of TI's document. The supplied revision's footer says September 2026; its revision-history entry says October 2026.

**Selected regulator:** TPS54561DPRR, chosen for TI documentation and design support. Selection of the IC does not establish suitability for every rail. Rail allocation, component values, sequencing, losses and stability remain unverified.

SLVA477C addresses basic power-stage sizing in continuous conduction mode (CCM). It does not design the feedback compensation network. Use the TPS54561 datasheet for device-specific limits, compensation, timing, component recommendations and layout.

## Inputs required per rail

| Input | Value / evidence |
|---|---|
| Rail name and loads | TBD |
| Regulator input voltage, minimum / nominal / maximum | TBD - include upstream conversion and source selection |
| Output voltage and allowed total error | TBD - load datasheets |
| Maximum continuous and transient load | TBD - power budget |
| Switching-frequency range including tolerance | TBD - TPS54561 datasheet |
| Minimum guaranteed switch current limit | TBD - TPS54561 datasheet |
| Allowed ripple, overshoot and undershoot | TBD - load requirements |
| Ambient temperature and cooling conditions | TBD |
| Efficiency estimate and source | TBD - estimate, not measurement |

Repeat the checks at input, load, temperature and component-tolerance corners. Raw battery maximum is not automatically the input voltage of every regulator.

## 1. Duty cycle and conversion limits

For a first ideal estimate:

$$D_{\mathrm{ideal}}=\frac{V_{\mathrm{OUT}}}{V_{\mathrm{IN}}}$$

**Source discrepancy:** main-text Equation 1 uses $D=V_{\mathrm{OUT}}/(V_{\mathrm{IN,max}}\eta)$, while Appendix A Equation 15 prints $D=V_{\mathrm{OUT}}\eta/V_{\mathrm{IN,max}}$. These expressions disagree. Do not copy the appendix expression into a calculator. The main-text efficiency adjustment is a sizing approximation, not an exact circuit model.

For the TPS54561 asynchronous topology, include diode and switch losses using the device-specific design method. Evaluate minimum on-time at high input / low output and maximum duty cycle at low input / high output. A buck cannot maintain 5 V from a 5 V source under load simply because its minimum input rating is below 5 V.

## 2. Inductor and switch current

In ideal CCM:

$$\Delta I_L=\frac{V_{\mathrm{OUT}}(1-D)}{L f_{\mathrm{SW}}}$$

$$I_{L,\mathrm{peak}}=I_{\mathrm{OUT,max}}+\frac{\Delta I_L}{2}$$

$$I_{L,\mathrm{RMS}}=\sqrt{I_{\mathrm{OUT}}^2+\frac{\Delta I_L^2}{12}}$$

SLVA477C Sections 2-3 suggest a preliminary ripple target of 20-40% of maximum output current when no device-specific recommendation is available:

$$L_{\mathrm{initial}}=\frac{V_{\mathrm{OUT}}(1-D)}{f_{\mathrm{SW}}\Delta I_L}$$

Check minimum inductance under tolerance and DC bias, minimum switching frequency, hot DCR, core losses, temperature rise, saturation and current-limit behavior. For a peak-current-limited converter, steady-state capability must satisfy:

$$I_{\mathrm{OUT,max}}+\frac{\Delta I_L}{2}<I_{\mathrm{LIMIT,min}}$$

Include transient margin; do not equate the IC's advertised current rating with validated board capability.

## 3. External catch diode

The TPS54561 needs an external catch diode. SLVA477C Section 4 gives the CCM estimates:

$$I_{D,\mathrm{avg}}=I_{\mathrm{OUT}}(1-D)$$

$$P_D\approx V_F I_{D,\mathrm{avg}}$$

Use the diode's forward voltage at the relevant current and temperature. Check reverse-voltage rating including ringing, peak current, leakage and thermal dissipation. This loss is particularly significant on low-output-voltage rails.

## 4. Feedback resistors

With the upper resistor from output to FB and the lower resistor from FB to ground:

$$V_{\mathrm{OUT}}=V_{\mathrm{FB}}\left(1+\frac{R_{\mathrm{TOP}}}{R_{\mathrm{BOTTOM}}}\right)$$

$$R_{\mathrm{TOP}}=R_{\mathrm{BOTTOM}}\left(\frac{V_{\mathrm{OUT}}}{V_{\mathrm{FB}}}-1\right)$$

Section 5 uses divider current at least 100 times the feedback bias current as an initial accuracy rule. Follow the TPS54561's resistor recommendations and calculate total error from reference tolerance, resistor tolerances and bias current. Handle an output equal to the reference according to the datasheet.

For BOM consolidation, try a common lower resistor with different upper resistors. This does not establish that the same inductor, capacitors and compensation work on every rail.

## 5. Input capacitance

Start with the device datasheet's requirements, then check effective capacitance after DC bias, temperature and tolerance. Evaluate ripple-current capability, ESR heating, hot-plug behavior and placement.

A supplementary ideal-CCM check is:

$$I_{C_{\mathrm{IN}},\mathrm{RMS}}\approx I_{\mathrm{OUT}}\sqrt{D(1-D)}$$

A dielectric label alone does not establish effective capacitance; use the exact manufacturer's part curves.

## 6. Output capacitance

SLVA477C Section 7 provides a preliminary capacitive-ripple estimate:

$$C_{\mathrm{OUT,min}}\approx\frac{\Delta I_L}{8 f_{\mathrm{SW}}\Delta V_{\mathrm{C}}}$$

Allocate a separate ripple allowance for ESR:

$$\Delta V_{\mathrm{ESR}}\approx\Delta I_L\,ESR$$

Use effective capacitance, not just the nominal value. The application note also gives a load-release overshoot estimate:

$$C_{\mathrm{OUT,min,OS}}\approx\frac{(\Delta I_{\mathrm{OUT}})^2L}{2V_{\mathrm{OUT}}V_{\mathrm{OS}}}$$

This is an initial estimate, not proof of transient compliance. Check load-application undershoot separately and include control-loop response, ESR/ESL and the load's local decoupling.

## 7. Complete the design before reusing it

- [ ] Check every rail's actual input range, output tolerance and current demand.
- [ ] Check minimum on-time, maximum duty cycle and startup.
- [ ] Select inductor and catch diode with electrical and thermal margin.
- [ ] Select effective input/output capacitance.
- [ ] Design external compensation using the TPS54561 datasheet.
- [ ] Check gain/phase margin and load transients.
- [ ] Verify enable/Power Good logic levels, pull-ups, startup and shutdown order.
- [ ] Calculate losses and review layout/thermal performance.
- [ ] Approve common BOM items only after each rail passes.

**Status:** Reference and worksheet added; no rail calculations or component values are approved by this document.
