#include "SPI.h"
#include "main.h"  // For CS pin definitions
#include "stdio.h"



uint8_t data_out_buffer[word_lenght] = {0};
uint16_t data_out = 0;
volatile uint8_t flag_read_done = 1;

int __io_putchar(int ch)
{
    HAL_UART_Transmit(&huart2, (uint8_t *)&ch, 1, HAL_MAX_DELAY);
    return ch;
}

void disable_slave(){

	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);
}

void enable_slave(){

	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);

}

HAL_StatusTypeDef  spi_write(uint8_t* message){
/*
	uint8_t value_msb = (value >> 8) & 0xFF;
	uint8_t value_lsb = value & 0xFF;

	uint8_t data[3] = {adress, value_msb,value_lsb};

	enable_slave();
*/


	HAL_StatusTypeDef status = HAL_SPI_Transmit_IT(&hspi1, message, LENGTH_WRITE);

	return status;
}


HAL_StatusTypeDef spi_read(uint8_t* command)
{
    // Transaction 1: send command, discard RX (it's the previous response)
    HAL_StatusTypeDef status = HAL_SPI_TransmitReceive_IT(&hspi1, command, data_out_buffer, LENGTH_READ);
    while(flag_read_done == 0);
    flag_read_done = 0;

    // Transaction 2: send NULL, receive actual command response
    uint8_t null_frame[LENGTH_READ] = {0};
    status = HAL_SPI_TransmitReceive_IT(&hspi1, null_frame, data_out_buffer, LENGTH_READ);
    while(flag_read_done == 0);
    flag_read_done = 0;

    return status;
}




void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *hspi)
{
    if(hspi->Instance == SPI1)
    {
    	disable_slave();
    }
}

// SPI callback for TX/RX complete
void HAL_SPI_TxRxCpltCallback(SPI_HandleTypeDef *hspi)
{
    if (hspi->Instance == hspi1.Instance)
    {


        // Set flag
        flag_read_done = 1;
    }
}

