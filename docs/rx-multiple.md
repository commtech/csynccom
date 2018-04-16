# RX Multiple

###### Support
| Code | Version |
| ---- | ------- |
| synccom-windows | 1.0.0 |
| synccom-linux | 1.0.0 |
| csynccom | 1.0.0 |


## Get
```c
int synccom_get_rx_multiple(synccom_handle h, unsigned *status)
```

| Parameter | Type | Description |
| --------- | ---- | ----------- |
| `h` | `synccom_handle` | The handle to your port |
| `status` | `unsigned int *` | The current rx multiple value |

| Return Value | Cause |
| ------------:| ----- |
| 0 | Success |

###### Examples
```c
#include <synccom.h>
...

unsigned status;

synccom_get_rx_multiple(h, &status);
```


## Enable
```c
int synccom_enable_rx_multiple(synccom_handle h)
```

| Parameter | Type | Description |
| --------- | ---- | ----------- |
| `h` | `synccom_handle` | The handle to your port |

| Return Value | Cause |
| ------------:| ----- |
| 0 | Success |

###### Examples
```c
#include <synccom.h>
...

synccom_enable_rx_multiple(h);
```


## Disable
```c
int synccom_disable_rx_multiple(synccom_handle h)
```

| Parameter | Type | Description |
| --------- | ---- | ----------- |
| `h` | `synccom_handle` | The handle to your port |

| Return Value | Cause |
| ------------:| ----- |
| 0 | Success |

###### Examples
```c
#include <synccom.h>
...

synccom_disable_rx_multiple(h);
```


### Additional Resources
- Complete example: [`examples/rx-multiple.c`](../examples/rx-multiple.c)
- Implementation details: [`src/synccom.c`](../src/synccom.c)
