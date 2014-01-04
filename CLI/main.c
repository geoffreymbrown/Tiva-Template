#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "driverlib/debug.h"
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

//*****************************************************************************
//
// Command: echo
//
//
//*****************************************************************************
int
CMD_echo(int argc, char **argv) {
  int i;
  for (i = 0 ; i < argc; i++) 
    UARTprintf("%s%s", i ? " " : "",argv[i]);
  UARTprintf("\n");
  return (0);
}

// Toggle led

int 
CMD_led(int argc, char **argv) {
  if (argc < 2)
    return (CMDLINE_TOO_FEW_ARGS);

  if (argc > 2)
    return (CMDLINE_TOO_MANY_ARGS);

  if (strcmp(argv[1],"on") == 0)  {
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, GPIO_PIN_2);
  }
  else if (strcmp(argv[1],"off") == 0 ) {
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, 0);
  }
  else
    return (CMDLINE_INVALID_ARG);
  return (0);
}

// Table of valid command strings, callback functions and help messages.  

tCmdLineEntry g_psCmdTable[] =
{
    {"help",     CMD_help,      " : Display list of commands" },
    {"echo",     CMD_echo,      " : Echo Arguments"},
    {"led",      CMD_led,       " : set led [on|off]"},
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

    UARTClockSourceSet(UART0_BASE, UART_CLOCK_PIOSC);

    // Initialize the UART for console I/O.

    UARTStdioConfig(0, 115200, 16000000);
}

int
main(void) {

    // Enable lazy stacking for interrupt handlers. 

    ROM_FPUEnable();
    ROM_FPULazyStackingEnable();


    // Set the clocking to run directly from the crystal.

    ROM_SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN |
                       SYSCTL_XTAL_16MHZ);

    // Enable the GPIO port and PF2 

    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    ROM_GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_2);

    // Enable Uart

    ConfigureUART();


    UARTprintf("\n*********cli example:************\n");

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
