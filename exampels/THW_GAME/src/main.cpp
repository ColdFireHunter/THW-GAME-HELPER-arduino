#include <Arduino.h>
#include <Wire.h>
#include <IS32FL3236A.h>
#include <thwgamehelper.h>
#include <pins.h>

void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSIDiv = RCC_HSI_DIV1;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = RCC_PLLM_DIV1;
  RCC_OscInitStruct.PLL.PLLN = 8;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

IS32FL3236A led (0x3F,SDB);
thwgamehelper game(&led);

ADC_HandleTypeDef hadc1;
static void MX_ADC1_Init(void);
void adc_cal(ADC_HandleTypeDef *hadc);
void selectCh0();
void selectCh1();

void setup() {
  Serial.begin(115200);
  Serial.println("TEST OF IS32FL3236A FOR GAME");

  pinMode(BUTTON_1,INPUT_PULLUP);
  pinMode(BUTTON_2,INPUT_PULLUP);
  pinMode(DIFFICULTY_BUTTON,INPUT_PULLUP);
  pinMode(PLAYER_BUTTON,INPUT_PULLUP);
  pinMode(TEST_LED,OUTPUT);

  digitalWrite(TEST_LED,HIGH);
  delay(10000);
  digitalWrite(TEST_LED,LOW);

  game.begin();
  game.setParam();
  game.ledtest(0);

  MX_ADC1_Init();
  adc_cal(&hadc1);
}

void loop() {
  if (digitalRead(BUTTON_1) == 0 || digitalRead(BUTTON_2) == 0 || digitalRead(DIFFICULTY_BUTTON) == 0 || digitalRead(PLAYER_BUTTON) == 0  )
  {
    digitalWrite(TEST_LED,HIGH);
  }
  else
  {
    digitalWrite(TEST_LED,LOW);
  }
  
}
static void MX_ADC1_Init(void)
{
  ADC_ChannelConfTypeDef sConfig = {0};
  /** Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion)
  */
  hadc1.Instance = ADC1;
  hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV2;
  hadc1.Init.Resolution = ADC_RESOLUTION_10B;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.ScanConvMode = ADC_SCAN_ENABLE;
  hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  hadc1.Init.LowPowerAutoWait = DISABLE;
  hadc1.Init.LowPowerAutoPowerOff = DISABLE;
  hadc1.Init.ContinuousConvMode = DISABLE;
  hadc1.Init.NbrOfConversion = 1;
  hadc1.Init.DiscontinuousConvMode = ENABLE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc1.Init.DMAContinuousRequests = DISABLE;
  hadc1.Init.Overrun = ADC_OVR_DATA_PRESERVED;
  hadc1.Init.SamplingTimeCommon1 = ADC_SAMPLETIME_160CYCLES_5;
  hadc1.Init.SamplingTimeCommon2 = ADC_SAMPLETIME_160CYCLES_5;
  hadc1.Init.OversamplingMode = DISABLE;
  hadc1.Init.TriggerFrequencyMode = ADC_TRIGGER_FREQ_HIGH;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }
}
void adc_cal(ADC_HandleTypeDef *hadc)
{
	HAL_StatusTypeDef ret;

	// Make sure ADC peripheral is stopped
	ret = HAL_ADC_Stop(hadc);
	if(ret != HAL_OK)
	{
		Error_Handler();
	}
	
	HAL_Delay(10);

	/* Choose type of measurement
	ADC_SINGLE_ENDED
	ADC_DIFFERENTIAL_ENDED
	*/
	ret = HAL_ADCEx_Calibration_Start(hadc);
	if(ret != HAL_OK)
	{
		Error_Handler();
	}
  if(ret == HAL_OK)
	{
    Serial.println("CAL COMPLETE");
	}

	// Small delay to ensur end of calibration procedure
	HAL_Delay(10);
}
void selectCh0(){
    ADC_ChannelConfTypeDef sConfig = {0};
  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_0;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC_SAMPLINGTIME_COMMON_1;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
}
void selectCh1(){
    ADC_ChannelConfTypeDef sConfig = {0};
  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_1;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC_SAMPLINGTIME_COMMON_1;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }  
}