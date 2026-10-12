#include "init.h"
#include <stdint.h>
void gpio_init(void){
// Включение тактирования портов B
*(volatile uint32_t*)(0x40023800UL + 0x30UL) |= 0x02UL;
// Настройка портов B0, B1, B2 на выход
*(volatile uint32_t*)(0x40020400UL + 0x00UL) |= 0x15UL;
// Настройка типа выхода данных портов как PP (Push-Pull)
*(volatile uint32_t*)(0x40020400UL + 0x04UL) |= 0x00UL;
// Настройка скорости работы пинов B0, B1, B2
*(volatile uint32_t*)(0x40020400UL + 0x08UL) |= 0x15UL;
}