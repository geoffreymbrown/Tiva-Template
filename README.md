Tiva-Template
================

Simple template for creating projects with the TM4CG123 Launchpad using
the gnu toolchain (see https://launchpad.net/gcc-arm-embedded)
and the Stellaris Driver Lab

To test:

   (1) install the toolchain and doxygen 
       (if you want the library documentation)

   (2) change the TOOLROOT in Makefile.common  
   
   (3) type make

Library documentation:

   open tiva/html/index.html

To create new projects:

   (1) clone the Demo directory (name the directory appropriately)

   (2) change TEMPLATEROOT in the cloned makefile to point to the template directory

   (3) modify as needed, adding any needed library objects to the OBJ list in the Makefile

Debugging:

    Use gdb with openocd in seperate terminal windows

    (1) openocd -f lm4f.cfg
    (2) arm-none-eabi-gdb -x gdbinit Demo/Demo.elf

See this link for getting openocd working on OS X
http://forum.stellarisiti.com/topic/1741-using-gdb-and-openocd-to-remote-debug-tivastellaris-on-a-mac-os/
