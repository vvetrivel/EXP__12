#include "TCS3200.h"

TCS3200::TCS3200(spi_inst_t *spi, uint8_t s0_pin, uint8_t s1_pin, uint8_t out_pin) {
    this->spi = spi;
    this->s0_pin = s0_pin;
    this->s1_pin = s1_pin;
    this->out_pin = out_pin;
    this->frequency = 0;
}

void TCS3200::begin() {
    // Initialize the SPI communication and configure pins for S0, S1, and OUT
    gpio_init(s0_pin);
    gpio_set_dir(s0_pin, GPIO_OUT);
    gpio_init(s1_pin);
    gpio_set_dir(s1_pin, GPIO_OUT);
    gpio_init(out_pin);
    gpio_set_dir(out_pin, GPIO_IN);
    
    // Set frequency to default (e.g., 100%)
    setFrequency(0);
}

void TCS3200::setFrequency(uint8_t freq) {
    // Set S0 and S1 to control the frequency scaling
    if (freq == 0) {
        gpio_put(s0_pin, 0);
        gpio_put(s1_pin, 0);
    } else if (freq == 1) {
        gpio_put(s0_pin, 1);
        gpio_put(s1_pin, 0);
    } else if (freq == 2) {
        gpio_put(s0_pin, 0);
        gpio_put(s1_pin, 1);
    } else if (freq == 3) {
        gpio_put(s0_pin, 1);
        gpio_put(s1_pin, 1);
    }
}

uint16_t TCS3200::readColorData() {
    // Read the color data from the OUT pin
    uint16_t colorData = 0;
    
    // Read data from the sensor (a few clock cycles)
    for (int i = 0; i < 16; i++) {
        colorData = (colorData << 1) | gpio_get(out_pin);
    }
    
    return colorData;
}

void TCS3200::readColor(uint16_t &red, uint16_t &green, uint16_t &blue) {
    // Read the color values for Red, Green, and Blue
    // Set the appropriate pin configurations for each color channel
    gpio_put(s0_pin, 0); // Enable full scale for frequency
    gpio_put(s1_pin, 0);
    
    // Read red value
    red = readColorData();
    
    // Set to green
    gpio_put(s0_pin, 1);
    gpio_put(s1_pin, 0);
    green = readColorData();
    
    // Set to blue
    gpio_put(s0_pin, 0);
    gpio_put(s1_pin, 1);
    blue = readColorData();
}
