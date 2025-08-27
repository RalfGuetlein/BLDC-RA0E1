/* generated thread source file - do not edit */
#include "i2c_slave_thread.h"

TX_THREAD i2c_slave_thread;
void i2c_slave_thread_create(void);
static void i2c_slave_thread_func(ULONG thread_input);
static uint8_t i2c_slave_thread_stack[1024] BSP_PLACE_IN_SECTION(BSP_UNINIT_SECTION_PREFIX ".stack.i2c_slave_thread") BSP_ALIGN_VARIABLE(BSP_STACK_ALIGNMENT);
void tx_startup_err_callback(void *p_instance, void *p_data);
void tx_startup_common_init(void);
iica_slave_instance_ctrl_t i2c_slave_ctrl;
const iica_slave_extended_cfg_t i2c_slave_extend =
{ .clock_settings.digital_filter = 0,
  .clock_settings.operation_clock = 0,
  .clock_settings.iicwl_value = 151,
  .clock_settings.iicwh_value = 170,
  .clock_settings.cks_value = 0,
#if defined(PIN_SDAA0)
    .sda_pin_settings.pin = PIN_SDAA0,
#else
  .sda_pin_settings.pin = (bsp_io_port_pin_t) UINT16_MAX,
#endif
#if defined(CFG_SDAA0)
    .sda_pin_settings.cfg = CFG_SDAA0 | (uint32_t) IOPORT_PERIPHERAL_PIN_IO,
#else
  .sda_pin_settings.cfg = (uint32_t) IOPORT_CFG_PORT_DIRECTION_INPUT,
#endif
#if defined(PIN_SCLA0)
    .scl_pin_settings.pin = PIN_SCLA0,
#else
  .scl_pin_settings.pin = (bsp_io_port_pin_t) UINT16_MAX,
#endif
#if defined(CFG_SCLA0)
    .scl_pin_settings.cfg = CFG_SCLA0 | (uint32_t) IOPORT_PERIPHERAL_PIN_IO,
#else
  .scl_pin_settings.cfg = (uint32_t) IOPORT_CFG_PORT_DIRECTION_INPUT,
#endif
        };
const i2c_slave_cfg_t i2c_slave_cfg =
{ .channel = 0, .rate = I2C_SLAVE_RATE_STANDARD, .slave = 0x20, .addr_mode = I2C_SLAVE_ADDR_MODE_7BIT, .p_callback =
          i2c_slave_callback,
  .p_context = NULL,
#if defined(VECTOR_NUMBER_IICA0_TXRXI)
    .tei_irq             = VECTOR_NUMBER_IICA0_TXRXI,
#else
  .tei_irq = FSP_INVALID_VECTOR,
#endif
  .ipl = (2),
  .p_extend = &i2c_slave_extend, };
/* Instance structure to use this module. */
const i2c_slave_instance_t i2c_slave =
{ .p_ctrl = &i2c_slave_ctrl, .p_cfg = &i2c_slave_cfg, .p_api = &g_iica_slave_on_iica };
extern bool g_fsp_common_initialized;
extern uint32_t g_fsp_common_thread_count;
extern TX_SEMAPHORE g_fsp_common_initialized_semaphore;

void i2c_slave_thread_create(void)
{
    /* Increment count so we will know the number of ISDE created threads. */
    g_fsp_common_thread_count++;

    /* Initialize each kernel object. */

    UINT err;
    err = tx_thread_create (&i2c_slave_thread, (CHAR*) "I2C Slave Thread", i2c_slave_thread_func, (ULONG) NULL,
                            &i2c_slave_thread_stack, 1024, 1, 1, 1, TX_AUTO_START);
    if (TX_SUCCESS != err)
    {
        tx_startup_err_callback (&i2c_slave_thread, 0);
    }
}

static void i2c_slave_thread_func(ULONG thread_input)
{
    /* Not currently using thread_input. */
    FSP_PARAMETER_NOT_USED (thread_input);

    /* Initialize common components */
    tx_startup_common_init ();

    /* Initialize each module instance. */

    /* Enter user code for this thread. */
    i2c_slave_thread_entry ();
}
