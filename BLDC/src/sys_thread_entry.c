#include "sys_thread.h"
#include "common_utils.h"
#include "globals.h"

timer_event_t g_event = 0;

void TestInt(timer_callback_args_t *p_args)
{
    g_event = p_args->event;
}

uint16_t fgout1_cnt = 0;
void cb_FGOUT1(external_irq_callback_args_t *p_args)
{
    p_args = p_args;
    fgout1_cnt++;
}

uint16_t fgout2_cnt = 0;
void cb_FGOUT2(external_irq_callback_args_t *p_args)
{
    p_args = p_args;
    fgout2_cnt++;
}


/* System Thread entry function */
void sys_thread_entry(void)
{
    fsp_err_t err;

    /* Configure the external interrupt. */

    err = R_ICU_ExternalIrqOpen(&g_irq_FGOUT1_ctrl, &g_irq_FGOUT1_cfg);
    assert(FSP_SUCCESS == err);
    /* Enable the external interrupt. */
    /* Enable not required when used with ELC or DMAC. */
    err = R_ICU_ExternalIrqEnable(&g_irq_FGOUT1_ctrl);
    assert(FSP_SUCCESS == err);

    err = R_ICU_ExternalIrqOpen(&g_irq_FGOUT2_ctrl, &g_irq_FGOUT2_cfg);
    assert(FSP_SUCCESS == err);
    /* Enable the external interrupt. */
    /* Enable not required when used with ELC or DMAC. */
    err = R_ICU_ExternalIrqEnable(&g_irq_FGOUT2_ctrl);
    assert(FSP_SUCCESS == err);

    // configure PWM1 and PWM2
    R_TAU_PWM_Open (&g_timer0_ctrl, &g_timer0_cfg);
    R_TAU_PWM_Start(&g_timer0_ctrl);

    /* Get the current period setting. */
    timer_info_t info;
    (void) R_TAU_PWM_InfoGet(&g_timer0_ctrl, &info);
    uint32_t period_counts = info.period_counts;

    while (1)
    {
        tx_thread_sleep (10);

        R_TAU_PWM_DutyCycleSet(&g_timer0_ctrl, (uint16_t) ((period_counts * gp_host->speed1) / 100), TAU_PWM_IO_PIN_CHANNEL_1);
        R_TAU_PWM_DutyCycleSet(&g_timer0_ctrl, (uint16_t) ((period_counts * gp_host->speed2) / 100), TAU_PWM_IO_PIN_CHANNEL_2);
        g_ioport.p_api->pinWrite(g_ioport.p_ctrl, OUT1,    gp_host->flags1.bit.Out);
        g_ioport.p_api->pinWrite(g_ioport.p_ctrl, OUT2,    gp_host->flags2.bit.Out);

        g_ioport.p_api->pinWrite(g_ioport.p_ctrl, BRAKE1,  gp_host->flags1.bit.Brk);
        g_ioport.p_api->pinWrite(g_ioport.p_ctrl, BRAKE2,  gp_host->flags2.bit.Brk);
        g_ioport.p_api->pinWrite(g_ioport.p_ctrl, DRVOFF1, gp_host->flags1.bit.Off);
        g_ioport.p_api->pinWrite(g_ioport.p_ctrl, DRVOFF2, gp_host->flags2.bit.Off);
        g_ioport.p_api->pinWrite(g_ioport.p_ctrl, SS_DIR1, gp_host->flags1.bit.Dir);
        g_ioport.p_api->pinWrite(g_ioport.p_ctrl, SS_DIR2, gp_host->flags2.bit.Dir);


       // short low pulse on NSLEEPx to reset fault conditions
        // might be necessary to safely change SS_DIRx level

        R_BSP_SoftwareDelay(25, BSP_DELAY_UNITS_MICROSECONDS);
        g_ioport.p_api->pinWrite(g_ioport.p_ctrl, NSLEEP1,  BSP_IO_LEVEL_LOW);
        g_ioport.p_api->pinWrite(g_ioport.p_ctrl, NSLEEP2,  BSP_IO_LEVEL_LOW);
        R_BSP_SoftwareDelay(25, BSP_DELAY_UNITS_MICROSECONDS);
        g_ioport.p_api->pinWrite(g_ioport.p_ctrl, NSLEEP1,  BSP_IO_LEVEL_HIGH);
        g_ioport.p_api->pinWrite(g_ioport.p_ctrl, NSLEEP2,  BSP_IO_LEVEL_HIGH);


        g_ioport.p_api->pinWrite(g_ioport.p_ctrl, SS_DIR1, gp_host->flags1.bit.Dir);
        g_ioport.p_api->pinWrite(g_ioport.p_ctrl, SS_DIR2, gp_host->flags2.bit.Dir);

        g_ioport.p_api->pinWrite(g_ioport.p_ctrl, OUT1,    gp_host->flags1.bit.Out);
        g_ioport.p_api->pinWrite(g_ioport.p_ctrl, OUT2,    gp_host->flags2.bit.Out);


        gp_slave->fgout1 = fgout1_cnt;
        gp_slave->fgout2 = fgout2_cnt;

    }
}


