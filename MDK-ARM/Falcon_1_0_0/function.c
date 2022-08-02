#include "function.h"

int fputc(int ch,FILE *f)
{
	uint8_t temp[1] ={ch};
	HAL_UART_Transmit(&huart1,temp,1,2);
	return ch;
}
/*******************************************************************************/
void Set_Motor(uint16_t pwm)
{
	__HAL_TIM_SET_COMPARE(&htim3,Motor_Channel,pwm);
}
/*******************************************************************************/
/*******************************************************************************/
void Set_Steer_L(uint16_t pwm)
{
	__HAL_TIM_SET_COMPARE(&htim3,STEER_L_Channel,pwm);
}	
/*******************************************************************************/
/*******************************************************************************/
void Set_Steer_R(uint16_t pwm)
{
	__HAL_TIM_SET_COMPARE(&htim3,STEER_R_Channel,pwm);
}
/*******************************************************************************/
/*******************************************************************************/
void Hardware_Init(void)
{
	HAL_TIM_IC_Start_IT(&htim4,TIM_CHANNEL_1);	//CH1
	HAL_TIM_IC_Start_IT(&htim4,TIM_CHANNEL_2);	//CH2
	HAL_TIM_IC_Start_IT(&htim4,TIM_CHANNEL_3);	//CH3
	HAL_TIM_IC_Start_IT(&htim4,TIM_CHANNEL_4);	//CH4
	HAL_TIM_IC_Start_IT(&htim1,TIM_CHANNEL_1);	//CH5
	HAL_TIM_IC_Start_IT(&htim1,TIM_CHANNEL_2);	//CH6
	HAL_TIM_IC_Start_IT(&htim1,TIM_CHANNEL_3);	//CH7
	HAL_TIM_IC_Start_IT(&htim1,TIM_CHANNEL_4);	//CH8

  __HAL_TIM_ENABLE_IT(&htim1,TIM_IT_UPDATE);	
	__HAL_TIM_ENABLE_IT(&htim4,TIM_IT_UPDATE);	
	HAL_TIM_Base_Start_IT(&htim2);
	HAL_TIM_PWM_Start(&htim3,STEER_L_Channel);	//STEER_L
	HAL_TIM_PWM_Start(&htim3,STEER_R_Channel);	//STEER_R
	HAL_TIM_PWM_Start(&htim3,Motor_Channel);		//Motor
	__HAL_TIM_SET_COMPARE(&htim3,Motor_Channel,150);
	HAL_Delay(3000);
	
}
/*******************************************************************************/
/*******************************************************************************/
void Get_Time(void)
{
	RTC_TimeTypeDef GET_Time;
	RTC_DateTypeDef GET_Date;
	HAL_RTC_GetTime(&hrtc,&GET_Time,RTC_FORMAT_BIN);
	HAL_RTC_GetDate(&hrtc,&GET_Date,RTC_FORMAT_BIN);
	printf("%02d.%02d.%02d\t",2000+GET_Date.Year,GET_Date.Month,GET_Date.Date);
	printf("%02d:%02d:%02d\r\n",GET_Time.Hours,GET_Time.Minutes,GET_Time.Seconds);	
}

/*******************************************************************************/
/*******************************************************************************/

void JY901_Test(void)
{
	read_att_angle();
	printf("roll = %.2f\t",roll);
	printf("pitch = %.2f\t",pitch);
	printf("yaw = %.2f\t\r\n",yaw);
}

/*******************************************************************************/
/*******************************************************************************/

void remote_test(void)
{
		
		printf("CH1:%d\t",CH1);
		printf("CH2:%d\t",CH2);
		printf("CH3:%d\t",CH3);
		printf("CH4:%d\t",CH4);
		printf("CH5:%d\t",CH5);
		printf("CH6:%d\t",CH6);
		printf("CH7:%d\t",CH7);
		printf("CH8:%d\t",CH8);
		printf("\r\n");
}

/*******************************************************************************/
/*******************************************************************************/
float qy1503_angle;
void QY1503_test(void)
{
		qy1503_angle = QY1503_ReadAngle();
		printf("%.2f\r\n",qy1503_angle);
}
/*******************************************************************************/
/*******************************************************************************/
void Hardware_Test(void)
{
	printf("-----Hardware Test Start-----\r\n");
	Get_Time();
	HAL_Delay(1000);
	printf("Motor Testing...\r\n");
	__HAL_TIM_SET_COMPARE(&htim3,Motor_Channel,155);
	HAL_Delay(2000);
	__HAL_TIM_SET_COMPARE(&htim3,Motor_Channel,145);
	HAL_Delay(2000);
	__HAL_TIM_SET_COMPARE(&htim3,Motor_Channel,150);
	printf("Steer Testing...\r\n");
	__HAL_TIM_SET_COMPARE(&htim3,STEER_L_Channel,100);
	__HAL_TIM_SET_COMPARE(&htim3,STEER_R_Channel,100);
	HAL_Delay(500);
	__HAL_TIM_SET_COMPARE(&htim3,STEER_L_Channel,200);
	__HAL_TIM_SET_COMPARE(&htim3,STEER_R_Channel,200);
	HAL_Delay(500);
	__HAL_TIM_SET_COMPARE(&htim3,STEER_L_Channel,150);
	__HAL_TIM_SET_COMPARE(&htim3,STEER_R_Channel,150);
	
	printf("QY1503_test:\t");
	QY1503_test();
	printf("JY901_test:\t");
	JY901_Test();
	printf("remote_test:\t");
	remote_test();
	printf("-----Hardware Test End-------\r\n");
}

/*******************************************************************************/
/*******************************************************************************/

void Set_Angle(float target_angle,float Kp,float Ki,float Kd)
{

	float 	add_pwm;
	float 	err_now=0.0f,err_last=0.0f,err_prev=0.0f;
	uint16_t			final_pwm,pwm_protect=40;
	uint8_t 			pwm_limit_add=0;		//155
	uint8_t 			pwm_limit_sub=0;
	
		qy1503_angle=QY1503_ReadAngle();
		if((0<=target_angle)&&(target_angle<40))
			if((320<qy1503_angle)&&(qy1503_angle<360))
					qy1503_angle-=360;
		if((320<target_angle)&&(target_angle<360))
			if((0<qy1503_angle)&&(qy1503_angle<40))
					qy1503_angle+=360;										//(0,360)->(-40,400)
			
		err_now = qy1503_angle-target_angle;

		add_pwm = (Kp*(err_now-err_last)+Ki*err_now+Kd*(err_now-2*err_last+err_prev));
		err_prev = 	err_last;
		err_last = err_now;
			
		if(add_pwm>0)
			add_pwm+=pwm_limit_add;
		if(add_pwm<0)
			add_pwm-=pwm_limit_add;
			
		final_pwm = 150+add_pwm;
		if(final_pwm>150+pwm_protect)
			final_pwm = 150+pwm_protect;
		if(final_pwm<150-pwm_protect)
			final_pwm = 150-pwm_protect;
			
		
		Set_Motor(final_pwm);
}

/*******************************************************************************/
/*******************************************************************************/

void Steer_Control(void)
{
	int16_t  servo_turn;
	int16_t  servo_up_down;
	int16_t  servoL;
	int16_t  servoR;
	
	servo_up_down=-0.06*CH2+240;	//(2000,	1500,		1000)			---->	(120,		150,	180)
																//“°∏Àœ¬£¨				“°∏À…œ		---->	◊ÛŒ≤“Ì…œ£¨		◊ÛŒ≤“Ìœ¬	
	
	servo_turn=CH4*0.04-60;				//(1000,	1500,		2000)			---->	(-20,		0,		20)
																//“°∏À◊Û£¨				“°∏À”“		---->	◊ÛŒ≤“Ì…œ£¨		◊ÛŒ≤“Ìœ¬

//(2000,	1500,		1000)			---->	(120,		150,	180)
//“°∏Àœ¬£¨				“°∏À…œ		---->	”“Œ≤“Ìœ¬			”“Œ≤“Ì…œ	
	
//(1000,	1500,		2000)			---->	(-20,		0,		20)
//“°∏À◊Û£¨				“°∏À”“		---->	”“Œ≤“Ìœ¬£¨		”“Œ≤“Ì…œ

//servoL∫ÕservoRœ‡µ» ±£¨Œ≤“Ì”–≤Ó∑÷£¨
//servoL∫ÕservoRª•≤π ±£¨Œ≤“ÌÕ¨œÚ∞⁄∂Ø
	servoL=servo_up_down+servo_turn;
	servoR=(300-servo_up_down)+servo_turn;
	if(servoL<100)
		servoL=100;
	if(servoL>200)
		servoL=200;
	if(servoR<100)
		servoR=100;
	if(servoR>200)
		servoR=200;	
	
	Set_Steer_L(servoL);
	Set_Steer_R(servoR);

}

/*******************************************************************************/
/*******************************************************************************/

void BLDC_Control(uint16_t pwm_in)
{
	uint16_t pwm;
	pwm = (int)(-0.05*pwm_in)+200;
	if	(pwm>=150)
		pwm = 150;
	if	(pwm<=100)
		pwm = 100;
	printf("pwm = %d\r\n",pwm);
	Set_Motor(pwm);

}

/*******************************************************************************/
/*******************************************************************************/

void Compute_Target_Angle(uint16_t pwm_in)
{
	float k = 0.179;
	float b = -364.482;
	Target_Angle = k*CH6+b;
		if(Target_Angle>360)
			Target_Angle = 360;
		if(Target_Angle<0)
			Target_Angle = 0;
}
/*******************************************************************************/
/*******************************************************************************/
void Int_Send_to_SerialPort(uint16_t data)
{
		uint8_t buffer[20];
		Int_to_Char(data,buffer);
		HAL_UART_Transmit(&huart1,buffer,sizeof(buffer),0xffff);
}
/*******************************************************************************/
void Float_Send_to_SerialPort(float data)
{
		uint8_t buffer[20];
		Float_to_Char(data,buffer);
		HAL_UART_Transmit(&huart1,buffer,sizeof(buffer),0xffff);
}
/*******************************************************************************/
void Float_to_Char(float data,uint8_t *pData)
{
		uint16_t size;
		size = sprintf((char *)pData, "%f\n", data);
}
/*******************************************************************************/
void Int_to_Char(uint16_t data,uint8_t *pData)
{
		uint16_t size;
		size = sprintf((char *)pData, "%d\n", data);
}
/*******************************************************************************/
/*******************************************************************************/


























