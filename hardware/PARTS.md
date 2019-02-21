# Sensof HT v2
## Part Numbering
Part numbers are made up as follows:

  0003-pp-rr

Where:
 - 0003: Project number
 - pp: Part number
 - rr: Part revision

## Parts
These are the assigned partnumbers:

 - 00: Sensof HT v2 PCB Assembled
 - 01: Top layer solder stencil for Sensof HT v2 PCB
 - 02: Bottom layer solder stencil for Sensof HT v2 PCB
 - 03: Sensof HT v2 PCB Bare
 - 10: Casing Assembled
 - 11: Casing - Top
 - 12: Casing - Bottom
 - 80: Sensof HT v2 assembled device

## Project Breakdown Structure
Below is a structured breakdown of the project components. The identifier
before the '=' sign is the reference of a component within the sub assembly.
So what you see here is like a tree of BOM's.

 - SENSOF = Sensof HT v2 assembled device (0003-80)
   - PCB = PCB assembled (0003-00)
     - PCB = PCB Bare (0003-03)
     - * = See BOM schematics
   - CASING = Casing Assembled (0003-10)
     - TOP = Casing - Top (0003-11)
     - BOT = Casing - Bottom (0003-12)
     - SCREW = Screw ST2.2x6.5
   - BAT = CR2032 battery

# Sensof HT v1
Project number: 0002

Parts:
 - 00: Sensof HT v1 PCB Assembled
 - 01: Top layer solder stencil for Sensof HT v1 PCB
 - 02: *reserved for bottom layer stencil*
 - 03: Sensof HT v1 PCB Bare
