## FilaWinder EEPROM addresses

_This firmware is written by Simon Tillema for a mechanism to spool filaments on empty rolls. You can use this firmware without any restriction, but note that using it is at your own risk. I do not take any responsibility for any harm caused by my code or the self-fabricated mechanism._

### EEPROM addresses
Following table shows the EEPROM addresses with a description
EEPROM address|Description
-|-
 0 - 3|EEPROM version
 4|material selection
 5 - 6|Spool size (a.k.a. target weight)
 7 - 10|Barrel diameter (in mm)
 11 - 12|Speed (in mm/s)