
#include "init.h"
#include <stdlib.h>
void Led_on_off(int counter);
uint32_t Pin_sum(uint32_t Led_array[], int counter);
int counter = 0;
int Led_amount = 1;
int Was_changed1 = 0;
int Was_changed2 = 0;
int Was_changed3 = 0;
int Was_changed4 = 0;
int flag = 0;
int main(void)
{
    gpio_init();

    while (1)
    {
        if (READ_BIT(GPIOB->IDR, GPIO_IDR_IDR_5) != 0)
        {
            if (Was_changed1 == 0)
            {
                Led_amount += 1;
                if (Led_amount > 6)
                {
                    Led_amount = 6;
                }
            }
            Was_changed1 = 1;
        }
        else
        {
            Was_changed1 = 0;
        }

        if (READ_BIT(GPIOB->IDR, GPIO_IDR_IDR_6) != 0)
        {
            if (Was_changed2 == 0)
            {
                Led_amount -= 1;
                if (Led_amount < 0)
                {
                    Led_amount = 0;
                }
            }
            Was_changed2 = 1;
        }
        else
        {
            Was_changed2 = 0;
        }

        if (READ_BIT(GPIOB->IDR, GPIO_IDR_IDR_7) != 0)
        {
            if (Was_changed3 == 0)
            {
                counter += Led_amount;
                if (counter > 6)
                {
                    counter = 6;
                }
            }
            Was_changed3 = 1;
        }
        else
        {
            Was_changed3 = 0;
        }

        if (READ_BIT(GPIOB->IDR, GPIO_IDR_IDR_8) != 0)
        {
            if (Was_changed4 == 0)
            {
                counter -= Led_amount;
                if (counter < 0)
                {
                    counter = 0;
                }
            }
            Was_changed4 = 1;
        }
        else
        {
            Was_changed4 = 0;
        }

        Led_on_off(counter);
    }
}
void Led_on_off(int counter)
{
    uint32_t set_Led_array[] = {GPIO_BSRR_BS0, GPIO_BSRR_BS1, GPIO_BSRR_BS2, GPIO_BSRR_BS14, GPIO_BSRR_BS13, GPIO_BSRR_BS12};
    uint32_t reset_Led_array[] = {GPIO_BSRR_BR0, GPIO_BSRR_BR1, GPIO_BSRR_BR2, GPIO_BSRR_BR14, GPIO_BSRR_BR13, GPIO_BSRR_BR12};

    SET_BIT(GPIOB->BSRR, Pin_sum(reset_Led_array, 6));
    if (counter > 0)
    {
        SET_BIT(GPIOB->BSRR, Pin_sum(set_Led_array, counter));
    }
}

uint32_t Pin_sum(uint32_t Led_array[], int counter)
{
    uint32_t final_mask = 0x00;
    if (counter > 0)
    {
        for (int i = 0; i < counter; i++)
        {
            final_mask |= Led_array[i];
        }
    }

    return final_mask;
}