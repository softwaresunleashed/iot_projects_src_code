/*
=================================================================================
 Name        : pcd8544_rpi.c
 Version     : 0.1

 Copyright (C) 2012 by Andre Wussow, 2012, desk@binerry.de

 Description :
     A simple PCD8544 LCD (Nokia3310/5110) for Raspberry Pi for displaying some system informations.
	 Makes use of WiringPI-library of Gordon Henderson (https://projects.drogon.net/raspberry-pi/wiringpi/)

	 Recommended connection (http://www.raspberrypi.org/archives/384):
	 LCD pins      Raspberry Pi
	 LCD1 - GND    P06  - GND
	 LCD2 - VCC    P01 - 3.3V
	 LCD3 - CLK    P11 - GPIO0
	 LCD4 - Din    P12 - GPIO1
	 LCD5 - D/C    P13 - GPIO2
	 LCD6 - CS     P15 - GPIO3
	 LCD7 - RST    P16 - GPIO4
	 LCD8 - LED    P01 - 3.3V 

================================================================================
This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.
================================================================================
 */
#include <wiringPi.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/sysinfo.h>
#include "PCD8544.h"

// pin setup
int _din = 1;
int _sclk = 0;
int _dc = 2;
int _rst = 4;
int _cs = 3;
  
// lcd contrast 
//may be need modify to fit your screen!  normal: 30- 90 ,default is:45 !!!maybe modify this value!
int contrast = 60;  
  
int main (void)
{
  // print infos
  printf("Raspberry Pi PCD8544 sysinfo display\n");
  printf("========================================\n");
  
  // check wiringPi setup
  if (wiringPiSetup() == -1)
  {
	printf("wiringPi-Error\n");
    exit(1);
  }
  
  // init and clear lcd
  LCDInit(_sclk, _din, _dc, _cs, _rst, contrast);
  LCDclear();
  
  // show logo
  LCDshowLogo();
  
  delay(5000);
  
  for (;;)
  {
	  // clear lcd
	  LCDclear();
	  
	  // get system usage / info
	  struct sysinfo sys_info;
	  if(sysinfo(&sys_info) != 0)
	  {
		printf("sysinfo-Error\n");
	  }
	  
	  // uptime
	  char uptimeInfo1[15];
      char uptimeInfo2[15];
	  unsigned long uptime = sys_info.uptime / 60;
      unsigned long days = uptime / 60 / 24;
      unsigned long hours = (uptime / 60) % 60 % 24;
      unsigned long minutes = uptime % 60;
      snprintf(uptimeInfo1, sizeof(uptimeInfo1),
               "Uptime %03ld dys", days);
      snprintf(uptimeInfo2, sizeof(uptimeInfo2),
               "%02ld hrs %02ld mns", hours, minutes);
	  
	  // cpu info
	  char cpuInfo[15]; 
	  snprintf(cpuInfo, sizeof(cpuInfo), 
               "CPU load %.2f", ((float)sys_info.loads[0])/(1<<SI_LOAD_SHIFT));
	  
	  // ram info
	  char ramInfo[15]; 
	  unsigned long totalRam = sys_info.freeram / 1024 / 1024;
	  snprintf(ramInfo, sizeof(ramInfo), 
               "RAM %ld MB", totalRam);

      // other
      char other[15];
      snprintf(other, sizeof(other),
               "Procs %ld", sys_info.procs);
	  
	  // build screen
      LCDdrawstring(0, 0, uptimeInfo1);
	  LCDdrawstring(0, 8, uptimeInfo2);
      LCDdrawstring(0, 16, cpuInfo);
	  LCDdrawstring(0, 24, ramInfo);
	  LCDdrawstring(0, 32, other);
      LCDdrawstring(0, 40, "");
	  LCDdisplay();
	  
	  delay(1000);
  }
  
    //for (;;){
  //  printf("LED On\n");
  //  digitalWrite(pin, 1);
  //  delay(250);
  //  printf("LED Off\n");
  //  digitalWrite(pin, 0);
  //  delay(250);
  //}

  return 0;
}
