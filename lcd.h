#ifndef lcd
#define lcd

#define F_CPU 8000000UL   //CPU FREQUENCY 8MHZ
#include<avr/io.h>
#include<util/delay.h>


#define LCD_Command_Dir DDRE						//LCD COMMAND PORT
#define LCD_Command_Port PORTE						//LCD COMMAND PORT
#define LCD_Data_Dir DDRC							//LCD DATA PORT
#define LCD_Data_Port PORTC							//LCD DATA PORT
#define RS PE4										//RS PIN
#define EN PE2										//ENABLE PIN
#define RW PE3										//READ-WRITE PIN

void LCD_Init(void);								//function to initialize lcd
void LCD_Clear(void);								//function to clear lcd display lcd
void LCD_Command(unsigned char cmnd);				//function to send command
void LCD_Char (unsigned char char_data);			//function to write data  
void LCD_String (char *str);						//function to display data on lcd
void LCD_String_xy (char row, char pos, char *str); //function to write data at particular row and column of lcd

#endif
