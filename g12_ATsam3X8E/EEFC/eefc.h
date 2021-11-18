#ifndef EEFC_H
#define EEFC_H

#include <stdint.h>

void eefc_init(void);

void eefc_read_single_page(uint16_t page_number);

#endif //EEFC_H
