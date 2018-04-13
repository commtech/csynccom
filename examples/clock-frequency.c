#include <synccom.h> /* synccom_* */

int main(void)
{
    synccom_handle h;

    synccom_connect(0, &h);

    /* 18.432 Mhz */
    synccom_set_clock_frequency(h, 18432000);

    synccom_disconnect(h);

    return 0;
}
