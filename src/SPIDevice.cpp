#include "SPIDevice.h"

#include <stdio.h>
#include <stdint.h>
#include <Arduino.h>
#include <SPI.h>

// #include <tools-log.h>

bool SPIDevice::begin()
{
    pinMode(_cs, OUTPUT);
    digitalWrite(_cs, HIGH);

    _spi.begin();

    _initialized = true;
    return true;
};

uint8_t SPIDevice::write(const uint8_t data[], const uint8_t len)
{
    digitalWrite(_cs, LOW);
    _spi.beginTransaction(_spisettings);
    // uint8_t cnt = 0;
    // while(cnt++ != len)
    //     _spi.transfer(data[cnt]);
    _spi.transferBytes(data, NULL, len);
    digitalWrite(_cs, HIGH);
    _spi.endTransaction();

    return len;
};

uint8_t SPIDevice::read(uint8_t* data, const uint8_t len)
{
    digitalWrite(_cs, LOW);
    _spi.beginTransaction(_spisettings);
    uint8_t cnt = 0;
    while(cnt != len)
        data[cnt++] = _spi.transfer(0);
    _spi.endTransaction();
    digitalWrite(_cs, HIGH);

    return cnt;
};

void SPIDevice::writeread(const uint8_t *wbuf, const size_t wlen, 
                                uint8_t *rbuf, const size_t rlen, 
                          const uint8_t rvalue) 
{
    digitalWrite(_cs, LOW);
    _spi.beginTransaction(_spisettings);

    _spi.transferBytes(wbuf, NULL, wlen);

    uint8_t rcnt = 0;
    while(rcnt != rlen)
        rbuf[rcnt++] = _spi.transfer(rvalue);

    _spi.endTransaction();
    digitalWrite(_cs, HIGH);
};

uint8_t SPIDevice::readreg8(const uint8_t reg)
{
    digitalWrite(_cs, LOW);
    _spi.beginTransaction(_spisettings);

    // Write address (MSB=0 -> read)
    _spi.transfer(reg & 0x7F);

    uint8_t r = _spi.transfer(0x00);

    _spi.endTransaction();
    digitalWrite(_cs, HIGH);

    return r;
};

void SPIDevice::writereg8(const uint8_t reg, const uint8_t data)
{
    write16(((reg | 0x80) << 8) | data);
};

uint16_t SPIDevice::readreg16(const uint8_t reg)
{
    digitalWrite(_cs, LOW);
    _spi.beginTransaction(_spisettings);

    // Write address (MSB=0 -> read)
    _spi.transfer(reg & 0x7F);

    uint16_t r = _spi.transfer16(0x0000);

    _spi.endTransaction();
    digitalWrite(_cs, HIGH);

    return r;
};

uint32_t SPIDevice::readreg24(const uint8_t reg)
{
    digitalWrite(_cs, LOW);
    _spi.beginTransaction(_spisettings);

    // Write address (MSB=0 -> read)
    _spi.transfer(reg & 0x7F);

    union
    {
        uint8_t raw[4];
        uint32_t i;
    } r;
    r.raw[3] = 0x00;
    r.raw[2] = _spi.transfer(0x00);
    r.raw[1] = _spi.transfer(0x00);
    r.raw[0] = _spi.transfer(0x00);

    _spi.endTransaction();
    digitalWrite(_cs, HIGH);

    return r.i;
};

void SPIDevice::write16(const uint16_t v)
{
    digitalWrite(_cs, LOW);
    _spi.beginTransaction(_spisettings);
    _spi.transfer16(v);
    digitalWrite(_cs, HIGH);
    _spi.endTransaction();
};

uint32_t SPIDevice::read32(void) 
{ 
    union {
        uint8_t raw[4];
        uint32_t i;
    } data;

    read(data.raw, sizeof(uint32_t));
    return data.i;
};

