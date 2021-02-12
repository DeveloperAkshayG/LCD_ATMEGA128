#define F_CPU 8000000UL		/* Define CPU Frequency e.g. here its 8MHz */
#include <avr/io.h>		/* Include AVR std. library file */
#include <util/delay.h>		/* Include inbuilt defined Delay header file */

#define LCD_Data_Dir DDRC	/* Define LCD data port direction */
#define LCD_Command_Dir DDRE	/* Define LCD command port direction register */
#define LCD_Data_Port PORTC	/* Define LCD data port */
#define LCD_Command_Port PORTE	/* Define LCD data port */
#define RS PE4										//RS PIN
#define EN PE2										//ENABLE PIN
#define RW PE3										//READ-WRITE PIN
 
char first_column_position_for_lcd[4]={0,64,20,84};

void LCD_Command(unsigned char cmnd)
{
	LCD_Data_Port= cmnd;
	LCD_Command_Port &= ~(1<<RS);	/* RS=0 command reg. */
	LCD_Command_Port &= ~(1<<RW);	/* RW=0 Write operation */
	LCD_Command_Port |= (1<<EN);	/* Enable pulse */
	_delay_us(1);
	LCD_Command_Port &= ~(1<<EN);
	_delay_ms(2);
}

void LCD_Char (unsigned char char_data)  /* LCD data write function */
{
	LCD_Data_Port= char_data;
	LCD_Command_Port |= (1<<RS);	/* RS=1 Data reg. */
	LCD_Command_Port &= ~(1<<RW);	/* RW=0 write operation */
	LCD_Command_Port |= (1<<EN);	/* Enable Pulse */
	_delay_us(1);
	LCD_Command_Port &= ~(1<<EN);
	_delay_ms(2);			/* Data write delay */
}

void LCD_Init (void)			/* LCD Initialize function */
{
	LCD_Command_Dir = 0xFF;		/* Make LCD command port direction as o/p */
	LCD_Data_Dir = 0xFF;		/* Make LCD data port direction as o/p */
	_delay_ms(20);			/* LCD Power ON delay always >15ms */
	
	LCD_Command (0x38);		/* Initialization of 16X2 LCD in 8bit mode */
	LCD_Command (0x0C);		/* Display ON Cursor OFF */
	LCD_Command (0x06);		/* Auto Increment cursor */
	LCD_Command (0x01);		/* clear display */
	_delay_ms(2);			/* Clear display command delay> 1.63 ms */
	LCD_Command (0x80);		/* Cursor at home position */
}


void LCD_String (char *str)		/* Send string to LCD function */
{
	int i;
	for(i=0;str[i]!=0;i++)		/* Send each char of string till the NULL */
	{
		LCD_Char (str[i]);
	}
}

void LCD_String_xy (char row, char pos, char *str)  /* Send string to LCD with xy position */
{
	if (row == 0 && pos<16)
	LCD_Command((pos & 0x0F)|0x80);	/* Command of first row and required position<16 */
	else if (row == 1 && pos<16)
	LCD_Command((pos & 0x0F)|0xC0);	/* Command of first row and required position<16 */
	LCD_String(str);		/* Call LCD string function */
}

void LCD_Clear()
{
	LCD_Command (0x01);		/* clear display */
	LCD_Command (0x80);		/* cursor at home position */
}
 

void LCD_Custom_Char (unsigned char loc, unsigned char *msg)
{
	unsigned char i;
	if(loc<8)
	{
		LCD_Command (0x40 + (loc*8));	/* Command 0x40 and onwards forces the device to point CGRAM address */
		for(i=0;i<8;i++)	/* Write 8 byte for generation of 1 character */
		LCD_Char(msg[i]);
	}
}

void goto_lcd_location(uint8_t x,uint8_t y)
{
	LCD_Command(0x80 + first_column_position_for_lcd[y-1] + (x-1));
}


int main()
{
	char i;
	
	
	unsigned char Character1[8] = { 0X04, 0X0E, 0X0E, 0X0E, 0X1F, 0X00, 0X04, 0X00 }; //BELL
	unsigned char Character2[8] = { 0x04, 0x04, 0x15, 0x15, 0x0E, 0x04, 0x00, 0x00 }; //ARROW
	unsigned char Character3[8] = { 0x1f, 0x0a, 0x0a, 0x1e, 0x1a, 0x02, 0x00, 0x00 }; //marathi letter

	LCD_Init();
	
	
	LCD_Custom_Char(0, Character1);  // Build Character1 at position 0 
	LCD_Custom_Char(1, Character2);  // Build Character2 at position 0 
	LCD_Custom_Char(2, Character3);  // Build Character3 at position 0 
	
	LCD_Command(0x80);		/*cursor at home position */
//	LCD_String_xy(0,5,"NETEL");
//	LCD_Command(0xc0);
	
	//LCD_Char(5);
	for(i=0;i<3;i++)		// function will send data 1 to 8 to lcd 
	{
		if (i==2);
		{
			goto_lcd_location(0,6);
			LCD_Char(i);		// char at 'i'th position will display on lcd 
		//	LCD_Char(' ');		// space between each custom char. 
		}
	}
//	while(1);
}