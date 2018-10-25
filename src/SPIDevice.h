
#ifndef __SPIDEVICE_H
#define __SPIDEVICE_H

#include <stdint.h>

#include <Arduino.h>
#include <SPI.h>

class SPIDevice
{
    public:
        SPIDevice(SPIClass& spi, const int8_t cs) : _spi(spi), _cs(cs) { }

    protected:
        SPIClass& _spi;
        int8_t _cs;

        uint8_t write(const uint8_t data[], const uint8_t len);
        void write16(const uint16_t);

        // uint8_t spixfer(uint8_t x);

        // void read(const uint8_t reg, uint8_t *buf, const uint8_t num);
        // void write(const uint8_t reg, const uint8_t *buf, const uint8_t num);

        // void      write8(const uint8_t reg, const uint8_t value);
        // void      write16(const uint8_t reg, const uint16_t value);
        // uint8_t   read8(const uint8_t reg);
        // uint16_t  read16(const uint8_t reg);
        // uint32_t  read24(const uint8_t reg);

};

#endif //__SPIDEVICE_H
