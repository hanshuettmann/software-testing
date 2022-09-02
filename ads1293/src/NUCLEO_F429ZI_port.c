/**
 ******************************************************************************
 * @file    Drivers/ADS1293/Src/NUCLEO_F429ZI.c
 * @author  Hans Hüttmann
 * @brief   This file provides firmware functions to port the ADS1293 on the
 * 			NUCLEO F429ZI board
 */
/* Includes ------------------------------------------------------------------*/
#include "NUCLEO_F429ZI_port.h"

/* SPI handler declaration */
static SPI_HandleTypeDef hspi;

/* Private function prototypes -----------------------------------------------*/

/**
 * @brief  Initialize SPI peripheral
 * @param  dummy set this value to 0
 * @retval NUCLEO_SPIStatusTypeDef Init process status
 */
NUCLEO_SPIStatusTypeDef spiInit(uint8_t dummy)
{
	/*##-1- Configure the SPI peripheral ######################################*/
	hspi.Instance = SPI1;

	hspi.Init.Mode = SPI_MODE_MASTER;
	hspi.Init.Direction = SPI_DIRECTION_2LINES;
	hspi.Init.DataSize = SPI_DATASIZE_8BIT;
	hspi.Init.CLKPolarity = SPI_POLARITY_LOW; // CPOL = 0
	hspi.Init.CLKPhase = SPI_PHASE_2EDGE;	  // CPHA = 1
	hspi.Init.FirstBit = SPI_FIRSTBIT_MSB;
	hspi.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_64;
	hspi.Init.NSS = SPI_NSS_SOFT;

	/* Init peripheral */
	if (HAL_SPI_Init(&hspi) != HAL_OK)
	{
		/* Initialization Error */
		return NUCLEO_SPI_ERROR;
	}
	return NUCLEO_SPI_OK;
}

/**
 * @brief  Send data through the SPI MOSI line
 * @param  ptxData pointer to the uint8_t buffer to be sent
 * @param  size amount of data to be sent
 * @retval none
 */
NUCLEO_SPIStatusTypeDef spiSendData(uint8_t *ptxData, uint16_t size)
{
	/* Validate ptxData and size parameters */
	if (ptxData == NULL || size <= 0) {
		return NUCLEO_SPI_ERROR;
	}

	if (HAL_SPI_Transmit(&hspi, ptxData, size, HAL_MAX_DELAY) != HAL_OK) {
		return NUCLEO_SPI_ERROR;
	}

	return NUCLEO_SPI_OK;
}

/**
 * @brief  Receive data from the SPI MISO line
 * @param  prxData pointer to the uint8_t buffer
 * @param  size amount of data to be sent
 * @retval none
 */
NUCLEO_SPIStatusTypeDef spiReceiveData(uint8_t *prxData, uint16_t size)
{
	/* Validate ptxData and size parameters */
	if (prxData == NULL || size <= 0) {
		return NUCLEO_SPI_ERROR;
	}

	if (HAL_SPI_Receive(&hspi, prxData, size, HAL_MAX_DELAY) != HAL_OK) {
		return NUCLEO_SPI_ERROR;
	}

	return NUCLEO_SPI_OK;
}

/**
 * @brief  Handle NSS line by software
 * @param  state set line to high or low
 * @retval none
 */
void setNSS(GPIO_PinState state)
{
	/* GPIO PA4 used as NSS line */
	HAL_GPIO_WritePin(SPIx_NSS_SOFT_GPIO_PORT, SPIx_NSS_SOFT_PIN, state);
	return;
}
