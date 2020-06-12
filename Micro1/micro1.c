

#include "keypad.h"
#include "lcd.h"
#include "uart.h"

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
	SREG |= (1<<7);  // Enable global interrupts in MC.
	uint8 second;
	uint8 door1;  // el hy3mlo display ll door will open w door will close..............
	uint8 read1;  // el ha2ra beh el password f el awl 5ales....
	//.........................
	uint8 status; // el h4of el 2 passwords el d5lhom f el awl dol zay b3d wla la2....
	uint8 read2; // el hy5tar beh howa 3ayz y3ml eih change pass wla opem door...
	uint8 read3;  // el h2ra beha el pass lama yb2a 3ayz y3ml open door aw y-change password............
	uint8 read4; // lw da5al el password 3'lt (fe case el change password)....
	uint8 last_chance;  // lw 3'alat el password el mara dy kman h43'l el buzzer........
	uint8 last_chance2; // a5er mara y3'lat f el password b2a .. el hya el mara el talta ...
	UART_init();
	LCD_init();
	LCD_clearScreen();

	second = UART_recieveByte();
	if(second == 0)
	 {

	// awl mara ...................................
	LCD_displayString("enter new pass");
	LCD_goToRowColumn(1,0);

	for(int i=0;i<5;i++)
	{
		read1 = KeyPad_getPressedKey();
		LCD_displayCharacter('*');
		UART_sendByte(read1);
		_delay_ms(500);
	}



		// tany mara..........................
			LCD_clearScreen();
			LCD_goToRowColumn(0,0);
			LCD_displayString("re-enter pass");
			LCD_goToRowColumn(1,0);
	for(int i=0;i<5;i++)
	{
		read1 = KeyPad_getPressedKey();
		LCD_displayCharacter('*');
		UART_sendByte(read1);
		_delay_ms(500);
	}


	status = UART_recieveByte();
    if(status != 1)
    {
    	 LCD_clearScreen();
    	 LCD_goToRowColumn(0,0);
    	 LCD_displayString("pass is wrong");
    	 _delay_ms(500);
         main();
    }
 }



	while(1)
	{
		LCD_clearScreen();
		LCD_goToRowColumn(0,0);
		LCD_displayString("+ : change pass");
		LCD_goToRowColumn(1,0);
		LCD_displayString("- : open door");
        read2 = KeyPad_getPressedKey();                      // ezay h5leh yrg3 l awl el main tany ????????!?!?!?!?!?

        if (read2 == 45)   // open door....
        {
        	UART_sendByte(45);
        	LCD_clearScreen();
        	LCD_goToRowColumn(0,0);
        	LCD_displayString("enter pass");
        	LCD_goToRowColumn(1,0);
        	for(int z=0;z<5;z++)
        	{
        	read3 = KeyPad_getPressedKey();
        	LCD_displayCharacter('*');
        	UART_sendByte(read3);
        	_delay_ms(500);  // da el delay bta3 el dosa bta3t el keypad.............
        	}
        	door1 = UART_recieveByte();
        	if(door1 == 1)                         // lw el password el d5lo sa7 hfta7 el door...
        	{
        		LCD_clearScreen();
        		LCD_displayString("door is opening");
        		timer1_func();
        		while(flag==0){}
        		flag=0;
        		LCD_clearScreen();
        		LCD_displayString("door is closing");
        		timer1_func();
        		while(flag==0){}
        		flag=0;
        	}
        	else                             // lw el password el d5lo 3'alat h5leh yd5l el pass tany w l2 d5lo 3'alat y3ml buzzer...
        	{
            	LCD_clearScreen();
            	LCD_goToRowColumn(0,0);
            	LCD_displayString("pass is wrong");
            	_delay_ms(1000);
            	LCD_clearScreen();
            	LCD_goToRowColumn(0,0);
            	LCD_displayString("enter again");
            	LCD_goToRowColumn(1,0);
            	for(int z=0;z<5;z++)
            	{
            	read3 = KeyPad_getPressedKey();
            	LCD_displayCharacter('*');
            	UART_sendByte(read3);
            	_delay_ms(500);
            	}

            last_chance = UART_recieveByte();
            if(last_chance == 1)
            {
        		LCD_clearScreen();
        		LCD_displayString("door is opening");
        		timer1_func();
        		while(flag==0){}
        		flag=0;
        		LCD_clearScreen();
        		LCD_displayString("door is closing");
        		timer1_func();
        		while(flag==0){}
        		flag=0;
            }
        		else
        		{
                	LCD_clearScreen();
                	LCD_goToRowColumn(0,0);
                	LCD_displayString("pass is wrong");
                	_delay_ms(1000);
                	LCD_clearScreen();
                	LCD_goToRowColumn(0,0);
                	LCD_displayString("enter again");
                	LCD_goToRowColumn(1,0);
                	for(int z=0;z<5;z++)
                	{
                	read3 = KeyPad_getPressedKey();
                	LCD_displayCharacter('*');
                	UART_sendByte(read3);
                	_delay_ms(500);
                	}

                last_chance2 = UART_recieveByte();
                if(last_chance2 == 1)
                {
            		LCD_clearScreen();
            		LCD_displayString("door is opening");
            		timer1_func();
            		while(flag==0){}
            		flag=0;
            		LCD_clearScreen();
            		LCD_displayString("door is closing");
            		timer1_func();
            		while(flag==0){}
            		flag=0;
                }
                else
		           {
                while(1)
            	{
            		LCD_clearScreen();
            	}
        		   }
        		}  // bta3et el else el hya lw da5al el password 3'lt tany mara....
            }  // bta3et el else el hya lw da5al el password 3'lt awl mara....



        }  // lw read2 == 45 (open the door).........

        else if(read2 == 43)        //change password...
        {

        	UART_sendByte(43);
        	LCD_clearScreen();
        	LCD_goToRowColumn(0,0);
        	LCD_displayString("enter old pass");
        	LCD_goToRowColumn(1,0);
        	for(int z=0;z<5;z++)
        	{
        	read3 = KeyPad_getPressedKey();
        	LCD_displayCharacter('*');
        	UART_sendByte(read3);
        	_delay_ms(500);       // da el delay bta3 el dosa bta3 el keypad ...................
        	}
        	read4 = UART_recieveByte();           // el old pass da sa7 wla la2 ...........
        	if(read4 == 1)
        	{
        		main();   // hbda2 mn el awl tany ....................
        	}
        	else              // da5al el password 3'lt lazm adelo forsa tanya .............
        	{
            	LCD_clearScreen();
            	LCD_goToRowColumn(0,0);
            	LCD_displayString("pass is wrong");
            	_delay_ms(1000);
            	LCD_clearScreen();
            	LCD_goToRowColumn(0,0);
            	LCD_displayString("enter again");
            	LCD_goToRowColumn(1,0);
            	for(int z=0;z<5;z++)
            	{
            	read3 = KeyPad_getPressedKey();
            	LCD_displayCharacter('*');
            	UART_sendByte(read3);
            	_delay_ms(500);
            	}

            last_chance = UART_recieveByte();
            if(last_chance == 1)
            {
            	main();
            }
            else    // da5al el password 3'alat tany mara ... lazm adelo forsa a5era....
            {
            LCD_clearScreen();
        	LCD_goToRowColumn(0,0);
        	LCD_displayString("pass is wrong");
        	_delay_ms(1000);
        	LCD_clearScreen();
        	LCD_goToRowColumn(0,0);
        	LCD_displayString("enter again");
        	LCD_goToRowColumn(1,0);
        	for(int z=0;z<5;z++)
        	{
        	read3 = KeyPad_getPressedKey();
        	LCD_displayCharacter('*');
        	UART_sendByte(read3);
        	_delay_ms(500);
        	}
        	last_chance2 = UART_recieveByte();
        	if(last_chance2 == 1)
        	{
        		main();
        	}
        	else
        	{  // lw da5al el password talet mara 3'alat ... y3ny 7aramy ....
        		 while(1)
        		          {
        		               LCD_clearScreen();
        		          }
        	}


        }  // da bta3 el else lama yd5al el password tany mara 3'lt

     }   // da bta3 el else lama yd5al el password awl mara 3'lt


   }  // if read2 == 43....



  }  // while(1)
}  // main function....
