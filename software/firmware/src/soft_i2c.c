#include "soft_i2c.h"

#include <si4010.h>

#ifdef HAVE_STDBOOL
 #include <stdbool.h>
#else
 #define bool bit
 #define true 1
 #define false 0
#endif
#include "timing_si4010.h"

#define SCL	GPIO1
#define SDA	GPIO2

unsigned char i2c_flags = 0;

void i2c_init()
{
	SCL = 1;
	SDA = 1;
	i2c_flags = 0;
}

static void i2c_delay()
{
	wait_10us(1);
}

static void i2c_start()
{
	unsigned int i;
	if (i2c_flags & I2C_STARTED) {
		SDA = 1;
		i2c_delay();
		SCL = 1;

		// clock stretching
		i = 0xFFFF;
		while (SCL == 0 && --i != 0) {
			i2c_delay();
		}
		if (i == 0) {
			i2c_flags |= I2C_TIMEOUT;
			return;
		}

		i2c_delay();
	}

	SDA = 0;
	SDA = 0; // dummy write to make sure next read returns correct value
	if (SDA != 0) {
		i2c_flags |= I2C_ARB;
		return;
	}
	i2c_delay();
	SCL = 0;

	i2c_flags &= (~I2C_START);
	i2c_flags |= I2C_STARTED;
}

void i2c_stop()
{
	SCL = 1;
	i2c_delay();
	SDA = 1;

	i2c_flags &= (~(I2C_STOP | I2C_STARTED));
}

static void i2c_write_bit(bool v)
{
	unsigned int i;

	SDA = v;
	i2c_delay();
	SCL = 1;

	// clock stretching
	i = 0xFFFF;
	while (SCL == 0 && --i != 0) i2c_delay();
	if (i == 0) {
		i2c_flags |= I2C_TIMEOUT;
		return;
	}

	// arbitration lost
	if (SDA != v) {
		i2c_flags |= I2C_ARB;
		return;
	}

	i2c_delay();
	SCL = 0;
}

static bool i2c_read_bit()
{
	unsigned int i;
	bool retval;

	SDA = 1;
	i2c_delay();
	SCL = 1;

	// clock stretching
	i = 0xFFFF;
	while (SCL == 0 && --i != 0) i2c_delay();
	if (i == 0) {
		i2c_flags |= I2C_TIMEOUT;
		return 1;
	}

	retval = SDA;

	i2c_delay();
	SCL = 0;

	return retval;
}

void i2c_write_byte(unsigned char b)
{
	unsigned char i;

	if (i2c_flags & I2C_START) {
		i2c_start();
		if (i2c_flags & I2C_BERR) {
			return;
		}
	}

	i=8;
	while (i--) {
		i2c_write_bit((b & 0x80) != 0);
		if (i2c_flags & I2C_BERR) {
			return;
		}
		b <<= 1;
	}

	if (i2c_read_bit()) {
		i2c_flags &= (~I2C_ACK);
	} else {
		i2c_flags |= I2C_ACK;
	}
	if (i2c_flags & I2C_BERR) {
		return;
	}

	if (i2c_flags & I2C_STOP) {
		i2c_stop();
	}
}

unsigned char i2c_read_byte()
{
	unsigned char i;
	unsigned char b = 0;

	i=8;
	while (i--) {
		b <<= 1;
		b |= i2c_read_bit() ? 1 : 0;
		if (i2c_flags & I2C_BERR) {
			return 0;
		}
	}

	i2c_write_bit((i2c_flags & I2C_LASTRD) != 0);
	i2c_flags &= (~I2C_LASTRD);
	if (i2c_flags & I2C_BERR) {
		return 0;
	}

	if (i2c_flags & I2C_STOP) {
		i2c_stop();
	}

	return b;
}
