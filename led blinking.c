#include<lpc17xx.h>
#include<system_lpc17xx.h>

void delay()
{ unsigned int i;
 for(i=0;i<=1000000;i++);
}

int main()
{
 LPC_PINCON->PINSEL3=0X00000000;
 LPC_GPIO1->FIODIR=0XFF<<19;
 while(1)
 { int i;
  for(i=19;i<=26;i++)
  {
  LPC_GPIO1->FIOSET=0X01<<i;
  delay();
  LPC_GPIO1->FIOCLR=0X01<<i; 
  }
   for(i=26;i>=19;i--)
  {
  LPC_GPIO1->FIOSET=0X01<<i;
  delay();
  LPC_GPIO1->FIOCLR=0X01<<i;
  }
 }
 }
