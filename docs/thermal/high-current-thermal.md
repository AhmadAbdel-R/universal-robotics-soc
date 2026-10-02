# High-Current Thermal Considerations

## Current Path Bottlenecks
[THEORY] The hottest point in a high-current path may NOT be the widest copper region. Bottlenecks cause localized heating.
[DESIGN CHOICE] Pay special attention to:
- Connector pins, mating surfaces, and neckdowns routing into components.
- Via transitions between layers.
- MOSFET thermal pads.
- Shunt resistors and fuse pads.
- Plane bottlenecks near mechanical cutouts.

## Convection
[THEORY] Heat removal from the PCB relies on both natural and forced convection.
[ASSUMPTION] Analysis should initially perform natural vs forced convection analysis to determine baseline requirements.

## Thermal Vias
[DESIGN CHOICE] Thermal via design must balance thermal resistance and manufacturability.
[FABRICATOR CONSTRAINT] Considerations include:
- Via count and array pitch.
- Via diameter.
- Copper plating thickness.
- Solder wicking prevention.
- Use of via-in-pad (requires filling and capping to prevent solder starvation).