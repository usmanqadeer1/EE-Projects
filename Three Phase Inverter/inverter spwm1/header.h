#define RCC_BASE			0x40023800
#define GPIOD_BASE		0x40020C00
#define GPIOA_BASE		0x40020000
#define GPIOB_BASE		0x40020400
#define GPIOC_BASE		0x40020800
#define TIM2_BASE			0x40000000
#define TIM3_BASE			0x40000400
#define TIM4_BASE			0x40000800
#define TIM5_BASE			0x40000C00
#define TIM12_BASE		0x40001800
#define TIM13_BASE		0x40001C00
#define ADC1_BASE			0x40012000

#define ADC_CR2				(*((volatile unsigned long *) (ADC1_BASE + 0x08)))
#define ADC_SQR2			(*((volatile unsigned long *) (ADC1_BASE + 0x30)))
#define ADC_SQR3			(*((volatile unsigned long *) (ADC1_BASE + 0x34)))
#define ADC_DR				(*((volatile unsigned long *) (ADC1_BASE + 0x4C)))
#define ADC_SR				(*((volatile unsigned long *) (ADC1_BASE + 0x00)))


#define RCC_AHB1ENR 	(*((volatile unsigned long *) (RCC_BASE + 0x30)))
#define RCC_APB1ENR 	(*((volatile unsigned long *) (RCC_BASE + 0x40)))
#define RCC_APB2ENR 	(*((volatile unsigned long *) (RCC_BASE + 0x44)))

#define GPIOA_MODER		(*((volatile unsigned long *)	(GPIOA_BASE + 0x00)))
#define GPIOA_SPEEDR	(*((volatile unsigned long *)	(GPIOA_BASE + 0x08)))
#define GPIOA_ODR			(*((volatile unsigned long *)	(GPIOA_BASE + 0x14)))
#define GPIOA_AFLR		(*((volatile unsigned long *)	(GPIOA_BASE + 0x20)))
#define GPIOA_AFHR		(*((volatile unsigned long *)	(GPIOA_BASE + 0x24)))
#define GPIOA_IDR			(*((volatile unsigned long *)	(GPIOA_BASE + 0x10)))
#define GPIOA_PUPDR		(*((volatile unsigned long *)	(GPIOA_BASE + 0x0C)))

#define GPIOB_MODER		(*((volatile unsigned long *)	(GPIOB_BASE + 0x00)))
#define GPIOB_SPEEDR	(*((volatile unsigned long *)	(GPIOB_BASE + 0x08)))
#define GPIOB_ODR			(*((volatile unsigned long *)	(GPIOB_BASE + 0x14)))
#define GPIOB_AFLR		(*((volatile unsigned long *)	(GPIOB_BASE + 0x20)))
#define GPIOB_AFHR		(*((volatile unsigned long *)	(GPIOB_BASE + 0x24)))
#define GPIOB_IDR			(*((volatile unsigned long *)	(GPIOB_BASE + 0x10)))
#define GPIOB_PUPDR		(*((volatile unsigned long *)	(GPIOB_BASE + 0x0C)))

#define GPIOC_MODER		(*((volatile unsigned long *)	(GPIOC_BASE + 0x00)))
#define GPIOC_SPEEDR	(*((volatile unsigned long *)	(GPIOC_BASE + 0x08)))
#define GPIOC_ODR			(*((volatile unsigned long *)	(GPIOC_BASE + 0x14)))
#define GPIOC_AFLR		(*((volatile unsigned long *)	(GPIOC_BASE + 0x20)))
#define GPIOC_AFHR		(*((volatile unsigned long *)	(GPIOC_BASE + 0x24)))
#define GPIOC_IDR			(*((volatile unsigned long *)	(GPIOC_BASE + 0x10)))
#define GPIOC_PUPDR		(*((volatile unsigned long *)	(GPIOC_BASE + 0x0C)))


#define GPIOD_MODER		(*((volatile unsigned long *)	(GPIOD_BASE + 0x00)))
#define GPIOD_ODR			(*((volatile unsigned long *)	(GPIOD_BASE + 0x14)))
#define GPIOD_AFLR		(*((volatile unsigned long *)	(GPIOD_BASE + 0x20)))
#define GPIOD_AFHR		(*((volatile unsigned long *)	(GPIOD_BASE + 0x24)))
#define GPIOD_IDR			(*((volatile unsigned long *)	(GPIOD_BASE + 0x10)))


#define TIM2_CR1			(*((volatile unsigned long *)	(TIM2_BASE + 0x00)))
#define TIM2_CNT			(*((volatile unsigned long *)	(TIM2_BASE + 0x24)))
#define TIM2_PSC			(*((volatile unsigned long *)	(TIM2_BASE + 0x28)))
#define TIM2_ARR			(*((volatile unsigned long *)	(TIM2_BASE + 0x2C)))
#define TIM2_SR				(*((volatile unsigned long *)	(TIM2_BASE + 0x10)))
#define TIM2_EGR			(*((volatile unsigned long *)	(TIM2_BASE + 0x14)))

#define TIM4_CR1			(*((volatile unsigned long *)	(TIM4_BASE + 0x00)))
#define TIM4_CNT			(*((volatile unsigned long *)	(TIM4_BASE + 0x24)))
#define TIM4_PSC			(*((volatile unsigned long *)	(TIM4_BASE + 0x28)))
#define TIM4_ARR			(*((volatile unsigned long *)	(TIM4_BASE + 0x2C)))
#define TIM4_SR				(*((volatile unsigned long *)	(TIM4_BASE + 0x10)))
#define TIM4_EGR			(*((volatile unsigned long *)	(TIM4_BASE + 0x14)))
#define TIM4_CCMR1		(*((volatile unsigned long *)	(TIM4_BASE + 0x18)))
#define TIM4_CCER 		(*((volatile unsigned long *)	(TIM4_BASE + 0x20)))
#define TIM4_CCR1 		(*((volatile unsigned long *)	(TIM4_BASE + 0x34)))

#define TIM5_CR1			(*((volatile unsigned long *)	(TIM5_BASE + 0x00)))
#define TIM5_CNT			(*((volatile unsigned long *)	(TIM5_BASE + 0x24)))
#define TIM5_PSC			(*((volatile unsigned long *)	(TIM5_BASE + 0x28)))
#define TIM5_ARR			(*((volatile unsigned long *)	(TIM5_BASE + 0x2C)))
#define TIM5_SR				(*((volatile unsigned long *)	(TIM5_BASE + 0x10)))
#define TIM5_EGR			(*((volatile unsigned long *)	(TIM5_BASE + 0x14)))
#define TIM5_CCMR1		(*((volatile unsigned long *)	(TIM5_BASE + 0x18)))
#define TIM5_CCMR2		(*((volatile unsigned long *)	(TIM5_BASE + 0x1C)))
#define TIM5_CCER 		(*((volatile unsigned long *)	(TIM5_BASE + 0x20)))
#define TIM5_CCR1 		(*((volatile unsigned long *)	(TIM5_BASE + 0x34)))

#define TIM3_CR1			(*((volatile unsigned long *)	(TIM3_BASE + 0x00)))
#define TIM3_CNT			(*((volatile unsigned long *)	(TIM3_BASE + 0x24)))
#define TIM3_PSC			(*((volatile unsigned long *)	(TIM3_BASE + 0x28)))
#define TIM3_ARR			(*((volatile unsigned long *)	(TIM3_BASE + 0x2C)))
#define TIM3_SR				(*((volatile unsigned long *)	(TIM3_BASE + 0x10)))
#define TIM3_EGR			(*((volatile unsigned long *)	(TIM3_BASE + 0x14)))
#define TIM3_CCMR1		(*((volatile unsigned long *)	(TIM3_BASE + 0x18)))
#define TIM3_CCMR2 		(*((volatile unsigned long *)	(TIM3_BASE + 0x1C)))
#define TIM3_CCER 		(*((volatile unsigned long *)	(TIM3_BASE + 0x20)))
#define TIM3_CCR1 		(*((volatile unsigned long *)	(TIM3_BASE + 0x34)))
#define TIM3_CCR3 		(*((volatile unsigned long *)	(TIM3_BASE + 0x3C)))


#define TIM12_CR1			(*((volatile unsigned long *)	(TIM12_BASE + 0x00)))
#define TIM12_CNT			(*((volatile unsigned long *)	(TIM12_BASE + 0x24)))
#define TIM12_PSC			(*((volatile unsigned long *)	(TIM12_BASE + 0x28)))
#define TIM12_ARR			(*((volatile unsigned long *)	(TIM12_BASE + 0x2C)))
#define TIM12_SR			(*((volatile unsigned long *)	(TIM12_BASE + 0x10)))
#define TIM12_EGR			(*((volatile unsigned long *)	(TIM12_BASE + 0x14)))
#define TIM12_CCMR1		(*((volatile unsigned long *)	(TIM12_BASE + 0x18)))
#define TIM12_CCER 		(*((volatile unsigned long *)	(TIM12_BASE + 0x20)))
#define TIM12_CCR1 		(*((volatile unsigned long *)	(TIM12_BASE + 0x34)))

#define TIM13_CR1			(*((volatile unsigned long *)	(TIM13_BASE + 0x00)))
#define TIM13_CNT			(*((volatile unsigned long *)	(TIM13_BASE + 0x24)))
#define TIM13_PSC			(*((volatile unsigned long *)	(TIM13_BASE + 0x28)))
#define TIM13_ARR			(*((volatile unsigned long *)	(TIM13_BASE + 0x2C)))
#define TIM13_SR			(*((volatile unsigned long *)	(TIM13_BASE + 0x10)))
#define TIM13_EGR			(*((volatile unsigned long *)	(TIM13_BASE + 0x14)))
#define TIM13_CCMR1		(*((volatile unsigned long *)	(TIM13_BASE + 0x18)))
#define TIM13_CCER 		(*((volatile unsigned long *)	(TIM13_BASE + 0x20)))
#define TIM13_CCR1 		(*((volatile unsigned long *)	(TIM13_BASE + 0x34)))


#define pi						3.14159265358979323846
#define dead_time			7e-6
#define sample_time		1e-3
#define initial_freq	5
#define	final_freq		50
#define initial_a			0.1
#define P							0.0008
#define I							0.001
#define integrator_delta_t	20e-3
#define poles 				4
#define rated_speed		1500
#define speed_sample_time	0.5



