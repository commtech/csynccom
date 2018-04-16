# Disconnect

###### Support
| Code | Version |
| ---- | ------- |
| synccom-windows | 1.0.0 |
| synccom-linux | 1.0.0 |
| csynccom | 1.0.0 |


## Disconnect
```c
int synccom_disconnect(synccom_handle h)
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

synccom_disconnect(h);
```


### Additional Resources
- Complete example: [`examples/tutorial.c`](../examples/tutorial.c)
- Implementation details: [`src/synccom.c`](../src/synccom.c)
