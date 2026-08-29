#include<lpc17xx.h>
#include<system_lpc17xx.h>

 /* -------------DELAY GENERATION------------*/
 
void delay()
{
  unsigned int i;
  for(i=0;i<10000;i++);
}
void del()
{
  unsigned int i;
  for(i=0;i<100000;i++);
}

/* -----------------READ COMMAND ------------------ */

void lcd_cmd(unsigned char a)
{
  LPC_GPIO0->FIOCLR=0XFF<<15;
  LPC_GPIO0->FIOCLR=1<<10;
  LPC_GPIO0->FIOSET=a<<15;
  LPC_GPIO0->FIOSET=1<<11;
  delay();
  LPC_GPIO0->FIOCLR=1<<11;
  delay();
 }
 
 /* -------------READ DATA---------------------------*/
 
 void lcd_data( unsigned char a)
{
  LPC_GPIO0->FIOCLR=0XFF<<15;
  LPC_GPIO0->FIOSET=1<<10;
  LPC_GPIO0->FIOSET=a<<15;
  LPC_GPIO0->FIOSET=1<<11;
  delay();
  LPC_GPIO0->FIOCLR=1<<11;
  delay();
 }
 
 /*--------------------LCD INITIALIZATION----------------*/
 void lcd_init()
 {
  	delay();
	lcd_cmd(0x38);
	delay();
	lcd_cmd(0x0E);
	delay();
	lcd_cmd(0x01);
	delay();
	lcd_cmd(0x80);
	delay();
  }

/*-----------------MAIN-----------------*/

int main()
{ 
 signed char i;
 unsigned char ch[4]="0000";
 unsigned int c,adc_result;
 LPC_PINCON->PINSEL0=0;
 LPC_PINCON->PINSEL1=0;
 LPC_PINCON->PINSEL1|=1<<16;
 LPC_GPIO0->FIODIR=(1<<10)|(1<<11)|(0xFF<<15);
 lcd_init();
 LPC_SC->PCONP|=(1<<12);
 LPC_SC->PCONP|=(1<<12);
 LPC_ADC->ADCR=((1<<21)|(1<<8)|(1<<1));

 while(1)

{ LPC_ADC->ADCR|=(1<<24);
  del();
  while((LPC_ADC->ADGDR&0x80000000)==0);
  adc_result=((LPC_ADC->ADGDR>>4)&0x00000FFF);

/*------------ CALCULATING THE ADC VALUE--------------------*/

  for(i=3;i>=0;i--)
{ 
  c=adc_result%10;
  ch[i]=c+48;
  adc_result=adc_result/10;
}

   for(i=0;i<=3;i++)
{
    lcd_data(ch[i]);
}

  del();delay();delay();delay();
  lcd_cmd(0x01);
  LPC_ADC->ADCR|=(0<<24);
}
}
