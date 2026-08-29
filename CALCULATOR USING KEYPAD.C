#include<lpc17xx.h>
#include<system_lpc17xx.h>

/*----------------DELAY GENERATION------------------*/

void delay()
{
 unsigned int i;
 for(i=0;i<100000;i++);
}
void del()
{
 unsigned int i;
 for(i=0;i<1000000;i++);
}

/*----------------READ THE COMMAND------------------*/

void lcd_cmd(unsigned char a)
{
 LPC_GPIO0->FIOCLR=0xFF<<15;
 LPC_GPIO0->FIOCLR=1<<10;
 LPC_GPIO0->FIOSET=a<<15;
 LPC_GPIO0->FIOSET=1<<11;
 delay();
 LPC_GPIO0->FIOCLR=1<<11;
 }
 
 /*------------------READ THE DATA--------------------*/
 
void lcd_data(unsigned char a)
{ 
 LPC_GPIO0->FIOCLR=0xFF<<15;
 LPC_GPIO0->FIOSET=1<<10;
 LPC_GPIO0->FIOSET=a<<15;
 LPC_GPIO0->FIOSET=1<<11;
 delay();
 LPC_GPIO0->FIOCLR=1<<11;
 
}

 /*---------------LCD INITIALIZATION------------------*/
void lcd_init()
{
  delay();
 lcd_cmd(0x38);
  delay();
 lcd_cmd(0x10);
  delay();
 lcd_cmd(0x0E);
  delay();
 lcd_cmd(0x80);
 
 }
 
 /*----------------LOGIC FOR SELECTING THE PERTICULAR SWITCH----------------*/
 
 unsigned char scan_row()
 {LPC_GPIO2->FIOSET=0x000000E0;
  if((LPC_GPIO2->FIOPIN&0x0000000F)==0x0000000E)
   return '1';
   if((LPC_GPIO2->FIOPIN&0x0000000F)==0x0000000D)
   return '2';
   if((LPC_GPIO2->FIOPIN&0x0000000F)==0x0000000B)
   return '3';
   if((LPC_GPIO2->FIOPIN&0x0000000F)==0x00000007)
   return '+';
   LPC_GPIO2->FIOCLR=0x000000E0;
   LPC_GPIO2->FIOSET=0x000000D0;

   if((LPC_GPIO2->FIOPIN&0x0000000F)==0x0000000E)
   return '4';
   if((LPC_GPIO2->FIOPIN&0x0000000F)==0x0000000D)
   return '5';
   if((LPC_GPIO2->FIOPIN&0x0000000F)==0x0000000B)
   return '6';
   if((LPC_GPIO2->FIOPIN&0x0000000F)==0x00000007)
   return '-';
   LPC_GPIO2->FIOCLR=0x000000D0;
   LPC_GPIO2->FIOSET=0x000000B0;

   if((LPC_GPIO2->FIOPIN&0x0000000F)==0x0000000E)
   return '7';
   if((LPC_GPIO2->FIOPIN&0x0000000F)==0x0000000D)
   return '8';
   if((LPC_GPIO2->FIOPIN&0x0000000F)==0x0000000B)
   return '9';
   if((LPC_GPIO2->FIOPIN&0x0000000F)==0x00000007)
   return '*';
   LPC_GPIO2->FIOCLR=0x000000B0;
   LPC_GPIO2->FIOSET=0x00000070;

   if((LPC_GPIO2->FIOPIN&0x0000000F)==0x0000000E)
   return '/';
   if((LPC_GPIO2->FIOPIN&0x0000000F)==0x0000000D)
   return '%';
   if((LPC_GPIO2->FIOPIN&0x0000000F)==0x0000000B)
   return '0';
   if((LPC_GPIO2->FIOPIN&0x0000000F)==0x00000007)
   return '#';
   LPC_GPIO2->FIOCLR=0x00000070;
 }
 
 /*-----------------MAIN-----------*/

int main()
{ 
  unsigned char ch,num1,num2;
  unsigned int result;
  LPC_PINCON->PINSEL0=0;										
  LPC_PINCON->PINSEL1=0;
  LPC_PINCON->PINSEL4=0;
  LPC_GPIO0->FIODIR=(1<<10)|(1<<11)|(0xFF<<15);
  LPC_GPIO2->FIODIR=0x000000F0;
  lcd_init();
  while(1)
  { LPC_GPIO2->FIOPIN=0x0000000F;
   while((LPC_GPIO2->FIOPIN & 0x0000000F)==0x0000000F);
   del();
   while((LPC_GPIO2->FIOPIN & 0x0000000F)==0x0000000F);
   num1=scan_row();
   num2=scan_row();
   ch=scan_row();
   lcd_data(ch);

   if(ch=='#')
   {
   lcd_cmd(0x10);
   }
   
    switch(ch)
     {
  	     case '+':

	          result =num1+num2;
			  lcd_data(result);
			  break;
		 case '-':
		       result=10-2;
			   lcd_data(result+'0');
			   break;
		 case '*':
		       result=10*2;
			   lcd_data(result);
			   break;
		 case '/':
		       result=10/2;
			   lcd_data(result+'0');
			   break;
		 case '%':
		       result=10%2;
			   lcd_data(result+'0');
			   break;
		 default:
		       result=0;
			   lcd_data(result+'0');
	   }
 }
 }
