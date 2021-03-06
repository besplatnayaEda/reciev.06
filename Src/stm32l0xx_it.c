/**
  ******************************************************************************
  * @file    stm32l0xx_it.c
  * @brief   Interrupt Service Routines.
  ******************************************************************************
  *
  * COPYRIGHT(c) 2017 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "stm32l0xx_hal.h"
#include "stm32l0xx.h"
#include "stm32l0xx_it.h"

/* USER CODE BEGIN 0 */
#include "match_dsp.h"
#include "math.h"
#include <string.h>

#define	N	16

// ��� 8 ������� ������


#define ALERT_H 65535
#define ALERT_L 0
#define REBOOT	0



extern uint32_t buff1;	// �����

static float retf11,retf12,retf21,retf22,retfl, buff0, buffl0;	// �������

uint16_t  tmptime = 0;


static uint8_t /*bin = 0,*/ bin8[2], numbit = 0;//, str[8] = {0x00U,0xFFU,0xFFU,0xFFU,0xFFU,0xFFU,0xFFU,0x0DU};	//modbus

static uint16_t j, crc, bin, binx;//,n = 0;
extern uint16_t name;


uint16_t bit_1 = 0;
uint16_t bit_0 = 0;
uint16_t bit_n = 0;
uint16_t binn;

extern uint8_t blink_type;
uint16_t blink_ext = 0;
uint16_t blink_cnt = 0;
uint8_t  blink_8sec = 0;

float max;
float min;


_Bool frame = 0;
_Bool pass = 0;
_Bool det = 0;
_Bool numb[N];
_Bool numbn[N];
extern _Bool blink_trg;

float tst = 0.0f;

static uint8_t  nop = 0;




extern _Bool trg_pin;

/*
const float coef719_1[] = {-0.31930648926751132,  0.99727198600603129, 0.069118341539523037,  -0.030159984550979461,   0.069118341539523037};
const float coef719_2[] = {-0.31391267740209011,  0.99727078945024961, 0.014483053822428604,  -0.0028295846247246475,  0.014483053822428604};
	
const float coef781_1[] = {-0.077292613280225797, 0.99727152694092847, 0.069453393437029332,  -0.013635786632875516,    0.069453393437029332};
const float coef781_2[] = {-0.071833716231854639, 0.99727124851500604, 0.014412510754072216,   0.00068539554318540984,  0.014412510754072216};
	*/


extern float history11[], history12[], history21[], history22[], historyl[];
extern SettingParametrs_t SETUP;
extern Cmd_Type CMD;
//rxData_t rxDATA;
//txData_t txDATA;

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
extern DMA_HandleTypeDef hdma_adc;
extern ADC_HandleTypeDef hadc;
extern DMA_HandleTypeDef hdma_tim2_ch1;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim21;
extern DMA_HandleTypeDef hdma_usart2_tx;
extern DMA_HandleTypeDef hdma_usart2_rx;
extern UART_HandleTypeDef huart2;

/******************************************************************************/
/*            Cortex-M0+ Processor Interruption and Exception Handlers         */ 
/******************************************************************************/

/**
* @brief This function handles Non maskable interrupt.
*/
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */

  /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
* @brief This function handles Hard fault interrupt.
*/
void HardFault_Handler(void)
{
  /* USER CODE BEGIN HardFault_IRQn 0 */

  /* USER CODE END HardFault_IRQn 0 */
  while (1)
  {
  }
  /* USER CODE BEGIN HardFault_IRQn 1 */

  /* USER CODE END HardFault_IRQn 1 */
}

/**
* @brief This function handles System service call via SWI instruction.
*/
void SVC_Handler(void)
{
  /* USER CODE BEGIN SVC_IRQn 0 */

  /* USER CODE END SVC_IRQn 0 */
  /* USER CODE BEGIN SVC_IRQn 1 */

  /* USER CODE END SVC_IRQn 1 */
}

/**
* @brief This function handles Pendable request for system service.
*/
void PendSV_Handler(void)
{
  /* USER CODE BEGIN PendSV_IRQn 0 */

  /* USER CODE END PendSV_IRQn 0 */
  /* USER CODE BEGIN PendSV_IRQn 1 */

  /* USER CODE END PendSV_IRQn 1 */
}

/**
* @brief This function handles System tick timer.
*/
void SysTick_Handler(void)
{
  /* USER CODE BEGIN SysTick_IRQn 0 */

  /* USER CODE END SysTick_IRQn 0 */
  HAL_IncTick();
  HAL_SYSTICK_IRQHandler();
  /* USER CODE BEGIN SysTick_IRQn 1 */

  /* USER CODE END SysTick_IRQn 1 */
}

/******************************************************************************/
/* STM32L0xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32l0xx.s).                    */
/******************************************************************************/

/**
* @brief This function handles EXTI line 0 and line 1 interrupts.
*/
void EXTI0_1_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI0_1_IRQn 0 */

  /* USER CODE END EXTI0_1_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_1);
  /* USER CODE BEGIN EXTI0_1_IRQn 1 */

  /* USER CODE END EXTI0_1_IRQn 1 */
}

/**
* @brief This function handles DMA1 channel 1 interrupt.
*/
void DMA1_Channel1_IRQHandler(void)
{
  /* USER CODE BEGIN DMA1_Channel1_IRQn 0 */

  /* USER CODE END DMA1_Channel1_IRQn 0 */
  HAL_DMA_IRQHandler(&hdma_adc);
  /* USER CODE BEGIN DMA1_Channel1_IRQn 1 */

  /* USER CODE END DMA1_Channel1_IRQn 1 */
}

/**
* @brief This function handles DMA1 channel 2 and channel 3 interrupts.
*/
void DMA1_Channel2_3_IRQHandler(void)
{
  /* USER CODE BEGIN DMA1_Channel2_3_IRQn 0 */
	
  /* USER CODE END DMA1_Channel2_3_IRQn 0 */
  HAL_DMA_IRQHandler(&hdma_usart2_tx);
  HAL_DMA_IRQHandler(&hdma_usart2_rx);
  /* USER CODE BEGIN DMA1_Channel2_3_IRQn 1 */

  /* USER CODE END DMA1_Channel2_3_IRQn 1 */
}

/**
* @brief This function handles DMA1 channel 4, channel 5, channel 6 and channel 7 interrupts.
*/
void DMA1_Channel4_5_6_7_IRQHandler(void)
{
  /* USER CODE BEGIN DMA1_Channel4_5_6_7_IRQn 0 */
	/*if(__HAL_DMA_GET_FLAG(&hdma_tim2_ch1, __HAL_DMA_GET_TC_FLAG_INDEX(&hdma_tim2_ch1)) != RESET)
	{
		HAL_TIM_PWM_Stop_DMA(&htim2,TIM_CHANNEL_1);
		HAL_GPIO_WritePin(HPT_Answer_OUT_GPIO_Port,HPT_Answer_OUT_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(Interrupt_OUT_GPIO_Port,Interrupt_OUT_Pin, GPIO_PIN_RESET);
		blink_trg = 0;
			//trg_pin = 0;
	}*/
  /* USER CODE END DMA1_Channel4_5_6_7_IRQn 0 */
  HAL_DMA_IRQHandler(&hdma_tim2_ch1);
  /* USER CODE BEGIN DMA1_Channel4_5_6_7_IRQn 1 */
	
  /* USER CODE END DMA1_Channel4_5_6_7_IRQn 1 */
}

/**
* @brief This function handles ADC1, COMP1 and COMP2 interrupts (COMP interrupts through EXTI lines 21 and 22).
*/
void ADC1_COMP_IRQHandler(void)
{
  /* USER CODE BEGIN ADC1_COMP_IRQn 0 */

  /* USER CODE END ADC1_COMP_IRQn 0 */
  HAL_ADC_IRQHandler(&hadc);
  /* USER CODE BEGIN ADC1_COMP_IRQn 1 */

  /* USER CODE END ADC1_COMP_IRQn 1 */
}

/**
* @brief This function handles TIM2 global interrupt.
*/
void TIM2_IRQHandler(void)
{
  /* USER CODE BEGIN TIM2_IRQn 0 */
	//HAL_GPIO_TogglePin(Interrupt_OUT_GPIO_Port,Interrupt_OUT_Pin);
  /* USER CODE END TIM2_IRQn 0 */
  HAL_TIM_IRQHandler(&htim2);
  /* USER CODE BEGIN TIM2_IRQn 1 */

  /* USER CODE END TIM2_IRQn 1 */
}

/**
* @brief This function handles TIM21 global interrupt.
*/
void TIM21_IRQHandler(void)
{
  /* USER CODE BEGIN TIM21_IRQn 0 */
	//HAL_GPIO_WritePin(Interrupt_OUT_GPIO_Port,Interrupt_OUT_Pin, GPIO_PIN_RESET);
	
	if(blink_cnt>0)
		blink_cnt++;
	if((blink_cnt>25600))
	{
		blink_cnt = 1;
		blink_8sec++;
		if(blink_8sec <= 4)
		{
			blink(blink_type);
		}
		else
		{
			blink_8sec = 0;
			blink_cnt = 0;
		}
	}
	
	if(!blink_trg)
	{
		if((blink_ext < 3200))
			blink_ext++;
		if(blink_ext == 3200)
			HAL_GPIO_WritePin(Interrupt_OUT_GPIO_Port,Interrupt_OUT_Pin, GPIO_PIN_RESET);
	}
	

	//buff00 = 0;	
	//for(n = 0; n < 1; n++)
	//	{
	//		buff00+=(((float)buff1[n])/1);
	//	}
	//buff00 = (float)buff1;
	buff0 = 3*((float)buff1)/65520; //65535;							// ?????? ? ?????? 
	
	
	// cheby 2
	retf11 = iir_test(buff0,SETUP.cf1s1,history11);			//f1
		retf12 = iir_test(retf11,SETUP.cf1s2,history12);
	
	retf21 = iir_test(buff0,SETUP.cf2s1,history21);			//f2
		retf22 = iir_test(retf21,SETUP.cf2s2,history22);
	
		buffl0 = fabsf(retf12)-fabsf(retf22);
		retfl  = iir_test(buffl0,SETUP.cflp,historyl);
	

		switch(CMD)
		{
			case START_DATA_TRANSMIT_FLP:
				HAL_UART_Transmit_DMA(&huart2,(uint8_t *)&retfl,sizeof(retfl));
			break;
			case START_DATA_TRANSMIT_F1:
				HAL_UART_Transmit_DMA(&huart2,(uint8_t *)&retf12,sizeof(retf12));
			break;
			case START_DATA_TRANSMIT_F2:
				HAL_UART_Transmit_DMA(&huart2,(uint8_t *)&retf22,sizeof(retf22));
			break;
			case START_DATA_TRANSMIT_IN:
				HAL_UART_Transmit_DMA(&huart2,(uint8_t *)&buff0,sizeof(buff0));
			break;
			default:
				break;
		}
		
		
	if(!det)
  {
		if ((retfl >= SETUP.ratio)||(retfl <= -SETUP.ratio))
			{
				j=0;
        det=1;
				max = 0;
				min = 0;
      }
  }
  else
	{
		if(j < SETUP.samplenum)
    {
			if(retfl >= SETUP.ratio)
			{	bit_1++; tst = 1;	}
			if(retfl <= -SETUP.ratio)
			{	bit_0++; tst = -1;  }
			if((retfl < SETUP.ratio)&&(retfl > -SETUP.ratio))
			{	bit_n++; tst = 0;	}
			
    }
    if(j == SETUP.samplenum)
		{
			if(numbit < N)
			{	
				if((bit_1 > bit_0)&&(bit_1 > bit_n)&&(bit_1 > (SETUP.samplenum/2)))
					{
						bin = bin<<1;
						bin = bin|1;
						binx = dataBuff(1);
						numb[numbit] = 1;
						numbit++;
						crc = crc_calculating((uint8_t *)&bin,1);
						//HAL_UART_Transmit_DMA(&huart2,(uint8_t *)&numbit,sizeof(numbit));
					}
				if((bit_0 > bit_1)&&(bit_0 > bit_n)&&(bit_0 > (SETUP.samplenum/2)))
					{
						bin = bin<<1;
						bin = bin|0;
						binx = dataBuff(0);
						numb[numbit] = 0;
						numbit++;
//						HAL_UART_Transmit_DMA(&huart2,(uint8_t *)&numbit,sizeof(numbit));
					}
				if((bit_n > bit_0)&&(bit_n > bit_1))
					{
						nop++;
						if((nop <= 0)&&(bit_n > (SETUP.samplenum/2)))
							{
								//bin = bin<<1;
								//bin = bin|0;
								//numb[numbit] = 0;
								binx = dataBuff(0);
								numbit++;
//								HAL_UART_Transmit_DMA(&huart2,(uint8_t *)&numbit,sizeof(numbit));
								
							}
						else
							{
								bit_1 = 0;
								bit_0 = 0;
								bit_n = 0;
								nop = 0;
								det=0;
								j=0;
								bin=0;
								numbit = 0;
								memset(numb,0,sizeof(numb));
							}
						
				}
					
					
			}
			
			bit_1 = 0;
			bit_0 = 0;
			bit_n = 0;
			j=0;
			
		}
  }
  j++;
	
	if( numbit == N )
	{
		
		bin8[0] = bin >> 8;
		bin8[1] = bin;
		//crc = crc_calculating((uint8_t *)bin8,2);
		binn = bin;

	/*	
		if(bin == name)
			txDATA.det = 1;
		else
			txDATA.det = 0;
		
		ret[0] = txDATA.det;
		ret[1] = 0;
		ret[2] = bin8[0];
		ret[3] = bin8[1];
				
		
		txDATA.name = bin;
		txDATA.crc = crc;
		
*/	//HAL_UART_Transmit_DMA(&huart2,(uint8_t *)&bin,sizeof(bin));
		if(bin == SETUP.name)
		{
			blink_cnt = 1;
			blink(PERSONAL);
		}
		if((bin == ALERT_H)||(bin == ALERT_L))
		{
			blink_cnt = 1;
			blink(ALARM);
		}
		/*if(bin == REBOOT)
			SCB->AIRCR = 0x05FA0004;*/
		
		det=0;
		bin=0;
		numbit = 0;
	}
	//HAL_GPIO_WritePin(Interrupt_OUT_GPIO_Port,Interrupt_OUT_Pin, GPIO_PIN_SET);
  /* USER CODE END TIM21_IRQn 0 */
  HAL_TIM_IRQHandler(&htim21);
  /* USER CODE BEGIN TIM21_IRQn 1 */

  /* USER CODE END TIM21_IRQn 1 */
}

/**
* @brief This function handles USART2 global interrupt / USART2 wake-up interrupt through EXTI line 26.
*/
void USART2_IRQHandler(void)
{
  /* USER CODE BEGIN USART2_IRQn 0 */
  /* USER CODE END USART2_IRQn 0 */
  HAL_UART_IRQHandler(&huart2);
  /* USER CODE BEGIN USART2_IRQn 1 */
  
  /* USER CODE END USART2_IRQn 1 */
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
