/* generated common source file - do not edit */
#include "common_data.h"
icu_instance_ctrl_t g_irq_FGOUT1_ctrl;

/** External IRQ extended configuration for ICU HAL driver */
const icu_extended_cfg_t g_irq_FGOUT1_ext_cfg =
{ .filter_src = EXTERNAL_IRQ_DIGITAL_FILTER_PCLK_DIV, };

const external_irq_cfg_t g_irq_FGOUT1_cfg =
{ .channel = 1, .trigger = EXTERNAL_IRQ_TRIG_BOTH_EDGE, .filter_enable = false, .clock_source_div =
          EXTERNAL_IRQ_CLOCK_SOURCE_DIV_1,
  .p_callback = cb_FGOUT1,
  /** If NULL then do not add & */
#if defined(NULL)
    .p_context           = NULL,
#else
  .p_context = (void*) &NULL,
#endif
  .p_extend = (void*) &g_irq_FGOUT1_ext_cfg,
  .ipl = (2),
#if defined(VECTOR_NUMBER_ICU_IRQ1)
    .irq                 = VECTOR_NUMBER_ICU_IRQ1,
#else
  .irq = FSP_INVALID_VECTOR,
#endif
        };
/* Instance structure to use this module. */
const external_irq_instance_t g_irq_FGOUT1 =
{ .p_ctrl = &g_irq_FGOUT1_ctrl, .p_cfg = &g_irq_FGOUT1_cfg, .p_api = &g_external_irq_on_icu };
ioport_instance_ctrl_t g_ioport_ctrl;
const ioport_instance_t g_ioport =
{ .p_api = &g_ioport_on_ioport, .p_ctrl = &g_ioport_ctrl, .p_cfg = &g_bsp_pin_cfg, };
TX_EVENT_FLAGS_GROUP g_new_event_flags0;
void tx_startup_err_callback(void *p_instance, void *p_data);
void g_common_init(void)
{
    UINT err_g_new_event_flags0;
    err_g_new_event_flags0 = tx_event_flags_create (&g_new_event_flags0, (CHAR*) "New Event Flags");
    if (TX_SUCCESS != err_g_new_event_flags0)
    {
        tx_startup_err_callback (&g_new_event_flags0, 0);
    }
}
