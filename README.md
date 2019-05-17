# CableWindingMechanism

#### Objective
A telecommunications contractor needs your team to design a device that can
accurately extend and retract a length of cable.

The device must be able to wind out any length consistently. 

It must also be able to wind the same length back in.

The operator should be able to have some way to see how much cable has been
dispensed.

The device must also have an emergency kill device.

#### Features
- outLever : releases wire from the spool
- retLever : rewinds spool
- resetButton : complete retracts spool
- killSwitch : stops all processes and breaks main task loop, allows for reset

#### To-Do List
- [x] Fix bug where motorEncoder surpasses 0 after reset() call
- [ ] Fix bug where retLever continues to function when the (motorEncoder >= 0)
