/* generated thread source file - do not edit */
#include "sys_thread.h"

TX_THREAD sys_thread;
void sys_thread_create(void);
static void sys_thread_func(ULONG thread_input);
static uint8_t sys_thread_stack[1024] BSP_PLACE_IN_SECTION(BSP_UNINIT_SECTION_PREFIX ".stack.sys_thread") BSP_ALIGN_VARIABLE(BSP_STACK_ALIGNMENT);
void tx_startup_err_callback(void *p_instance, void *p_data);
void tx_startup_common_init(void);
const tau_pwm_channel_cfg_t g_timer_channel_cfg2 =
{ .channel = 2,
#define OPERATION_TIMER_MODE_ONE_SHOT (0xFFFFFFFF)
#if (OPERATION_TIMER_MODE_ONE_SHOT == OPERATION_TIMER_MODE_PWM)
    /* Actual pulse width: 0.00204796875 seconds. */  .duty_cycle_counts = (uint16_t) 0xffff,
#else
  /* Actual duty cycle percent: 50 %. */.duty_cycle_counts = (uint16_t) 0x640,
#endif
#undef OPERATION_TIMER_MODE_ONE_SHOT
  .output_level = TAU_PWM_OUTPUT_LEVEL_LOW,
  .output_polarity = TAU_PWM_OUTPUT_POLARITY_ACTIVE_HIGH, .cycle_end_ipl = (BSP_IRQ_DISABLED),
#if defined(VECTOR_NUMBER_TAU0_TMI02)
    .cycle_end_irq       = VECTOR_NUMBER_TAU0_TMI02,
#else
  .cycle_end_irq = FSP_INVALID_VECTOR,
#endif
        };
const tau_pwm_channel_cfg_t g_timer_channel_cfg1 =
{ .channel = 1,
#define OPERATION_TIMER_MODE_ONE_SHOT (0xFFFFFFFF)
#if (OPERATION_TIMER_MODE_ONE_SHOT == OPERATION_TIMER_MODE_PWM)
    /* Actual pulse width: 0.00204796875 seconds. */  .duty_cycle_counts = (uint16_t) 0xffff,
#else
  /* Actual duty cycle percent: 30 %. */.duty_cycle_counts = (uint16_t) 0x3c0,
#endif
#undef OPERATION_TIMER_MODE_ONE_SHOT
  .output_level = TAU_PWM_OUTPUT_LEVEL_LOW,
  .output_polarity = TAU_PWM_OUTPUT_POLARITY_ACTIVE_HIGH, .cycle_end_ipl = (BSP_IRQ_DISABLED),
#if defined(VECTOR_NUMBER_TAU0_TMI01)
    .cycle_end_irq       = VECTOR_NUMBER_TAU0_TMI01,
#else
  .cycle_end_irq = FSP_INVALID_VECTOR,
#endif
        };
tau_pwm_instance_ctrl_t g_timer0_ctrl;

const tau_pwm_extended_cfg_t g_timer0_extend =
{ .operation_clock = TAU_PWM_OPERATION_CLOCK_CK00,
#define TRIGGER_TAU_PWM_SOURCE_PIN_INPUT (0xFFFFFFFF)
#if (TRIGGER_TAU_PWM_SOURCE_PIN_INPUT == TRIGGER_TAU_PWM_SOURCE_PIN_INPUT)
  .trigger_source = TAU_PWM_SOURCE_PIN_INPUT,
#else
    .trigger_source                  = TAU_PWM_SOURCE_ELC_EVENT,
#endif
#undef TRIGGER_TAU_PWM_SOURCE_PIN_INPUT
  .detect_edge = TAU_PWM_DETECT_EDGE_FALLING,
  .p_slave_channel_cfgs =
  {
#define RA_NOT_DEFINED (0xFFFFFFFF)
#if (RA_NOT_DEFINED != 1)
    &g_timer_channel_cfg1,
#endif
#if (RA_NOT_DEFINED != 2)
    &g_timer_channel_cfg2,
#endif

#if (RA_NOT_DEFINED != RA_NOT_DEFINED)
    &g_timer_channel_cfgRA_NOT_DEFINED,
#endif

#if (RA_NOT_DEFINED != RA_NOT_DEFINED)
    &g_timer_channel_cfgRA_NOT_DEFINED,
#endif

#if (RA_NOT_DEFINED != RA_NOT_DEFINED)
    &g_timer_channel_cfgRA_NOT_DEFINED,
#endif

#if (RA_NOT_DEFINED != RA_NOT_DEFINED)
    &g_timer_channel_cfgRA_NOT_DEFINED,
#endif

#if (RA_NOT_DEFINED != RA_NOT_DEFINED)
    &g_timer_channel_cfgRA_NOT_DEFINED,
#endif
#undef RA_NOT_DEFINED
          } };
const timer_cfg_t g_timer0_cfg =
{ .mode = TIMER_MODE_PWM,
/* Actual pulse period: 0.0001 seconds. */.period_counts = (uint32_t) 0xc80,
  .source_div = (timer_source_div_t) BSP_CFG_TAU_CK00, .channel = 0, .p_callback = TestInt,
  /** If NULL then do not add & */
#if defined(NULL)
    .p_context           = NULL,
#else
  .p_context = (void*) &NULL,
#endif
  .p_extend = &g_timer0_extend,
  .cycle_end_ipl = (2),
#if defined(VECTOR_NUMBER_TAU0_TMI00)
    .cycle_end_irq       = VECTOR_NUMBER_TAU0_TMI00,
#else
  .cycle_end_irq = FSP_INVALID_VECTOR,
#endif
        };
/* Instance structure to use this module. */
const timer_instance_t g_timer0 =
{ .p_ctrl = &g_timer0_ctrl, .p_cfg = &g_timer0_cfg, .p_api = &g_timer_on_tau_pwm };
extern bool g_fsp_common_initialized;
extern uint32_t g_fsp_common_thread_count;
extern TX_SEMAPHORE g_fsp_common_initialized_semaphore;

void sys_thread_create(void)
{
    /* Increment count so we will know the number of ISDE created threads. */
    g_fsp_common_thread_count++;

    /* Initialize each kernel object. */

    UINT err;
    err = tx_thread_create (&sys_thread, (CHAR*) "System Thread", sys_thread_func, (ULONG) NULL, &sys_thread_stack,
                            1024, 1, 1, 1, TX_AUTO_START);
    if (TX_SUCCESS != err)
    {
        tx_startup_err_callback (&sys_thread, 0);
    }
}

static void sys_thread_func(ULONG thread_input)
{
    /* Not currently using thread_input. */
    FSP_PARAMETER_NOT_USED (thread_input);

    /* Initialize common components */
    tx_startup_common_init ();

    /* Initialize each module instance. */

    /* Enter user code for this thread. */
    sys_thread_entry ();
}
