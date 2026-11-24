# Processor Design
## Prerequistes
### Multipurpose Register
- On `EN = 1`, values are driven at *rising edge*.
- Every action (total 8) happens at *falling edge*.
- **Note:** At most 1 control must be set at any point. `EN` can remain set alongside any control.

### ROM
- There are `k` input lines and `n` input lines.
- ROM contains `2^k` words of length `n` (essentially a `2^k * n` bit table).
- **Note:** We can thing of each output bit as `k`-variable binary function.

## THE BUS
- Possible because of tristate (not possible ordinarily).
- Only one of the devices connected to the bus must output and others must be in High-Z, or else devices may be damaged.

### Arithmetic Processing and Dat a Transfer
> LITE

### Enhanced Architecture
- `OR` is always enabled?

### Accumulator Architecture
- `AR` is the source and destination of all operations.
- Many real processors follow it. We will use it to simply.
- Next task - design machine (and assembly) language for our processor.

## Basic Instruction Set
- Next task - implementing these instructions as control signals.