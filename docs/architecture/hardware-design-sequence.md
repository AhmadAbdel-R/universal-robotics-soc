# Hardware Design Sequence (STM32MP257)

Because the SoC acts as the central hub that influences every other subsystem, the hardware schematic capture and PCB layout must follow a strict sequential order. This document outlines the step-by-step roadmap for designing the universal robotics board around the **STMicroelectronics STM32MP257**.

> **Essential Reference:** [AN5489: Getting started with STM32MP25xx hardware development (PDF)](https://www.st.com/resource/en/application_note/an5489-getting-started-with-stm32mp25xx-mpus-hardware-development-stmicroelectronics.pdf)

## Workflow Steps

1. Architecture freeze
2. Processor/package freeze
3. Sensor/actuator requirements freeze
4. Industrial I/O freeze
5. Connector architecture
6. CubeMX resource budget
7. CubeMX peripheral allocation
8. RIF ownership verification
9. DDR verification
10. Boot/recovery verification
11. High-speed interfaces
12. Real-time interfaces
13. Industrial buses
14. Clock-tree validation
15. Pinout CSV freeze
16. Power budgeting
17. PMIC / rail architecture
18. Schematic capture
19. PCB stackup / SI verification
20. Layout
21. Design review
22. Fabrication
23. Power bring-up
24. DDR bring-up
25. Linux bring-up
26. M33 bring-up
27. Peripheral validation
28. Industrial I/O validation
29. RF / antenna tuning
30. System testing
