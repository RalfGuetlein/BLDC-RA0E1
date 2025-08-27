/* generated vector header file - do not edit */
#ifndef VECTOR_DATA_H
#define VECTOR_DATA_H
#ifdef __cplusplus
        extern "C" {
        #endif
/* Number of interrupts allocated */
#ifndef VECTOR_DATA_IRQ_COUNT
#define VECTOR_DATA_IRQ_COUNT    (3)
#endif
/* ISR prototypes */
void r_icu_isr(void);
void tau_pwm_master_tmi_isr(void);
void iica_slave_txrxi_isr(void);

/* Vector table allocations */
#define VECTOR_NUMBER_ICU_IRQ1 ((IRQn_Type) 3) /* ICU IRQ1 (External pin interrupt 1) */
#define ICU_IRQ1_IRQn          ((IRQn_Type) 3) /* ICU IRQ1 (External pin interrupt 1) */
#define VECTOR_NUMBER_TAU0_TMI00 ((IRQn_Type) 19) /* TAU0 TMI00 (End of timer channel 00 count or capture) */
#define TAU0_TMI00_IRQn          ((IRQn_Type) 19) /* TAU0 TMI00 (End of timer channel 00 count or capture) */
#define VECTOR_NUMBER_IICA0_TXRXI ((IRQn_Type) 26) /* IICA0 TXRXI (End of IICA0 communication) */
#define IICA0_TXRXI_IRQn          ((IRQn_Type) 26) /* IICA0 TXRXI (End of IICA0 communication) */
/* The number of entries required for the ICU vector table. */
#define BSP_ICU_VECTOR_NUM_ENTRIES (27)

#ifdef __cplusplus
        }
        #endif
#endif /* VECTOR_DATA_H */
