
#define STM32F051 //COMPULSORY
#include "stm32f0xx.h" //COMPULSORY
#include "lcd_stm32f0.h"

// If using UCT STM32 Development board, write #define UCT_BOARD below
#define UCT_BOARD

// GLOBAL VARIABLES ----------------------------------------------------------|
char display[3];
uint8_t count=0; uint32_t press_count=0;



// FUNCTION DECLARATIONS -----------------------------------------------------|

void main(void); //COMPULSORY
void init_LEDs(void); //COMPULSORY
void display_on_LEDs(uint8_t num); //COMPULSORY
void display_on_LCD (uint8_t dec);
void init_switches (void);
void init_sw3(void);
void init_external_interrupts(void);
void EXTI2_3_IRQHandler(void);
void q1_6(void);

// MAIN FUNCTION -------------------------------------------------------------|

void main(void)
{ lcd_command(CLEAR); /* clear LCD */
 init_sw3 ();
 init_external_interrupts();
 init_LEDs();
 init_switches ();


 while(1)
 {
  if ((press_count%2)!=0){q1_6();}
  else if ((press_count%2)==0){
   lcd_command(CLEAR);
   display_on_LEDs(0);
   count=0;}}
}

