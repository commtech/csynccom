# TX Modifiers

| Modifiers | Value | Description |
| --------- | -----:| ----------- |
| `XF` | 0 | Normal transmit (disable modifiers) |
| `XREP` | 1 | Transmit frame repeatedly |
| `TXT` | 2 | Transmit frame on timer |
| `TXEXT` | 4 | Transmit frame on external signal |

###### Support
| Code | Version |
| ---- | ------- |
| synccom-windows | 1.0.0 |
| synccom-linux | 1.0.0 |
| csynccom | 1.0.0 |

## Get
```c
int synccom_get_tx_modifiers(synccom_handle h, unsigned *modifiers)
```

| Parameter | Type | Description |
| --------- | ---- | ----------- |
| `h` | `synccom_handle` | The handle to your port |
| `modifiers` | `unsigned int *` | The current tx modifiers value |

| Return Value | Cause |
| ------------:| ----- |
| 0 | Success |

###### Examples
```
#include <synccom.h>
...

unsigned modifiers;

synccom_get_tx_modifiers(h, &modifiers);
```


## Set
```c
int synccom_set_tx_modifiers(synccom_handle h, unsigned modifiers)
```

| Parameter | Type | Description |
| --------- | ---- | ----------- |
| `h` | `synccom_handle` | The handle to your port |
| `modifiers` | `unsigned int` | What tx modifiers you would like to set |

| Return Value | Cause |
| ------------:| ----- |
| 0 | Success |

###### Examples
```
#include <synccom.h>
...

synccom_set_tx_modifiers(h, TXT | XREP);
```


### Additional Resources
- Complete example: [`examples/tx-modifiers.c`](../examples/tx-modifiers.c)
- Implementation details: [`src/synccom.c`](../src/synccom.c)
