#include <synccom.h> /* synccom_* */

int main(void)
{
	synccom_handle h;
    unsigned status;

	synccom_connect(0, &h);

    synccom_get_append_status(h, &status);

	synccom_enable_append_status(h);
	synccom_disable_append_status(h);

	synccom_disconnect(h);

	return 0;
}
