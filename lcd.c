#include<lpc17xx.h>
#include<system_lpc17xx.h>
void delay()
{
 unsigned int i;
 for(i=0;i<50000;i++);
 }
 void delay1()
 { unsigned int i;
 for(i=0;i<1000000;i++);
 }
  
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
 void lcd_data(unsigned char a)
 { 
  LPC_GPIO0->FIOCLR=0XFF<<15;
  LPC_GPIO0->FIOSET=1<<10;
  LPC_GPIO0->FIOSET=a<<15;
  LPC_GPIO0->FIOSET=1<<11;
  delay();
  LPC_GPIO0->FIOCLR=1<<11;
  delay();
  }
  void lcd_init()
 { delay();
  lcd_cmd(0x38);
  delay();
  lcd_cmd(0x0E);
  delay();
  lcd_cmd(0x01);
  delay();
  lcd_cmd(0x80);
  delay();
  }
int main()
{ while(1)
 {
 unsigned char a[]="IGNITE EMBEDDED SYSTEMS";
 unsigned int i;
 LPC_PINCON->PINSEL0=0;
 LPC_PINCON->PINSEL1=0;
 LPC_GPIO0->FIODIR=(1<<10)|(1<<11)|(0XFF<<15);
 lcd_init();
 for(i=0;a[i]!='\0';i++)
 { if(i==16)
   { lcd_cmd(0xC0);
   }
  lcd_data(a[i]);
  }
  lcd_cmd(0x01);
  delay1();
  
  }
 }

