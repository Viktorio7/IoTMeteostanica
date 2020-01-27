//DataSheet pre dosku IKS01A1: https://pdf1.alldatasheet.com/datasheet-pdf/view/882381/STMICROELECTRONICS/HTS221.html

#include "main.h"
#include "i2c.h"


//adresa zariadenia, senzorovej dosky
#define 	LPS25HB_DEVICE_ADDRESS_0				0xB8
#define 	LPS25HB_DEVICE_ADDRESS_1				0xBA

//WHO_AM_I register, iba na citanie
#define 	LPS25HB_WHO_AM_I_VALUE					0xBD
#define 	LPS25HB_WHO_AM_I_ADDRES					0x0F

#define 	LPS25HB_ADDRESS_CTRL1					0x20
#define 	LPS25HB_ADDRESS_CTRL2					0x21

//adresy registrov low hodnot pre jenotlive osi
#define 	LPS25HB_ADDRESS_PRESS_XL				0x28
#define 	LPS25HB_ADDRESS_PRESS_L					0x29
#define 	LPS25HB_ADDRESS_PRESS_H					0x2A

#define 	LPS25HB_ADDRESS_TEMP_L					0x20

uint8_t lps25hb_init(void);
void lps25hb_get_press(float* p);
uint8_t lps25hb_read_byte(uint8_t reg_addr);
void lps25hb_write_byte(uint8_t reg_addr, uint8_t value);
int8_t lps25hb_get_temp();
