
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
        SPIClass&   _spi;
        int8_t      _cs;
        SPISettings _spisettings;
        bool        _initialized = false;

        bool        begin();

        uint8_t     write(const uint8_t data[], const uint8_t len);
        uint8_t     read(uint8_t* data, const uint8_t len);

        void        writeread(const uint8_t *wbuf, const size_t wlen, 
                                    uint8_t *rbuf, const size_t rlen, 
                              const uint8_t rvalue = 0x00);

        uint8_t     readreg8(const uint8_t reg);
        void        writereg8(const uint8_t reg, const uint8_t data);
        uint16_t    readreg16(const uint8_t reg);
        uint32_t    readreg24(const uint8_t reg);

        void        write16(const uint16_t);
        uint32_t    read32();
};

#endif //__SPIDEVICE_H
