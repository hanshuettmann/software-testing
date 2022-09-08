/*
 * NUCLEO_F429ZI_port.h
 *
 *  Created on: Jun 16, 2022
 *      Author: hansh
 */

#ifndef ADS1293_INC_NUCLEO_F429ZI_PORT_H_
#define ADS1293_INC_NUCLEO_F429ZI_PORT_H_

/* Includes ------------------------------------------------------------------*/
#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

/* Public typedef ------------------------------------------------------------*/
/**
 * @brief  GPIO Bit SET and Bit RESET enumeration
 */
typedef enum
{
	GPIO_PIN_RESET = 0,
	GPIO_PIN_SET
} GPIO_PinState;

typedef enum
{
	NUCLEO_SPI_ERROR,
	NUCLEO_SPI_OK
} NUCLEO_SPIStatusTypeDef;

/* User can use this section to tailor SPIx instance used and associated
 resources */
/* Definition for SPIx clock resources */
#define SPIx SPI
#define SPIx_CLK_ENABLE() __HAL_RCC_SPI1_CLK_ENABLE()

#define SPIx_SCK_GPIO_CLK_ENABLE() __HAL_RCC_GPIOA_CLK_ENABLE()
#define SPIx_MISO_GPIO_CLK_ENABLE() __HAL_RCC_GPIOA_CLK_ENABLE()
#define SPIx_MOSI_GPIO_CLK_ENABLE() __HAL_RCC_GPIOA_CLK_ENABLE()
#define SPIx_NSS_GPIO_CLK_ENABLE() __HAL_RCC_GPIOA_CLK_ENABLE()
#define SPIx_NSS_SOFT_GPIO_CLK_ENABLE() __HAL_RCC_GPIOD_CLK_ENABLE()

#define SPIx_FORCE_RESET() __HAL_RCC_SPI1_FORCE_RESET()
#define SPIx_RELEASE_RESET() __HAL_RCC_SPI1_RELEASE_RESET()

/* Definition for SPIx Pins */
#define SPIx_SCK_PIN GPIO_PIN_5
#define SPIx_SCK_GPIO_PORT GPIOA

#define SPIx_MISO_PIN GPIO_PIN_6
#define SPIx_MISO_GPIO_PORT GPIOA

#define SPIx_MOSI_PIN GPIO_PIN_7
#define SPIx_MOSI_GPIO_PORT GPIOA

#define SPIx_NSS_PIN GPIO_PIN_4
#define SPIx_NSS_GPIO_PORT GPIOA

#define SPIx_NSS_SOFT_PIN GPIO_PIN_14 // In order to use CS manually by software
#define SPIx_NSS_SOFT_GPIO_PORT GPIOD

/* Definition for SPIx Pins AF */
#define SPIx_SCK_AF GPIO_AF5_SPI1
#define SPIx_MISO_AF GPIO_AF5_SPI1
#define SPIx_MOSI_AF GPIO_AF5_SPI1
#define SPIx_NSS_AF GPIO_AF5_SPI1

/* Public function prototypes ------------------------------------------------*/
NUCLEO_SPIStatusTypeDef spiInit(uint8_t dummy);
NUCLEO_SPIStatusTypeDef spiSendData(uint8_t *ptxData, uint16_t size);
NUCLEO_SPIStatusTypeDef spiReceiveData(uint8_t *prxData, uint16_t size);
void setNSS(GPIO_PinState state);

#endif /* API_ADS1293_INC_NUCLEO_F429ZI_PORT_H_ */
