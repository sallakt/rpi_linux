#include <wiringPi.h>
#include <lcd.h>

int main(void){
	int lcd;
	wiringPiSetup();
	lcd = lcdInit(2,16,4,25,24,23,22,21,14,0,0,0,0);
	lcdPuts(lcd, "Hello World!");
	return 0;
}
