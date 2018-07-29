# Si443x based Sensof receiver
This is a Sensof packet receiver based on the SiLabs Si443x transceiver chip.

**Development status:** Rough but 'works for me(tm)'

# Compile
The decryption key is hardcoded into the binary and needs to be provided in a
include file called key.inc. For example:

   # cat key.cinc 
   0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff

To compile sensof_recv run:

   # gcc -std=gnu99 sensof_recv.c -o sensof_recv -lcrypto

sensof_to_json requires node addresses to be hard coded in the source. Then to
compile run:

   # gcc -std=gnu99 sensof_to_json.c -o sensof_to_json -lcrypto

# Requirements
This program depends on the si443x_drv driver. This driver is available at:
https://github.com/dimhoff/si443x_drv.

# Run
To run the program first start the si443x_drv daemon with the register settings
for the Sensof packets.

   # si443x_drv -c si443x_sensof.regs

To dump all received sensof packets run:

   # sensof_recv /tmp/si443x.sock

Or to save received packets from known nodes to a JSON file run:

   # sensof_to_json /tmp/si443x.sock

By default the JSON file is written to '/dev/shm/sensof.json'.
