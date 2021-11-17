#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/systick.h"
#include "driverlib/interrupt.h"

#ifdef DEBUG
void __error__(char *pcFilename, uint32_t ui32Line)
{
    while(1);
}
#endif

int main(void)
{
    volatile uint32_t ui32Loop;
    volatile uint32_t ui32Period = 0;

    SysTickPeriodSet(12000000); // f = 1Hz para clock = 24MHz
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPION);    // Enable the GPIO port that is used for the on-board LED.
    
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOJ); // Habilita GPIO J (push-button SW1 = PJ0, push-button SW2 = PJ1)
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOJ)); // Aguarda final da habilitação
    
    GPIOPinTypeGPIOInput(GPIO_PORTJ_BASE, GPIO_PIN_0 | GPIO_PIN_1); // push-buttons SW1 e SW2 como entrada
    GPIOPadConfigSet(GPIO_PORTJ_BASE, GPIO_PIN_0 | GPIO_PIN_1, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
    
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPION))    // Check if the peripheral access is enabled.
    {
    }
      SysTickIntEnable();
      SysTickEnable();      
    
    GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE, GPIO_PIN_1); // Led 1
    printf("Start\n");
    
    while(1)
    {
        for(ui32Loop = 0; ui32Loop < 200000; ui32Loop++) //Delay
        {}
        if(GPIOPinRead(GPIO_PORTJ_BASE, GPIO_PIN_0) == GPIO_PIN_0)// Testa estado do push-button SW1
        {
         SysTickDisable();    
         SysTickValueGet(); // periodo do Systick counter
                  
         ui32Period = SysTickValueGet(); //Atribui o valor de SystickValueGet para ui32Period
         GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_1, GPIO_PIN_1);// LED 1 é acesso
         for(ui32Loop = 0; ui32Loop < 200000; ui32Loop++) //Delay
        {}                 
        }else       
          printf("O valor do periodo eh %d.\n", ui32Period);
        for(ui32Loop = 0; ui32Loop < 200000; ui32Loop++) // Delay
        {}    
    }
}
