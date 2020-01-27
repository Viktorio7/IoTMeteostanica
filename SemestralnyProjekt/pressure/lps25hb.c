#include "lps25hb.h"

uint8_t addresP = LPS25HB_DEVICE_ADDRESS_0;		//adresa zariadenia, senzorovej dosky


uint8_t lps25hb_read_byte(uint8_t reg_addr)
{
	uint8_t data = 0;
	return *(i2c_master_read(&data, 1, reg_addr, addresP, 0));
}



void lps25hb_write_byte(uint8_t reg_addr, uint8_t value)
{
	i2c_master_write(value, reg_addr, addresP, 0);
}



void lps25hb_readArray(uint8_t * data, uint8_t reg, uint8_t length)
{
	i2c_master_read(data, length, reg, addresP, 1);
}



int8_t lps25hb_get_temp()
{
	uint8_t temp[2];
	lps25hb_readArray(temp, LPS25HB_ADDRESS_TEMP_L, 2);

	return (((int16_t)((temp[1] << 8) | temp[0])) >> 3)  + 25;
}



//funkcia na vypocet realneho zrychlenia z dat
void lps25hb_get_press(float* p)
{
	uint8_t data[3];
	uint32_t pp;

	lps25hb_readArray(data, LPS25HB_ADDRESS_PRESS_XL, 3);
	pp = ((uint32_t)data[2]) << 16 | ((uint16_t)data[1]) << 8 | data[0];
	*p = pp/4096.0f;
}



uint8_t lps25hb_init(void)
{

	uint8_t status = 1;

	LL_mDelay(100);

	uint8_t val = lps25hb_read_byte(LPS25HB_WHO_AM_I_ADDRES);

	if(val == LPS25HB_WHO_AM_I_VALUE)
	{
		status = 1;
	}
	else			//if the device is not found on one address, try another one
	{
		addresP= LPS25HB_DEVICE_ADDRESS_1;
		val = lps25hb_read_byte(LPS25HB_WHO_AM_I_ADDRES);
		if(val == LPS25HB_WHO_AM_I_VALUE)
		{
			status = 1;
		}
		else
		{
			status = 0;
			//return status;
		}
	}

	//press device init
	uint8_t ctrl1 = 8 << 4; // +-2g res
	lps25hb_write_byte(LPS25HB_ADDRESS_CTRL1, ctrl1);
	lps25hb_write_byte(LPS25HB_ADDRESS_CTRL2, 1);
	return status;
}
