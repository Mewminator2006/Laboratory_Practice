#ifndef INIT_H
#define INIT_H
#define RCC_GPIO_EN   *(volatile uint32_t*)(0x40023800UL + 0x30UL)
#define RCC_GPIOB_EN 0x02UL
#define GPIO_MODE_B0_OUT 0x01UL
#define GPIO_MODE_B1_OUT 0x04UL
#define GPIO_MODE_B2_OUT 0x10UL

#define GPIO_SPEED_B0_MID 0x01UL
#define GPIO_SPEED_B1_MID 0x04UL
#define GPIO_SPEED_B2_MID 0x10UL


#define GPIOB_MODER   *(volatile uint32_t*)(0x40020400UL + 0x00UL)
#define GPIOB_OTYPER  *(volatile uint32_t*)(0x40020400UL + 0x04UL)
#define GPIOB_OSPEEDR *(volatile uint32_t*)(0x40020400UL + 0x08UL)

#define READ_GPIO_B3 (*(uint32_t *)(0x40020400UL + 0x10UL) & (0x08UL))
#define READ_GPIO_B4 (*(uint32_t *)(0x40020400UL + 0x10UL) & (0x10UL))
#define READ_GPIO_B5 (*(uint32_t *)(0x40020400UL + 0x10UL) & (0x20UL))
#define READ_GPIO_B6 (*(uint32_t *)(0x40020400UL + 0x10UL) & (0x40UL))

#define SET_GPIO_B0 *(uint32_t *)(0x40020400UL + 0x18UL) = 0x01UL
#define RESET_GPIO_B0 *(uint32_t *)(0x40020400UL + 0x18UL) = 0x010000UL
#define SET_GPIO_B1 *(uint32_t *)(0x40020400UL + 0x18UL) = 0x02UL
#define RESET_GPIO_B1 *(uint32_t *)(0x40020400UL + 0x18UL) = 0x020000UL
#define SET_GPIO_B2 *(uint32_t *)(0x40020400UL + 0x18UL) = 0x04UL
#define RESET_GPIO_B2 *(uint32_t *)(0x40020400UL + 0x18UL) = 0x040000UL

void gpio_init(void);

#endif