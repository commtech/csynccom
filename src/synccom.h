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

#ifndef SYNCCOM_H
#define SYNCCOM_H

#ifdef __cplusplus
extern "C"
{
#endif

#ifdef _WIN32
#include <Windows.h>
#else
#include <stdint.h>
#include <sys/ioctl.h>
#endif

#include <string.h> /* memset */

#define SYNCCOM_REGISTERS_INIT(regs) memset(&regs, -1, sizeof(regs))
#define SYNCCOM_MEMORY_CAP_INIT(memcap) memset(&memcap, -1, sizeof(memcap))
#define SYNCCOM_UPDATE_VALUE -2

enum error_type { SYNCCOM_TIMEOUT=16000, SYNCCOM_INCORRECT_MODE,
                  SYNCCOM_BUFFER_TOO_SMALL, SYNCCOM_PORT_NOT_FOUND,
                  SYNCCOM_INVALID_ACCESS, SYNCCOM_INVALID_PARAMETER };
enum transmit_type { XF=0, XREP=1, TXT=2, TXEXT=4 };

#ifdef _WIN32
typedef INT64 synccom_register;
#else
typedef int64_t synccom_register;
#endif

struct synccom_registers {
    /* BAR 0 */
    synccom_register reserved1[2];

    synccom_register FIFOT;

    synccom_register reserved2[2];

    synccom_register CMDR;
    synccom_register STAR; /* Read-only */
    synccom_register CCR0;
    synccom_register CCR1;
    synccom_register CCR2;
    synccom_register BGR;
    synccom_register SSR;
    synccom_register SMR;
    synccom_register TSR;
    synccom_register TMR;
    synccom_register RAR;
    synccom_register RAMR;
    synccom_register PPR;
    synccom_register TCR;
    synccom_register VSTR; /* Read-only */

    synccom_register reserved3[1];

    synccom_register IMR;
    synccom_register DPLLR;

    /* BAR 2 */
    synccom_register FCR;
};

struct synccom_memory_cap {
    int input;
    int output;
};

#ifdef _WIN32
    #define SYNCCOM_IOCTL_MAGIC 0x8018

    #define SYNCCOM_GET_REGISTERS CTL_CODE(SYNCCOM_IOCTL_MAGIC, 0x800, METHOD_BUFFERED, FILE_ANY_ACCESS)
    #define SYNCCOM_SET_REGISTERS CTL_CODE(SYNCCOM_IOCTL_MAGIC, 0x801, METHOD_BUFFERED, FILE_ANY_ACCESS)

    #define SYNCCOM_PURGE_TX CTL_CODE(SYNCCOM_IOCTL_MAGIC, 0x802, METHOD_BUFFERED, FILE_ANY_ACCESS)
    #define SYNCCOM_PURGE_RX CTL_CODE(SYNCCOM_IOCTL_MAGIC, 0x803, METHOD_BUFFERED, FILE_ANY_ACCESS)

    #define SYNCCOM_ENABLE_APPEND_STATUS CTL_CODE(SYNCCOM_IOCTL_MAGIC, 0x804, METHOD_BUFFERED, FILE_ANY_ACCESS)
    #define SYNCCOM_DISABLE_APPEND_STATUS CTL_CODE(SYNCCOM_IOCTL_MAGIC, 0x805, METHOD_BUFFERED, FILE_ANY_ACCESS)
    #define SYNCCOM_GET_APPEND_STATUS CTL_CODE(SYNCCOM_IOCTL_MAGIC, 0x80D, METHOD_BUFFERED, FILE_ANY_ACCESS)

    #define SYNCCOM_SET_MEMORY_CAP CTL_CODE(SYNCCOM_IOCTL_MAGIC, 0x806, METHOD_BUFFERED, FILE_ANY_ACCESS)
    #define SYNCCOM_GET_MEMORY_CAP CTL_CODE(SYNCCOM_IOCTL_MAGIC, 0x807, METHOD_BUFFERED, FILE_ANY_ACCESS)

    #define SYNCCOM_SET_CLOCK_BITS CTL_CODE(SYNCCOM_IOCTL_MAGIC, 0x808, METHOD_BUFFERED, FILE_ANY_ACCESS)

    #define SYNCCOM_ENABLE_IGNORE_TIMEOUT CTL_CODE(SYNCCOM_IOCTL_MAGIC, 0x80A, METHOD_BUFFERED, FILE_ANY_ACCESS)
    #define SYNCCOM_DISABLE_IGNORE_TIMEOUT CTL_CODE(SYNCCOM_IOCTL_MAGIC, 0x80B, METHOD_BUFFERED, FILE_ANY_ACCESS)
    #define SYNCCOM_GET_IGNORE_TIMEOUT CTL_CODE(SYNCCOM_IOCTL_MAGIC, 0x80F, METHOD_BUFFERED, FILE_ANY_ACCESS)

    #define SYNCCOM_SET_TX_MODIFIERS CTL_CODE(SYNCCOM_IOCTL_MAGIC, 0x80C, METHOD_BUFFERED, FILE_ANY_ACCESS)
    #define SYNCCOM_GET_TX_MODIFIERS CTL_CODE(SYNCCOM_IOCTL_MAGIC, 0x80E, METHOD_BUFFERED, FILE_ANY_ACCESS)

    #define SYNCCOM_ENABLE_RX_MULTIPLE CTL_CODE(SYNCCOM_IOCTL_MAGIC, 0x810, METHOD_BUFFERED, FILE_ANY_ACCESS)
    #define SYNCCOM_DISABLE_RX_MULTIPLE CTL_CODE(SYNCCOM_IOCTL_MAGIC, 0x811, METHOD_BUFFERED, FILE_ANY_ACCESS)
    #define SYNCCOM_GET_RX_MULTIPLE CTL_CODE(SYNCCOM_IOCTL_MAGIC, 0x812, METHOD_BUFFERED, FILE_ANY_ACCESS)

    #define SYNCCOM_ENABLE_APPEND_TIMESTAMP CTL_CODE(SYNCCOM_IOCTL_MAGIC, 0x813, METHOD_BUFFERED, FILE_ANY_ACCESS)
    #define SYNCCOM_DISABLE_APPEND_TIMESTAMP CTL_CODE(SYNCCOM_IOCTL_MAGIC, 0x814, METHOD_BUFFERED, FILE_ANY_ACCESS)
    #define SYNCCOM_GET_APPEND_TIMESTAMP CTL_CODE(SYNCCOM_IOCTL_MAGIC, 0x815, METHOD_BUFFERED, FILE_ANY_ACCESS)

    //#define SYNCCOM_TRACK_INTERRUPTS CTL_CODE(SYNCCOM_IOCTL_MAGIC, 0x819, METHOD_BUFFERED, FILE_ANY_ACCESS) // No longer necessary
#else
    #define SYNCCOM_IOCTL_MAGIC 0x18
    #define SYNCCOM_GET_REGISTERS _IOR(SYNCCOM_IOCTL_MAGIC, 0, struct synccom_registers *)
    #define SYNCCOM_SET_REGISTERS _IOW(SYNCCOM_IOCTL_MAGIC, 1, const struct synccom_registers *)

    #define SYNCCOM_PURGE_TX _IO(SYNCCOM_IOCTL_MAGIC, 2)
    #define SYNCCOM_PURGE_RX _IO(SYNCCOM_IOCTL_MAGIC, 3)

    #define SYNCCOM_ENABLE_APPEND_STATUS _IO(SYNCCOM_IOCTL_MAGIC, 4)
    #define SYNCCOM_DISABLE_APPEND_STATUS _IO(SYNCCOM_IOCTL_MAGIC, 5)
    #define SYNCCOM_GET_APPEND_STATUS _IOR(SYNCCOM_IOCTL_MAGIC, 13, unsigned *)

    #define SYNCCOM_SET_MEMORY_CAP _IOW(SYNCCOM_IOCTL_MAGIC, 6, struct synccom_memory_cap *)
    #define SYNCCOM_GET_MEMORY_CAP _IOR(SYNCCOM_IOCTL_MAGIC, 7, struct synccom_memory_cap *)

    #define SYNCCOM_SET_CLOCK_BITS _IOW(SYNCCOM_IOCTL_MAGIC, 8, const unsigned char[20])

    #define SYNCCOM_ENABLE_IGNORE_TIMEOUT _IO(SYNCCOM_IOCTL_MAGIC, 10)
    #define SYNCCOM_DISABLE_IGNORE_TIMEOUT _IO(SYNCCOM_IOCTL_MAGIC, 11)
    #define SYNCCOM_GET_IGNORE_TIMEOUT _IOR(SYNCCOM_IOCTL_MAGIC, 15, unsigned *)

    #define SYNCCOM_SET_TX_MODIFIERS _IOW(SYNCCOM_IOCTL_MAGIC, 12, const unsigned)
    #define SYNCCOM_GET_TX_MODIFIERS _IOR(SYNCCOM_IOCTL_MAGIC, 14, unsigned *)

    #define SYNCCOM_ENABLE_RX_MULTIPLE _IO(SYNCCOM_IOCTL_MAGIC, 16)
    #define SYNCCOM_DISABLE_RX_MULTIPLE _IO(SYNCCOM_IOCTL_MAGIC, 17)
    #define SYNCCOM_GET_RX_MULTIPLE _IOR(SYNCCOM_IOCTL_MAGIC, 18, unsigned *)

    #define SYNCCOM_ENABLE_APPEND_TIMESTAMP _IO(SYNCCOM_IOCTL_MAGIC, 19)
    #define SYNCCOM_DISABLE_APPEND_TIMESTAMP _IO(SYNCCOM_IOCTL_MAGIC, 20)
    #define SYNCCOM_GET_APPEND_TIMESTAMP _IOR(SYNCCOM_IOCTL_MAGIC, 21, unsigned *)
#endif


#ifndef _WIN32
typedef void OVERLAPPED;
#endif

#ifdef _WIN32
typedef HANDLE synccom_handle;
#else
typedef int synccom_handle;
#endif

#ifdef _WIN32
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT
#endif

DLL_EXPORT int synccom_connect(unsigned port_num, synccom_handle *h);
DLL_EXPORT int synccom_set_tx_modifiers(synccom_handle h, unsigned modifiers);
DLL_EXPORT int synccom_get_tx_modifiers(synccom_handle h, unsigned *modifiers);
DLL_EXPORT int synccom_set_memory_cap(synccom_handle h, const struct synccom_memory_cap *memcap);
DLL_EXPORT int synccom_get_memory_cap(synccom_handle h, struct synccom_memory_cap *memcap);
DLL_EXPORT int synccom_set_registers(synccom_handle h, const struct synccom_registers *regs);
DLL_EXPORT int synccom_get_registers(synccom_handle h, struct synccom_registers *regs);
DLL_EXPORT int synccom_get_append_status(synccom_handle h, unsigned *status);
DLL_EXPORT int synccom_enable_append_status(synccom_handle h);
DLL_EXPORT int synccom_disable_append_status(synccom_handle h);
DLL_EXPORT int synccom_get_append_timestamp(synccom_handle h, unsigned *status);
DLL_EXPORT int synccom_enable_append_timestamp(synccom_handle h);
DLL_EXPORT int synccom_disable_append_timestamp(synccom_handle h);
DLL_EXPORT int synccom_get_ignore_timeout(synccom_handle h, unsigned *status);
DLL_EXPORT int synccom_enable_ignore_timeout(synccom_handle h);
DLL_EXPORT int synccom_disable_ignore_timeout(synccom_handle h);
DLL_EXPORT int synccom_get_rx_multiple(synccom_handle h, unsigned *status);
DLL_EXPORT int synccom_enable_rx_multiple(synccom_handle h);
DLL_EXPORT int synccom_disable_rx_multiple(synccom_handle h);
DLL_EXPORT int synccom_track_interrupts(synccom_handle h, unsigned interrupts, unsigned *matches, OVERLAPPED *o);
DLL_EXPORT int synccom_track_interrupts_with_blocking(synccom_handle h, unsigned interrupts, unsigned *matches);
DLL_EXPORT int synccom_track_interrupts_with_timeout(synccom_handle h, unsigned interrupts, unsigned *matches, unsigned timeout);
DLL_EXPORT int synccom_purge(synccom_handle h, unsigned tx, unsigned rx);
DLL_EXPORT int synccom_write(synccom_handle h, char *buf, unsigned size, unsigned *bytes_written, OVERLAPPED *o);
DLL_EXPORT int synccom_write_with_blocking(synccom_handle h, char *buf, unsigned size, unsigned *bytes_written);
DLL_EXPORT int synccom_read(synccom_handle h, char *buf, unsigned size, unsigned *bytes_read, OVERLAPPED *o);
DLL_EXPORT int synccom_read_with_blocking(synccom_handle h, char *buf, unsigned size, unsigned *bytes_written);
DLL_EXPORT int synccom_read_with_timeout(synccom_handle h, char *buf, unsigned size, unsigned *bytes_read, unsigned timeout);
DLL_EXPORT int synccom_disconnect(synccom_handle h);
DLL_EXPORT int synccom_set_clock_frequency(synccom_handle h, unsigned frequency);

#ifdef __cplusplus
}
#endif

#endif