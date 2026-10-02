# Power Bring-Up Plan

[MEASUREMENT] Power bring-up must follow a strict, phased approach.
[CRITICAL] Do not energize actuator pass-through during initial compute bring-up.

## Bring-up Order
1. [MEASUREMENT] Board unpowered resistance checks
2. [MEASUREMENT] Current-limited source
3. [MEASUREMENT] Verify input protection
4. [MEASUREMENT] Verify source mux
5. [MEASUREMENT] Verify VIN_SYS
6. [MEASUREMENT] Verify always-on rails
7. [MEASUREMENT] Verify PMIC sequencing
8. [MEASUREMENT] Verify core rails
9. [MEASUREMENT] Verify DDR rails
10. [MEASUREMENT] Verify sensor rails
11. [MEASUREMENT] Verify reset
12. [MEASUREMENT] Verify clocks
13. [MEASUREMENT] Boot ROM
14. [MEASUREMENT] DDR
15. [MEASUREMENT] Linux
16. [MEASUREMENT] High-current actuator path LAST

## Protection tests:
- [ ] reverse polarity
- [ ] current-limited startup
- [ ] UVLO
- [ ] OVP where safe
- [ ] source switchover
- [ ] fuse path
- [ ] fault-state

## Power tests:
- [ ] regulator startup
- [ ] ripple
- [ ] load transient
- [ ] efficiency
- [ ] thermal

## High-current tests:
- [ ] start at low current
- [ ] connector drop
- [ ] trace/plane drop
- [ ] thermal camera
- [ ] step current upward
- [ ] controlled actuator fault tests

## SI tests:
- [ ] clocks
- [ ] USB
- [ ] Ethernet
- [ ] DDR training
- [ ] PCIe link
- [ ] MIPI