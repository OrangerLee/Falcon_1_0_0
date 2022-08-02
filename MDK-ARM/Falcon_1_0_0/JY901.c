#include "JY901.h"


uint8_t chrtemp[10];
float roll,pitch,yaw;
int temp;

short CharToShort(unsigned char cData[])
{
	return ((short)cData[1]<<8)|cData[0];//left shift 8 bit
}

void read_att_angle(void)
{
	HAL_StatusTypeDef iic_status;
	iic_status = HAL_I2C_Mem_Read(&hi2c1,(0x50)<<1,ROLL,I2C_MEMADD_SIZE_8BIT,&(chrtemp[0]),6,100);
	roll = 	(float)CharToShort(&chrtemp[0])/32768*180;//¡À180	-180 0 +180
	pitch =	(float)CharToShort(&chrtemp[2])/32768*180;//-90 0 90
	yaw = 	(float)CharToShort(&chrtemp[4])/32768*180;

}





