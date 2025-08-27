#ifndef _GLOBALS_H
#define _GLOBALS_H

#define __PACKED__ __attribute__((__packed__))

typedef struct __PACKED__{
    uint8_t error;
    uint8_t ain1;
    uint8_t ain2;
    uint8_t ain3;
    uint8_t Reserved;
} payload_tx_t;

typedef struct __PACKED__{
    uint8_t motor1;
    uint8_t motor2;
    uint8_t flags1;
    uint8_t flags2;
    uint8_t Reserved;
} payload_rx_t;

typedef struct __PACKED__{
    uint8_t      size;
    payload_tx_t payload;
    uint8_t     chksum;
} tx_buffer_t;

typedef struct __PACKED__{
    uint8_t      size;
    payload_rx_t payload;
    uint8_t     chksum;
} rx_buffer_t;

extern payload_rx_t* gp_buffer_rx;
extern payload_tx_t* gp_buffer_tx;

typedef enum {
    SM_STOP,
    SM_TEAR,
    SM_FEED,
    SM_CLEAR
} sm_enum_t;

extern sm_enum_t g_sm_enum;

#endif // _GLOBALS_H
