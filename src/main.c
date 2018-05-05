#include "em_device.h"
#include "em_chip.h"
#include "em_gpio.h"
#include "em_cmu.h"
#include "em_device.h"
#include "em_chip.h"
#include "em_system.h"
#include "em_cmu.h"
#include "em_adc.h"
#include "em_gpio.h"
#include "bsp.h"
#include "InitDevice.h"
#include "em_usart.h"
// C std header fájlok
#include <stdio.h>
#include <string.h>
// saját header fájlok
#include "constants.h" // Konstansok a projektben.
#include "message.h" // Üzenetkezeléshez tartozó változók és függvények.
#include "main.h"

#define adref 3.3
#define felbontas 4096
#define adkonst  (adref/felbontas)
#define adcmeret 100
#define FS 5000 // mintavételi frekvencia megadása Hz-ben
#define TIMER_DIV (12000000/FS-1) // osztási arány
#define LEDS 12

 uint32_t ADC_data_in_tomb[adcmeret];
 uint32_t ADC_data_in;
 double AD_voltage[adcmeret];
 int idx=0;


void ADC_config(){
	 //*********************************************
	  // ADC configuration *
	  //*********************************************
	  ADC_Init_TypeDef ADC0_Init = ADC_INIT_DEFAULT;
	  //void ADC_Init(ADC_TypeDef *adc, const ADC_Init_TypeDef *init);
	  ADC0_Init.prescale = 0; // 12MHz
	  ADC0_Init.timebase = 16;
	  ADC0_Init.warmUpMode = adcWarmupKeepADCWarm;
	  ADC_Init(ADC0, &ADC0_Init);
	  ADC_InitSingle_TypeDef ADC0_s_Init = ADC_INITSINGLE_DEFAULT;
	  //void ADC_InitSingle(ADC_TypeDef *adc, const ADC_InitSingle_TypeDef *init);
	  ADC0_s_Init.reference = adcRefVDD;
	  ADC0_s_Init.input = adcSingleInputCh0;
	  ADC_InitSingle(ADC0, &ADC0_s_Init);
}

void ADC_CMU_config(){
	//*********************************************
	 // CMU configuration *
	 //*********************************************
	 //void CMU_OscillatorEnable(CMU_Osc_TypeDef osc, bool enable, bool wait);
	 CMU_OscillatorEnable(cmuOsc_HFXO, true, true);
	 //void CMU_ClockSelectSet(CMU_Clock_TypeDef clock, CMU_Select_TypeDef ref);
	 CMU_ClockSelectSet(cmuClock_HF, cmuSelect_HFXO);
	 //SystemHFXOClockSet(uint32_t freq);
	 SystemHFXOClockSet(48000000);
	 //HFPERCLK: 48MHz/4 = 12MHz
	 //void CMU_ClockDivSet(CMU_Clock_TypeDef clock, CMU_ClkDiv_TypeDef div);
	 CMU_ClockDivSet(cmuClock_HFPER, cmuClkDiv_4);
	 // enable clock signals
	 //CMU_ClockEnable(CMU_Clock_TypeDef clock, bool enable);
	 CMU_ClockEnable(cmuClock_HFPER, true);
	 CMU_ClockEnable(cmuClock_GPIO, true);
	 CMU_ClockEnable(cmuClock_ADC0, true);



}



void init_leds()
{
	CMU_OscillatorEnable(cmuOsc_HFXO, true, true);
	CMU_ClockSelectSet(cmuClock_HF, cmuSelect_HFXO);
	//CMU_ClockSelectSet(cmuClock_HF, cmuSelect_HFRCO);
	//CMU_ClockEnable(cmuClock_HFPER, true);
	CMU_ClockEnable(cmuClock_GPIO, true);
	GPIO_PinModeSet(gpioPortC, 4, gpioModePushPull, 0);
}

volatile uint32_t msTicks; /* counts 1ms timeTicks */

//void Delay(uint32_t dlyTicks);

/***************************************************************************//**
 * @brief SysTick_Handler
 * Interrupt Service Routine for system tick counter
 ******************************************************************************/
void SysTick_Handler(void)
{
  msTicks++;       /* increment counter necessary in Delay()*/
}

/***************************************************************************//**
 * @brief Delays number of msTick Systicks (typically 1 ms)
 * @param dlyTicks Number of ticks to delay
 ******************************************************************************/
void Delay(uint32_t dlyTicks)
{
  uint32_t curTicks;

  curTicks = msTicks;
  while ((msTicks - curTicks) < dlyTicks) ;
}


#define bit0 GPIO->P[2].DOUTSET = 1 << 4; \
__asm__ __volatile__ ("nop"); \
__asm__ __volatile__ ("nop"); \
__asm__ __volatile__ ("nop"); \
__asm__ __volatile__ ("nop"); \
__asm__ __volatile__ ("nop"); \
__asm__ __volatile__ ("nop"); \
__asm__ __volatile__ ("nop"); \
__asm__ __volatile__ ("nop"); \
__asm__ __volatile__ ("nop"); \
__asm__ __volatile__ ("nop"); \
__asm__ __volatile__ ("nop"); \
__asm__ __volatile__ ("nop"); \
__asm__ __volatile__ ("nop"); \
GPIO->P[2].DOUTCLR = 1 << 4; \
__asm__ __volatile__ ("nop"); \
__asm__ __volatile__ ("nop"); \
__asm__ __volatile__ ("nop"); \
__asm__ __volatile__ ("nop"); \
__asm__ __volatile__ ("nop"); \
__asm__ __volatile__ ("nop"); \
__asm__ __volatile__ ("nop"); \
__asm__ __volatile__ ("nop"); \
__asm__ __volatile__ ("nop"); \
__asm__ __volatile__ ("nop"); \
__asm__ __volatile__ ("nop"); \
__asm__ __volatile__ ("nop"); \
__asm__ __volatile__ ("nop"); \
__asm__ __volatile__ ("nop"); \
__asm__ __volatile__ ("nop"); \
__asm__ __volatile__ ("nop"); \
__asm__ __volatile__ ("nop"); \
__asm__ __volatile__ ("nop"); \
__asm__ __volatile__ ("nop"); \
__asm__ __volatile__ ("nop"); \
__asm__ __volatile__ ("nop"); \
__asm__ __volatile__ ("nop"); \
__asm__ __volatile__ ("nop"); \
__asm__ __volatile__ ("nop"); \
__asm__ __volatile__ ("nop"); \
__asm__ __volatile__ ("nop"); \
__asm__ __volatile__ ("nop"); \
__asm__ __volatile__ ("nop"); \
__asm__ __volatile__ ("nop"); \
__asm__ __volatile__ ("nop"); \
__asm__ __volatile__ ("nop"); \
__asm__ __volatile__ ("nop"); \

#define bit1 GPIO->P[2].DOUTSET = 1 << 4; \
__asm__ __volatile__ ("nop"); \
__asm__ __volatile__ ("nop"); \
__asm__ __volatile__ ("nop"); \
__asm__ __volatile__ ("nop"); \
__asm__ __volatile__ ("nop"); \
__asm__ __volatile__ ("nop"); \
__asm__ __volatile__ ("nop"); \
__asm__ __volatile__ ("nop"); \
__asm__ __volatile__ ("nop"); \
__asm__ __volatile__ ("nop"); \
__asm__ __volatile__ ("nop"); \
__asm__ __volatile__ ("nop"); \
__asm__ __volatile__ ("nop"); \
__asm__ __volatile__ ("nop"); \
__asm__ __volatile__ ("nop"); \
__asm__ __volatile__ ("nop"); \
__asm__ __volatile__ ("nop"); \
__asm__ __volatile__ ("nop"); \
__asm__ __volatile__ ("nop"); \
__asm__ __volatile__ ("nop"); \
__asm__ __volatile__ ("nop"); \
__asm__ __volatile__ ("nop"); \
__asm__ __volatile__ ("nop"); \
__asm__ __volatile__ ("nop"); \
__asm__ __volatile__ ("nop"); \
__asm__ __volatile__ ("nop"); \
__asm__ __volatile__ ("nop"); \
__asm__ __volatile__ ("nop"); \
__asm__ __volatile__ ("nop"); \
__asm__ __volatile__ ("nop"); \
__asm__ __volatile__ ("nop"); \
__asm__ __volatile__ ("nop"); \
GPIO->P[2].DOUTCLR = 1 << 4; \
__asm__ __volatile__ ("nop"); \
__asm__ __volatile__ ("nop"); \
__asm__ __volatile__ ("nop"); \
__asm__ __volatile__ ("nop"); \
__asm__ __volatile__ ("nop"); \
__asm__ __volatile__ ("nop"); \
__asm__ __volatile__ ("nop"); \
__asm__ __volatile__ ("nop"); \
__asm__ __volatile__ ("nop"); \
__asm__ __volatile__ ("nop"); \
__asm__ __volatile__ ("nop"); \
__asm__ __volatile__ ("nop"); \

#define PIROS 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0
#define KEK 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,1,1,1,1,1
#define ZOLD 0,0,0,1,1,1,1,1, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0
#define rszin 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1
#define feher 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1

int zold[24] = {1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0};

int zold_szin[24] = {ZOLD};

int GLOBAL_COLORARRAY[LEDS][24];
/* *************
  ÜZENETKEZELÉS
************* */
// A PC-rõl UART-on keresztül érkezett üzenet.
extern char message[MESSAGE_MAX_SIZE]; // Üzenet tartalma.
extern int messageSize; // Üzenet hossza.
extern char command[COMMAND_MAX_SIZE]; //
// Változó egy új üzenet jelzésére. Az értéke true, ha új (még feldolgozatlan) üzenet érkezett.
extern bool volatile receivedMessage;
// Write Text parancshoz flag. Értéke true, ha éppen futó szöveg fut a kijelzõn. Egyébként false az értéke.
extern bool volatile writingText;
extern uint8_t ch; // UART-on kapott karakter.
extern bool volatile new_char; // Érkezett-e új karakter flag.

/* ********** */

void LEDprocess(int tomb[][24])
{
	int i,j;
	for(i = 0; i < LEDS; i++)
	{
		for(j = 0; j < 24; j++)
		{
			if(tomb[i][j]==1)
			{
				bit1;
			}
			else
			{
				bit0;
			}
		}
	}
	if(i == LEDS)
	{
		ADC_Start(ADC0, adcStartSingle);
		Delay(1);
	}
}

void delay50ms()
{
	int i;
	for(i=0;i<2800;i++)
	{
		__asm__ __volatile__ ("nop");
	}
}

void clear()
{
	int i;
	int j;
	for(i = 1; i <= LEDS; i++)
	{
		for(j = 1; j <= 24; j++)
		{
			bit0
		}
	}
}

void init_hardware()
{
	CHIP_Init();

	enter_DefaultMode_from_RESET();
	ADC_CMU_config();
	ADC_config();
	init_leds();

	/* Setup SysTick Timer for 1 msec interrupts  */
	if (SysTick_Config(CMU_ClockFreqGet(cmuClock_CORE) / 1000))
	{
		while (1) ;
	}
}

// AD átalakítás kiolvasása
void AD_process()
{

	ADC_data_in = ADC_DataSingleGet(ADC0);
	ADC_data_in_tomb[idx]= ADC_data_in;
	AD_voltage[idx]=ADC_data_in * adkonst;
	if(idx==(adcmeret-1))
	{
		idx=0;
	}
	else
	{
		idx++;
	}
}

/* ********************************************************* */
/* ********************************************************* */
/* ********************************************************* */

void color2array()
{
	int i;
	for(i = 0; i < LEDS; i++)
	{
		if(i % 2 == 0) { color2led(i, 255, 0, 0); }
		else { color2led(i, 0, 255, 0); }
	}
}

// RGB ---> GREEN RED BLUE
void color2led(int led, int red, int green, int blue)
{
	int j;
	int r = red;
	int g = green;
	int b = blue;
	for(j = 0; j < 24; j++)
	{
		if(j >= 0 && j <= 7)
		{
			GLOBAL_COLORARRAY[led][7-j] = g % 2;
			g = g / 2;
		}
		else if(j >= 8 && j <= 15)
		{
			GLOBAL_COLORARRAY[led][15-j+8] = r % 2;
			r = r / 2;
		}
		else if(j >= 16 && j <= 23)
		{
			GLOBAL_COLORARRAY[led][23-j+16] = b % 2;
			b = b / 2;
		}
		else
		{
			GLOBAL_COLORARRAY[led][j] = 0;
		}
	}
}

void oneColor(int red, int green, int blue)
{
	int i;
	for(i = 0; i < LEDS; i++)
	{
		color2led(i, red, green, blue);
	}
}

void setArray(int szin_tomb[])
{
	int i,j;
	for(i = 0; i < LEDS; i++)
	{
		for(j = 0; j < 24; j++)
		{
			GLOBAL_COLORARRAY[i][j] = szin_tomb[j];
		}
	}
}

int main(void)
{
	int i;
	init_hardware();
	USART_IntEnable(UART0, USART_IF_RXDATAV); // UART IT engedélyezés
	NVIC_EnableIRQ(UART0_RX_IRQn);  // UART IT engedélyezés
	USART_Tx(UART0, '<');
	USART_Tx(UART0, '<');
	Delay(1000);
	clear();
	Delay(1000);
	//color2array();
	//color2led(10, 255, 255, 255);
	//color2led(9, 255, 0, 0);
	oneColor(0, 255, 255);
	while(1)
	{
		// Érkezett karakter echo-ja.
				if (new_char) {
					new_char = false;
					USART_Tx(UART0, ch); // Karakterenkénti echo.
					// DEBUG-oláshoz: SegmentLCD_Number(ch);
				}

				// Ha új üzennet érkezett, akkor dolgozzuk fel.
				if(receivedMessage)
				{
					receivedMessage = false; // Feldolgozás után új üzenet várunk majd.
					writingText = false;

					// Üzenetek feldolgozása:
					processCommand(message);

					// Üzenetet feldolgoztuk, "töröljük" az elõzõ üzenetet az új fogadása elõtt.
					message[0] = '\0';
					messageSize = 0;
					// Terminál felkészítése a következõ parancsra:
					USART_Tx(UART0, '\n');
					string2USART(">>"); // Új prompt küldése.
				}
		AD_process();
	}
}
