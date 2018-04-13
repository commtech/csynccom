/*
    Copyright (C) 2017 Commtech, Inc.

    This file is part of cfscc.

    csynccom is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    csynccom is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with csynccom.  If not, see <http://www.gnu.org/licenses/>.

*/

#include <stdio.h>
#include <fcntl.h> /* open, O_RDWR */

#ifndef _WIN32
#include <unistd.h> /* write, close */
#include <poll.h>
#else
#include <TCHAR.h>
#endif

#include "synccom.h"
#include "errno.h"
#include "calculate-clock-bits.h"

#define UNUSED(x) (void)(x)

#define MAX_NAME_LENGTH 25

int translate_error(int e)
{
#ifdef _WIN32
    switch (e) {
        case ERROR_ACCESS_DENIED:
            return SYNCCOM_INVALID_ACCESS;
        case ERROR_FILE_NOT_FOUND:
            return SYNCCOM_PORT_NOT_FOUND;
        case ERROR_SEM_TIMEOUT:
            return SYNCCOM_TIMEOUT;
        case ERROR_INSUFFICIENT_BUFFER:
            return SYNCCOM_BUFFER_TOO_SMALL;
    default:
        return e;
    }
#else
    switch (e) {
        case ENOENT:
            return SYNCCOM_PORT_NOT_FOUND;
        case EACCES:
            return SYNCCOM_INVALID_ACCESS;
        case EOPNOTSUPP:
            return SYNCCOM_INCORRECT_MODE;
        case ETIMEDOUT:
            return SYNCCOM_TIMEOUT;
        case ENOBUFS:
            return SYNCCOM_BUFFER_TOO_SMALL;
    default:
        return e;
    }
#endif
}

int ioctl_action(synccom_handle h, int ioctl_name)
{
    int result;

#ifdef _WIN32
    DWORD temp;

    result = DeviceIoControl(h, (DWORD)ioctl_name, NULL, 0, NULL, 0, &temp, (LPOVERLAPPED)NULL);

    return (result == TRUE) ? 0 : translate_error(GetLastError());
#else
    result = ioctl(h, ioctl_name);

    return (result != -1) ? 0 : translate_error(errno);
#endif
}

int ioctl_get_boolean(synccom_handle h, int ioctl_name, unsigned *status)
{
    int result;

#ifdef _WIN32
    DWORD temp;

    result = DeviceIoControl(h, (DWORD)ioctl_name, NULL, 0, status, sizeof(*status), &temp, (LPOVERLAPPED)NULL);

    return (result == TRUE) ? 0 : translate_error(GetLastError());
#else
    result = ioctl(h, ioctl_name, status);

    return (result != -1) ? 0 : translate_error(errno);
#endif
}

int ioctl_set_integer(synccom_handle h, int ioctl_name, int value)
{
    int result;

#ifdef _WIN32
    DWORD temp;

    result = DeviceIoControl(h, (DWORD)ioctl_name, &value, sizeof(value), NULL, 0, &temp, (LPOVERLAPPED)NULL);

    return (result == TRUE) ? 0 : translate_error(GetLastError());
#else
    result = ioctl(h, ioctl_name, value);

    return (result != -1) ? 0 : translate_error(errno);
#endif
}

int ioctl_get_integer(synccom_handle h, int ioctl_name, int *value)
{
    int result;

#ifdef _WIN32
    DWORD temp;

    result = DeviceIoControl(h, (DWORD)ioctl_name, NULL, 0, value, sizeof(*value), &temp, (LPOVERLAPPED)NULL);

    return (result == TRUE) ? 0 : translate_error(GetLastError());
#else
    result = ioctl(h, ioctl_name, value);

    return (result != -1) ? 0 : translate_error(errno);
#endif
}

int ioctl_set_pointer(synccom_handle h, int ioctl_name, const void *value, int size)
{
    int result;

    #ifdef _WIN32
        DWORD temp;

        result = DeviceIoControl(h, (DWORD)ioctl_name, (void *)value, size, NULL, 0, &temp, (LPOVERLAPPED)NULL);

        return (result == TRUE) ? 0 : translate_error(GetLastError());
    #else
        UNUSED(size);

        result = ioctl(h, ioctl_name, value);

        return (result != -1) ? 0 : translate_error(errno);
    #endif
}

int ioctl_get_pointer(synccom_handle h, int ioctl_name, void *value, int size)
{
    int result;

#ifdef _WIN32
    DWORD temp;

    result = DeviceIoControl(h, (DWORD)ioctl_name, NULL, 0, value, size, &temp, (LPOVERLAPPED)NULL);

    return (result == TRUE) ? 0 : translate_error(GetLastError());
#else
    UNUSED(size);

    result = ioctl(h, ioctl_name, value);

    return (result != -1) ? 0 : translate_error(errno);
#endif
}

int ioctl_getset_pointer(synccom_handle h, int ioctl_name, void *value, int size)
{
    int result;

#ifdef _WIN32
    DWORD temp;

    result = DeviceIoControl(h, (DWORD)ioctl_name, value, size, value, size, &temp, (LPOVERLAPPED)NULL);

    return (result == TRUE) ? 0 : translate_error(GetLastError());
#else
    UNUSED(size);

    result = ioctl(h, ioctl_name, value);

    return (result != -1) ? 0 : translate_error(errno);
#endif
}

int synccom_connect(unsigned port_num, synccom_handle *h)
{
#ifdef _WIN32
    TCHAR name[MAX_NAME_LENGTH];

    _stprintf_s(name, sizeof(name)/sizeof(TCHAR), _T("\\\\.\\SYNCCOM%u"), port_num);

    *h = CreateFile(name, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, NULL);

    return (*h != INVALID_HANDLE_VALUE) ? 0 : translate_error(GetLastError());
#else
    char name[MAX_NAME_LENGTH];

    sprintf(name, "/dev/synccom%u", port_num);

    *h = open(name, O_RDWR);

    return (*h != -1) ? 0 : translate_error(errno);
#endif
}

int synccom_set_tx_modifiers(synccom_handle h, unsigned modifiers)
{
    return ioctl_set_integer(h, SYNCCOM_SET_TX_MODIFIERS, modifiers);
}

int synccom_get_tx_modifiers(synccom_handle h, unsigned *modifiers)
{
    return ioctl_get_integer(h, SYNCCOM_GET_TX_MODIFIERS, (int *)modifiers);
}

int synccom_set_memory_cap(synccom_handle h, const struct synccom_memory_cap *memcap)
{
    return ioctl_set_pointer(h, SYNCCOM_SET_MEMORY_CAP, memcap, sizeof(*memcap));
}

int synccom_get_memory_cap(synccom_handle h, struct synccom_memory_cap *memcap)
{
    return ioctl_get_pointer(h, SYNCCOM_GET_MEMORY_CAP, memcap, sizeof(*memcap));
}

int synccom_set_registers(synccom_handle h, const struct synccom_registers *regs)
{
    return ioctl_set_pointer(h, SYNCCOM_SET_REGISTERS, regs, sizeof(*regs));
}

int synccom_get_registers(synccom_handle h, struct synccom_registers *regs)
{
    return ioctl_getset_pointer(h, SYNCCOM_GET_REGISTERS, regs, sizeof(*regs));
}

int synccom_get_append_status(synccom_handle h, unsigned *status)
{
    return ioctl_get_boolean(h, SYNCCOM_GET_APPEND_STATUS, status);
}

int synccom_enable_append_status(synccom_handle h)
{
    return ioctl_action(h, SYNCCOM_ENABLE_APPEND_STATUS);
}

int synccom_disable_append_status(synccom_handle h)
{
    return ioctl_action(h, SYNCCOM_DISABLE_APPEND_STATUS);
}

int synccom_get_append_timestamp(synccom_handle h, unsigned *status)
{
    return ioctl_get_boolean(h, SYNCCOM_GET_APPEND_TIMESTAMP, status);
}

int synccom_enable_append_timestamp(synccom_handle h)
{
    return ioctl_action(h, SYNCCOM_ENABLE_APPEND_TIMESTAMP);
}

int synccom_disable_append_timestamp(synccom_handle h)
{
    return ioctl_action(h, SYNCCOM_DISABLE_APPEND_TIMESTAMP);
}

int synccom_get_ignore_timeout(synccom_handle h, unsigned *status)
{
    return ioctl_get_boolean(h, SYNCCOM_GET_IGNORE_TIMEOUT, status);
}

int synccom_enable_ignore_timeout(synccom_handle h)
{
    return ioctl_action(h, SYNCCOM_ENABLE_IGNORE_TIMEOUT);
}

int synccom_disable_ignore_timeout(synccom_handle h)
{
    return ioctl_action(h, SYNCCOM_DISABLE_IGNORE_TIMEOUT);
}

int synccom_get_rx_multiple(synccom_handle h, unsigned *status)
{
    return ioctl_get_boolean(h, SYNCCOM_GET_RX_MULTIPLE, status);
}

int synccom_enable_rx_multiple(synccom_handle h)
{
    return ioctl_action(h, SYNCCOM_ENABLE_RX_MULTIPLE);
}

int synccom_disable_rx_multiple(synccom_handle h)
{
    return ioctl_action(h, SYNCCOM_DISABLE_RX_MULTIPLE);
}

int synccom_purge(synccom_handle h, unsigned tx, unsigned rx)
{
    int error;

    if (tx) {
        error = ioctl_action(h, SYNCCOM_PURGE_TX);

        if (error) return error;
    }

    if (rx) {
        error = ioctl_action(h, SYNCCOM_PURGE_RX);

        if (error) return error;
    }

    return 0;
}

int synccom_set_clock_frequency(synccom_handle h, unsigned frequency)
{
    unsigned char clock_bits[20];
    int result = 0;

    result = calculate_clock_bits(frequency, 10, clock_bits);

    if (result != 0) return SYNCCOM_INVALID_PARAMETER;

    return ioctl_set_pointer(h, SYNCCOM_SET_CLOCK_BITS, clock_bits, sizeof(clock_bits));
}

int synccom_write(synccom_handle h, char *buf, unsigned size, unsigned *bytes_written, OVERLAPPED *o)
{
    int result;

#ifdef _WIN32
    result = WriteFile(h, buf, size, (DWORD*)bytes_written, o);

    return (result == TRUE) ? 0 : translate_error(GetLastError());
#else
    UNUSED(o);

    result = write(h, buf, size);

    if (result == -1) return translate_error(errno);

    *bytes_written = result;

    return 0;
#endif
}

int synccom_write_with_blocking(synccom_handle h, char *buf, unsigned size, unsigned *bytes_written)
{
#ifdef _WIN32
    int result;
    OVERLAPPED ol;

    memset(&ol, 0, sizeof(ol));

    result = synccom_write(h, buf, size, bytes_written, &ol);

    if (result == 997) result = GetOverlappedResult(h, &ol, (DWORD *)bytes_written, 1);

    return (result == TRUE) ? 0 : translate_error(GetLastError());
#else
    return synccom_write(h, buf, size, bytes_written, 0);
#endif
}

int synccom_read(synccom_handle h, char *buf, unsigned size, unsigned *bytes_read, OVERLAPPED *o)
{
    int result;
#ifdef _WIN32

    result = ReadFile(h, buf, size, (DWORD*)bytes_read, o);

    return (result == TRUE) ? 0 : translate_error(GetLastError());
#else
    UNUSED(o);

    result = read(h, buf, size);

    if (result == -1) return translate_error(errno);

    *bytes_read = result;

    return 0;
#endif
}

int synccom_read_with_blocking(synccom_handle h, char *buf, unsigned size, unsigned *bytes_read)
{
#ifdef _WIN32
    int result;
    OVERLAPPED ol;

    memset(&ol, 0, sizeof(ol));

    result = synccom_read(h, buf, size, bytes_read, &ol);

    if (result == 997) result = GetOverlappedResult(h, &ol, (DWORD *)bytes_read, 1);

    return (result == TRUE) ? 0 : translate_error(GetLastError());
#else
    return synccom_read(h, buf, size, bytes_read, 0);
#endif
}

/******************************************************************************/
/*!

  \note
    Due to supporting Windows XP we have to use CancelIo() instead of
    CancelIoEx(). As a biproduct if there is a WAIT_TIMEOUT both pending
    transmit and receive IO will be cancelled instead of just receiving. If you
    are using Vista or newer you can change this to use CancelIoEx and you will
    only cancel the receiving IO.

*/
/******************************************************************************/
int synccom_read_with_timeout(synccom_handle h, char *buf, unsigned size, unsigned *bytes_read, unsigned timeout)
{
#ifdef _WIN32
    OVERLAPPED o;
    BOOL result;

    memset(&o, 0, sizeof(o));

    o.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

    if (o.hEvent == NULL) return GetLastError();

    result = ReadFile(h, buf, size, (DWORD*)bytes_read, &o);

    if (result == FALSE) {
        DWORD status;
        int e;

        /* There was an actual error instead of a pending read */
        if ((e = GetLastError()) != ERROR_IO_PENDING) {
            CloseHandle(o.hEvent);
            return e;
        }

        do {
            status = WaitForSingleObject(o.hEvent, timeout);

            switch (status) {
            case WAIT_TIMEOUT:
                *bytes_read = 0;
                /* Switch to CancelIoEx if using Vista or higher and prefer the
                   way CancelIoEx operates. */
                /* CancelIoEx(h, &o); */
                CancelIo(h);
                CloseHandle(o.hEvent);
                return ERROR_SUCCESS;

            case WAIT_FAILED:
                e = GetLastError();
                CloseHandle(o.hEvent);
                return e;
            }
        }
        while (status != WAIT_OBJECT_0);

        result = GetOverlappedResult(h, &o, (DWORD *)bytes_read, TRUE);
    }

    CloseHandle(o.hEvent);

    return (result == TRUE) ? 0 : translate_error(GetLastError());
#else
    struct pollfd fds[1];
    int e = 0;

    fds[0].fd = h;
    fds[0].events = POLLIN;

    switch (poll(fds, 1, timeout)) {
    case -1:
        e = errno;
        break;

    case 0:
        break;

    default:
        e = synccom_read_with_blocking(h, buf, size, bytes_read);
        break;
    }

    return e;
#endif
}

int synccom_disconnect(synccom_handle h)
{
    int result;

#ifdef _WIN32
    result = CloseHandle(h);

    return (result == TRUE) ? 0 : GetLastError();
#else

    result = close(h);

    return (result != -1) ? 0 : errno;
#endif
}