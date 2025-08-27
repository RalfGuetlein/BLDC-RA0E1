/* generated vector source file - do not edit */
#include "bsp_api.h"
/* Do not build these data structures if no interrupts are currently allocated because IAR will have build errors. */
#if VECTOR_DATA_IRQ_COUNT > 0
        BSP_DONT_REMOVE const fsp_vector_t g_vector_table[BSP_ICU_VECTOR_NUM_ENTRIES] BSP_PLACE_IN_SECTION(BSP_SECTION_APPLICATION_VECTORS) =
        {
                        [3] = r_icu_isr, /* ICU IRQ1 (External pin interrupt 1) */
            [19] = tau_pwm_master_tmi_isr, /* TAU0 TMI00 (End of timer channel 00 count or capture) */
            [26] = iica_slave_txrxi_isr, /* IICA0 TXRXI (End of IICA0 communication) */
        };
        #if BSP_FEATURE_ICU_HAS_IELSR
        const bsp_interrupt_event_t g_interrupt_event_link_select[BSP_ICU_VECTOR_NUM_ENTRIES] =
        {
            [3] = BSP_PRV_VECT_ENUM(EVENT_ICU_IRQ1,GROUP3), /* ICU IRQ1 (External pin interrupt 1) */
            [19] = BSP_PRV_VECT_ENUM(EVENT_TAU0_TMI00,GROUP3), /* TAU0 TMI00 (End of timer channel 00 count or capture) */
            [26] = BSP_PRV_VECT_ENUM(EVENT_IICA0_TXRXI,GROUP2), /* IICA0 TXRXI (End of IICA0 communication) */
        };
        #endif
        #endif
