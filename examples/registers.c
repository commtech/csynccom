#include <synccom.h> /* synccom_* */

int main(void)
{
    synccom_handle h;
    struct synccom_registers regs;

    synccom_connect(0, &h);

    /* Initialize our registers structure */
    SYNCCOM_REGISTERS_INIT(regs);

    /* Change the CCR0 and BGR elements to our desired values */
    regs.CCR0 = 0x0011201c;
    regs.BGR = 0;

    /* Set the CCR0 and BGR register values */
    synccom_set_registers(h, &regs);

    /* Re-initialize our registers structure */
    SYNCCOM_REGISTERS_INIT(regs);

    /* Mark the CCR0 and CCR1 elements to retrieve values */
    regs.CCR1 = SYNCCOM_UPDATE_VALUE;
    regs.CCR2 = SYNCCOM_UPDATE_VALUE;

    /* Get the CCR1 and CCR2 register values */
    synccom_get_registers(h, &regs);

    synccom_disconnect(h);

    return 0;
}
