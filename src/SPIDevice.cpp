#include "SPIDevice.h"

#include <stdio.h>
#include <stdint.h>
#include <Arduino.h>
#include <SPI.h>

uint8_t SPIDevice::write(const uint8_t data[], const uint8_t len)
{
    digitalWrite(_cs, LOW);
    uint8_t cnt = 0;
    while(cnt++ != len)
        _spi.transfer(data[cnt]);
    digitalWrite(_cs, HIGH);
    return cnt;
}

void SPIDevice::write16(const uint16_t v)
{
    digitalWrite(_cs, LOW);
    _spi.transfer16(v);
    digitalWrite(_cs, HIGH);
}
