/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "rtc.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "oled.h" 
#include "bmp.h"
#include <stdio.h>
#include <math.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define High     1
#define Low      2
#define Analog   3
#define Floating 4
/**
  *�������һ������ģʽ��Ӧ��gpio���ֹ���ģʽ�е������֣�
	1 High ��������ߵ�ƽ3.3v
	2 Low ��������͵�ƽ0v�����ݵ�зŵ�ʱӦ��ѡ�ô�ģʽ���
	*�����뿪©���������
	������������ṩ�ߵ�ƽ�͵͵�ƽ������������������������ָ��ء�
  ��©���ֻ���ṩ�͵�ƽ������������������źŵĹ���͸��롣
	
	3 Analog ģ������ģʽ�����ڶ�ȡ�ⲿģ���źţ�������ת��Ϊ����ֵ
	4 Floating ��������ģʽ����ʱ��gpio�ڴ���һ�����յ�״̬����������δʹ�õ��Ĺܽ�
  */


#define ADCZERO 300 //Ԥ��ŵ絽����mv
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
uint16_t ADC_Value;
volatile uint32_t count_0_1ms = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

//����˯��ģʽ�Ӻ���


void Mode_Init()//����ȫ����ʼ��Ϊģ��״̬
{
	//2�˿�
	GPIO_SwitchMode(GPIOA,GPIO_PIN_1,Analog);
	GPIO_SwitchMode(GPIOB,GPIO_PIN_3,Analog);
	GPIO_SwitchMode(GPIOB,GPIO_PIN_4,Analog);
	GPIO_SwitchMode(GPIOB,GPIO_PIN_5,Analog);

	//1�˿�
	GPIO_SwitchMode(GPIOA,GPIO_PIN_2,Analog);
	GPIO_SwitchMode(GPIOB,GPIO_PIN_6,Analog);
	GPIO_SwitchMode(GPIOB,GPIO_PIN_7,Analog);
	GPIO_SwitchMode(GPIOB,GPIO_PIN_8,Analog);
	GPIO_SwitchMode(GPIOB,GPIO_PIN_9,Analog);
}


///////////////////////////////////////////////////////////



void Measure_F1T2_680()//FΪfront TΪto
{
	Mode_Init();
	GPIO_SwitchMode(GPIOB,GPIO_PIN_6,High);
	GPIO_SwitchMode(GPIOB,GPIO_PIN_5,Low);
	
	//���õĶ˿�ȫ������
	GPIO_SwitchMode(GPIOB,GPIO_PIN_3,Floating);
	GPIO_SwitchMode(GPIOB,GPIO_PIN_4,Floating);
	GPIO_SwitchMode(GPIOB,GPIO_PIN_7,Floating);
	GPIO_SwitchMode(GPIOB,GPIO_PIN_8,Floating);
	
	//ʣ��˿��������ѹ
}


void Measure_F1T2_470k()//FΪfront TΪto
{
	Mode_Init();
	GPIO_SwitchMode(GPIOB,GPIO_PIN_6,High);
	GPIO_SwitchMode(GPIOB,GPIO_PIN_4,Low);
	
	//���õĶ˿�ȫ������
	GPIO_SwitchMode(GPIOB,GPIO_PIN_3,Floating);
	GPIO_SwitchMode(GPIOB,GPIO_PIN_5,Floating);
	GPIO_SwitchMode(GPIOB,GPIO_PIN_7,Floating);
	GPIO_SwitchMode(GPIOB,GPIO_PIN_8,Floating);
	
	//ʣ��˿��������ѹ
}




void Measure_F2T1_680()//FΪfront TΪto
{
	Mode_Init();
	GPIO_SwitchMode(GPIOB,GPIO_PIN_6,Low);
	GPIO_SwitchMode(GPIOB,GPIO_PIN_5,High);
	
	//���õĶ˿�ȫ������
	GPIO_SwitchMode(GPIOB,GPIO_PIN_3,Floating);
	GPIO_SwitchMode(GPIOB,GPIO_PIN_4,Floating);
	GPIO_SwitchMode(GPIOB,GPIO_PIN_7,Floating);
	GPIO_SwitchMode(GPIOB,GPIO_PIN_9,Floating);
	
	//ʣ��˿��������ѹ
}


void Measure_680_discharge()//FΪfront TΪto
{
	Mode_Init();
	GPIO_SwitchMode(GPIOB,GPIO_PIN_6,Low);
	GPIO_SwitchMode(GPIOB,GPIO_PIN_5,Low);
	
	//���õĶ˿�ȫ������
	GPIO_SwitchMode(GPIOB,GPIO_PIN_3,Floating);
	GPIO_SwitchMode(GPIOB,GPIO_PIN_4,Floating);
	GPIO_SwitchMode(GPIOB,GPIO_PIN_7,Floating);
	GPIO_SwitchMode(GPIOB,GPIO_PIN_9,Floating);
	
	//ʣ��˿��������ѹ
}


void Measure_F2T1_470k()//FΪfront TΪto
{
	Mode_Init();
	GPIO_SwitchMode(GPIOB,GPIO_PIN_6,Low);
	GPIO_SwitchMode(GPIOB,GPIO_PIN_4,High);
	
	//���õĶ˿�ȫ������
	GPIO_SwitchMode(GPIOB,GPIO_PIN_3,Floating);
	GPIO_SwitchMode(GPIOB,GPIO_PIN_5,Floating);
	GPIO_SwitchMode(GPIOB,GPIO_PIN_7,Floating);
	GPIO_SwitchMode(GPIOB,GPIO_PIN_9,Floating);

	//ʣ��˿��������ѹ
}

void Measure_470k_discharge()//FΪfront TΪto
{
	Mode_Init();
	GPIO_SwitchMode(GPIOB,GPIO_PIN_6,Low);
	GPIO_SwitchMode(GPIOB,GPIO_PIN_4,Low);
	
	//���õĶ˿�ȫ������
	GPIO_SwitchMode(GPIOB,GPIO_PIN_3,Floating);
	GPIO_SwitchMode(GPIOB,GPIO_PIN_5,Floating);
	GPIO_SwitchMode(GPIOB,GPIO_PIN_7,Floating);

	//ʣ��˿��������ѹ
}

void Measure_F2T1_1M()//FΪfront TΪto
{
	Mode_Init();
	GPIO_SwitchMode(GPIOB,GPIO_PIN_6,Low);
	GPIO_SwitchMode(GPIOB,GPIO_PIN_9,High);
	
	//���õĶ˿�ȫ������
	GPIO_SwitchMode(GPIOB,GPIO_PIN_3,Floating);
	GPIO_SwitchMode(GPIOB,GPIO_PIN_4,Floating);
	GPIO_SwitchMode(GPIOB,GPIO_PIN_5,Floating);
	GPIO_SwitchMode(GPIOB,GPIO_PIN_7,Floating);
}

///////////////////////////////////////////////////////////////////

// �жϻص�����
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  if (htim->Instance == TIM1) count_0_1ms++;
}

// ��ȡ����������������΢����
uint32_t GetTime(void) 
{
    return count_0_1ms;
}

///////////////////////////////////////////////////////////////////

/**
  * ��������: ���adc������ֵ����λmV��
  * �������:�������� 1,2���ֱ���1,2�˵�ADC
  * �� �� ֵ: ������mVֵ
  * ˵    ����
  */
void GetVol(uint32_t vol_arr[2])
{
    uint16_t arrget[2] = {0};
    int i,j;
    for(i = 0; i < 5; i++)
    {
        for(j = 0; j < 2; j++)
        {
            HAL_ADC_Start(&hadc1);
            if(HAL_ADC_PollForConversion(&hadc1, 10) == HAL_OK)
            {
                arrget[j] += HAL_ADC_GetValue(&hadc1);
            }
        }
        HAL_ADC_Stop(&hadc1);
    }
    vol_arr[0] = (uint32_t)(arrget[0] * 3300 / 4096.0 / 5); // ��һ���˿ڵ�ƽ��ֵ
    vol_arr[1] = (uint32_t)(arrget[1] * 3300 / 4096.0 / 5); // �ڶ����˿ڵ�ƽ��ֵ
}




uint32_t GetVol1(int a)//aΪ1,2�ֱ���1,2�˵�ADC(PA1,PA2)
{
	uint16_t arrget[2] = {0};
	uint16_t Vol;
	int i,j;
	for(i=0;i<5;i++)
	{
		for(j=0;j<2;j++)
		{
			HAL_ADC_Start(&hadc1);
			if(HAL_ADC_PollForConversion(&hadc1, 10) == HAL_OK)
			{
				arrget[j] += HAL_ADC_GetValue(&hadc1);
			}
		}
		HAL_ADC_Stop(&hadc1);
	}
	Vol = (int)(arrget[a-1] * 3300 / 4096.0 / 5);//��β�����ȡƽ��
	//Res = (int)((3300.0/Vol-1.0)*510);

	return Vol;
}


uint32_t GetVol2(int a)//aΪ1,2�ֱ���1,2�˵�ADC(PA1,PA2)
{
	uint16_t arrget[2] = {0};
	uint16_t Vol;
	int i,j;
		for(j=0;j<2;j++)
		{
			HAL_ADC_Start(&hadc1);
			if(HAL_ADC_PollForConversion(&hadc1, 10) == HAL_OK)
			{
				arrget[j] += HAL_ADC_GetValue(&hadc1);
			}
		}
		HAL_ADC_Stop(&hadc1);
	Vol = (int)(arrget[a-1] * 3300 / 4096.0 );//��β�����ȡƽ��
	//Res = (int)((3300.0/Vol-1.0)*510);

	return Vol;
}


/**
  * ��������: �жϺ���Ԫ�����ͣ������жϽ����ӡ����Ļ��
  * �������: ��
  * �� �� ֵ: 1-3������
  * ˵    ����1����2����3���4������1-2 5������2-1
  */

int Element_Type()
{
	uint32_t adcget1,adcget2,adc_values[2];
	Measure_F1T2_470k();
	HAL_Delay(300);
	GetVol(adc_values);
	if(adc_values[1]>=3250 && adc_values[0]<=70)
	{
		Measure_F2T1_680();
	  HAL_Delay(300);
	  GetVol(adc_values);
		if(adc_values[0]>=3250 && adc_values[1]<=50) return 2;
		else return 5;
			
	}
	else{
	  Measure_F1T2_680();
	  HAL_Delay(500);
	  GetVol(adc_values);
		if(adc_values[1]>=3250 && adc_values[0]<=50) 
		{
			Measure_680_discharge();
			HAL_Delay(300);
			Measure_F2T1_680();
			HAL_Delay(100);
			GPIO_SwitchMode(GPIOB,GPIO_PIN_5,Low);
			adcget1=GetVol2(1);
			HAL_Delay(1);
			adcget2=GetVol2(1);
			if(adcget1-adcget2 >=10 && adcget2-adcget1>=10) return 2;
			else return 1;
		}
		Measure_F2T1_680();
	  HAL_Delay(300);
	  GetVol(adc_values);
		if(adc_values[0]>=3250 && adc_values[1]<=50) return 4;
		else return 1;
	}

}




/**
  * ��������: ����ļ�������ʾ
  * �������: 
  * �� �� ֵ: 
  * ˵    ������������ֵ�����ѽ��������Ļ��
  */
void Resistance_Check()
{
	float Res_1;
	uint32_t Res_2;
	uint32_t adc_values[2];
	Measure_F1T2_680();
	HAL_Delay(5);
	GetVol(adc_values);
	Res_1 = ( ( (float)adc_values[1] ) / ( (float)adc_values[0] )-1.0)*708;
	Measure_F1T2_470k();
	HAL_Delay(5);
	GetVol(adc_values);
	Res_2 = (int)(( ( (float)adc_values[1] ) / ( (float)adc_values[0] )-1.0)*475000);
	
	OLED_DrawBMP(32,2,80,4,BMP1);//������
	if(Res_1 <= 15000) OLED_Showdecimal(0,4,Res_1,7,1,16);   
	else OLED_ShowNum(0,4,Res_2,7,16);
	OLED_ShowCHinese(80,4,7);				
}



/**
  * ��������: ���ݵļ�������ʾ
  * �������: 
  * �� �� ֵ: 
  * ˵    ����������ݵ�ֵ�����ѽ��������Ļ��
  */
void Capacitance_Check()
{
	uint16_t adcget1, adcget2;
	float Res;
  uint32_t time1, time2;
  uint16_t i = 0;
	
	Measure_F2T1_680();
	HAL_Delay(100);
	GPIO_SwitchMode(GPIOB,GPIO_PIN_5,Low);
	adcget1 = GetVol2(1);
	time1 = GetTime();
	
	 while (i < 0xffff) {
       adcget2 = GetVol2(1);
       i++;
       if (adcget2 < ADCZERO) {
           break;
      }
  }
	time2 = GetTime();
	
	Res = (time2 - time1) / (375 * log(adcget1 / (float) adcget2)) * 1000;

		
		if(Res >= 1000) {
			OLED_DrawBMP(32,2,80,4,BMP2);//������
		OLED_Showdecimal(0,4,Res/1000,4,2,16);
		OLED_ShowString(80,4,"uF");	
			return;
	}
		
	
		Measure_F2T1_470k();
		HAL_Delay(100);
	  GPIO_SwitchMode(GPIOB,GPIO_PIN_4,Low);
		adcget1 = GetVol2(1);
	  time1 =GetTime();
	
	  while (i < 0xffff) {
       adcget2 = GetVol2(1);
       i++;
       if (adcget2 < ADCZERO) {
           break;
      }
  }
	time2 = GetTime();
	
	Res = (time2 - time1) / (240000 * log(adcget1 / (float) adcget2)) * 1000;
	if(Res >= 10){
		OLED_DrawBMP(32,2,80,4,BMP2);//������
	    OLED_Showdecimal(0,4,Res,4,2,16);
		  OLED_ShowString(80,4,"nF");	
			return;
	}
	
	else {
		Measure_F2T1_1M();
		HAL_Delay(100);
	  GPIO_SwitchMode(GPIOB,GPIO_PIN_9,Low);
		adcget1 = GetVol2(1);
	  time1 =GetTime();
	
	  while (i < 0xffff) {
       adcget2 = GetVol2(1);
       i++;
       if (adcget2 < ADCZERO) {
           break;
      }
  }
	time2 = GetTime();
	
		  if(adcget1<=550) {
			OLED_ShowCHinese(0,2,8); OLED_ShowCHinese(16,2,9); OLED_ShowCHinese(32,2,10);
	    OLED_ShowCHinese(48,2,11); OLED_ShowCHinese(64,2,12); OLED_ShowCHinese(80,2,13);return;
		}
	
	Res = (time2 - time1) / (0.66 * log(adcget1 / (float) adcget2));
	OLED_DrawBMP(32,2,80,4,BMP2);//������
	OLED_Showdecimal(0,4,Res,4,2,16);
	OLED_ShowString(80,4,"pF");

	}

}





/**
  * ��������: ��еļ�������ʾ
  * �������: 
  * �� �� ֵ: 
  * ˵    ���������е�ֵ�����ѽ��������Ļ��
  */
void Inductance_Check()
{
	uint32_t adcget1, adcget2, adc_values[2];
	float Res,Esr;
	
	
	Measure_680_discharge();
	HAL_Delay(100);
	GPIO_SwitchMode(GPIOB,GPIO_PIN_5,High);
	adcget1=GetVol2(1);
	adcget2=GetVol2(1);
	HAL_Delay(100);
	
	Measure_F1T2_680();
	HAL_Delay(5);
	GetVol(adc_values);
	Esr = ( ( (float)adc_values[1] ) / ( (float)adc_values[0] )-1.0)*708;
	OLED_ShowString(0,6,"ESR=");	
	OLED_Showdecimal(32,6,Esr,2,2,16);
  OLED_ShowCHinese(80,6,7);	
	
	
}

/**
  * ��������: ������ѹ���ļ�������ʾ
  * �������: 
  * �� �� ֵ: 
  * ˵    ��������ѹ����ֵ�����ѽ��������Ļ��
  */
void Diode_Check_1()//����4ʱʹ��
{
		uint32_t adcget,adc_values[2];
	  Measure_F1T2_680();
		GetVol(adc_values);	  
	  HAL_Delay(100);
	  adcget = adc_values[1] - adc_values[0];
	  OLED_ShowNum(16,2,1,1,16);
	  OLED_DrawBMP(32,2,80,4,BMP4);//��������
	  OLED_ShowNum(80,2,2,1,16);
		OLED_ShowString(0,4,"Vd=");	
	  OLED_Showdecimal(32,4,adcget/1000.0,1,2,16);
	  OLED_ShowString(64,4,"V");	
}

void Diode_Check_2()//����5ʱʹ��
{
	  float adcget;
	  Measure_F2T1_680();
	  HAL_Delay(100);
		adcget = GetVol1(1) / 1000.0;
	  OLED_ShowNum(16,2,2,1,16);
	  OLED_DrawBMP(32,2,80,4,BMP4);//��������
	  OLED_ShowNum(80,2,1,1,16);
		OLED_ShowString(0,4,"Vd=");	
	  OLED_Showdecimal(32,4,adcget,1,2,16);
	  OLED_ShowString(64,4,"V");	
}




/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_SPI1_Init();
  MX_ADC1_Init();
  MX_USART1_UART_Init();
  MX_RTC_Init();
  MX_TIM1_Init();
  /* USER CODE BEGIN 2 */
	
	//HAL_ADCEx_Calibration_Start(&hadc1);    //ADУ׼
	HAL_TIM_Base_Start_IT(&htim1);
	OLED_Init();
	OLED_Clear();

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
		
		OLED_ShowCHinese(0,0,17); OLED_ShowCHinese(16,0,18); OLED_ShowCHinese(32,0,19);
	  OLED_ShowCHinese(48,0,20); OLED_ShowCHinese(64,0,21); OLED_ShowCHinese(80,0,22);

    HAL_Delay(1000);
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSI|RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 25;
  RCC_OscInitStruct.PLL.PLLN = 200;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	HAL_Delay(10);
	if(HAL_GPIO_ReadPin(KEY_GPIO_Port,KEY_Pin) == GPIO_PIN_RESET)
	{
		OLED_Clear();
			switch(Element_Type())
		{
			case 1:
		  Resistance_Check();break;
			case 2:
			Capacitance_Check();break;
			case 3:OLED_DrawBMP(32,2,80,4,BMP3);//�����
			Inductance_Check();break;
			case 4:Diode_Check_1(); break;
			case 5:Diode_Check_2(); break;			
		}

	}
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
