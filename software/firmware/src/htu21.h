#ifndef __HTU21_H__
#define __HTU21_H__

#include <stdint.h>
#include <stdbool.h>

void htu21_init();

bool htu21_read(uint16_t *temp, uint16_t *hum);

#endif // __HTU21_H__