#include <ads1293.h>
#include <NUCLEO_F429ZI_port.h>

/**
 * @brief  Initialize ADS1293 device
 * @param  dummy set this value to 0
 * @retval ADS1293_StatusTypeDef Init process status
 */
ADS1293_StatusTypeDef ads1293Init(uint8_t dummy)
{
    /* Init SPI peripheral */
    if (spiInit(0) != NUCLEO_SPI_OK)
    {
        return ADS1293_ERROR;
    }

    /* Set device CS to HIGH */
    setNSS(GPIO_PIN_SET);

    return ADS1293_OK;
}

/**
 * @brief  Read register from *ptxData address
 * @param  ptxData pointer to the uint8_t buffer to be sent with the register address
 * @param  prxData pointer to the uint8_t buffer to store the register value
 * @param  size size amount of data to be sent
 * @retval ADS1293_StatusTypeDef process status
 */
ADS1293_StatusTypeDef ads1293ReadRegister(uint8_t *ptxData, uint8_t *prxData,
                                          uint16_t size)
{
    /* Validate *ptxData, *prxData and size parameters */
    if (ptxData == NULL || prxData == NULL || size <= 0)
    {
        return ADS1293_ERROR;
    }

    /* ADS1293 sensor uses 7bit register addresses. MSB in ptxData indicates if the register is being
     * read or write. Set MSB to 1 will read the register value */
    uint8_t readAddress = *ptxData | RREG;

    /* Set ADS1293 CS to LOW to start communication */
    setNSS(GPIO_PIN_RESET);

    /* Send register address with the read command over SPI protocol */
    if (spiSendData(&readAddress, REG_ID_SIZE) != NUCLEO_SPI_OK)
    {
        return ADS1293_ERROR;
    }

    /* Read register and load value into *prxData */
    if (spiReceiveData(prxData, REG_ID_SIZE) != NUCLEO_SPI_OK)
    {
        return ADS1293_ERROR;
    }

    /* Set ADS1293 CS to HIGH to finish communication */
    setNSS(GPIO_PIN_SET);

    return ADS1293_OK;
}

/**
 * @brief  Read register from *ptxData address
 * @param  ptxData pointer to the uint8_t buffer to be sent with the register address
 * @param  prxData pointer to the uint8_t buffer to store the register value
 * @param  size size amount of data to be sent
 * @retval ADS1293_StatusTypeDef process status
 */
ADS1293_StatusTypeDef ads1293WriteRegister(uint8_t wrAddress, uint8_t data,
                                           uint16_t size)
{
    uint8_t dataToSend = data;

    /* ADS1293 sensor uses 7bit register addresses. MSB in ptxData indicates if the register is being
     * read or write. Set MSB to 1 will read the register value */
    uint8_t writeAddress = wrAddress & WREG;

    /* Set ADS1293 CS to LOW to start communication */
    setNSS(GPIO_PIN_RESET);

    /* Send register address with the read command over SPI protocol */
    if (spiSendData(&writeAddress, size) != NUCLEO_SPI_OK)
    {
        return ADS1293_ERROR;
    }

    /* Send register address with the read command over SPI protocol */
    if (spiSendData(&dataToSend, size) != NUCLEO_SPI_OK)
    {
        return ADS1293_ERROR;
    }

    /* Set ADS1293 CS to HIGH to finish communication */
    setNSS(GPIO_PIN_SET);

    return ADS1293_OK;
}

/**
 * @brief  Read ADS1293 ID register
 * @param  pidData pointer to the uint8_t buffer
 * @retval ADS1293_StatusTypeDef process status
 */
ADS1293_StatusTypeDef ads1293ReadID(uint8_t *pidData) {

	uint8_t ptxData = REVID | RREG;

	/* Validate *pidData */
	if (pidData == NULL) {
		return ADS1293_ERROR;
	}

	/* Read register and get sensor ID into pidData */
	if (ads1293ReadRegister(&ptxData, pidData, REG_ID_SIZE) != ADS1293_OK) {
		return ADS1293_ERROR;
	}

	return ADS1293_OK;

}