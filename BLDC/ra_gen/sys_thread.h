/* generated thread header file - do not edit */
#ifndef SYS_THREAD_H_
#define SYS_THREAD_H_
#include "bsp_api.h"
#include "tx_api.h"
#include "hal_data.h"
#ifdef __cplusplus
                extern "C" void sys_thread_entry(void);
                #else
extern void sys_thread_entry(void);
#endif
#include "r_tau_pwm.h"
#include "r_timer_api.h"
FSP_HEADER
/** TAU PWM Timer Instance */
extern const timer_instance_t g_timer0;

/** Access the TAU PWM instance using these structures when calling API functions directly (::p_api is not used). */
extern tau_pwm_instance_ctrl_t g_timer0_ctrl;
extern const timer_cfg_t g_timer0_cfg;

#ifndef TestInt
void TestInt(timer_callback_args_t *p_args);
#endif
FSP_FOOTER
#endif /* SYS_THREAD_H_ */
