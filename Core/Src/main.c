
#include "init.h"
#include <stdlib.h>
#include <stdbool.h>

int counter = 0;
int cursor = 0;
unsigned char mask = 0x00;
int Led_amount = 1;
int Was_changed1 = 0;
int Was_changed2 = 0;
int Was_changed3 = 0;
int Was_changed4 = 0;
int flag = 0;
void Led_step(int step, int direction);
uint32_t Pin_sum(uint32_t Led_array[], unsigned char mask);
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
                if (Led_amount < 1)
                {
                    Led_amount = 1;
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
                Led_step(Led_amount, 1);
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
                Led_step(Led_amount, 2);
            }
            Was_changed4 = 1;
        }
        else
        {
            Was_changed4 = 0;
        }
    }
}
void Led_step(int step, int direction)
{
    uint32_t set_Led_array[] = {GPIO_BSRR_BS0, GPIO_BSRR_BS1, GPIO_BSRR_BS2, GPIO_BSRR_BS14, GPIO_BSRR_BS13, GPIO_BSRR_BS12};
    uint32_t reset_Led_array[] = {GPIO_BSRR_BR0, GPIO_BSRR_BR1, GPIO_BSRR_BR2, GPIO_BSRR_BR14, GPIO_BSRR_BR13, GPIO_BSRR_BR12};

    if (step == 0)
        return;

    if (direction == 1)
    {
        if ((cursor + step > 6) || (mask == 0b00111111))
        {
            SET_BIT(GPIOB->BSRR, Pin_sum(reset_Led_array, 0b00111111));
            mask = 0x00;
        }
        for (int i = cursor; i < cursor + step; i++)
        {
            mask |= (1 << (i % 6));
        }

        cursor = (cursor + step) % 6;
    }
    else if (direction == 2)
    {
        if (cursor - step < 0)
        {
            SET_BIT(GPIOB->BSRR, Pin_sum(reset_Led_array, 0b00111111));
            mask = 0x00;

            int new_cursor = 6 + (cursor - step);

            for (int i = 0; i < new_cursor; i++)
            {
                mask |= (1 << i);
            }

            cursor = new_cursor;

            SET_BIT(GPIOB->BSRR, Pin_sum(set_Led_array, mask));
        }
        else
        {
            unsigned char delete_mask = 0x00;
            for (int i = cursor - 1; i >= cursor - step; i--)
            {
                mask &= ~(1 << i);
                delete_mask |= (1<<i);
            }

            cursor = cursor - step;
            SET_BIT(GPIOB->BSRR, Pin_sum(reset_Led_array, delete_mask));
        }
    }
    

    SET_BIT(GPIOB->BSRR, Pin_sum(set_Led_array, mask));
}

uint32_t Pin_sum(uint32_t Led_array[], unsigned char mask)
{
    uint32_t final_mask = 0x00;

    for (int i = 0; i < 6; i++)
    {
        unsigned char scaner = (1 << i);
        if ((mask & scaner) != 0)
        {
            final_mask |= Led_array[i];
        }
    }

    return final_mask;
}