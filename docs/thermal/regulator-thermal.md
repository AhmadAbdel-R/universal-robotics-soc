# Regulator Thermal Estimation

## Thermal Resistance Network
[THEORY] Heat flows through multiple paths, establishing a thermal resistance network:
JUNCTION $\rightarrow$ PACKAGE $\rightarrow$ PCB/COPPER $\rightarrow$ AIR/HEATSINK/ENCLOSURE

## Metric Definitions and Usage
[THEORY] $\theta_{JA}$, $\theta_{JC}$, $\theta_{JB}$, $\Psi_{JT}$, and $\Psi_{JB}$ are NOT interchangeable.
- [DATASHEET REQUIREMENT] $\theta_{JA}$ (Junction-to-Ambient) depends heavily on the JEDEC standard test PCB and cannot be blindly used for custom board layout calculations.
- [THEORY] Do NOT simply calculate $T_J = T_A + P \times \theta_{JA}$.
- [DESIGN CHOICE] Prefer the use of thermal characterization parameters ($\Psi_{JT}$, $\Psi_{JB}$), manufacturer simulation tools, detailed board simulation, and physical measurement.

## Estimation Methodology
[CALCULATION] A more accurate estimation using top surface temperature ($T_T$) measured via thermal camera or thermocouple:
$$ T_J = T_T + P_{total} \times \Psi_{JT} $$
Where $P_{total}$ is the total power dissipated in the package (TBD - REQUIRES SIMULATION).