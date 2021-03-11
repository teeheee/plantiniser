#ifndef __TEST__

#include "nrf24_hal.h"
#include <NRFLite.h>
#include <string>

#define NO_ISR_CHECK 0
#define OWN_ID 0

NRFLite radio;

void hal_nrf24_impl::init()
{
    if(radio.init(OWN_ID, 2, 2) > 0)   
    {
        is_initialized = true;
    }
}

hal_nrf24_package_type* hal_nrf24_impl::recv()
{
    if( ! is_initialized)
        return 0;
    rx_package.length = radio.hasData( NO_ISR_CHECK );
    rx_package.id = OWN_ID;
    if( rx_package.length )
    {
        radio.readData(rx_payload);
        rx_package.data = rx_payload;
    }
}

void hal_nrf24_impl::send(hal_nrf24_package_type* data)
{
    if( ! is_initialized)
        return;
    if( radio.send(data->id, data->data, data->length) )
    {
        is_initialized = false;
    }
}

#endif
