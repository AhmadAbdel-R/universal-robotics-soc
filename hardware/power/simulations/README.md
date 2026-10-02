# Power Simulations Framework

[DESIGN CHOICE] Intended simulation tools: LTspice, ngspice, vendor PSpice models, Python.

## Future Simulations List
1. [SIMULATION] Battery hot plug
2. [SIMULATION] External supply hot plug
3. [SIMULATION] Battery/external switchover
4. [SIMULATION] Source dropout
5. [SIMULATION] Compute load step
6. [SIMULATION] Wi-Fi burst
7. [SIMULATION] NPU load step
8. [SIMULATION] M.2 load
9. [SIMULATION] Actuator load step
10. [SIMULATION] Short-circuit event
11. [SIMULATION] Input filter stability
12. [SIMULATION] Regulator startup
13. [SIMULATION] Regulator ripple
14. [SIMULATION] PDN impedance vs frequency
15. [SIMULATION] Anti-resonance
16. [SIMULATION] High-current MOSFET thermal loss

## Documentation Requirements
[DESIGN CHOICE] Every result must record:
- Simulation tool and version
- Model source
- Schematic version
- Component values
- Assumptions
- Temperature
- Source voltage
- Load
- Result plot
- Engineering conclusion
- Pass/Fail criterion

[CRITICAL] Do not save screenshots without context.