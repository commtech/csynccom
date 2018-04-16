# Read

The `size` argument of the various read functions means different things depending on the mode you are using.

In a frame based mode the `size` argument specifies the maximum frame `size` to return. If the next queued frame is larger than the size you specified the error `SYNCCOM_BUFFER_TOO_SMALL` is returned and the data will remain waiting for a read of a larger value. If a `size` is specified that is larger than the length of multiple frames in queue, you will still only receive one frame per read call.

In streaming mode (no frame termination) the `size` argument specifies the maximum amount of data to return. If there are 100 bytes of streaming data in the card and you read with a `size` of 50, you will receive 50 bytes. If you do a read of 200 bytes, you will receive the 100 bytes available.

Frame based data and streaming data are kept separate within the driver. To understand what this means, first imagine the following scenario. You are in a frame based mode and receive a couple of frames. You then switch to streaming mode and receive a stream of data. When calling read
you will receive the the streaming data until you switch back into a frame based mode and do a read.

Most users will want the advanced I/O capabilities included by using the Windows [OVERLAPPED I/O API](http://msdn.microsoft.com/en-us/library/windows/desktop/ms686358.aspx). We won't duplicate the documentation here, but for your reference, here is an [article](http://blogs.msdn.com/b/oldnewthing/archive/2011/02/02/10123392.aspx) on a common bug developers introduce while trying to cancel I/O operations when using OVERLAPPED I/O.

###### Support
| Code | Version |
| ---- | ------- |
| synccom-windows | 1.0.0 |
| synccom-linux | 1.0.0 |
| csynccom | 1.0.0 |


## Read
```c
int synccom_read(synccom_handle h, char *buf, unsigned size, unsigned *bytes_read, OVERLAPPED *o)
```

| Parameter | Type | Description |
| --------- | ---- | ----------- |
| `h` | `synccom_handle` | The handle to your port |
| `buf` | `char *` | The data buffer to hold incoming data |
| `size` | `unsigned` | The data buffer size |
| `bytes_read` | `unsigned *` | How many bytes were returned from the read |
| `o` | `OVERLAPPED *`| [Overlapped IO structure](http://msdn.microsoft.com/en-us/library/windows/desktop/ms686358.aspx) |

| Return Code | Value | Cause |
| ------------ | -----:| ----- |
| | 0 | Success |
| `SYNCCOM_INCORRECT_MODE` | 16001 | Using the synchronous port while in asynchronous mode |
| `SYNCCOM_BUFFER_TOO_SMALL` | 16002 | The buffer size is smaller than the next frame |
| `Other` | `Other` | [`See Windows System standard error codes`](http://msdn.microsoft.com/en-us/library/windows/desktop/ms681381%28v=vs.85%29.aspx) |

###### Examples
```c
#include <synccom.h>
...

char idata[20] = {0};
unsigned bytes_read;

synccom_read(h, idata, sizeof(idata), &bytes_read, NULL);
```


## Read (Timeout)
```c
int synccom_read_with_timeout(synccom_handle h, char *buf, unsigned size, unsigned *bytes_read, unsigned timeout)
```

| Parameter | Type | Description |
| --------- | ---- | ----------- |
| `h` | `synccom_handle` | The handle to your port |
| `buf` | `char *` | The data buffer to hold incoming data |
| `size` | `unsigned` | The data buffer size |
| `bytes_read` | `unsigned *` | How many bytes were returned to the buffer |
| `timeout` | `unsigned` | Number of milliseconds to wait for data before timing out |

| Return Code | Value | Cause |
| ----------- | -----:| ----- |
| | 0 | Success |
| `SYNCCOM_INCORRECT_MODE` | 16001 | Using the synchronous port while in asynchronous modes |
| `SYNCCOM_BUFFER_TOO_SMALL` | 16002 | The buffer size is smaller than the next frames |
| `Other` | `Other` | [`See Windows System standard error codes`](http://msdn.microsoft.com/en-us/library/windows/desktop/ms681381%28v=vs.85%29.aspx) |

###### Examples
```c
#include <synccom.h>
...

char idata[20] = {0};
unsigned bytes_read;

synccom_read_with_timeout(h, idata, sizeof(idata), &bytes_read, 100);
```


## Read (Blocking)
```c
int synccom_read_with_blocking(synccom_handle h, char *buf, unsigned size, unsigned *bytes_read)
```

| Parameter | Type | Description |
| --------- | ---- | ----------- |
| `h` | `synccom_handle` | The handle to your port |
| `buf` | `char *` | The data buffer to hold incoming data |
| `size` | `unsigned` | The data buffer size |
| `bytes_read` | `unsigned *` | How many bytes were returned to the buffer |

| Return Code | Value | Cause |
| ----------- | -----:| ----- |
| | 0 | Success |
| `SYNCCOM_INCORRECT_MODE` | 16001 | Using the synchronous port while in asynchronous mode |
| `SYNCCOM_BUFFER_TOO_SMALL` | 16002 | The buffer size is smaller than the next frame |
| `Other` | `Other` | [`See Windows System standard error codes`](http://msdn.microsoft.com/en-us/library/windows/desktop/ms681381%28v=vs.85%29.aspx) |

###### Examples
```c
#include <synccom.h>
...

char idata[20] = {0};
unsigned bytes_read;

synccom_read_with_blocking(h, idata, sizeof(idata), &bytes_read);
```


### Additional Resources
- Complete example: [`examples/tutorial.c`](../examples/tutorial.c)
- Implementation details: [`src/synccom.c`](../src/synccom.c)
