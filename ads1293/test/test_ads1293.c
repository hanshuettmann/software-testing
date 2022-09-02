#include <unity.h>
#include "ads1293.h"

// Requisitos driver ADS1293

// El sensor debe comunicarse a traves de protocolo SPI
// Se podra escribir el valor de un registro de manera individual
// Se podra leer el valor actual de un registro de manera individual
// Se podra obtener el ID del sensor
// Se podra configurar el Sensor para iniciar modo Data Loop
// Se podra leer el valor del registro Data loop

// Tests
// Se inicializa el puerto SPI dejando el CS en estado alto
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
	/* Choose register address */
	uint8_t regAddress = FLEX_CH1_CN;
	/* Define data to send */
	uint8_t data = 0x11;
	/* Write register */
	ads1293WriteRegister(regAddress, data, REG_ID_SIZE);

	/* Define data buffer */
	uint8_t dataBuffer;
	/* Read register */
	ads1293ReadRegister(&regAddress, &dataBuffer, REG_ID_SIZE);

	/* data and dataBuffer should match */
	TEST_ASSERT_EQUAL(dataBuffer, data);
}

// Test Read Register
void test_read_register(void)
{
	/* Choose register address */
	uint8_t regAddress = LOD_CN;
	/* Define data buffer */
	uint8_t dataBuffer;
	/* Read register */
	ads1293ReadRegister(&regAddress, &dataBuffer, REG_ID_SIZE);

	/* data and dataBuffer should match */
	TEST_ASSERT_EQUAL(dataBuffer, reg_data[0].value);
}

// Test Read ID
void test_read_id(void)
{
	/* Define data buffer */
	uint8_t dataBuffer;
	/* Read register */
	ads1293ReadID(&dataBuffer);

	/* dataBuffer should match sensor id */
	TEST_ASSERT_EQUAL(dataBuffer, reg_data[1].value);
}