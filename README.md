# Arduino Serial RFID Library

This is a simple Arduino library to interact with [ID-innovations RFID readers](https://www.sparkfun.com/products/11827) when these are connected to the [SparkFun RFID USB Reader](https://www.sparkfun.com/products/9963). All RFID tags detected by the reader are transmitted over serial (or USB, using the USB-to-serial converter) and can be easily read on an Arduino by just consuming a serial buffer.

This library does not do much, it basically abstracts all the tasks related to the serial buffer management and discards the input when there is noise or the RFID tag is malformed.

There are some usage examples in the `examples` folder.

## Installation

Follow the instructions in the [Arduino Libraries page](https://www.arduino.cc/en/Guide/Libraries) (download a .zip file and import it using `Add .ZIP library`).