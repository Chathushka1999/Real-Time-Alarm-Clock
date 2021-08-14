#include "RTC_DS3232.h"

                                                     

void I2C_Init()                                                     //Initialize I2C Communication
{
	TWSR=0x00; //set presca1er bits to zero
	TWBR=0x46; //SCL frequency is 50K for 16Mhz
	TWCR=0x04; //enab1e TWI module
}
void I2C_Start()                                                    //Start I2C Communication
{
	TWCR = ((1<<TWINT) | (1<<TWSTA) | (1<<TWEN));
	while (!(TWCR & (1<<TWINT)));
}
void I2C_Stop(void)                                                 //Stop I2C Communication
{
	TWCR = ((1<< TWINT) | (1<<TWEN) | (1<<TWSTO));
	_delay_us(100) ; //wait for a short time
}
void I2C_Write(uint8_t v_i2cData_u8)                                //Write data to I2C data line
{
	TWDR = v_i2cData_u8 ;
	TWCR = ((1<< TWINT) | (1<<TWEN));
	while (!(TWCR & (1 <<TWINT)));
}
uint8_t I2C_Read(uint8_t v_ackOption_u8)                            //Read data from I2C data line
{
	TWCR = ((1<< TWINT) | (1<<TWEN) | (v_ackOption_u8<<TWEA));
	while ( !(TWCR & (1 <<TWINT)));
	return TWDR;
}

void RTC_Initialize(void){ //Initialize RTC
	DDRC = 0b01000000;  //Set C port for input
	PORTC=0b01000000;
	PORTC |= (1<<PORTC4) & (1<<PORTC5);                   //Setting internal pull ups
	I2C_Init();
	I2C_Start();
	I2C_Write(Ds3232WriteMode);
	I2C_Write(Ds3232ControlRegAddress);
	I2C_Write(0x00);
	I2C_Stop();
}
void RTC_Set_Time(rtc_t *rtc){  //Write Date time values to the memory
	I2C_Start();
	I2C_Write(Ds3232WriteMode);
	I2C_Write(Ds3232SecondRegAddress);
	I2C_Write(encode(rtc->sec));
	I2C_Write(encode(rtc->min));
	I2C_Write(encode(rtc->hour));
	I2C_Write(encode(rtc->weekDay));
	I2C_Write(encode(rtc->date));
	I2C_Write(encode(rtc->month));
	I2C_Write(encode(rtc->year));
	I2C_Stop();
}


void RTC_Get_Time(rtc_t *rtc){ //Get date time values from memory
	I2C_Start();
	I2C_Write(Ds3232WriteMode);
	I2C_Write(Ds3232SecondRegAddress);
	I2C_Stop();
	I2C_Start();
	I2C_Write(Ds3232ReadMode);
	rtc->sec=decode(I2C_Read(1));
	rtc->min =decode(I2C_Read(1));
	rtc->hour= decode(I2C_Read(1));
	rtc->weekDay = decode(I2C_Read(1));
	rtc->date= decode(I2C_Read(1));
	rtc->month=decode(I2C_Read(1));
	rtc->year =decode(I2C_Read(0));
	I2C_Stop();
}


uint8_t	decode(uint8_t value)
{
	uint8_t decoded = (value & 15) + 10 * ((value & (15 << 4)) >> 4);
	return decoded;
}


uint8_t encode(uint8_t value)
{
	uint8_t encoded = ((value / 10) << 4) + (value % 10);
	return encoded;
}




