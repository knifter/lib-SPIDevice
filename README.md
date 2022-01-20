# Introduction
Arduino library to wrap SPI device classes

While writing several supoport libraries for several devices it became cumbersome to keep implementing the read/write functions and sorting out the byte order for each device. 
That is what this libary supports.

It's major features are:
 * [ ] Wrap the SPI functions such that:
 * [ ] Set the specific SPI parameters on a per device basis
 * [ ] Handle the CS pin, whether software or hardware controlled

There is a twin: [lib-TwoWireDevice](https://github.com/knifter/lib-TwoWireDevice)

# Usage
## Code
### Declare
Inherited your devices from SPIDevice:
```
```

### Read / Write to device
[TODO]

### Check results
[TODO]

## Copy constructor
Personally I find it good practice to, at first, disable copy constructors and assignment operators until I've thought about them. In TwoWireDevices this is seldom something you want to support, I guess.. So I've disabled them in TwoWireDevice.h. Implement your own in your (inherited) device to re-enable them after you have done the thinking ;)
```
    private:
		    TwoWireDevice(const TwoWireDevice&);
		    TwoWireDevice& operator=(const TwoWireDevice&);
```

## PlatformIO
I'm an advocate of [Platform-IO](https://platformio.org/platformio-ide). To use this library with your PlatformIO project, add this to you platformio.ini environment:
``` 
lib_deps =
  https://github.com/knifter/lib-SPIDevice
```

## Examples
Some example devices are between my github repositories, like:
 * [x] [LS7366 Quadrature Counter](https://github.com/knifter/lib-LS7366)
 * [x] [MAX31855 Thermocouple reader](https://github.com/knifter/lib-MAX31855)
