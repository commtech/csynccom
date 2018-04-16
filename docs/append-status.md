# Append Status

It is a good idea to pay attention to the status of each frame. For example, you may want to see if the frame's CRC check succeeded or failed.

The Sync Com reports this data to you by appending two additional bytes to each frame you read from the device, if you opt-in to see this data. There are a few methods of enabling this additional data.

###### Driver Support
| Code | Version |
| ---- | ------- |
| synccom-windows | 1.0.0 |
| synccom-linux | 1.0.0 |
| csynccom | 1.0.0 |


## Get
```c
int synccom_get_append_status(synccom_handle h, unsigned *status)
```

| Parameter | Type | Description |
| --------- | ---- | ----------- |
| `h` | `synccom_handle` | The handle to your port |
| `status` | `unsigned int *` | The current append status value |

| Return Value | Cause |
| ------------:| ----- |
| 0 | Success |

###### Examples
```c
#include <synccom.h>
...

unsigned status;

synccom_get_append_status(h, &status);
```


## Enable
```c
int synccom_enable_append_status(synccom_handle h)
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

synccom_enable_append_status(h);
```


## Disable
```c
int synccom_disable_append_status(synccom_handle h)
```

| Parameter | Type | Description |
| --------- | ---- | ----------- |
| `h` | `synccom_handle`| The handle to your port |

| Return Value | Cause |
| ------------:| ----- |
| 0 | Success |


###### Examples
```c
#include <synccom.h>
...

synccom_disable_append_status(h);
```


### Additional Resources
- Complete example: [`examples/append-status.c`](../examples/append-status.c)
- Implementation details: [`src/synccom.c`](../src/synccom.c)
