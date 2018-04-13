#include <synccom.h> /* synccom_* */

int main(void)
{
    synccom_handle h;
    struct synccom_memory_cap memcap;

    synccom_connect(0, &h);

    memcap.input = 1000000; /* 1 MB */
    memcap.output = 1000000; /* 1 MB */

    synccom_set_memory_cap(h, &memcap);

    synccom_get_memory_cap(h, &memcap);

    synccom_disconnect(h);

    return 0;
}
