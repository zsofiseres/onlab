/***************************************************************************//**
 * @file
 * @brief Simple LED Blink Demo for EFM32GG_STK3700
 * @version 5.2.2
 *******************************************************************************
 * # License
 * <b>Copyright 2015 Silicon Labs, Inc. http://www.silabs.com</b>
 *******************************************************************************
 *
 * This file is licensed under the Silabs License Agreement. See the file
 * "Silabs_License_Agreement.txt" for details. Before using this software for
 * any purpose, you must agree to the terms of that agreement.
 *
 ******************************************************************************/

/*
#include "em_device.h"
#include "em_chip.h"
#include "em_system.h"
#include "em_cmu.h"
#include "em_timer.h"
#include "em_adc.h"
#include "em_dac.h"
#include "em_gpio.h"
#include "bsp.h"

#define adref 3.3
#define felbontas 4096
#define adkonst  (adref/felbontas)
#define adcmeret 100
#define FS 5000 // mintavételi frekvencia megadása Hz-ben
#define TIMER_DIV (12000000/FS-1) // osztási arány

 uint32_t ADC_data_in_tomb[adcmeret];
 double AD_voltage[adcmeret];
 int index=0;

void TIMER_config(){
	   //*********************************************
	   // Timer configuration *
	   //*********************************************
	   TIMER_Init_TypeDef TIMER0_init = TIMER_INIT_DEFAULT;
	   //void TIMER_Init(TIMER_TypeDef *timer, const TIMER_Init_TypeDef *init);
	   TIMER_Init(TIMER0, &TIMER0_init);
	   TIMER_CounterSet(TIMER0, 0); //
	   //__STATIC_INLINE void TIMER_TopSet(TIMER_TypeDef *timer, uint32_t val)
	   TIMER_TopSet(TIMER0, TIMER_DIV); // 48MHz/4/x = 12MHz/x
	   //__STATIC_INLINE void TIMER_IntClear(TIMER_TypeDef *timer, uint32_t flags);
	   TIMER_IntClear(TIMER0, TIMER_IF_OF);
	   //TIMER_IntEnable(TIMER_TypeDef *timer, uint32_t flags);
	   TIMER_IntEnable(TIMER0, TIMER_IF_OF);
	   NVIC_EnableIRQ(TIMER0_IRQn);

}
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
	 CMU_ClockEnable(cmuClock_TIMER0, true);
	 CMU_ClockEnable(cmuClock_ADC0, true);
	 CMU_ClockEnable(cmuClock_DAC0, true);
}

// ******************************************
// * T I M E R I R Q *
// ******************************************
uint32_t ADC_data_in; //DAC_data_out;
uint32_t TimerCnt;
void TIMER0_IRQHandler(void){
	ADC_data_in = ADC_DataSingleGet(ADC0);
	ADC_Start(ADC0, adcStartSingle);
	ADC_data_in_tomb[index]= ADC_data_in;
	AD_voltage[index]=ADC_data_in * adkonst;
	if(index==(adcmeret-1))
	{
		index=0;
	}
	else
	{
		index++;
	}

	//DAC_data_out = process(ADC_data_in);
	//DAC_Channel0OutputSet(DAC0, DAC_data_out);
	TIMER_IntClear(TIMER0, TIMER_IF_OF);
	TimerCnt++;
	if (TimerCnt>FS){
	TimerCnt=0;
	}
}

*/
