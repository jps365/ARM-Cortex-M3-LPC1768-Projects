#include <LPC17xx.h>

/*------------------------------------------------
              BASIC DELAY
------------------------------------------------*/

void delay(void)
{
    unsigned int i;

    for(i = 0; i < 50000; i++);
}


/*------------------------------------------------
              DELAY IN MILLISECONDS
------------------------------------------------*/

void delay_ms(unsigned int ms)
{
    unsigned int i;

    for(i = 0; i < ms; i++)
    {
        delay();
    }
}


/*------------------------------------------------
              LCD COMMAND
------------------------------------------------*/

void lcd_cmd(unsigned char a)
{
    /* Clear LCD data pins P0.15-P0.22 */
    LPC_GPIO0->FIOCLR = (0xFF << 15);

    /* RS = 0 : command */
    LPC_GPIO0->FIOCLR = (1 << 10);

    /* Put command on P0.15-P0.22 */
    LPC_GPIO0->FIOSET = ((unsigned int)a << 15);

    /* EN = 1 */
    LPC_GPIO0->FIOSET = (1 << 11);

    delay();

    /* EN = 0 */
    LPC_GPIO0->FIOCLR = (1 << 11);

    delay();
}


/*------------------------------------------------
              LCD DATA
------------------------------------------------*/

void lcd_data(unsigned char a)
{
    /* Clear LCD data pins */
    LPC_GPIO0->FIOCLR = (0xFF << 15);

    /* RS = 1 : data */
    LPC_GPIO0->FIOSET = (1 << 10);

    /* Put data on P0.15-P0.22 */
    LPC_GPIO0->FIOSET = ((unsigned int)a << 15);

    /* EN = 1 */
    LPC_GPIO0->FIOSET = (1 << 11);

    delay();

    /* EN = 0 */
    LPC_GPIO0->FIOCLR = (1 << 11);

    delay();
}


/*------------------------------------------------
              LCD STRING
------------------------------------------------*/

void lcd_str(char *str)
{
    while(*str)
    {
        lcd_data(*str);
        str++;
    }
}


/*------------------------------------------------
              LCD INITIALIZATION
------------------------------------------------*/

void lcd_init(void)
{
    delay();

    lcd_cmd(0x38);      // 8-bit, 2-line mode
    delay();

    lcd_cmd(0x0E);      // Display ON, cursor ON
    delay();

    lcd_cmd(0x01);      // Clear display
    delay();

    lcd_cmd(0x80);      // First line
    delay();
}


/*------------------------------------------------
              MAIN
------------------------------------------------*/

int main(void)
{
    int i;

    /*
       Configure P0 pins as GPIO
    */
    LPC_PINCON->PINSEL0 = 0;
    LPC_PINCON->PINSEL1 = 0;

    /*
       P0.10       -> RS
       P0.11       -> EN
       P0.15-P0.22 -> D0-D7
    */
    LPC_GPIO0->FIODIR =
        (1 << 10) |
        (1 << 11) |
        (0xFF << 15);

    lcd_init();

    while(1)
    {
        for(i = 15; i >= 0; i--)
        {
            /* Clear LCD */
            lcd_cmd(0x01);

            /* First line */
            lcd_cmd(0x80);
            lcd_str("COUNTDOWN");

            /* Second line */
            lcd_cmd(0xC0);

            /* Display two digits */
            if(i >= 10)
            {
                lcd_data((i / 10) + '0');
                lcd_data((i % 10) + '0');
            }
            else
            {
                lcd_data('0');
                lcd_data(i + '0');
            }

            delay_ms(1000);
        }
    }
}