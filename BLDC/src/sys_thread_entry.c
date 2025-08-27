#include "sys_thread.h"
#include "common_utils.h"

timer_event_t g_event = 0;

void TestInt(timer_callback_args_t *p_args)
{
    g_event = p_args->event;
}

uint8_t fgout_cnt = 0;
void cb_FGOUT1(external_irq_callback_args_t *p_args)
{
    p_args = p_args;
    fgout_cnt++;
//    APP_PRINT("FGOUT1\n");
}

//void cb_FGOUT2(external_irq_callback_args_t *p_args)
//{
//    p_args = p_args;
////    APP_PRINT("FGOUT2\n");
//}
//

/* System Thread entry function */
void sys_thread_entry(void)
{

    /* Configure the external interrupt. */
    fsp_err_t err = R_ICU_ExternalIrqOpen(&g_irq_FGOUT1_ctrl, &g_irq_FGOUT1_cfg);
    assert(FSP_SUCCESS == err);
    /* Enable the external interrupt. */
    /* Enable not required when used with ELC or DMAC. */
    err = R_ICU_ExternalIrqEnable(&g_irq_FGOUT1_ctrl);
    assert(FSP_SUCCESS == err);

    uint8_t pwm_lvl = 30;
//    bsp_io_level_t nsleep_lvl = BSP_IO_LEVEL_LOW;
    bsp_io_level_t dir_lvl    = BSP_IO_LEVEL_LOW;
    bsp_io_level_t brake_lvl  = BSP_IO_LEVEL_LOW;
    bsp_io_level_t drvoff_lvl = BSP_IO_LEVEL_LOW;

    R_TAU_PWM_Open (&g_timer0_ctrl, &g_timer0_cfg);
    R_TAU_PWM_Start(&g_timer0_ctrl);

    /* Get the current period setting. */
    timer_info_t info;
    (void) R_TAU_PWM_InfoGet(&g_timer0_ctrl, &info);
    uint32_t period_counts = info.period_counts;

    /* TODO: add your own code here */
    while (1)
    {
        tx_thread_sleep (100);

        //clear screen
        APP_PRINT("\x1B[2J");

        APP_PRINT ("PWM:    %d\n", pwm_lvl);
        APP_PRINT ("DIR:    %d\n", dir_lvl);
        APP_PRINT ("BRAKE:  %d\n", brake_lvl);
        APP_PRINT ("DRVOFF: %d\n", drvoff_lvl);
        APP_PRINT ("FGOUT:  %d\n", fgout_cnt);

        if (SEGGER_RTT_HasKey())
        {
            switch (SEGGER_RTT_GetKey())
            {
                case 's':
                    g_ioport.p_api->pinWrite(g_ioport.p_ctrl, NSLEEP, BSP_IO_LEVEL_LOW);
                    R_BSP_SoftwareDelay(50, BSP_DELAY_UNITS_MICROSECONDS);
                    g_ioport.p_api->pinWrite(g_ioport.p_ctrl, NSLEEP, BSP_IO_LEVEL_HIGH);
                    break;
                case '+':
                    if (pwm_lvl <= 90)
                        pwm_lvl +=5;
                    /* Set the calculated duty cycle. */
                    R_TAU_PWM_DutyCycleSet(&g_timer0_ctrl, (uint16_t) ((period_counts * pwm_lvl) / 100), TAU_PWM_IO_PIN_CHANNEL_1);
                    //assert(FSP_SUCCESS == err);
                    break;
                case '-':
                    if (pwm_lvl >= 10)
                        pwm_lvl -=5;
                    /* Set the calculated duty cycle. */
                    R_TAU_PWM_DutyCycleSet(&g_timer0_ctrl, (uint16_t) ((period_counts * pwm_lvl) / 100), TAU_PWM_IO_PIN_CHANNEL_1);
                    //assert(FSP_SUCCESS == err);
                    break;
                case 'd':
                    if (dir_lvl == BSP_IO_LEVEL_LOW)
                        dir_lvl = BSP_IO_LEVEL_HIGH;
                    else
                        dir_lvl = BSP_IO_LEVEL_LOW;
                    g_ioport.p_api->pinWrite(g_ioport.p_ctrl, SS_DIR1, dir_lvl);
                    break;
                case 'b':
                    if (brake_lvl == BSP_IO_LEVEL_LOW)
                        brake_lvl = BSP_IO_LEVEL_HIGH;
                    else
                        brake_lvl = BSP_IO_LEVEL_LOW;
                    g_ioport.p_api->pinWrite(g_ioport.p_ctrl, BRAKE1, brake_lvl);
                    break;
                case 'o':
                    if (drvoff_lvl == BSP_IO_LEVEL_LOW)
                        drvoff_lvl = BSP_IO_LEVEL_HIGH;
                    else
                        drvoff_lvl = BSP_IO_LEVEL_LOW;
                    g_ioport.p_api->pinWrite(g_ioport.p_ctrl, DRVOFF1, drvoff_lvl);
                    break;
            }
        }
    }
}
