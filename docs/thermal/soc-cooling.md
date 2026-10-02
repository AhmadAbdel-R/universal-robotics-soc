# STM32MP257 Thermal Management

## Max Recommended Operating Temps
[DATASHEET REQUIREMENT] The maximum operating junction temperature ($T_J$) for the STM32MP257 is TBD - REQUIRES DATASHEET.

## Power Modes & Expected High-Load
[ASSUMPTION] Expected high-load scenarios will concurrently stress the NPU, GPU, CPU, and DDR interface.
[TBD - REQUIRES SIMULATION] Expected power dissipation in max-load state is TBD.

## Thermal Throttling Capabilities
[DATASHEET REQUIREMENT] The SoC supports internal temperature monitoring and thermal throttling capabilities. Thresholds are TBD.

## Cooling Approach
[DESIGN CHOICE] The baseline cooling approach involves thermal spreading through the PCB using ground planes, combined with a thermal pad.
[ASSUMPTION] Airflow may be limited depending on enclosure design.
[FABRICATOR CONSTRAINT] PCB thermal conductivity relies on copper thickness and via density constraints.

[CRITICAL] Do NOT determine heatsink size until actual dissipation is known via measurement or detailed thermal simulation.