# Sync Com C Library (csynccom)
This README file is best viewed [online](http://github.com/commtech/csynccom/).

## Installing Library

##### Downloading Library
- You can use the pre-built library files that are included with the driver
- Or, you can download the latest library version from
[Github releases](https://github.com/commtech/csynccom/releases).


## Quick Start Guide

Lets get started with a quick programming example for fun.

_This tutorial has already been set up for you at_ [`examples/tutorial.c`](examples/tutorial.c).

First, drop `csynccom.dll` and `csynccom.lib` into a test directory. Now that those files are copied over, create a new C file (named tutorial.c) with the following code.

```c
#include <stdio.h> /* fprintf */
#include <stdlib.h> /* EXIT_SUCCESS, EXIT_FAILURE */
#include <synccom.h> /* synccom_* */

int main(void)
{
    synccom_handle h;
    int e = 0;
    char odata[] = "Hello world!";
    char idata[20] = {0};
    unsigned tmp;

    /* Open port 0 in a blocking IO mode */
    e = synccom_connect(0, &h);
    if (e != 0) {
        fprintf(stderr, "synccom_connect failed with %d\n", e);
        return EXIT_FAILURE;
    }

    /* Send "Hello world!" text */
    synccom_write_with_blocking(h, odata, sizeof(odata), &tmp, NULL);

    /* Read the data back in (with our loopback connector) */
    synccom_read_with_blocking(h, idata, sizeof(idata), &tmp, NULL);

    fprintf(stdout, "%s\n", idata);

    synccom_disconnect(h);

    return EXIT_SUCCESS;
}
```

For this example I will use the Visual Studio command line compiler, but you can use your compiler of choice.

```
# cl tutorial.c cfscc.lib /I <CSYNCCOM_DIR>\src\
```

Now attach the included loopback connector.

```
# tutorial.exe
Hello world!
```

You have now transmitted and received an HDLC frame!


## API Reference

There are likely other configuration options you will need to set up for your own program. All of these options are described on their respective documentation page.

- [Connect](docs/connect.md)
- [Append Status](docs/append-status.md)
- [Append Timestamp](docs/append-timestamp.md)
- [Clock Frequency](docs/clock-frequency.md)
- [Ignore Timeout](docs/ignore-timeout.md)
- [Memory Cap](docs/memory-cap.md)
- [Purge](docs/purge.md)
- [Read](docs/read.md)
- [Registers](docs/registers.md)
- [RX Multiple](docs/rx-multiple.md)
- [Track Interrupts](docs/track-interrupts.md)
- [TX Modifiers](docs/tx-modifiers.md)
- [Write](docs/write.md)
- [Disconnect](docs/disconnect.md)


## Visual Studio Integration
The process for using the library will differ slightly depending on the version of Visual Studio.

1. Configuration Properties -> C/C++ -> General -> Additional Include Directories: (folder containing synccom.h)
2. Configuration Properties -> Linker -> General -> Additional Library Directories: (folder containing csynccom{d}.lib)
3. Configuration Properties -> Linker -> Input -> Additional Dependencies: csynccom{d}.lib
4. Configuration Properties -> Debugging -> Environment: PATH=%PATH%;(folder containing csynccom{d}.dll)


## Build Dependencies
- C compiler (GCC & Visual Studio tested)


## Run-time Dependencies
- OS: Windows XP+ & Linux


## API Compatibility
We follow [Semantic Versioning](http://semver.org/) when creating releases.


## License

Copyright (C) 2019 [Commtech, Inc.](https://fastcomproducts.com/)

Licensed under the [MIT license](https://opensource.org/licenses/MIT).