/* generated configuration header file - do not edit */
#ifndef BSP_PIN_CFG_H_
#define BSP_PIN_CFG_H_
#include "r_ioport.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

#define OUT1 (BSP_IO_PORT_00_PIN_08)
#define BRAKE2 (BSP_IO_PORT_00_PIN_09)
#define SS_DIR1 (BSP_IO_PORT_00_PIN_10)
#define OUT2 (BSP_IO_PORT_00_PIN_11)
#define AIN1 (BSP_IO_PORT_00_PIN_12)
#define AIN2 (BSP_IO_PORT_00_PIN_13)
#define AIN3 (BSP_IO_PORT_00_PIN_14)
#define IRQ (BSP_IO_PORT_00_PIN_15)
#define DRVOFF1 (BSP_IO_PORT_01_PIN_01)
#define NSLEEP (BSP_IO_PORT_01_PIN_02)
#define DRVOFF2 (BSP_IO_PORT_01_PIN_03)
#define PWM2 (BSP_IO_PORT_01_PIN_09)
#define PWM1 (BSP_IO_PORT_01_PIN_10)
#define SS_DIR2 (BSP_IO_PORT_01_PIN_12)
#define NFAULT (BSP_IO_PORT_02_PIN_00)
#define FGOUT2 (BSP_IO_PORT_02_PIN_01)
#define FGOUT1 (BSP_IO_PORT_02_PIN_12)
#define BRAKE1 (BSP_IO_PORT_02_PIN_13)
#define RES_IN2 (BSP_IO_PORT_02_PIN_14)
#define RES_IN1 (BSP_IO_PORT_02_PIN_15)
#define MODBUS_DIR (BSP_IO_PORT_04_PIN_07)
#define PIN_SDAA0 (BSP_IO_PORT_09_PIN_13)
#define CFG_SDAA0 ((uint32_t) IOPORT_CFG_PERIPHERAL_PIN | (uint32_t) IOPORT_PERIPHERAL_IICA1)
#define PIN_SCLA0 (BSP_IO_PORT_09_PIN_14)
#define CFG_SCLA0 ((uint32_t) IOPORT_CFG_PERIPHERAL_PIN | (uint32_t) IOPORT_PERIPHERAL_IICA1)

extern const ioport_cfg_t g_bsp_pin_cfg; /* R7FA0E1073CFJ.pincfg */

void BSP_PinConfigSecurityInit();

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER
#endif /* BSP_PIN_CFG_H_ */
