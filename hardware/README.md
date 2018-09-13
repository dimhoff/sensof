Sensof HT hardware
==================
Currently there are two PCB designs for the Sensof HT nodes:

 - v1: With on board 50 Ohm ceremic antenna
 - v2: With on board printed trace loop antenna

Sensof HT v1 PCB (0002-00-00)
=============================
This is an experimental PCB for the Sensof HT nodes. Main features of this PCB
are:

 - Uses a Ceramic 50 Ohm antenna + matching network
 - Has extensions connectors to connect to GPIO/I2C

The Ceramic antenna was chosen to see if it had a better range then a
differential loop antenna. It also allows for a smaller PCB.

The extension headers would allow other uses then just the Humidity/Temperature
sensor. And make it easier to experiment/develop with these modules.

Issues
-------
The following issues are found with the first prototype board(tag:
'hardware/0002-00-00')

### Range
The range of the is very limited. Apparently the antenna matching isn't optimal.

Replacing the antenna with a SMA connector, and then hooking the PCB up to a
HackRF through an attenuator, allowed for some simple tests.

This showed the output power to be relative high compared to a RFM60S. But the
power level is not very constant when sending a long pulse.

Doing a frequency sweep shows the power level is stable in the 300-400 MHz
range. I would have expected a spike around 434 MHz, like in AN369 "SI4010
Antenna Interface and Matching Network Guide"

### Assembly
The matching network makes assembly complicated and requires the device to be
reflow soldered.

### Price
The amount of quality components needed for antenna matching and the antenna it
self are relative expensive.

Sensof HT v2 PCB (0003-00-00)
=============================
This is an experimental PCB for the Sensof HT nodes. Main features of this PCB
are:

 - Use a differential loop antenna
 - Have a properly placed test pads to build test bed

The differential loop antenna is cheap and is easy in assembly.

To allow testing and firmware loading access is required to some of the Si4010
pins. In this design test pads are chosen. This eliminates the cost and
assembly of an extra connector that is only used during production. By placing
the test pads at a fixed pitch it should be easy to build a test bed with test
pins and a protoboard.

Issues
------
No serious issues were found with the first prototype board(tag:
'hardware/0003-00-00').

Range is comparable with the RFM60s based nodes I used before.

Only minor point is that the test points are spaced an 2.5 mm instead of 2.54
mm(0.1") but this within the acceptable margins.
