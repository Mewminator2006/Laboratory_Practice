#include "init.h"
#include <stdint.h>
void gpio_init(void){
// Включение тактирования портов B
RCC_GPIO_EN |= RCC_GPIOB_EN;
// Настройка портов B0, B1, B2 на выход
GPIOB_MODER |= GPIO_MODE_B0_OUT|GPIO_MODE_B1_OUT|GPIO_MODE_B2_OUT;
// Настройка типа выхода данных портов как PP (Push-Pull)
GPIOB_OTYPER |= 0x00UL;
// Настройка скорости работы пинов B0, B1, B2
GPIOB_OSPEEDR |= GPIO_SPEED_B0_MID|GPIO_SPEED_B1_MID|GPIO_SPEED_B2_MID;
}