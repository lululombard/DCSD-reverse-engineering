# Driving DCSD LEDs

Alright, the least interesting part: driving the LEDs. All those LEDs are connected to the CBUS of this FT232 chip.

The CBUS/bitbang is a mode of the FTDI chip. It requires a 8 bit long message to operate 4 GPIO ports. The first 4 bits are to specify if you want to read or write to the port.

Here we want to write a status to the LED, so our message will start with 1111, that's 0xF0 in hex. Then we must specify the wanted state of each LED.

The MSB is the yellow LED, followed by a disconnected pin, then the green LED, and finally the LSB is the red LED.

In dec we can say that yellow is 8 or 0x08, that green is 2 or 0x02 and that red is 1 or 0x01.

All we need to do is to add what we want to be turned on to 0xF0. Turning on the yellow LED would be 0xF0 + 0x08 = 0xF8.

You can turn on multiple LEDs, for instance green and red would be 0xF0 + 0x02 + 0x01 = 0xF3.

## Available downloads

- dcsd.c : fork of the libftdi bitbang example with custom USB address
- dcsd : compiled executable for linux arm
