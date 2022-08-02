#ifndef __QY1503_H
#define __QY1503_H
#include "stm32f4xx_hal.h"
#include "spi.h"
#include <stdint.h>
#include <stdbool.h>
#define QY1503_HYSTLSB (0x01<<5)
#define QY1503_ABS(x) ((x)>0?(x):(-(x)))

typedef struct
{
	union
	{
			uint8_t buf[2];
			uint16_t val;
	} angle;       
	uint8_t status; 
	uint8_t crc;    

} qy1503_raw_data_t;

unsigned char PUDI_CRC8(unsigned char *message, unsigned char Bytelength, const unsigned char *TableCRC);
uint8_t QY1503_CRC8(uint8_t *data, uint8_t length);
void QY1503_SPI_EndTransaction(void);
void QY1503_SPI_BeginTransaction(void);
bool QY1503_ReadRawData(qy1503_raw_data_t *raw_data);
float QY1503_ReadAngle(void);
#endif 

