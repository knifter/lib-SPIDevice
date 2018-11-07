
#ifndef __SPIDEVICE_H
#define __SPIDEVICE_H

#include <stdint.h>

#include <Arduino.h>
#include <SPI.h>

class SPIDevice
{
    public:
        SPIDevice(SPIClass& spi, const int8_t cs) 
            : _spi(spi), _cs(cs) { }
        SPIDevice(SPIClass& spi, const int8_t cs, const SPISettings& settings) 
            : _spi(spi), _cs(cs), _spisettings(settings) { }
        SPIDevice(SPIClass& spi, const int8_t cs, const uint32_t clock, const uint8_t bitOrder, const uint8_t dataMode)
            : _spi(spi), _cs(cs), _spisettings(clock, bitOrder, dataMode) { }

    protected:
        SPIClass& _spi;
        int8_t _cs;
        SPISettings _spisettings;

        uint8_t write(const uint8_t data[], const uint8_t len);
        void write16(const uint16_t);
        uint32_t read32();
};

#endif //__SPIDEVICE_H
