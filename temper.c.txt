#include <wiringPi.h>
#include <lcd.h>
#include <wiringPiI2C.h>

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <net/if.h>
#include <unistd.h>
#include <arpa/inet.h>

int main(void){
        int lcd;
        wiringPiSetup();
        lcd = lcdInit(2,16,4,25,24,23,22,21,14,0,0,0,0);
        int n;
        struct ifreq ifr;

	//get ip address
        n = socket(AF_INET, SOCK_DGRAM, 0);
        ifr.ifr_addr.sa_family = AF_INET;
        strncpy(ifr.ifr_name, "wlan0", IFNAMSIZ-1);
        ioctl(n, SIOCGIFADDR, &ifr);
        close(n);

	//print ip address
        lcdClear(lcd);
        lcdPosition(lcd, 0, 0);
        lcdPuts(lcd, ("%s\n", inet_ntoa(((struct sockaddr_in *)&ifr.ifr_addr)-$

        lcdPosition(lcd, 0, 1);
        lcdPuts(lcd, "Temperature:");
        int fd = 0;
	//setup I2C and check if fails
        if((fd =  wiringPiI2CSetup(0x4a)) < 0){
                lcdPosition(lcd,0,1);
                lcdPuts(lcd, "failed wiringPiI2C setup");
        }

	//led
	pinMode(0, OUTPUT);

        int data = 0;
        int rpl = 0;
        char temp[3];
        while(1){
                //int temp = readTempInC(1, 0x4a);
                //rpl = wiringPiI2CWrite(fd,0x4a | 1);
		data = wiringPiI2CRead(fd);
                if((data & 0x80) != 0){         //if negative
                        data = data&0x7F;       //mask with 0111 1111
                        data = data-128;        //subtract most significant
                }
		//print temperature
		//(with spaces at end for clearing previous values)
                sprintf(temp, "%d ", data);
                printf("%s \n", temp);
                lcdPosition(lcd, 12, 1);
                lcdPuts(lcd, temp);
                
		//turn led on if temperature less than 20
		if(data < 20){
			digitalWrite(0, HIGH);
		}
		else{
			digitalWrite(0, LOW);
		}

		sleep(1);
        }
        return 0;
}