//DataSheet pre dosku IKS01A1: https://pdf1.alldatasheet.com/datasheet-pdf/view/882381/STMICROELECTRONICS/HTS221.html

#include "main.h"
#include "i2c.h"


//adresa zariadenia, senzorovej dosky
#define 	HTS221_DEVICE_ADDRESS_0					0xBE

//WHO_AM_I register, iba na citanie
#define 	HTS221_WHO_AM_I_VALUE					0xBC
#define 	HTS221_WHO_AM_I_ADDRES					0x0F


#define 	HTS221_ADDRESS_CTRL1					0x20
#define 	HTS221_ADDRESS_CTRL2					0x21

//adresy registrov hodnot
#define 	HTS221_ADDRESS_HUM						0x28
#define 	HTS221_ADDRESS_TEMP						0x2A

//adresy kalibracnych registrov
#define 	HTS221_ADDRESS_CONF_H0r					0x30
#define 	HTS221_ADDRESS_CONF_H1r					0x31
#define 	HTS221_ADDRESS_CONF_H0T0out				0x36
#define 	HTS221_ADDRESS_CONF_H1T0out				0x3A

#define 	HTS221_ADDRESS_CONF_T0out				0x3C
#define 	HTS221_ADDRESS_CONF_T0deg				0x32
#define 	HTS221_ADDRESS_CONF_T1out				0x3E
#define 	HTS221_ADDRESS_CONF_T1deg				0x33
#define 	HTS221_ADDRESS_CONF_T1T0msb				0x35


uint8_t hts221_init(void);
void hts221_get_hum(float * h);
void hts221_get_temp(float * t);
uint8_t hts221_read_byte(uint8_t reg_addr);
void hts221_write_byte(uint8_t reg_addr, uint8_t value);

