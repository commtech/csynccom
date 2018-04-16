# Append Timestamp

###### Windows
[`KeQuerySystemTime`](http://msdn.microsoft.com/en-us/library/windows/hardware/ff553068.aspx) is used to acquire the timestamp upon complete reception of a frame.

###### Linux
[`do_gettimeofday`](http://www.fsl.cs.sunysb.edu/kernel-api/re29.html) is used to acquire the timestamp upon complete reception of a frame.

###### Support
| Code | Version |
| ---- | ------- |
| synccom-windows | 1.0.0 |
| synccom-linux | 1.0.0 |
| csynccom | 1.0.0 |


## Get
```c
int synccom_get_append_timestamp(synccom_handle h, unsigned *status)
```

| Parameter | Type | Description |
| --------- | ---- | ----------- |
| `h` | `synccom_handle` | The handle to your port |
| `status`  | `unsigned int *` | The current `append timestamp` value |

| Return Value | Cause |
| ------------:| ----- |
| 0 | Success |

###### Examples
```c
#include <synccom.h>
...

unsigned status;

synccom_get_append_timestamp(h, &status);
```


## Enable
```c
int synccom_enable_append_timestamp(synccom_handle h)
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

synccom_enable_append_timestamp(h);
```


## Disable
```c
int synccom_disable_append_timestamp(synccom_handle h)
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

synccom_disable_append_timestamp(h);
```


### Additional Resources
- Complete example: [`examples/append-timestamp.c`](../examples/append-timestamp.c)
- Implementation details: [`src/synccom.c`](../src/synccom.c)
