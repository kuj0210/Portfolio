#include <wiringPi.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <fcntl.h>
#include <unistd.h>
#include "pi.h"

#define DHTPIN 7
#define MAXTIMING 83

time_t time_sensor;
char temp_time[MAXLINE];
char timestring[MAXLINE];
int flag = 0;
int dht11_dat[5] = {0};

void read_dht11_dat();
void getargs_pi(char hostname[], int *port, char *filename, int *time_pi);
void clientSend(int fd, char *filename, char *body);
void userTask(char *myname, char *hostname, int port, char *filename, int first, int second);

int main()
{
	int time_pi, port, time = 1000;
	char filename[MAXLINE], hostname[MAXLINE];
	
	getargs_pi(hostname, &port, filename, &time_pi);


	printf("dht11 Raspberry pi temperature and humidity test\n");

	if(wiringPiSetup() == -1) {
		printf("wiring Pi setup faill\n");
		exit(1);
	}

	while(1){
		read_dht11_dat();
		if(flag)
		{
			/*qurey create temperature*/
			printf("\n");
			userTask("temperature", hostname, port, filename, 2, 3);

			delay(time * (time_pi / 2)); //Wait period / 2

			/*query create humidity*/
			
			userTask("humidity", hostname, port, filename, 0, 1);

			delay(time * (time_pi / 2)); // Wait period / 2
		}
		else
			delay(time);
	}
	return 0;
}

void clientSend(int fd, char *filename, char *body)
{
	char buf[MAXLINE];
	char hostname[MAXLINE];

	Gethostname(hostname, MAXLINE);
	
	sprintf(buf,"POST %s HTTP/1.1\n", filename);
	sprintf(buf, "%sHost: %s\n",buf, hostname);
	sprintf(buf, "%sContent-Type: Text/plain: charset=utf-8\n",buf);
	sprintf(buf, "%sContent-Length: %d\n\r\n",buf, strlen(body));
	sprintf(buf, "%s%s\n",buf, body);
	

	Rio_writen(fd, buf, strlen(buf));
}

void userTask(char *myname, char *hostname, int port, char *filename, int first, int second)
{
	int clientfd;
	char query[MAXLINE];

	sprintf(query, "name=%s&", myname);
	sprintf(query, "%stime=%s&",query, timestring);
	sprintf(query, "%svalue=%d.%d",query, dht11_dat[first],dht11_dat[second]);
	printf("%s\n\n",query);
	
	clientfd = Open_clientfd(hostname, port);
	clientSend(clientfd, filename, query);
	Close(clientfd);
}


void getargs_pi(char hostname[], int *port, char *filename, int *time_pi)
{
	FILE *fp;
	int i;
	
	fp = fopen("config-pi.txt", "r");
	if(fp == NULL){
		printf("config-pi.txt file is not open\n\n");
		exit(0);
	}
	fscanf(fp, "%s", hostname);
	fscanf(fp, "%d", port);
	fscanf(fp, "%s", filename);
	fscanf(fp, "%d", time_pi);
	
	fclose(fp);
}

void read_dht11_dat()
{
	uint8_t laststate = HIGH;
	uint8_t counter = 0;
	uint8_t j = 0, i;
	int z, time_len;
	float f;
	
	dht11_dat[0] = dht11_dat[1] = dht11_dat[2] = dht11_dat[3] = dht11_dat[4] = 0;

	pinMode(DHTPIN, OUTPUT);
	digitalWrite(DHTPIN, LOW);
	delay(18);

	digitalWrite(DHTPIN, HIGH);
	delayMicroseconds(30);
	pinMode(DHTPIN, INPUT);

	for(i = 0; i < MAXTIMING; i++){
		counter = 0;
		while(digitalRead(DHTPIN) == laststate){
			counter++;
			delayMicroseconds(1);
			if(counter == 255) break;
		}

		laststate = digitalRead(DHTPIN);

		if(counter == 255) { break; }

		if( (i >= 4) && ((i % 2) == 0) ){
			dht11_dat[j / 8] <<= 1;
			if(counter > 20) { dht11_dat[j / 8] |= 1; }
			j++;
		}
	}

	if( (j >= 40) && (dht11_dat[4] == ((dht11_dat[0] + dht11_dat[1] + dht11_dat[2] + dht11_dat[3]) & 0xff) ) )
	{
		time(&time_sensor);
		strcpy(temp_time,ctime(&time_sensor));
		time_len = strlen(temp_time);
		for(z = 0; z < time_len - 1; z++)
		{
			timestring[z] = temp_time[z];
		}
		f= dht11_dat[2] * 9./5. +32;
		printf("humidity = %d.%d %% Temperature = %d.%d *C (%.1f F) \n",dht11_dat[0], dht11_dat[1], dht11_dat[2], dht11_dat[3], f);
		flag = 1;
	}
	else { printf("Data get failed\n"); flag = 0; }
}






