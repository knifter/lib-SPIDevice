#include "SPIDevice.h"

#include <stdio.h>
#include <stdint.h>
#include <Arduino.h>
#include <SPI.h>

uint8_t SPIDevice::write(const uint8_t data[], const uint8_t len)
{
    _spi.beginTransaction(_spisettings);
    digitalWrite(_cs, LOW);
    uint8_t cnt = 0;
    while(cnt++ != len)
        _spi.transfer(data[cnt]);
    digitalWrite(_cs, HIGH);
    _spi.endTransaction();

    return cnt;
}

void SPIDevice::write16(const uint16_t v)
{
    digitalWrite(_cs, LOW);
    _spi.beginTransaction(_spisettings);
    _spi.transfer16(v);
    digitalWrite(_cs, HIGH);
    _spi.endTransaction();
}

uint32_t SPIDevice::read32(void) 
{ 
    uint32_t d = 0;

    // Do beginTransaction after setting CS low to introduce a little delay after CS
    digitalWrite(_cs, LOW);
    _spi.beginTransaction(_spisettings);
    d = _spi.transfer(0);
    d <<= 8;
    d |= _spi.transfer(0);
    d <<= 8;
    d |= _spi.transfer(0);
    d <<= 8;
    d |= _spi.transfer(0);
    digitalWrite(_cs, HIGH);
    _spi.endTransaction();

    return d;
}
