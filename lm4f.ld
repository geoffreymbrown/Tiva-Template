ENTRY(Reset_Handler)

MEMORY
{
  FLASH (rx) : ORIGIN = 0x00000000, LENGTH = 128K
  RAM  (xrw) : ORIGIN = 0x20000000, LENGTH = 32K
}

/* highest address of the user mode stack */
/* this is essentially 0x20000000 + 32K */

_estack = 0x20008000;

SECTIONS
{
    .text :
    {
        _text = .;
        KEEP(*(.isr_vector))      
        *(.text*)    
        *(.rodata*)  
        _etext = .;
        _sidata = _etext;
    } >FLASH
    
    .data  : AT (ADDR(.text) + SIZEOF(.text))
    {
        _sdata = . ;
        _data = . ;
        *(vtable)
        *(.data*)
        _edata = . ;
    } >RAM
    
    .bss :
    {
        _sbss = .;
	__bss_start__ = _sbss;
        _bss = .;
        *(.bss*) 
        *(COMMON)
        _ebss = . ;
	__bss_end__ = _ebss;
    } >RAM
    
    PROVIDE ( end = _ebss );
    PROVIDE ( _end = _ebss );
    PROVIDE ( _exit = _ebss );
}