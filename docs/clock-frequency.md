# Clock Frequency

The Sync Com device has a programmable clock that can be set anywhere from 20 KHz to 200 MHz. However, this is not the full operational range of a Sync Com port, only the range that the on-board clock can be set to.

Using one of the synchronous modes you can only receive data consistently up to 30 MHz (when you are using an external clock). If you are transmitting data using an internal clock, you can safely receive data consistently up to 50 MHz.

Lower clock rates (less than 1 MHz for example) can take a long time for the frequency generator to finish. If you run into this situation we recommend using a larger frequency and then dividing it down to your desired baud rate using the `BGR` register.

_If you are receiving timeout errors when using slow data rates you can bypass the safety checks by using the [`synccom_enable_ignore_timeout()`](https://github.com/commtech/csynccom/blob/master/docs/ignore-timeout.md) option._

###### Support
| Code | Version |
| ---- | ------- |
| synccom-windows | 1.0.0 |
| synccom-linux | 1.0.0 |
| csynccom | 1.0.0 |


## Set
```c
int synccom_set_clock_frequency(synccom_handle h, unsigned frequency)
```

| Parameter | Type | Description |
| --------- | ---- | ----------- |
| `h` | `synccom_handle` | The handle to your port |
| `frequency` | `unsigned` | The new clock frequency (Hz) |

| Return Code | Value | Cause |
| ----------- | -----:| ----- |
| | 0 | Success |
| `SYNCCOM_INVALID_PARAMETER` | 16005 | Clock frequency is out of range (15,000 to 270,000,000) |


###### Examples
```c
#include <synccom.h>
...

/* 18.432 MHz */
synccom_set_clock_frequency(h, 18432000);
```


### Additional Resources
- Complete example: [`examples/clock-frequency.c`](../examples/clock-frequency.c)
- Implementation details: [`src/synccom.c`](../src/synccom.c)
