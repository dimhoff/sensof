#include "htu21.h"
#include "soft_i2c.h"
#include "crc.h"
#include "timing_si4010.h"

#define HTU21_MEASURE_TEMP         0xE3 // Trigger Temperature Measurement (Hold master)
#define HTU21_MEASURE_HUM          0xE5 // Trigger Humidity Measurement (Hold master)
#define HTU21_MEASURE_TEMP_NO_HOLD 0xF3 // Trigger Temperature Measurement (No Hold master)
#define HTU21_MEASURE_HUM_NO_HOLD  0xF5 // Trigger Humidity Measurement (No Hold master)
#define HTU21_WRITE_REG            0xE6 // Write user register
#define HTU21_READ_REG             0xE7 // Read user register 
#define HTU21_SOFT_RESET           0xFE // Soft Reset

#define HTU21_MAX_RETRIES          5

static uint8_t _htu21_measure(bool temperature, uint16_t *val)
{
	unsigned char b;
	uint8_t crc;

	crc = 0;

	i2c_flags |= I2C_START;

	i2c_write_byte(0x80);
	if (! (i2c_flags & I2C_ACK)) goto fatal;
	if (i2c_flags & I2C_BERR) goto fatal;

	if (temperature) {
		i2c_write_byte(HTU21_MEASURE_TEMP);
	} else {
		i2c_write_byte(HTU21_MEASURE_HUM);
	}
	if (! (i2c_flags & I2C_ACK)) goto fatal;
	if (i2c_flags & I2C_BERR) goto fatal;

	i2c_flags |= I2C_START;

	i2c_write_byte(0x81);
	if (! (i2c_flags & I2C_ACK)) goto fatal;
	if (i2c_flags & I2C_BERR) goto fatal;

	// Data (MSB)
	b = i2c_read_byte();
	if (i2c_flags & I2C_BERR) goto fatal;
	crc = crc8(crc, b);
	((uint8_t *) val)[0] = b; // same as: *val = b << 8; but much less instructions

	// Data (LSB) | Status
	b = i2c_read_byte();
	if (i2c_flags & I2C_BERR) goto fatal;
	crc = crc8(crc, b);
	((uint8_t *) val)[1] = b; // same as: *val = *val | b; but much less instructions

	// CRC-8
	i2c_flags |= I2C_LASTRD;
	b = i2c_read_byte();
	if (i2c_flags & I2C_BERR) goto fatal;

	i2c_stop();

	return (b != crc);

fatal:
	i2c_stop();
	return 1;
}

void htu21_init()
{
	i2c_init();
}

bool htu21_read(uint16_t *temp, uint16_t *hum)
{
	uint8_t i;
	uint8_t res;

	//
	// soft reset
	//
	i2c_flags |= I2C_START;

	i2c_write_byte(0x80);
	if (! (i2c_flags & I2C_ACK)) goto fatal;
	if (i2c_flags & I2C_BERR) goto fatal;

	i2c_write_byte(HTU21_SOFT_RESET);
	if (! (i2c_flags & I2C_ACK)) goto fatal;
	if (i2c_flags & I2C_BERR) goto fatal;

	i2c_stop();

	wait_10us(250);
	wait_10us(250);
	wait_10us(250);
	wait_10us(250);
	wait_10us(250);
	wait_10us(250);

/*This was only for testing?
	//
	// Read status/config register
	//
	i2c_flags |= I2C_START;

	i2c_write_byte(0x80);
	if (! (i2c_flags & I2C_ACK)) goto fatal;
	if (i2c_flags & I2C_BERR) goto fatal;

	i2c_write_byte(HTU21_READ_REG);
	if (! (i2c_flags & I2C_ACK)) goto fatal;
	if (i2c_flags & I2C_BERR) goto fatal;

	i2c_flags |= I2C_START;

	i2c_write_byte(0x81);
	if (! (i2c_flags & I2C_ACK)) goto fatal;
	if (i2c_flags & I2C_BERR) goto fatal;

	i2c_flags |= I2C_LASTRD;
	b = i2c_read_byte();
	if (i2c_flags & I2C_BERR) goto fatal;

	i2c_stop();
*/

	//
	// Measure Temperature
	//
	i = 0;
	do {
		res = _htu21_measure(true, temp);
	} while (res != 0 && i++ < HTU21_MAX_RETRIES);

	if (res != 0) {
		return 1;
	}

	//
	// Measure Humidity
	//
	i = 0;
	do {
		res = _htu21_measure(false, hum);
	} while (res != 0 && i++ < HTU21_MAX_RETRIES);
	
	if (res != 0) {
		return 1;
	}

	return 0;

fatal:
	i2c_stop();
	return 1;
}