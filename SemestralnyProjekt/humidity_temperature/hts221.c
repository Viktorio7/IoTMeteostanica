#include "hts221.h"

uint8_t addresTH = HTS221_DEVICE_ADDRESS_0;		//adresa zariadenia, senzorovej dosky


uint8_t hts221_read_byte(uint8_t reg_addr)
{
	uint8_t data = 0;
	return *(i2c_master_read(&data, 1, reg_addr, addresTH, 0));
}


void hts221_write_byte(uint8_t reg_addr, uint8_t value)
{
	i2c_master_write(value, reg_addr, addresTH, 0);
}


void hts221_readArray(uint8_t * data, uint8_t reg, uint8_t length)
{
	i2c_master_read(data, length, reg, addresTH, 1);
}



//funkcia na vypocet realnej teploty z dat
void hts221_get_temp(float * t)
{

	int16_t temp;
	uint16_t T0, T1, T2, T3;
	uint8_t raw, val0, val1;

	// Read data back from 0x32(50), 1 byte
	T0 = hts221_read_byte(HTS221_ADDRESS_CONF_T0deg);

	// Read data back from 0x32(51), 1 byte
	T1 = hts221_read_byte(HTS221_ADDRESS_CONF_T1deg);

	// Read data back from 0x35(53), 1 byte
	raw = hts221_read_byte(HTS221_ADDRESS_CONF_T1T0msb);
	raw = (raw & 0x0F);

	// Convert the temperature Calibration values to 10-bits
	T0 = (int16_t)(raw & 0x03) << 8 | T0;
	T1 = (int16_t)(raw & 0x0C) << 6 | T1;

	// Read data back from 0x3C(60), 2 bytes
	val0 = hts221_read_byte(HTS221_ADDRESS_CONF_T0out);
	val1 = hts221_read_byte(HTS221_ADDRESS_CONF_T0out + 1);
	T2 = ((uint16_t)val1) << 8 | val0;

	// Read data back from 0x3E(62), 2 bytes
	val0 = hts221_read_byte(HTS221_ADDRESS_CONF_T1out);
	val1 = hts221_read_byte(HTS221_ADDRESS_CONF_T1out + 1);
	T3 = ((uint16_t)val1) << 8 | val0;

	// Read data back from 0x28(40) with 2 bytes
	val0 = hts221_read_byte(HTS221_ADDRESS_TEMP);
	val1 = hts221_read_byte(HTS221_ADDRESS_TEMP + 1);
	temp = ((uint16_t)val1) << 8 | val0;

	// Convert the data
	if(temp > 32767)
		{
			temp -= 35536;
		}

	*t = ((T1 - T0) / 8.0f) * (temp - T2) / (T3 - T2) + (T0 / 8.0f);
}



//funkcia na vypocet realnej vlhkosti z dat
void hts221_get_hum(float * h)
{

	uint8_t val, val0, val1, H0, H1;
	uint16_t H2, H3, hum;

	// Read data back from 0x30(48), 1 byte
	val = hts221_read_byte(HTS221_ADDRESS_CONF_H0r);
	H0 = val / 2;

	// Read data back from 0x31(49), 1 byte
	val = hts221_read_byte(HTS221_ADDRESS_CONF_H1r);
	H1 = val / 2;

	// Read data back from 0x36(54), 2 bytes
	val0 = hts221_read_byte(HTS221_ADDRESS_CONF_H0T0out);
	val1 = hts221_read_byte(HTS221_ADDRESS_CONF_H0T0out + 1);
	H2 = ((uint16_t)val1) << 8 | val0;

	// Read data back from 0x3A(58), 2 bytes
	val0 = hts221_read_byte(HTS221_ADDRESS_CONF_H1T0out);
	val1 = hts221_read_byte(HTS221_ADDRESS_CONF_H1T0out + 1);
	H3 = ((uint16_t)val1) << 8 | val0;

	// Read data back from 0x28(40) with 2 bytes
	val0 = hts221_read_byte(HTS221_ADDRESS_HUM);
	val1 = hts221_read_byte(HTS221_ADDRESS_HUM + 1);
	hum = ((uint16_t)val1) << 8 | val0;

	// Convert the data
	*h = ((1.0f * H1) - (1.0f * H0)) * (1.0f * hum - 1.0f * H2) / (1.0f * H3 - 1.0f * H2) + (1.0f * H0);
}



uint8_t hts221_init(void)
{

	uint8_t status = 1;

	LL_mDelay(100);

	uint8_t val = hts221_read_byte(HTS221_WHO_AM_I_ADDRES);

	if(val == HTS221_WHO_AM_I_VALUE)
	{
		status = 1;
	}

	else
	{
		status = 0;
		//return status;
	}

	//temperature device init
	uint8_t ctrl1 = 8 << 4; // +-2g res
	hts221_write_byte(HTS221_ADDRESS_CTRL1, ctrl1);
	hts221_write_byte(HTS221_ADDRESS_CTRL2, 1);

	return status;
}
