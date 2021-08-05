#include "led.h"

uint8_t ledflag;

void LED(uint8_t id,uint8_t led)
{
	switch(id)
	{
		case 0:
		{
			switch(led)
			{
				case 0:
				{
					 HAL_GPIO_WritePin(GPIOE, GPIO_PIN_11, GPIO_PIN_RESET);
				}
				break;
				case 1:
				{
					 HAL_GPIO_WritePin(GPIOE, GPIO_PIN_11, GPIO_PIN_SET);
				}
				break;
			}
		}
		break;
		case 1:
		{
			switch(led)
			{
				case 0:
				{
					 HAL_GPIO_WritePin(GPIOF, GPIO_PIN_14, GPIO_PIN_RESET);
				}
				break;
				case 1:
				{
					 HAL_GPIO_WritePin(GPIOF, GPIO_PIN_14, GPIO_PIN_SET);
				}
				break;
			}
		}
		break;
	}
}



