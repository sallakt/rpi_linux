#include <wiringPi.h>
#include <lcd.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <net/if.h>
#include <unistd.h>
#include <arpa/inet.h>

int main(){
	int lcd;
	wiringPiSetup();
	lcd = lcdInit(2,16,4,25,24,23,22,21,14,0,0,0,0);
	int n;
	struct ifreq ifr;

	n = socket(AF_INET, SOCK_DGRAM, 0);
	ifr.ifr_addr.sa_family = AF_INET;
	strncpy(ifr.ifr_name, "wlan0", IFNAMSIZ-1);
	ioctl(n, SIOCGIFADDR, &ifr);
	close(n);

	lcdPrintf(lcd, ("%s\n", inet_ntoa(((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr)));
	return 0;
}
