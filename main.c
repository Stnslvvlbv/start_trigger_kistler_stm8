/* Includes ------------------------------------------------------------------*/
#include "stm8s.h"

uint8_t ReceivedData = 0;
static void GPIO_Config(void);
static void CLK_Config(void);
static void UART1_Config(void); 
void Delay(uint32_t nCount);
/* Private functions ---------------------------------------------------------*/

#define LED_GPIO_PORT  (GPIOH)
#define LED_GPIO_PINS  (GPIO_PIN_3 | GPIO_PIN_2 | GPIO_PIN_1 | GPIO_PIN_0)

void main(void)
{
  //  Delay((uint32_t)0xFFFFF);
  /* Clock configuration -----------------------------------------*/
  CLK_Config();  

  /* GPIO configuration -----------------------------------------*/
  GPIO_Config();  

  /* UART1 configuration -----------------------------------------*/
  UART1_Config();  

  while (1)
  {
      /* Wait u12ntil a byte is received */
     while (UART1_GetFlagStatus(UART1_FLAG_RXNE) == RESET)
      {
        
      /* Read the received byte */
      ReceivedData = UART1_ReceiveData8();
     
     switch (ReceivedData) 
     {
     //case '1':
     case 49:
       GPIO_WriteLow(GPIOB, GPIO_PIN_5);
       GPIO_WriteLow(GPIOD, GPIO_PIN_1);
       break;
     //case '2':
     case 50:
       GPIO_WriteHigh(GPIOB, GPIO_PIN_5);
       GPIO_WriteHigh(GPIOD, GPIO_PIN_1);
       break;
     default:
       break;
     }
      }
     
  }
}

static void CLK_Config(void)
{
    CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);
}

static void GPIO_Config(void)
{ 
  GPIO_Init(GPIOB, GPIO_PIN_5, GPIO_MODE_OUT_PP_HIGH_FAST);
  GPIO_Init(GPIOD, GPIO_PIN_1, GPIO_MODE_OUT_PP_HIGH_FAST);
}

static void UART1_Config(void)
{
  
  UART1_Init((uint32_t)9600, UART1_WORDLENGTH_8D,UART1_STOPBITS_1, UART1_PARITY_NO,
                   UART1_SYNCMODE_CLOCK_DISABLE, UART1_MODE_TXRX_ENABLE);

  /* Enable the UART Receive interrupt: this interrupt is generated when the UART
    receive data register is not empty */
  UART1_ITConfig(UART1_IT_RXNE_OR, ENABLE);
  
  /* Enable the UART Transmit complete interrupt: this interrupt is generated 
     when the UART transmit Shift Register is empty */
  UART1_ITConfig(UART1_IT_TXE, ENABLE);

  /* Enable UART */
  UART1_Cmd(ENABLE);
  
    /* Enable general interrupts */
  enableInterrupts();
}

void Delay(uint32_t nCount)
{
  /* Decrement nCount value */
  while (nCount != 0)
  {
    nCount--;
  }
}

#ifdef USE_FULL_ASSERT

void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif
