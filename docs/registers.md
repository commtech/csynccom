# Registers

The SYNCCOM driver is a Swiss army knife of sorts with communication. It can handle many different situations, if configured correctly. Typically to configure it to handle your specific situation you need to modify the card's register values.

_For a complete listing of all of the configuration options please see the manual._

In HDLC mode some settings are fixed at certain values. If you are in HDLC mode and after setting/getting your registers some bits don't look correct, then they are likely fixed. A complete list of the fixed values can be found in the `CCR0` section of the manual.

_The read-only registers will return the value of the `VSTR` register upon reading._

All of the registers, except `FCR`, are tied to a single port. `FCR` on the other hand is shared between two ports on a card. You can differentiate between which `FCR` settings affects what port by the A/B labels. A for port 0 and B for port 1.

_An [`synccom_purge()`](https://github.com/commtech/csynccom/blob/master/docs/purge.md) (receive side) is required after changing the `MODE` bits in the `CCR0` register. If you need to change the `MODE` bits but don't have a clock present, change the `CM` bits to `0x7` temporarily. This will give you an internal clock to switch modes. You can then switch to your desired `CM` now that your `MODE` is locked in._

###### Support
| Code | Version |
| ---- | ------- |
| synccom-windows | 1.0.0 |
| synccom-linux | 1.0.0 |
| csynccom | 1.0.0 |


## Structure
```c
struct synccom_registers {
    /* BAR 0 */
    synccom_register reserved1[2];

    synccom_register FIFOT;

    synccom_register reserved2[2];

    synccom_register CMDR;
    synccom_register STAR; /* Read-only */
    synccom_register CCR0;
    synccom_register CCR1;
    synccom_register CCR2;
    synccom_register BGR;
    synccom_register SSR;
    synccom_register SMR;
    synccom_register TSR;
    synccom_register TMR;
    synccom_register RAR;
    synccom_register RAMR;
    synccom_register PPR;
    synccom_register TCR;
    synccom_register VSTR; /* Read-only */

    synccom_register reserved3[1];

    synccom_register IMR;
    synccom_register DPLLR;

    /* BAR 2 */
    synccom_register FCR;
};
```


## Macros
```c
SYNCCOM_REGISTERS_INIT(regs)
```

| Parameter | Type | Description |
| --------- | ---- | ----------- |
| `regs` | `struct synccom_registers *` | The registers structure to initialize |

The `SYNCCOM_REGISTERS_INIT` macro should be called each time you use the `struct synccom_registers` structure. An initialized structure will allow you to only set/receive the registers you need.


## Set
```c
int synccom_set_registers(synccom_handle h, struct synccom_registers *regs)
```

| Parameter | Type | Description |
| --------- | ---- | ----------- |
| `h` | `synccom_handle` | The handle to your port |
| `regs` | `struct synccom_registers *` | The registers you would like to set |

| Return Value | Cause |
| ------------:| ----- |
| 0 | Success |

###### Examples
```
#include <synccom.h>
...

struct synccom_registers regs;

SYNCCOM_REGISTERS_INIT(regs);

regs.CCR0 = 0x0011201c;
regs.BGR = 0;

synccom_set_registers(h, &regs);
```


## Get
```c
int synccom_get_registers(synccom_handle h, struct synccom_registers *regs)
```

| Parameter | Type | Description |
| --------- | ---- | ----------- |
| `h` | `synccom_handle` | The handle to your port |
| `regs` | `struct synccom_registers *` | The register values you would like to view |

| Return Value | Cause |
| ------------:| ----- |
| 0 | Success |

###### Examples
```
#include <synccom.h>
...

struct synccom_registers regs;

SYNCCOM_REGISTERS_INIT(regs);

regs.CCR0 = SYNCCOM_UPDATE_VALUE;
regs.BGR = SYNCCOM_UPDATE_VALUE;

synccom_get_registers(h, &regs);
```

At this point `regs.CCR0` and `regs.BGR` would be set to their respective values.


### Additional Resources
- Complete example: [`examples/registers.c`](../examples/registers.c)
- Implementation details: [`src/synccom.c`](../src/synccom.c)
