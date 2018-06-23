#include <math.h>
#include "header.h"
#include <stdlib.h>

volatile double speed;
volatile int captured_pulses;


void delay(double delay_time)
{
	volatile unsigned long auto_reload_value;
	if(delay_time<1e-10)	return;
	RCC_APB1ENR |= 0x01;
	TIM2_CR1 = 0x080;
	TIM2_PSC = 0;
	auto_reload_value = ceil(delay_time*84e6/(TIM2_PSC+1));
		if(auto_reload_value>0xFFFFFFFF)
	{
		auto_reload_value = 0xFFFFFFFF;
	}
	TIM2_ARR = auto_reload_value;
	TIM2_EGR |= 0x01;
	TIM2_SR &= ~0x01;
	TIM2_CR1 |= 0x01;

	while(1)
	{
		if(TIM2_SR&0x01)
		{
			TIM2_CR1 &= ~0x01;
			TIM2_SR &= ~0x01;
			return;
		}
	}
}

double theta(double freq)	// function giving angle in radians of reference vector as
{							// output and reference vector will be rotating with
							// with the angular velocity of (2*π*freq) rad/s
	int neg_flag;
	neg_flag = 0;
	if(freq<0)
	{
		freq = -freq;
		neg_flag = 1;		// checking whether freq is +ve or -ve
	}

	if(!(TIM5_CR1&0x01))	// initializing the Timer 5
	{
		RCC_APB1ENR |= 0x08;
		TIM5_CR1 |= 0x0080;
		TIM5_PSC = 5;
		TIM5_EGR |= 0x01;
		TIM5_CR1 |= 0x01;
	}

	if(TIM5_SR&0x01)		// execution at timer overflow
	{
		TIM5_ARR = ceil((84e6/(TIM5_PSC+1))/freq);	// adjusting the reload value
		TIM5_EGR |= 0x01;							// according to the freq
		TIM5_SR &= ~0x01;
	}

	if(neg_flag == 0)	return (2*pi*TIM5_CNT/TIM5_ARR);// anti-clockwise rotation for
														// +ve freq
	else				return (-2*pi*TIM5_CNT/TIM5_ARR);// clockwise rotation for
														 //-ve freq
}

double trianglular_generator(double freq)
{
	double count, reload;
	if(!(TIM4_CR1&0x01))
	{
		RCC_APB1ENR |= 0x04;
		TIM4_CR1 |= 0xE0;
		TIM4_PSC = 2624;
		TIM4_ARR = 0xFFFF;
		TIM4_EGR |= 0x01;
		TIM4_CR1 |= 0x01;
	}

	if(TIM4_SR&0x01)
	{
		if((TIM4_CNT&0xFFFF) < ceil((0xFFFF&TIM4_ARR)/2))
		{
		  TIM4_ARR = (1/freq)*0.5*84e6/(TIM4_PSC+1);
			TIM4_EGR |= 0x01;
		}
		TIM4_SR &= ~0x01;
	}
	count = 0xFFFF&TIM4_CNT;
	reload = 0xFFFF&TIM4_ARR;
	return ((2*count/reload)-1);
}




void output_pwm(volatile unsigned long logic_a, volatile unsigned long logic_b, volatile unsigned long logic_c, volatile double dead_band)
{
	int transition_flag_a, transition_flag_b, transition_flag_c;
	unsigned long check_1, check_2, check_3;

	check_1 = GPIOC_ODR&0x02;
	if(check_1!=0)	check_1=1;

	check_2 = GPIOA_ODR&0x02;
	if(check_2!=0)	check_2=1;

	check_3 = GPIOA_ODR&0x20;
	if(check_3!=0)	check_3=1;

	if(check_1 != logic_a)
	{
		transition_flag_a = 1;
		GPIOC_ODR &= ~0xA;
	}
	else
	{
		transition_flag_a = 0;
	}

	if(check_2 != logic_b)
	{
		transition_flag_b = 1;
		GPIOA_ODR &= ~0xA;
	}
	else
	{
		transition_flag_b = 0;
	}

	if(check_3 != logic_c)
	{
		transition_flag_c = 1;
		GPIOA_ODR &= ~0xA0;
	}
	else
	{
		transition_flag_c = 0;
	}

	if(transition_flag_a || transition_flag_b || transition_flag_c)
	{
		delay(dead_band);

		if(transition_flag_a==1)
		{
			if(logic_a==1)
			{
				GPIOC_ODR |= 0x02;
				GPIOC_ODR &= ~0x08;
			}
			else
			{
				GPIOC_ODR &= ~0x02;
				GPIOC_ODR |= 0x08;
			}
		}

		if(transition_flag_b==1)
		{
			if(logic_b==1)
			{
				GPIOA_ODR |= 0x02;
				GPIOA_ODR &= ~0x08;
			}
			else
			{
				GPIOA_ODR &= ~0x02;
				GPIOA_ODR |= 0x08;
			}
		}

		if(transition_flag_c==1)
		{
			if(logic_c==1)
			{
				GPIOA_ODR |= 0x20;
				GPIOA_ODR &= ~0x80;

			}
			else
			{
				GPIOA_ODR &= ~0x20;
				GPIOA_ODR |= 0x80;
			}
		}
	}

}


int sector_calculation(double angle_radians)
{
	double angle_degrees;
	angle_degrees = angle_radians*180/pi;

	if	   (angle_degrees>0   &&  angle_degrees<=60)		return 1;
	else if(angle_degrees>60  && angle_degrees<=120)		return 2;
	else if(angle_degrees>120 && angle_degrees<=180)		return 3;
	else if(angle_degrees>180 && angle_degrees<=240)		return 4;
	else if(angle_degrees>240 && angle_degrees<=300)		return 5;
	else if(angle_degrees>300 && angle_degrees<=360)		return 6;

	else if(angle_degrees<0     && angle_degrees>=-60)		return 6;
	else if(angle_degrees<-60   && angle_degrees>=-120)		return 5;
	else if(angle_degrees<-120  && angle_degrees>=-180)		return 4;
	else if(angle_degrees<-180  && angle_degrees>=-240)		return 3;
	else if(angle_degrees<-240  && angle_degrees>=-300)		return 2;
	else	return 1;
}

double T1_calculation(double Tc, double modulation_index, int sector, double theta)
{
	return (Tc*modulation_index*sin((pi/3)-theta+(pi/3)*(sector-1)));
}

double T2_calculation(double Tc, double modulation_index, int sector, double theta)
{
	return (Tc*modulation_index*sin(theta-(pi/3)*(sector-1)));
}

void vector_switching_pattern(int discrete_vector)
{
	if     (discrete_vector == 0)		output_pwm(0, 0, 0, dead_time);
	else if(discrete_vector == 1)		output_pwm(1, 0, 0, dead_time);
	else if(discrete_vector == 2)		output_pwm(1, 1, 0, dead_time);
	else if(discrete_vector == 3)		output_pwm(0, 1, 0, dead_time);
	else if(discrete_vector == 4)		output_pwm(0, 1, 1, dead_time);
	else if(discrete_vector == 5)		output_pwm(0, 0, 1, dead_time);
	else if(discrete_vector == 6)		output_pwm(1, 0, 1, dead_time);
	else								output_pwm(1, 1, 1, dead_time);
}


void vector_application(int sector, double T1, double T2, double T0)
{
	if(sector == 1)
	{
		vector_switching_pattern(0);
		delay(T0/4);
		vector_switching_pattern(1);
		delay(T1/2);
		vector_switching_pattern(2);
		delay(T2/2);
		vector_switching_pattern(7);
		delay(T0/2);
		vector_switching_pattern(2);
		delay(T2/2);
		vector_switching_pattern(1);
		delay(T1/2);
		vector_switching_pattern(0);
		delay(T0/4);
	}

	else if(sector == 2)
	{
		vector_switching_pattern(0);
		delay(T0/4);
		vector_switching_pattern(3);
		delay(T2/2);
		vector_switching_pattern(2);
		delay(T1/2);
		vector_switching_pattern(7);
		delay(T0/2);
		vector_switching_pattern(2);
		delay(T1/2);
		vector_switching_pattern(3);
		delay(T2/2);
		vector_switching_pattern(0);
		delay(T0/4);
	}

	else if(sector == 3)
	{
		vector_switching_pattern(0);
		delay(T0/4);
		vector_switching_pattern(3);
		delay(T1/2);
		vector_switching_pattern(4);
		delay(T2/2);
		vector_switching_pattern(7);
		delay(T0/2);
		vector_switching_pattern(4);
		delay(T2/2);
		vector_switching_pattern(3);
		delay(T1/2);
		vector_switching_pattern(0);
		delay(T0/4);
	}

	else if(sector == 4)
	{
		vector_switching_pattern(0);
		delay(T0/4);
		vector_switching_pattern(5);
		delay(T2/2);
		vector_switching_pattern(4);
		delay(T1/2);
		vector_switching_pattern(7);
		delay(T0/2);
		vector_switching_pattern(4);
		delay(T1/2);
		vector_switching_pattern(5);
		delay(T2/2);
		vector_switching_pattern(0);
		delay(T0/4);
	}

	else if(sector == 5)
	{
		vector_switching_pattern(0);
		delay(T0/4);
		vector_switching_pattern(5);
		delay(T1/2);
		vector_switching_pattern(6);
		delay(T2/2);
		vector_switching_pattern(7);
		delay(T0/2);
		vector_switching_pattern(6);
		delay(T2/2);
		vector_switching_pattern(5);
		delay(T1/2);
		vector_switching_pattern(0);
		delay(T0/4);
	}

	else
	{
		vector_switching_pattern(0);
		delay(T0/4);
		vector_switching_pattern(1);
		delay(T2/2);
		vector_switching_pattern(6);
		delay(T1/2);
		vector_switching_pattern(7);
		delay(T0/2);
		vector_switching_pattern(6);
		delay(T1/2);
		vector_switching_pattern(1);
		delay(T2/2);
		vector_switching_pattern(0);
		delay(T0/4);
	}
}

double ADC_voltage()		//ADC imput is at PC0
{
	volatile double ADC_data;
	if(!(ADC_CR2&0x01))
	{
		RCC_APB2ENR |= 0x100;
		GPIOC_MODER |= 0x03;
		ADC_SQR3 |= 0x0A;
		ADC_CR2 |= 0x01;
		delay(0.0001);
		ADC_CR2 |= 0x02;
		ADC_CR2 |= 0x40000000;
	}
	ADC_data = ADC_DR;
	return(ADC_data*3/4095);
}

double feedback_speed(double freq)
{
	static double delta_t = 1e8;
	static int counter = 0;
	volatile double auto_reload_value;
	volatile double captured_value;	//feedback is given at PB0
	if(!(TIM3_CR1&0x01))
	{
		RCC_AHB1ENR |= 0x02;
		GPIOB_MODER |= 0x02;
		GPIOB_AFLR |=  0x02;
		RCC_APB1ENR |= 0x02;
		TIM3_PSC = 5000;
		//auto_reload_value = ceil(time_period*84e6/(TIM3_PSC+1));
		TIM3_ARR = 14160;
		TIM3_CR1 |= 0x80;
		TIM3_CCMR2 |= 0x01;
		TIM3_CCMR2 |= 0x30;
		TIM3_CCER |= 0x100;
		TIM3_EGR |= 0x01;
		TIM3_SR &= ~0x01;
		TIM3_CR1 |= 0x01;
	}

	if((TIM3_SR&0x08) != 0)
	{
		counter++;
		TIM3_SR &= ~0x08;
		if(counter >= 2)
		{
			captured_value = TIM3_CCR3;
			delta_t = (captured_value/84e6)*(TIM3_PSC+1);
			TIM3_EGR |= 0x01;
			TIM3_SR &= ~0x01;
			if(counter > 100)	counter = 10;
		}
		else
		{
			TIM3_EGR |= 0x01;
			TIM3_SR &= ~0x01;
		}

	}

	if(TIM3_SR&0x01)
	{
		counter = 0;
		delta_t = 0;
		return 0;
	}
	if(freq>0)	return (60/delta_t);
	else				return -(60/delta_t);
}



void GPIO_ACD_init()
{
	RCC_AHB1ENR |= 0x0D;
	GPIOD_MODER |= 0x55000000;
	GPIOA_MODER |= 0x4444;
	GPIOA_SPEEDR |= 0x4444;
	GPIOC_MODER |= 0x044;
	GPIOC_SPEEDR |= 0x044;
}

double integrator(double input)
{
	static double f_x_old = 0;
	static double integral = 0;
	volatile unsigned long auto_reload_value;
	if(!(TIM12_CR1&0x01))
	{
		RCC_APB1ENR |= 0x40;
		TIM12_CR1 |= 0x80;
		TIM12_PSC = 8399;	//Timer frequency of 10KHz
		auto_reload_value = ceil(integrator_delta_t*84e6/(TIM12_PSC+1));
		if(auto_reload_value>0xFFFF)	auto_reload_value = 0xFFFF;
		TIM12_ARR = auto_reload_value;
		TIM12_EGR |= 0x01;
		TIM12_SR &= ~0x01;
		TIM12_CR1 |= 0x01;
	}

	if(TIM12_SR&0x01)
	{
		integral = 0.5*integrator_delta_t*(f_x_old+input) + integral;
		f_x_old = input;
		TIM12_SR &= ~0x01;
	}
	return integral;
}

double PI_controller(double error)
{
	double answer;
	answer = P*error + I*integrator(error);

	return(answer);
}

int main()
{
	volatile double my_theta, time_1, time_2, time_0, a, ADC_volts, error, input_speed, measured_speed;
	volatile static double low_frequency;
	volatile int my_sector;
	low_frequency = 5;
	input_speed = 0;

	GPIO_ACD_init();

	while(1)
	{
		measured_speed = feedback_speed(low_frequency);
		ADC_volts = ADC_voltage();
		input_speed = 1579 * ADC_volts - 1500;
		error = input_speed - measured_speed;

		if(abs(error)>5)		low_frequency = low_frequency + (0.008333*poles)*PI_controller(error);


		if(low_frequency>final_freq)	low_frequency =  final_freq;
		if(low_frequency<-final_freq)	low_frequency = -final_freq;

		if(low_frequency>-5 && low_frequency<5)	output_pwm(0,0,0, dead_time);
		else
		{

			if(low_frequency<0)			a = 1 -((1-initial_a)/(50-initial_freq))*(50+low_frequency);
			else						a = 1 -((1-initial_a)/(50-initial_freq))*(50-low_frequency);

			my_theta = theta(low_frequency);
			my_sector = sector_calculation(my_theta);
			time_1 = T1_calculation(sample_time, a, my_sector, my_theta);
			time_2 = T2_calculation(sample_time, a, my_sector, my_theta);
			time_0 = sample_time - time_1 - time_2;
			vector_application(my_sector, time_1, time_2, time_0);
		}
	}

}
