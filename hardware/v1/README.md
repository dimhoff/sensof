# Sensof HT v1 PCB (0002-00-00)
This is an experimental PCB for the Sensof HT nodes. Main features of this PCB
are:

 - Uses a Ceramic 50 Ohm antenna + matching network
 - Has extensions connectors to connect to GPIO/I2C

The Ceramic antenna was chosen to see if it had a better range then a
differential loop antenna. It also allows of a small PCB.

The extension headers would allow other uses then just the Humidity/Temperature
sensor.

# Issues
The following issues are found with the first prototype board(tag:
'hardware/0002-00-00')

## Range
The range of the is very limited. Apparently the antenna matching isn't optimal.

Replacing the antenna with a SMA connector, and then hooking the PCB up to a
HackRF through an attenuator, allowed for some simple tests.

This showed the output power to be relative high compared to a RFM60S. But the
power level is not very constant when sending a long pulse.

Doing a frequency sweep shows the power level is stable in the 300-400 MHz
range. I would have expected a spike around 434 MHz, like in AN369 "SI4010
Antenna Interface and Matching Network Guide"

## Assembly
The matching network makes assembly complicated and requires the device to be
reflow soldered.

## Price
The amount of quality components needed for antenna matching and the antenna it
self are relative expensive.
