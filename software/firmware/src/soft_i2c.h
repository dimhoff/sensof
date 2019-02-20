#ifndef __SOFT_I2C_H__
#define __SOFT_I2C_H__

#define I2C_ACK		(0x01)
#define I2C_LASTRD	(0x02)
#define I2C_STOP	(0x04)
#define I2C_START	(0x08)
#define I2C_ARB		(0x10)
#define I2C_TIMEOUT	(0x20)
#define I2C_STARTED	(0x80)

#define I2C_BERR	(0x30) // mask for all types of errors

extern unsigned char i2c_flags;

void i2c_init();
void i2c_stop();
void i2c_write_byte(unsigned char b);
unsigned char i2c_read_byte();

#endif // __SOFT_I2C_H__
