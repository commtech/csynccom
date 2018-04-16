# Connect

Opening a handle using this API will only give you access to the synchronous functionality of the device.

###### Support
| Code | Version |
| ---- | ------- |
| synccom-windows | 1.0.0 |
| synccom-linux | 1.0.0 |
| csynccom | 1.0.0 |


## Connect
```c
int synccom_connect(unsigned port_num, synccom_handle *h)
```

| Parameter | Type | Description |
| --------- | ---- | ----------- |
| `port_num` | `unsigned` | The port number you would like to connect to |
| `h` | `synccom_handle *` | The handle to your port |

| Return Code | Value | Cause |
| ----------- | -----:| ----- |
| | 0 | Success |
| `SYNCCOM_PORT_NOT_FOUND` | 16003 | Port not found |
| `SYNCCOM_INVALID_ACCESS` | 16004 | Insufficient permissions |

###### Examples
Connect to port 0.

```c
#include <synccom.h>
...

synccom_handle h;

synccom_connect(0, &h);
```


### Additional Resources
- Complete example: [`examples/tutorial.c`](../examples/tutorial.c)
- Implementation details: [`src/synccom.c`](../src/synccom.c)
