
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
 
 // OTHER FUNCTIONS -----------------------------------------------------------|

/* Description:
 * This function initialises the GPIO to display output data
 */
void init_LEDs()
{
// Enable GPIOB clock
RCC->AHBENR |= RCC_AHBENR_GPIOBEN;

// Setup GPIOB pins 0-7 as outputs
GPIOB->MODER |= GPIO_MODER_MODER0_0 | GPIO_MODER_MODER1_0 | GPIO_MODER_MODER2_0 | GPIO_MODER_MODER3_0;
GPIOB->MODER |= GPIO_MODER_MODER4_0 | GPIO_MODER_MODER5_0 | GPIO_MODER_MODER6_0 | GPIO_MODER_MODER7_0;
}

/* Description:
 * This function takes in an 8 bit positive number and displays it on the LEDs
 */
void display_on_LEDs(uint8_t num)
{
#ifdef UCT_BOARD
 *(uint8_t *)0x48000414 = num;
#else
 *(uint8_t *)0x48000814 = num << 8;
#endif
}

/* Description:
 * This function displays an 8 bit integer onto the LCD
 */
void display_on_LCD(uint8_t dec)
{
 init_LCD();
 sprintf(display,"%d", dec);
 lcd_command(CLEAR); /* clear LCD */
 lcd_putstring(display);

}

/* Description:
 * This function initialises SW1 and SW2
 */
void init_switches(void)
{
RCC->AHBENR | = RCC_AHBENR_GPIOAEN; // enables clock to GPIOA

GPIOA-> PUPDR |= GPIO_PUPDR_PUPDR1_1; // enables pull-up resistor to SW1
GPIOA-> PUPDR |= GPIO_PUPDR_PUPDR2_1; // enables pull-up resistor to SW2
}
void init_sw3(void){

 RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
 GPIOA->PUPDR |= GPIO_PUPDR_PUPDR3_0;
}


void init_external_interrupts(void){
 RCC->APB2ENR |= RCC_APB2ENR_SYSCFGCOMPEN;

 SYSCFG->EXTICR[0] |= SYSCFG_EXTICR1_EXTI3_PA;
 EXTI->IMR|= EXTI_IMR_MR3;
 EXTI->FTSR |= EXTI_FTSR_TR3;

 NVIC_EnableIRQ(EXTI2_3_IRQn);
}



void EXTI2_3_IRQHandler(void){

 press_count++;
 display_on_LCD(0);
 delay(8000);
 EXTI->PR|=EXTI_PR_PR3;}



void q1_6(void) {
    init_LEDs();
    init_switches();

        if ((GPIOA->IDR & GPIO_IDR_1) == 0) {
            count++;
            lcd_command(CLEAR);
            display_on_LEDs(count);
            display_on_LCD(count);
            init_switches();
        } else if ((GPIOA->IDR & GPIO_IDR_2) == 0) {
            count--;
            lcd_command(CLEAR);
            display_on_LEDs(count);
            display_on_LCD(count);
            init_switches();
        }
    }



 while(1)
 {
  if ((press_count%2)!=0){q1_6();}
  else if ((press_count%2)==0){
   lcd_command(CLEAR);
   display_on_LEDs(0);
   count=0;}}
}

