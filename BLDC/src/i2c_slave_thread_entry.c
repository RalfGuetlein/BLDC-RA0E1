#include "i2c_slave_thread.h"
#include "globals.h"

i2c_slave_event_t g_i2c_slave_callback_event;

int16_t rx_tx_timeout = 0;
rx_buffer_t g_rx_buffer;
tx_buffer_t g_tx_buffer;

host_payload_t rx_payload;

slave_payload_t* gp_slave = &g_tx_buffer.payload;
host_payload_t*  gp_host  = &rx_payload;

static void i2c_tx_prepare(tx_buffer_t* tx_buf)
{
    tx_buf->size = sizeof(tx_buffer_t);
    uint8_t chksum = 0;
    uint8_t* payload = (uint8_t*)(&tx_buf->payload);
    for (uint8_t i = 0; i < sizeof(tx_buffer_t)-2; i++)
    {
        chksum += payload[i];
    }
    tx_buf->chksum = chksum;
}

typedef enum {
    I2C_SUCCESS = 0,
    I2C_SIZE,
    I2C_CHECKSUM
} i2c_err_t;

static i2c_err_t i2c_rx_check(rx_buffer_t* rx_buf)
{
    if (sizeof(rx_buffer_t) != rx_buf->size)
        return I2C_SIZE;

    uint8_t chksum = 0;
    uint8_t* payload = (uint8_t*)(&rx_buf->payload);
    for (uint8_t i = 0; i < sizeof(rx_buffer_t)-2; i++)
    {
        chksum += payload[i];
    }
    if (rx_buf->chksum != chksum)
        return I2C_CHECKSUM;

    return I2C_SUCCESS;
}

void i2c_slave_callback (i2c_slave_callback_args_t * p_args)
{
    uint16_t err;
    g_i2c_slave_callback_event = p_args->event;
    if ((p_args->event == I2C_SLAVE_EVENT_TX_COMPLETE))
    {
        /* Transaction Successful */
        rx_tx_timeout = 100; //ms
    }
    else if ((p_args->event == I2C_SLAVE_EVENT_RX_COMPLETE))
    {
        /* Transaction Successful */
        if (I2C_SUCCESS == i2c_rx_check(&g_rx_buffer))
        {
            memcpy(&rx_payload, &g_rx_buffer.payload, sizeof(rx_payload));
            rx_tx_timeout = 100; //ms
        }
    }
    else if ((p_args->event == I2C_SLAVE_EVENT_RX_REQUEST) || (p_args->event == I2C_SLAVE_EVENT_RX_MORE_REQUEST))
    {
        /* Read from Master */
        err = R_IICA_SLAVE_Read(&i2c_slave_ctrl, (uint8_t*)&g_rx_buffer, sizeof(g_rx_buffer));

        assert(FSP_SUCCESS == err);
    }
    else if ((p_args->event == I2C_SLAVE_EVENT_TX_REQUEST) || (p_args->event == I2C_SLAVE_EVENT_TX_MORE_REQUEST))
    {
        /* Write to master */
        i2c_tx_prepare(&g_tx_buffer);
        err = R_IICA_SLAVE_Write(&i2c_slave_ctrl, (uint8_t*)&g_tx_buffer, sizeof(g_tx_buffer));
        assert(FSP_SUCCESS == err);
    }
    else
    {
        /* Error Event - reported through g_i2c_slave_callback_event */
    }
}

/* I2C Slave Thread entry function */
void i2c_slave_thread_entry(void)
{
    uint8_t adr_pin;
    g_ioport.p_api->pinRead(g_ioport.p_ctrl, MODBUS_DIR, &adr_pin);

    i2c_slave_cfg_t slave_cfg;
    memcpy(&slave_cfg, &i2c_slave_cfg, sizeof(i2c_slave_cfg_t));

    // detect address jumper
    if (BSP_IO_LEVEL_HIGH == adr_pin)
    {
        slave_cfg.slave = 0x21;
    }

    R_IICA_SLAVE_Open(&i2c_slave_ctrl, &slave_cfg);

    while (1)
    {
       tx_thread_sleep (10);
    }
}
