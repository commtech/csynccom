# Memory Cap

If your system has limited memory available, there are safety checks in place to prevent spurious incoming data from overrunning your system. Each port has an option for setting it's input and output memory cap.


###### Support
| Code | Version |
| ---- | ------- |
| synccom-windows | 1.0.0 |
| synccom-linux | 1.0.0 |
| csynccom | 1.0.0 |


## Structure
```c
struct synccom_memory_cap {
    int input;
    int output;
};
```


## Macros
```c
SYNCCOM_MEMORY_CAP_INIT(memcap)
```

| Parameter | Type | Description |
| --------- | ---- | ----------- |
| `memcap` | `struct synccom_memory_cap *` | The memory cap structure to initialize |

The `SYNCCOM_MEMORY_CAP_INIT` macro should be called each time you use the `struct synccom_memory_cap` structure. An initialized structure will allow you to only set/receive the memory cap you need.


## Get
```c
int synccom_get_memory_cap(synccom_handle h, const struct synccom_memory_cap *memcap)
```

| Parameter | Type | Description |
| --------- | ---- | ----------- |
| `h`       | `synccom_handle` | The handle to your port |
| `memcap`  | `const struct synccom_memory_cap *` | The current `memory cap` values |

| Return Value | Cause |
| ------------:| ----- |
| 0 | Success |

###### Examples
```
#include <synccom.h>
...

struct synccom_memory_cap memcap;

SYNCCOM_MEMORY_CAP_INIT(memcap);

synccom_get_memory_cap(h, &memcap);
```

At this point `memcap.input` and `memcap.output` would be set to their respective values.


## Set
```c
int synccom_set_memory_cap(synccom_handle h, struct synccom_memory_cap *memcap)
```

| Parameter | Type | Description |
| --------- | ---- | ----------- |
| `h` | `synccom_handle` | The handle to your port |
| `memcap` | `struct synccom_memory_cap *` | The new `memory cap` value(s) |

| Return Value | Cause |
| ------------:| ----- |
| 0 | Success |

###### Examples
```
#include <synccom.h>
...

struct synccom_memory_cap memcap;

SYNCCOM_MEMORY_CAP_INIT(memcap);

memcap.input = 1000000; /* 1 MB */
memcap.output = 1000000; /* 1 MB */

synccom_set_memory_cap(h, &memcap);
```


### Additional Resources
- Complete example: [`examples/memory-cap.c`](../examples/memory-cap.c)
- Implementation details: [`src/synccom.c`](../src/synccom.c)
