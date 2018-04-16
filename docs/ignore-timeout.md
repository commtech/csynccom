# Ignore Timeout

###### Support
| Code | Version |
| ---- | ------- |
| synccom-windows | 1.0.0 |
| synccom-linux | 1.0.0 |
| csynccom | 1.0.0 |


## Get
```c
int synccom_get_ignore_timeout(synccom_handle h, unsigned *status)
```

| Parameter | Type | Description |
| --------- | ---- | ----------- |
| `h` | `synccom_handle` | The handle to your port |
| `status` | `unsigned int *` | The current ignore timeout value |

| Return Value | Cause |
| ------------:| ----- |
| 0 | Success |


###### Examples
```c
#include <synccom.h>
...

unsigned status;

synccom_get_ignore_timeout(h, &status);
```


## Enable
```c
int synccom_enable_ignore_timeout(synccom_handle h)
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

synccom_enable_ignore_timeout(h);
```


## Disable
```c
int synccom_disable_ignore_timeout(synccom_handle h)
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

synccom_disable_ignore_timeout(h);
```


### Additional Resources
- Complete example: [`examples/ignore-timeout.c`](../examples/ignore-timeout.c)
- Implementation details: [`src/synccom.c`](../src/synccom.c)
