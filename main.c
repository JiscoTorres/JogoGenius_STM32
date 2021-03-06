/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
// Nossa sequência de até 100 itens vai começar vazia.
int sequencia[100] = {}; // aqui, tem {} por estar vazia

// Indica a rodada atual que o jogo se encontra.

int rodada_atual = 0; //Está em 0 por não ter que selecionar uma especifica, se não daria erro.

// Indica o passo atual dentro da sequência, é usado enquanto a sequência

// está sendo reproduzida.

int passo_atual_na_sequencia = 0;



/*

 * Indica o pino de leds e botões.

 * Os pinos de leds e botões estão em ordem, relacionados uns aos outros, ou

 * seja, o primeiro led está relacionado ao primeiro botão. A ordem destas

 * sequências também estão relacionadas a ordem dos tons.

 */

int pinosLeds[4] = {GPIO_PIN_3, GPIO_PIN_4, GPIO_PIN_5, GPIO_PIN_6}; // [4], indica que tem 4 diferentes pinos de leds
int pinosBotoes[4] = {GPIO_PIN_9,GPIO_PIN_10,GPIO_PIN_11,GPIO_PIN_12}; // [4], indica que tem 4 diferentes pinos de botão
// Indica se um botão foi pressionado durante o loop principal.

int pressionar = 0;

// Flag indicando se o jogo acabou.

int lose = 0; //declarar a parte de perder.

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

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
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  // Se perdeu o jogo reinicializamos todas as variáveis.

	    if (lose) {

	      int sequencia[100] = {};

	      rodada_atual = 0;
	      passo_atual_na_sequencia = 0;

	      lose = 0;

	    }
	    // Chama a função que inicializa a próxima rodada.


	   	    // Reproduz a sequência atual.

	   	    reproduzirSequencia();

	   	    // Aguarda os botões serem pressionados pelo jogador.

	   	    aguardarUser();


	   	    // Aguarda 1 segundo entre cada jogada.

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

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6, GPIO_PIN_RESET);

  /*Configure GPIO pins : PA3 PA4 PA5 PA6 */
  GPIO_InitStruct.Pin = GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PA10 PA11 PA12 PA13 */
  GPIO_InitStruct.Pin = GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
void reproduzirSequencia(){
  for (int i = 0; i < rodada_atual; i++) {


    HAL_GPIO_WritePin(GPIOA,pinosLeds[sequencia[i]], 1);
    HAL_Delay(500);
    HAL_GPIO_WritePin(GPIOA,pinosLeds[sequencia[i]], 0);
    HAL_Delay(100);

  }
}



// Aguarda o jogador iniciar sua jogada.

void aguardarUser() {

  for (int i = 0; i < rodada_atual; i++) {
    aguardarJogada();

    verificarJogada();


    if (lose){

      break;
    }



    passo_atual_na_sequencia++;

  }



  // Redefine a variável para 0.

  passo_atual_na_sequencia = 0;
}


void aguardarJogada(){

  int jogada_efetuada = 0;

  while (!jogada_efetuada) {

    for (int i = 0; i <= 3; i++) {

      if (HAL_GPIO_ReadPin(GPIOB,pinosBotoes[i]) == 1) {

        //Dizendo qual foi o botao pressionado.

        pressionar = i;

        HAL_GPIO_WritePin(GPIOA,pinosLeds[i], 1);

        HAL_Delay(300);

       HAL_GPIO_WritePin(GPIOA,pinosLeds[i], 0);

        jogada_efetuada = 1;

      }

    }

    HAL_Delay(10);
  }
}


void verificarJogada() {
  if (sequencia[passo_atual_na_sequencia] != pressionar) {
    // GAME OVER.

    for (int i = 0; i <= 3; i++) {
      HAL_GPIO_WritePin(GPIOA,pinosLeds[i], 1);
      HAL_Delay(200);
      HAL_GPIO_WritePin(GPIOA,pinosLeds[i], 0);
    }



    for (int i = 0; i <= 3; i++) {

      HAL_GPIO_WritePin(GPIOA,pinosLeds[0], 1);

      HAL_GPIO_WritePin(GPIOA,pinosLeds[1], 1);

      HAL_GPIO_WritePin(GPIOA,pinosLeds[2], 1);

      HAL_GPIO_WritePin(GPIOA,pinosLeds[3], 1);

      HAL_Delay(100);

      HAL_GPIO_WritePin(GPIOA,pinosLeds[0], 0);

      HAL_GPIO_WritePin(GPIOA,pinosLeds[1], 0);

      HAL_GPIO_WritePin(GPIOA,pinosLeds[2], 0);

      HAL_GPIO_WritePin(GPIOA,pinosLeds[3], 0);

      HAL_Delay(100);

    }

    lose = 1;

  }

}

void tocarSomDeInicio() {

  HAL_GPIO_WritePin(GPIOA,pinosLeds[0], 1); //led3

  HAL_GPIO_WritePin(GPIOA,pinosLeds[1], 1); //led4
  HAL_GPIO_WritePin(GPIOA,pinosLeds[2], 1); //led5
  HAL_GPIO_WritePin(GPIOA,pinosLeds[3], 1); //led6

  HAL_Delay(500);

  HAL_GPIO_WritePin(GPIOA,pinosLeds[0], 0);
  HAL_GPIO_WritePin(GPIOA,pinosLeds[1], 0);
  HAL_GPIO_WritePin(GPIOA,pinosLeds[2], 0);

  HAL_GPIO_WritePin(GPIOA,pinosLeds[3], 0);
  HAL_Delay(500);
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
     Hex: print("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
