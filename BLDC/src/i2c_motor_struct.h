#ifndef _I2C_MOTOR_STRUCT_H
#define _I2C_MOTOR_STRUCT_H

#define __PACKED__ __attribute__((__packed__))

typedef union {
    uint8_t byte;
    struct {
        uint8_t Din: 1;
        uint8_t Flt: 1;
    } bit;
} slave_flags_t;

typedef struct __PACKED__{
    slave_flags_t flags;
    uint16_t ain1;
    uint16_t ain2;
    uint16_t ain3;
    uint16_t fgout1;
    uint16_t fgout2;
} slave_payload_t;

typedef union {
    uint8_t byte;
    struct {
        uint8_t Dir: 1;
        uint8_t Brk: 1;
        uint8_t Off: 1;
        uint8_t Out: 1;
    } bit;
} host_flags_t;

typedef struct __PACKED__{
    uint8_t speed1;
    uint8_t speed2;
    host_flags_t   flags1;
    host_flags_t   flags2;
} host_payload_t;

typedef struct __PACKED__{
    uint8_t      size;
    slave_payload_t payload;
    uint8_t     chksum;
} tx_buffer_t;

typedef struct __PACKED__{
    uint8_t      size;
    host_payload_t payload;
    uint8_t     chksum;
} rx_buffer_t;


#endif // _I2C_MOTOR_STRUCT_H
