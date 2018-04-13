#include <synccom.h> /* synccom_* */

int main(void)
{
    synccom_handle h;
    unsigned status;

    synccom_connect(0, &h);

    synccom_get_rx_multiple(h, &status);

    synccom_enable_rx_multiple(h);
    synccom_disable_rx_multiple(h);

    synccom_disconnect(h);

    return 0;
}
