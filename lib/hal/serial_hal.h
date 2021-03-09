#ifndef _SERIAL_HAL_H_
#define _SERIAL_HAL_H_

#include <stdint.h>
#include <string>

class hal_serial {
    public:
        virtual void init() = 0;
        virtual void write(std::string data) = 0;
        virtual std::string read() = 0;
};

class hal_serial_impl : public hal_serial{
    private:
        std::string input_string;
    public:
        void init();
        std::string read();
        void write(std::string data);
};

#endif