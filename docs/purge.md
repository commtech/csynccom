# Purge

Between the hardware FIFO and the driver's software buffers there are multiple places data could  be stored, excluding your application code. If you ever need to clear this data and start fresh, there are a couple of methods you can use.

An `synccom_purge()` (receive side) is required after changing the `MODE` bits in the `CCR0` register. If you need to change the `MODE` bits but don't have a clock present, change the `CM` bits to `0x7` temporarily. This will give you an internal clock to switch modes. You can then switch to your desired `CM` now that your `MODE` is locked in.

###### Support
| Code | Version |
| ---- | ------- |
| synccom-windows | 1.0.0 |
| synccom-linux | 1.0.0 |
| csynccom | 1.0.0 |


## Execute
```c
synccom_purge(synccom_handle h, unsigned tx, unsigned rx)
```

| Parameter | Type | Description |
| --------- | ---- | ----------- |
| `h` | `synccom_handle` | The handle to your port |
| `tx` | `unsigned int` | Whether to purge the transmit data |
| `rx` | `unsigned int` | Whether to purge the receive data |

| Return Code | Value | Cause |
| ----------- | -----:| ----- |
| | 0 | Success |
| `SYNCCOM_TIMEOUT` | 16000 | Command timed out (missing clock) |

###### Examples
Purge both the transmit and receive data.
```c
#include <synccom.h>
...

synccom_purge(h, 1, 1);
```

Purge only the transmit data.
```c
#include <synccom.h>
...

synccom_purge(h, 1, 0);
```

Purge only the receive data.
```c
#include <synccom.h>
...

synccom_purge(h, 0, 1);
```


### Additional Resources
- Complete example: [`examples/purge.c`](../examples/purge.c)
- Implementation details: [`src/synccom.c`](../src/synccom.c)
