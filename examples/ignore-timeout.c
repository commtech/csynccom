#include <synccom.h> /* synccom_* */

int main(void)
{
    synccom_handle h;
    unsigned status;

    synccom_connect(0, &h);

    synccom_get_ignore_timeout(h, &status);

    synccom_enable_ignore_timeout(h);
    synccom_disable_ignore_timeout(h);

    synccom_disconnect(h);

    return 0;
}
