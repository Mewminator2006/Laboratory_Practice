
#include "init.h"
#include <stdlib.h>
void Led_on_off(int counter);
uint32_t Pin_sum(uint32_t Led_array[], int counter);
int counter = 0;
int Led_amount = 1;
int timer1 = 0;
int timer2 = 0;
int timer3 = 0;
int timer4 = 0;
int flag = 0;
int main(void)
{
    gpio_init();

    while (1)
    {
        if (READ_BIT(GPIOB->IDR, GPIO_IDR_IDR_5) != 0)
        {
            Led_amount += 1;
            flag = 1;
        }
        else{
            flag = 0;
        }

        if (READ_BIT(GPIOB->IDR, GPIO_IDR_IDR_6) != 0)
        {
            Led_amount -= 1;
            flag = 1;
        }
        else{
            flag = 0;
        }


        if (READ_BIT(GPIOB->IDR, GPIO_IDR_IDR_7) != 0)
        {
            counter += Led_amount;
            flag = 1;
        }
        else{
            flag = 0;
        }

        if (READ_BIT(GPIOB->IDR, GPIO_IDR_IDR_8) != 0)
        {
            counter -= Led_amount;
            flag = 1;
        }
        else{
            flag = 0;
        }

        
        Led_on_off(counter);
    }
}
void Led_on_off(int counter)
{
    uint32_t set_Led_array[] = {GPIO_BSRR_BS0, GPIO_BSRR_BS1, GPIO_BSRR_BS2, GPIO_BSRR_BS14, GPIO_BSRR_BS13, GPIO_BSRR_BS12};
    uint32_t reset_Led_array[] = {GPIO_BSRR_BR0, GPIO_BSRR_BR1, GPIO_BSRR_BR2, GPIO_BSRR_BR14, GPIO_BSRR_BR13, GPIO_BSRR_BR12};

    SET_BIT(GPIOB->BSRR, Pin_sum(reset_Led_array, 6));
    if(counter > 0){
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