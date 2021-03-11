#ifndef _NRF24_HAL_H_
#define _NRF24_HAL_H_

#include <stdint.h>

#define NRF24_MAX_PAYLOAD_SIZE 32

typedef struct{
    int id;
    int length;
    uint8_t* data;
} hal_nrf24_package_type;

class hal_nrf24 {
    public:
        virtual void init() = 0;
        virtual hal_nrf24_package_type* recv() = 0;
        virtual void send(hal_nrf24_package_type* data) = 0;
};

class hal_nrf24_impl : public hal_nrf24{
    private:
        bool is_initialized = false;
        uint8_t rx_payload[NRF24_MAX_PAYLOAD_SIZE];
        hal_nrf24_package_type rx_package;
    public:
        void init();
        hal_nrf24_package_type* recv();
        void send(hal_nrf24_package_type* data);
};

#endif