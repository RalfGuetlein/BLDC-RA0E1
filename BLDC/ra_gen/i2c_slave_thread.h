/* generated thread header file - do not edit */
#ifndef I2C_SLAVE_THREAD_H_
#define I2C_SLAVE_THREAD_H_
#include "bsp_api.h"
#include "tx_api.h"
#include "hal_data.h"
#ifdef __cplusplus
                extern "C" void i2c_slave_thread_entry(void);
                #else
extern void i2c_slave_thread_entry(void);
#endif
#include "r_iica_slave.h"
#include "r_i2c_slave_api.h"
FSP_HEADER
/** IICA Slave on IICA Instance. */
extern const i2c_slave_instance_t i2c_slave;

/** Access the IICA Slave instance using these structures when calling API functions directly (::p_api is not used). */
extern iica_slave_instance_ctrl_t i2c_slave_ctrl;
extern const i2c_slave_cfg_t i2c_slave_cfg;

#ifndef i2c_slave_callback
void i2c_slave_callback(i2c_slave_callback_args_t *p_args);
#endif
FSP_FOOTER
#endif /* I2C_SLAVE_THREAD_H_ */
