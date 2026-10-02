# Fiber-Weave Effect and Signal Delay

## Glass-Weave Effect

(THEORY)
PCB dielectrics are typically composed of fiberglass woven into a resin matrix. The local dielectric constant ($\varepsilon_r$) is not strictly uniform. In a differential pair, it is possible for one trace to run directly over a glass bundle while the other runs primarily over resin. 
This creates an effective Dk mismatch between the two lines, leading to **differential skew**. This effect becomes highly problematic for long routes, fast edge rates, and tightly phase-matched interfaces.

## Mitigation

(DESIGN CHOICE)
Strategies to evaluate include:
- Utilizing spread-glass laminates.
- Routing traces at a slight angle relative to the glass weave.
- Using wider traces that span both glass and resin more evenly.
- Carefully selecting specific glass styles (e.g., avoiding loose weaves).
- Keeping critical routing lengths short.
- Employing deterministic deskew loops.

*Do NOT hard-code a specific routing angle as universally correct; the mitigation must match the board and fabricator constraints.*

## Differential Skew

(THEORY)
For a geometric mismatch, the skew in time is:
$$\Delta t = \frac{\Delta L}{v_p}$$
However, **fiber-weave skew exists EVEN if the CAD physical trace lengths are identical**. Length matching in CAD is necessary but not always sufficient for critical high-speed pairs.

## Propagation Delay

(THEORY)
Microstrip:
$$t_{delay} = \frac{L \cdot \sqrt{\varepsilon_{effective}}}{c}$$
Stripline:
$$t_{delay} \approx \frac{L \cdot \sqrt{\varepsilon_r}}{c}$$

## Trace Length vs Electrical Length

(THEORY)
A trace becomes electrically significant when its propagation delay is non-negligible relative to the signal's rise time. 
Do NOT decide on the necessity of transmission-line treatment based solely on the clock frequency. The determining factors are the edge rate, trace length, and resulting propagation delay.
