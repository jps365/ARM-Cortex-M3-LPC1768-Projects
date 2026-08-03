#include <lpc17xx.h>
#include <system_lpc17xx.h>

void delay()
{
    unsigned int i;
    for(i=0;i<50000;i++);
}

void delay1()
{
    unsigned int i;
    for(i=0;i<1000000;i++);
}

void lcd_cmd(unsigned char a)
{
    LPC_GPIO0->FIOCLR = 0xFF<<15;
    LPC_GPIO0->FIOCLR = 1<<10;      // RS = 0

    LPC_GPIO0->FIOSET = a<<15;

    LPC_GPIO0->FIOSET = 1<<11;      // EN = 1
    delay();
    LPC_GPIO0->FIOCLR = 1<<11;      // EN = 0
    delay();
}

void lcd_data(unsigned char a)
{
    LPC_GPIO0->FIOCLR = 0xFF<<15;
    LPC_GPIO0->FIOSET = 1<<10;      // RS = 1

    LPC_GPIO0->FIOSET = a<<15;

    LPC_GPIO0->FIOSET = 1<<11;
    delay();
    LPC_GPIO0->FIOCLR = 1<<11;
    delay();
}

void lcd_init()
{
    delay();

    lcd_cmd(0x38);
    lcd_cmd(0x0E);
    lcd_cmd(0x01);
    lcd_cmd(0x80);
}

/*----------- Create Custom Character -----------*/
void lcd_custom(unsigned char *ptr)
{
    int i;

    lcd_cmd(0x40);      // CGRAM Address (Location 0)

    for(i=0;i<8;i++)
    {
        lcd_data(ptr[i]);
    }

    lcd_cmd(0x80);      // Return to DDRAM
}

/*----------- Heart Character -----------*/
unsigned char heart[8]=
{
    0x0E,
    0x0E,
    0x0E,
    0x0E,
    0x15,
    0x04,
    0x0A,
    0x11
};

int main()
{
    LPC_PINCON->PINSEL0 = 0;
    LPC_PINCON->PINSEL1 = 0;

    LPC_GPIO0->FIODIR = (1<<10)|(1<<11)|(0xFF<<15);

    lcd_init();

    lcd_custom(heart);      // Store Heart in CGRAM Location 0

    while(1)
    {
        lcd_cmd(0x80);

        lcd_data('I');
        lcd_data(' ');

        lcd_data(0);        // Display Heart

        lcd_data(' ');
        lcd_data('J');
		 lcd_data('Y');
		  lcd_data('O');


        delay1();
    }
}
