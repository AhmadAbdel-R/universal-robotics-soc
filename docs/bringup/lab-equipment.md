# Lab Equipment Requirements

[DESIGN CHOICE] The following lab equipment is required for bring-up:
- Current-limited bench supply, oscilloscope, differential probes, current probe
- Low-inductance ground springs, DMM, thermal camera, electronic load
- VNA for antenna/RF, near-field EMI probes, logic analyzer
- USB analyzer, Ethernet test tools, TDR/VNA

[THEORY] Explain WHY long ground clips should not be used for measuring HF regulator ripple:
Long ground clips introduce high parasitic inductance ($L$). When measuring high-frequency switching regulators, the high $di/dt$ switching currents will induce a voltage noise ($V = L \frac{di}{dt}$) across this ground loop. This artifacts as large spikes on the oscilloscope, artificially inflating the ripple measurement.