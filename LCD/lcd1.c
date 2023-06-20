#include <wiringPiI2C.h>
#include <wiringPi.h>
#include <stdlib.h>
#include <stdio.h>

#define I2C_ADDR	0x27

#define LCD_CHR	1
#define LCD_CMD	0

#define LINE1	0x80
#define LINE2	0xC0

#define LCD_BACKLIGHT	0x0b
#define ENABLE 0b00000100

void lcd_init(void);
void lcd_byte(int bits, int mode);
void lcd_toggle_enable(int bits);
void typeInt(int i);
void typeFloat(float myFloat);
void lcdLoc(int line);
void ClrLcd(void);
void typeln(const char *s);
void typeChar(char val);
int fd;


int main() {
	if (wiringPiSetup() == -1) exit(1);

	fd = wiringPiI2CSetup(I2C_ADDR);

	lcd_init();

	char array1[] = "Hello World!";

	while(1) 
	{
		lcdLoc(LINE1);
		typeln("Using wiringPi");
		lcdLoc(LINE2);
		typeln("Geany editor.");

		delay(2000);
		ClrLcd();
		lcdLoc(LINE1);
		typeln("l2c programmed");
		lcdLoc(LINE2);
		typeln("in C not Python.");

		delay(2000);
		ClrLcd();
		lcdLoc(LINE1);
		typeln("Arduino like");
		lcdLoc(LINE2);
		typeln("fast and easy.");
		
		delay(2000);
		ClrLcd();
		lcdLoc(LINE1);
		typeln(array1);
		
		delay(2000);
		ClrLcd();
		typeln("Int ");
		int value = 20125;
		typeInt(value);
		
		delay(2000);
		lcdLoc(LINE2);
		typeln("Float ");
		float FloatVal = 10045.25989;
		typeFloat(FloatVal);
		delay(2000);

	}
	return 0;
}

void typeFloat(float myFloat) {
	char buffer[20];
	sprintf(buffer, "%4.2f", myFloat);
	typeln(buffer);
}

void typeInt(int i) {
	char array1[20];
	sprintf(array1, "%d", i);
	typeln(array1);
}

void ClrLcd(void) {
	lcd_byte(0x01, LCD_CMD);
	lcd_byte(0x02, LCD_CMD);
}

void lcdLoc(int line) {
	lcd_byte(line, LCD_CMD);
}

void typeChar(char val) {
	lcd_byte(val, LCD_CHR);
}

void typeln(const char *s) {
	while ( *s ) lcd_byte(*(s++), LCD_CHR);
}

void lcd_byte(int bits, int mode) {
	int bits_high;
	int bits_low;
	bits_high = mode | (bits & 0xF0) | LCD_BACKLIGHT ;
	bits_low = mode | ((bits << 4) & 0xF0) | LCD_BACKLIGHT ;
	wiringPiI2CReadReg8(fd, bits_high);
	lcd_toggle_enable(bits_high);
	wiringPiI2CReadReg8(fd, bits_low);
	lcd_toggle_enable(bits_low);
}

void lcd_toggle_enable(int bits) {
	delayMicroseconds(500);
	wiringPiI2CReadReg8(fd, (bits | ENABLE));
	delayMicroseconds(500);
	wiringPiI2CReadReg8(fd, (bits & ~ENABLE));
	delayMicroseconds(500);
}

void lcd_init() {
	lcd_byte(0x33, LCD_CMD); 
	lcd_byte(0x32, LCD_CMD); 
	lcd_byte(0x06, LCD_CMD); 
	lcd_byte(0x0C, LCD_CMD); 
	lcd_byte(0x28, LCD_CMD);
	lcd_byte(0x01, LCD_CMD); 
	delayMicroseconds(500);
}


