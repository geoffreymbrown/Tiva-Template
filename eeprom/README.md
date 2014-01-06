Command line program to test eeprom.  

read addr :  returns the word stored at (addr & ~3); i.e, the word address.

write addr val :  writes val to location (addr & ~3)



