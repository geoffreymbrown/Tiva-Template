#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "driverlib/debug.h"
#include "driverlib/eeprom.h"
#include "driverlib/fpu.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "utils/ustdlib.h"
#include "utils/uartstdio.h"
#include "utils/cmdline.h"

// Input buffer for commands

static char g_cInput[128];

#ifdef DEBUG
void
__error__(char *pcFilename, uint32_t ui32Line)
{
}
#endif


//*****************************************************************************
//
// Command: help
//
// Print the help strings for all commands.
//
//*****************************************************************************

int
CMD_help(int argc, char **argv)
{
    int32_t i32Index;

    (void)argc;
    (void)argv;

    //
    // Start at the beginning of the command table
    //
    i32Index = 0;

    //
    // Get to the start of a clean line on the serial output.
    //
    UARTprintf("\nAvailable Commands\n------------------\n\n");

    //
    // Display strings until we run out of them.
    //
    while(g_psCmdTable[i32Index].pcCmd)
    {
      UARTprintf("%17s %s\n", g_psCmdTable[i32Index].pcCmd,
                 g_psCmdTable[i32Index].pcHelp);
      i32Index++;
    }

    //
    // Leave a blank line after the help strings.
    //

    UARTprintf("\n");

    return (0);
}

int
CMD_read(int argc, char **argv) {
  uint32_t addr;
  uint32_t val;

  if (argc < 2)
    return (CMDLINE_TOO_FEW_ARGS);

  if (argc > 2)
    return (CMDLINE_TOO_MANY_ARGS);

  addr = ustrtoul(argv[1], 0, 10);

  ROM_EEPROMRead(&val, addr & ~3, 4);

  UARTprintf("EEPROM[%d] == %d\n", addr & ~3, val);
  return (0);

}

int
CMD_write(int argc, char **argv) {
  uint32_t addr;
  uint32_t val;

  if (argc < 3)
    return (CMDLINE_TOO_FEW_ARGS);

  if (argc > 3)
    return (CMDLINE_TOO_MANY_ARGS);

  addr = ustrtoul(argv[1],  0, 10);
  val  = ustrtoul(argv[2],  0, 10);

  ROM_EEPROMProgram(&val, addr & ~3, 4);
  UARTprintf("EEPROM[%d] <- %d\n", addr & ~3, val);


  return (0);

}

// Table of valid command strings, callback functions and help messages.  

tCmdLineEntry g_psCmdTable[] =
{
    {"help",     CMD_help,      " : Display list of commands" },
    {"read",     CMD_read,      " : Read word from eeprom :  read addr "},
    {"write",    CMD_write,     " : Write word to eeprom :  write addr val"},
    {0,0,0}
};


void
ConfigureUART(void) {

    // Enable the GPIO Peripheral used by the UART.

    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    // Enable UART0

    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);


    // Configure GPIO Pins for UART mode.

    ROM_GPIOPinConfigure(GPIO_PA0_U0RX);
    ROM_GPIOPinConfigure(GPIO_PA1_U0TX);
    ROM_GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    // Use the internal 16MHz oscillator as the UART clock source.

    ROM_UARTClockSourceSet(UART0_BASE, UART_CLOCK_PIOSC);

    // Initialize the UART for console I/O.

    UARTStdioConfig(0, 115200, 16000000);
}

int
main(void) {

  int32_t err;

    // Enable lazy stacking for interrupt handlers. 

    ROM_FPUEnable();
    ROM_FPULazyStackingEnable();


    // Set the clocking to run directly from the crystal.

    ROM_SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN |
                       SYSCTL_XTAL_16MHZ);


    // Enable EEPROM

    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_EEPROM0);

    err = ROM_EEPROMInit();

    // Enable Uart

    ConfigureUART();


    UARTprintf("\n## eeprom example: eeprom status %d, size %d, blocks %d\n", 
	       err, ROM_EEPROMSizeGet(), ROM_EEPROMBlockCountGet());

    while(1) { 

      int32_t i32CommandStatus;

      UARTprintf("\n>");

      while(UARTPeek('\r') == -1) {
            SysCtlDelay(SysCtlClockGet() / (1000 / 3));
      }
      UARTgets(g_cInput,sizeof(g_cInput));
      i32CommandStatus = CmdLineProcess(g_cInput);

      switch (i32CommandStatus) {
      case CMDLINE_BAD_CMD:
	UARTprintf("Bad command!\n");
	break;
      case CMDLINE_TOO_MANY_ARGS:
	UARTprintf("Too many arguments for command processor!\n");
	break;
      case CMDLINE_TOO_FEW_ARGS:
	UARTprintf("Too few arguments for command processor!\n");
	break;
      case CMDLINE_INVALID_ARG:
	UARTprintf("Invalid argument for command processor!\n");
	break;
      }
    }
}
