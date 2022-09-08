#include <unity.h>
#include "ads1293.h"
#include "mock_NUCLEO_F429ZI_port.h"

// Tests
// SPI es inicializado correctamente
// Se escribe un registro de manera individual
// Se lee un registro de manera individual
// La lectura de ID register debe regresar el ID del sensor

static ADS1293_StatusTypeDef status;

// Register example with address and value from datasheet
static const struct
{
	uint8_t address;
	uint8_t value;
} reg_data[] = {
	{.address = LOD_CN,
	 .value = 0x08},
	{.address = REVID,
	 .value = 0x01}};

// Executed before starting tests
void setUp(void)
{
	/* Prevent spiInit and setNss failures */
	spiInit_IgnoreAndReturn(NUCLEO_SPI_OK);
	setNSS_Ignore();

	/* Init ADS1293 Comm */
	status = ads1293Init(0);
}

// Test Init SPI
void test_init_spi(void)
{
	/* Check init state */
	TEST_ASSERT_EQUAL(ADS1293_OK, status);
}

// Test Write Register
void test_write_register(void)
{
	uint8_t expectedData[] = {0x01, 0x11, 0x81};

	/* Choose register address */
	uint8_t regAddress = FLEX_CH1_CN;
	/* Define data to send */
	uint8_t data = 0x11;

	/* Define returns from spi functions */s
	spiSendData_ExpectWithArrayAndReturn(&expectedData[0], 1, REG_ID_SIZE, NUCLEO_SPI_OK);
	spiSendData_ExpectWithArrayAndReturn(&expectedData[1], 1, REG_ID_SIZE, NUCLEO_SPI_OK);

	/* Write register */
	ads1293WriteRegister(regAddress, data, REG_ID_SIZE);

	/* Define data buffer */
	uint8_t dataBuffer;

	/* Define returns from spi functions */
	spiSendData_ExpectWithArrayAndReturn(&expectedData[2], 1, REG_ID_SIZE, NUCLEO_SPI_OK);
	spiReceiveData_ExpectAndReturn(NULL, REG_ID_SIZE, NUCLEO_SPI_OK);
	spiReceiveData_IgnoreArg_prxData();
	spiReceiveData_ReturnArrayThruPtr_prxData(&expectedData[1], REG_ID_SIZE);

	/* Read register */
	ads1293ReadRegister(&regAddress, &dataBuffer, REG_ID_SIZE);

	/* data and dataBuffer should match */
	TEST_ASSERT_EQUAL(dataBuffer, data);
}

// Test Read Register
void test_read_register(void)
{
	// expectedData[0] = LOD_CN & WREG
	// expectedData[1] = reg_data[0].value
	uint8_t expectedData[] = {0x86, 0x08};

	/* Choose register address */
	uint8_t regAddress = LOD_CN;
	/* Define data buffer */
	uint8_t dataBuffer;

	/* Define returns from spi functions */
	spiSendData_ExpectWithArrayAndReturn(&expectedData[0], 1, REG_ID_SIZE, NUCLEO_SPI_OK);
	spiReceiveData_ExpectAndReturn(NULL, REG_ID_SIZE, NUCLEO_SPI_OK);
	spiReceiveData_IgnoreArg_prxData();
	spiReceiveData_ReturnArrayThruPtr_prxData(&expectedData[1], REG_ID_SIZE);

	/* Read register */
	ads1293ReadRegister(&regAddress, &dataBuffer, REG_ID_SIZE);

	/* dataBuffer should match expected value from datasheet */
	TEST_ASSERT_EQUAL(dataBuffer, reg_data[0].value);
}

// Test Read ID
void test_read_id(void)
{
	// expectedData[0] = RVID & WREG
	// expectedData[1] = reg_data[1].value
	uint8_t expectedData[] = {0xC0, 0x01};

	/* Define data buffer */
	uint8_t dataBuffer;

	/* Define returns from spi functions */
	spiSendData_ExpectWithArrayAndReturn(&expectedData[0], 1, REG_ID_SIZE, NUCLEO_SPI_OK);
	spiReceiveData_ExpectAndReturn(NULL, REG_ID_SIZE, NUCLEO_SPI_OK);
	spiReceiveData_IgnoreArg_prxData();
	spiReceiveData_ReturnArrayThruPtr_prxData(&expectedData[1], REG_ID_SIZE);

	/* Read register */
	ads1293ReadID(&dataBuffer);

	/* dataBuffer should match sensor id */
	TEST_ASSERT_EQUAL(dataBuffer, reg_data[1].value);
}