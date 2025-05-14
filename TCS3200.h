#ifndef TCS3200_H
#define TCS3200_H

#include "hardware/spi.h"
#include "pico/stdlib.h"

class TCS3200 {
public:
    TCS3200(spi_inst_t *spi, uint8_t s0_pin, uint8_t s1_pin, uint8_t out_pin);
    void begin();
    void setFrequency(uint8_t freq);
    void readColor(uint16_t &red, uint16_t &green, uint16_t &blue);

private:
    spi_inst_t *spi;
    uint8_t s0_pin, s1_pin, out_pin;
    uint8_t frequency;
    
    uint16_t readColorData();
    void setPins();
};

#endif
