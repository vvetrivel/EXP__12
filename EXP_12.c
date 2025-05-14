#include "TCS3200.h"
#include "pico/stdlib.h"
#include "hardware/spi.h"

TCS3200 colorSensor(spi0, 17, 18, 19); // Assuming S0, S1, OUT pins on GPIO 17, 18, and 19

int main() {
    stdio_init_all();
    
    // Initialize the sensor
    colorSensor.begin();
    
    uint16_t red, green, blue;
    
    while (true) {
        // Read color values
        colorSensor.readColor(red, green, blue);
        
        // Print the values
        printf("Red: %u, Green: %u, Blue: %u\n", red, green, blue);
        
        sleep_ms(1000);
    }
}
