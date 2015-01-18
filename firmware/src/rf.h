#ifndef __RF_H__
#define __RF_H__


#include <stdint.h>

void rf_setup();
void ezradiopro_send_frame(uint8_t *payload, uint8_t len);

#endif // __RF_H__