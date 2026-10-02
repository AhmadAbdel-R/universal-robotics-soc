# PCB Stackup and Materials

## Stackup Parameters

- **Fabricator**: JLCPCB (FABRICATOR CONSTRAINT)
- **Board type**: TBD - Standard vs HDI (DESIGN CHOICE)
- **Layer count**: TBD - Target 6-10 layers (DESIGN CHOICE)
- **Total thickness**: TBD (DESIGN CHOICE)
- **Copper per layer**: TBD - Nominal oz values; actual finished copper may differ (FABRICATOR CONSTRAINT)
- **Core materials**: TBD (DESIGN CHOICE)
- **Prepreg materials**: TBD (DESIGN CHOICE)
- **Dielectric thicknesses**: TBD (FABRICATOR CONSTRAINT)
- **Dk / Df**: TBD (FABRICATOR CONSTRAINT)
- **Tg / Glass style**: TBD (FABRICATOR CONSTRAINT)
- **Impedance tolerance**: TBD (FABRICATOR CONSTRAINT)
- **Via types**: TBD - through, microvia dimensions, buried, backdrill capability (DESIGN CHOICE / FABRICATOR CONSTRAINT)
- **Minimum traces / spaces**: TBD (FABRICATOR CONSTRAINT)

## JLCPCB Material Data

Current JLC impedance-calculator parameters will be used. The exact production material will be recorded.
*TBD - REQUIRES material selection from JLC.* (Do not use generic nominal FR-4 parameters; Dk DESIGN VALUE must be specified).

## Dielectric Selection

(THEORY / DESIGN CHOICE)
Dielectric choice critically affects impedance, propagation delay, high-frequency loss, skew, thermal stability, cost, and manufacturing. Glass weave impacts skew, while Dk tolerance limits impedance control. Df affects insertion loss. JLCPCB-supported controlled-impedance laminates are preferred. Standard FR-4 can often be utilized for PCIe Gen2, LPDDR4, USB, and MIPI when appropriately engineered, avoiding unnecessary costs associated with materials like Rogers unless necessitated by specific SI constraints.

## Recovered Stackup

(ASSUMPTION / TBD)
OUTER MICROSTRIP DIELECTRIC HEIGHT: TBD - RESELECT FROM JLCPCB IMPEDANCE CALCULATOR
INNER STRIPLINE REFERENCE SPACING: TBD - RESELECT FROM JLCPCB IMPEDANCE CALCULATOR

## Build-Up Justification

(DESIGN CHOICE)
The final stackup is designed to achieve:
- BGA escape routing density (STM32MP257 in TFBGA436, 0.8mm pitch)
- Short via transitions to minimize stubs
- Controlled impedance geometries
- Adjacent reference planes for signal return
- Low loop inductance for PDN
- Efficient power distribution
- Lower via-stub length

## Layer Pairing

(DESIGN CHOICE)
Every high-speed signal layer must have an adjacent reference plane.
*TBD - Generate arrangement from selected JLC stackup.*

## Stackup Symmetry

(DESIGN CHOICE)
A symmetric stackup is preferred to ensure warpage control, lamination balance, copper balance, and fabrication repeatability.

## Fabricator Assumptions

(FABRICATOR CONSTRAINT)
Any calculation depending on PCB construction must reference: FABRICATOR, STACKUP ID, MATERIAL, COPPER, DIELECTRIC HEIGHT, DK, IMPEDANCE TOLERANCE. Generic internet FR-4 parameters are invalid for precise engineering.
