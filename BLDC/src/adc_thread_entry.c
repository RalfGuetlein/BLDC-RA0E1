#include "adc_thread.h"
#include "globals.h"

void cb_adc0(adc_callback_args_t *p_args)
{
    (void)p_args;

}
void adc_read(adc_channel_t ch, uint16_t * const pdat);
void adc_read(adc_channel_t ch, uint16_t * const pdat)
{
    adc_d_channel_cfg_t act_channel_cfg;
    adc_status_t status;

    act_channel_cfg.channel_input = ch;

    R_ADC_D_ScanCfg(&g_adc0_ctrl, &act_channel_cfg);

    R_ADC_D_ScanStart (&g_adc0_ctrl);

    do{
        R_ADC_D_StatusGet(&g_adc0_ctrl, &status);
    } while (ADC_STATE_SCAN_IN_PROGRESS == status.state);

    R_ADC_D_Read (&g_adc0_ctrl, 0, pdat);
}

/* ADC thread entry function */
void adc_thread_entry(void)
{
    // NFAULT is initially set to open drain and low, in order to prevent
    // the MCT8316ZT from entering test mode due to slow rising pin
    // Has to be set to input when initialization is complete
    R_IOPORT_PinCfg(&g_ioport_ctrl,
                    NFAULT,
                    IOPORT_CFG_PORT_DIRECTION_INPUT);

    R_ADC_D_Open (&g_adc0_ctrl, &g_adc0_cfg);
    while (1)
    {
        uint16_t adc;
        bsp_io_level_t din;
        adc_read(ADC_CHANNEL_4, &adc);
       // adc value to mV
        gp_slave->ain1 = (int16_t)((((int32_t)adc)*10000)/4096);
        adc_read(ADC_CHANNEL_5, &adc);
        // adc value to mV
        gp_slave->ain2 = (int16_t)((((uint32_t)adc)*10000)/4096);
        adc_read(ADC_CHANNEL_6, &adc);
        // adc value to mV
        gp_slave->ain3 = (int16_t)((((int32_t)adc)*10000)/4096);
        // digital input
        g_ioport.p_api->pinRead(g_ioport.p_ctrl, IRQ, &din);
        gp_slave->flags.bit.Din = din;
        g_ioport.p_api->pinRead(g_ioport.p_ctrl, NFAULT, &din);
        gp_slave->flags.bit.Flt = din;

        tx_thread_sleep(3);

    }
}
