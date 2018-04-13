#include <stdio.h> /* fprintf */
#include <stdlib.h> /* EXIT_SUCCESS, EXIT_FAILURE */
#include <synccom.h> /* synccom_* */

int main(void)
{
    synccom_handle h;
	int e = 0;

	e = synccom_connect(0, &h);
    if (e != 0) {
        fprintf(stderr, "synccom_connect failed with %d\n", e);
        return EXIT_FAILURE;
    }

    /* TX */
    synccom_purge(h, 1, 0);

    /* RX */
    synccom_purge(h, 0, 1);

    /* TX & RX */
    synccom_purge(h, 1, 1);

    synccom_disconnect(h);

    return 0;
}
