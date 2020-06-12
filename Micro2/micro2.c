


#include "uart.h"
#include "i2c.h"
#include "external_eeprom.h"

uint8 tick=0;
uint8 flag =0;
void timer1_func()
{

	// PRESCALAR B 1024 ...page 107.....

	TCCR1B |= (1<<CS12) | (1<<CS10) |(1<<WGM12);  // dol mwgoden fe TCCR1B .......
	TCCR1A |= (1<<FOC1A);                        // page 105
	TCCR1B &= ~(1<<CS11);
	TCNT1 = 0;                                    // hbda2 counting mn zero......
	OCR1A = 1000;                                  // h3d 1000 3ada......
	TIMSK |= (1<<OCIE1A);                        // h43'l channel A.......enable interrupt
}

ISR(TIMER1_COMPA_vect)
{
	tick++;
	if(tick==15)
	{
		flag=1;
		tick=0;
	}
}



int main()
{
    /*
	EEPROM_writeByte(0x0111,0);          // lw 3ayz abda2 el system mn el awl 5ales ... mn awl el entering new password.............h7ot el makan da b zero w a3mel build w a43'l proteus awl mara w b3d kda ha4elha(a3mlha commented y3ny) w a3ml build.... 34an m4 kol mara yla2y el makan b zero lama yfta7 el main ....enta bs bt7otha f el awl mara kda w t4elha b3dha 34an tt3'yr w tb2a 1 m4 tfdal 0 3ltol......
	_delay_ms(10);  */


	SREG |= (1<<7);  // Enable global interrupts in MC.

	uint8 fourth;
	// dol el 10 variables el h2ra behom el password 3ala marten f el awl 5als...................
	uint8 read1;
	uint8 read2;
	uint8 read3;
	uint8 read4;
	uint8 read5;
	uint8 read6;
	uint8 read7;
	uint8 read8;
	uint8 read9;
	uint8 read10;
	//........................
	// da el variable el b3raf beh hy3ml open door wla change passwrod
	uint8 option;
	//........................
	// dol el 5 variables el ha5od behom el password lw 3ayz y3ml open door aw change password.............
	uint8 read11;
	uint8 read12;
	uint8 read13;
	uint8 read14;
	uint8 read15;
	//................................
	//dol el variables el h7ot fehom 2erayat el eeprom...................
	uint8 prom1=0;
	uint8 prom2=0;
	uint8 prom3=0;
	uint8 prom4=0;
	uint8 prom5=0;
	//.........................
	UART_init();
	TWI_init();
	EEPROM_init();
	SET_BIT(DDRA,PA0);
	CLEAR_BIT(PORTA,PA0);  // el awl el motor b zero...
	SET_BIT(DDRA,PA1);
	CLEAR_BIT(PORTA,PA1);    // el awl el motor b zero.........
	SET_BIT(DDRB,PB0);
	CLEAR_BIT(PORTB,PB0);   //  el awl el LED b zero...........


     EEPROM_readByte(0x0111,&fourth);

     if(fourth != 1)
     {
         UART_sendByte(0);
	   read1=UART_recieveByte();
	   read2=UART_recieveByte();
	   read3=UART_recieveByte();
	   read4=UART_recieveByte();
	  read5=UART_recieveByte();
	  read6=UART_recieveByte();
	 read7=UART_recieveByte();
	 read8=UART_recieveByte();
	 read9=UART_recieveByte();
	 read10=UART_recieveByte();



	if((read1==read6) &&(read2==read7)&&(read3==read8)&&(read4==read9)&&(read5==read10))  // lw sa7 lazm h5zn el password f el eeprom w lw 3'alat lazm arg3lo zero 34an ytla3 3ala el LCD error w y5leh yd5l el password tany..........
	{
		UART_sendByte(1);
		EEPROM_writeByte(0x0111,1); // lazm a7ot 1 b2a f el eeprom 34an myge4 hena tany...
		_delay_ms(10);
		EEPROM_writeByte(0x0311,read6);
		_delay_ms(10);                       // a7a mtnsa4 el delay :( ...............
		EEPROM_writeByte(0x0322,read7);
		_delay_ms(10);
		EEPROM_writeByte(0x0333,read8);
		_delay_ms(10);
		EEPROM_writeByte(0x0344,read9);
		_delay_ms(10);
		EEPROM_writeByte(0x0355,read10);
		_delay_ms(10);

	}
	else
		UART_sendByte(0);
      }
     else
	  UART_sendByte(1); // dy el byte el micro1 mstneha mn el awl 5als lw el fourth b 1...ya y5o4 3ala el options 3alatol....


	while(1)
	{
		  EEPROM_writeByte(0x0111,1);
		  option = UART_recieveByte();
		  /*
		  EEPROM_readByte(0x0311,&prom1);
		  EEPROM_readByte(0x0322,&prom2);
		  EEPROM_readByte(0x0333,&prom3);
		  EEPROM_readByte(0x0344,&prom4);
		  EEPROM_readByte(0x0355,&prom5);*/
		  if(option==45)  // open door..
		  {
			  EEPROM_readByte(0x0311,&prom1);
			  EEPROM_readByte(0x0322,&prom2);
			  EEPROM_readByte(0x0333,&prom3);
			  EEPROM_readByte(0x0344,&prom4);
			  EEPROM_readByte(0x0355,&prom5);
	          read11 = UART_recieveByte();
	          read12 = UART_recieveByte();
	          read13 = UART_recieveByte();
			  read14 = UART_recieveByte();
			  read15 = UART_recieveByte();

			  if((read11 == prom1)&&(read12 == prom2)&&(read13==prom3)&&(read14==prom4)&&(read15==prom5))
			  {
			  // el awl halef el motor 15 seconds clockwise...     ?!?!?!?!?!??! ana el awl garabt mn 3'er timer bl delay :D
			  UART_sendByte(1);
      		  timer1_func();
              while(flag == 0){
			  CLEAR_BIT(PORTA,PA0);
			  SET_BIT(PORTA,PA1);}
              flag = 0;
			  // b3dha halef el motor 15 seconds anticlockwise...
              timer1_func();
              while(flag==0){
			  SET_BIT(PORTA,PA0);
			  CLEAR_BIT(PORTA,PA1);}
              flag=0;
			  CLEAR_BIT(PORTA,PA0);
			  CLEAR_BIT(PORTA,PA1);
			  }
			  else
			  {
				  UART_sendByte(0);      // lw da5al el password 3'lt............
				  EEPROM_readByte(0x0311,&prom1);
				  EEPROM_readByte(0x0322,&prom2);
				  EEPROM_readByte(0x0333,&prom3);
				  EEPROM_readByte(0x0344,&prom4);
				  EEPROM_readByte(0x0355,&prom5);
		          read11 = UART_recieveByte();
		          read12 = UART_recieveByte();
		          read13 = UART_recieveByte();
				  read14 = UART_recieveByte();
				  read15= UART_recieveByte();
				  if((read11 == prom1)&&(read12 == prom2)&&(read13==prom3)&&(read14==prom4)&&(read15==prom5))  // lw d5lo sa7 b3d ma d5lo 3'alat awl mara..........
				  {
				  // el awl halef el motor 15 seconds clockwise...     ?!?!?!?!?!??! ana el awl garabt mn 3'er timer bl delay :D
				  UART_sendByte(1);
	     		  timer1_func();
	              while(flag == 0){
				  CLEAR_BIT(PORTA,PA0);
				  SET_BIT(PORTA,PA1);}
	              flag = 0;
				  // b3dha halef el motor 15 seconds anticlockwise...
	              timer1_func();
	              while(flag==0){
				  SET_BIT(PORTA,PA0);
				  CLEAR_BIT(PORTA,PA1);}
	              flag=0;
				  CLEAR_BIT(PORTA,PA0);
				  CLEAR_BIT(PORTA,PA1);
				  }
				  else
				  {
					  UART_sendByte(0);      // lw da5al el password 3'lt............
					  EEPROM_readByte(0x0311,&prom1);
					  EEPROM_readByte(0x0322,&prom2);
					  EEPROM_readByte(0x0333,&prom3);
					  EEPROM_readByte(0x0344,&prom4);
					  EEPROM_readByte(0x0355,&prom5);
			          read11 = UART_recieveByte();
			          read12 = UART_recieveByte();
			          read13 = UART_recieveByte();
					  read14 = UART_recieveByte();
					  read15= UART_recieveByte();
					  if((read11 == prom1)&&(read12 == prom2)&&(read13==prom3)&&(read14==prom4)&&(read15==prom5))  // lw d5lo sa7 b3d ma d5lo 3'alat awl mara..........
					  {
					  // el awl halef el motor 15 seconds clockwise...     ?!?!?!?!?!??! ana el awl garabt mn 3'er timer bl delay :D
					  UART_sendByte(1);
		     		  timer1_func();
		              while(flag == 0){
					  CLEAR_BIT(PORTA,PA0);
					  SET_BIT(PORTA,PA1);}
		              flag = 0;
					  // b3dha halef el motor 15 seconds anticlockwise...
		              timer1_func();
		              while(flag==0){
					  SET_BIT(PORTA,PA0);
					  CLEAR_BIT(PORTA,PA1);}
		              flag=0;
					  CLEAR_BIT(PORTA,PA0);
					  CLEAR_BIT(PORTA,PA1);
					  }
					  else        // lw d5lo 3'alat talet mara..................
					   {
					  	  UART_sendByte(0);
					  	  SET_BIT(PORTB,PB0);

					    }
				  }


			  }

		  }
		  else if(option==43)   // change password.....
		  {
			  EEPROM_readByte(0x0311,&prom1);
			  EEPROM_readByte(0x0322,&prom2);
			  EEPROM_readByte(0x0333,&prom3);
			  EEPROM_readByte(0x0344,&prom4);
			  EEPROM_readByte(0x0355,&prom5);
			 read11=UART_recieveByte();
			 read12=UART_recieveByte();
			 read13=UART_recieveByte();
			 read14=UART_recieveByte();
			 read15=UART_recieveByte();
            if((read11 == prom1) && (read12==prom2)&&(read13==prom3)&&(read14==prom4)&&(read15==prom5))
            {
            	EEPROM_writeByte(0x0111,0);
            	_delay_ms(10);
            	UART_sendByte(1); // tamam ... da5al b2a el new password.....
                main();
            }
            else
            {// da lw el password el d5lo 3'alat lama 7ab y3ml change password.............
           UART_sendByte(0);
		  read11 =UART_recieveByte();
		  read12 =UART_recieveByte();
		  read13 =UART_recieveByte();
		  read14 =UART_recieveByte();
		  read15 =UART_recieveByte();
		  if((read11 == prom1) && (read12==prom2)&&(read13==prom3)&&(read14==prom4)&&(read15==prom5))
		  {
			  EEPROM_writeByte(0x0111,0);
			  _delay_ms(10);
			   UART_sendByte(0);
			   main();
		  }
		  else   // da5al el password tany 3'lt ......
		  {
	          UART_sendByte(0);
			  read11 =UART_recieveByte();
			  read12 =UART_recieveByte();
			  read13 =UART_recieveByte();
			  read14 =UART_recieveByte();
			  read15 =UART_recieveByte();
			  if((read11 == prom1) && (read12==prom2)&&(read13==prom3)&&(read14==prom4)&&(read15==prom5))
			  {
				  EEPROM_writeByte(0x0111,0);
				  _delay_ms(10);
				   UART_sendByte(1);
				   main();
			  }
			  else
			  {  // lw da5al el password 3'alat talet mara .... kda howa 7aramy ......
				  UART_sendByte(0);         // yb3at 1 lw howa 7aramy ..............
				  SET_BIT(PORTB,PB0);
			  }
		  }   // dy bta3t el else lw da5al el password tany mara 3'lt bardo ...

		 }   // awl mara 3'lt....
	 } // if read2 == 43
	}  // while (1)

} // main func....


