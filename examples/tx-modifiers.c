#include <synccom.h> /* synccom_* */

int main(void)
{
    synccom_handle h;
    unsigned modifiers;

    synccom_connect(0, &h);

    synccom_get_tx_modifiers(h, &modifiers);

    /* Enable transmit repeat & transmit on timer */
    synccom_set_tx_modifiers(h, TXT | XREP);

    /* Revert to normal transmission */
    synccom_set_tx_modifiers(h, XF);

    synccom_disconnect(h);

    return 0;
}
