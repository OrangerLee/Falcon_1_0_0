#ifndef __FUCNTION_H
#define __FUCNTION_H

#include "stm32f4xx_hal.h"
#include "stdio.h"
#include "rtc.h"
#include "i2c.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

#include "JY901.h"
#include "QY1503.h"



extern float roll,pitch,yaw;
extern uint16_t CH1,CH2,CH3,CH4,CH5,CH6,CH7,CH8;
extern float Target_Angle;

void Hardware_Init(void);
void Get_Time(void);
void JY901_Test(void);
void remote_test(void);
void QY1503_test(void);
void Hardware_Test(void);

void Set_Motor(uint16_t pwm);
void Set_Steer_L(uint16_t pwm);
void Set_Steer_R(uint16_t pwm);


void Set_Angle(float target_angle,float Kp,float Ki,float Kd);
void Steer_Control(void);
void BLDC_Control(uint16_t pwm_in);
void Compute_Target_Angle(uint16_t pwm_in);

void Int_Send_to_SerialPort(uint16_t data);
void Float_Send_to_SerialPort(float data);
void Float_to_Char(float data,uint8_t *pData);
void Int_to_Char(uint16_t data,uint8_t *pData);

#endif 

