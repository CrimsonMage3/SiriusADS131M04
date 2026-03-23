#include "ADS131M04.h"
#include "SPI.h"



typedef union {
	uint16_t COMMAND;
	struct{
		uint8_t REGISTER_NUMBER : 7;
		uint8_t ADDRESS : 6;
		uint8_t CMD : 3;
	}field;
	struct{
			uint8_t LSB;
			uint8_t MSB;
	}bytes;
}RW_REG;



void ADS131M04_write(uint8_t address, uint16_t value){

	RW_REG WREG;


	WREG.field.REGISTER_NUMBER = 0;
	WREG.field.ADDRESS = address;
	WREG.field.CMD = WREG_CMD;

	uint8_t valueMSB = (value & MSB_uint16_mask) >> 8;
	uint8_t valueLSB = (value & LSB_uint16_mask);

	uint8_t message[4] = {WREG.bytes.MSB, WREG.bytes.LSB, valueMSB, valueLSB};

	spi_write(message);

}

void ADS131M04_read(uint8_t address){

	RW_REG RREG;


	RREG.field.REGISTER_NUMBER = 0;
	RREG.field.ADDRESS = address;
	RREG.field.CMD = WREG_CMD;


	uint8_t message[2] = {RREG.bytes.MSB, RREG.bytes.LSB};

	spi_read(message);

}





