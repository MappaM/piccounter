#include <htc.h>
#include <stdio.h>
#include "lcd.h"
#include <eeprom_routines.h> 
#define _XTAL_FREQ 4000000
__CONFIG(
FOSC_INTOSCIO &
WDTE_OFF &
PWRTE_OFF&
BOREN_OFF&
MCLRE_OFF&
LVP_OFF&
CP_OFF&
CPD_OFF);

void
main(void)
{
TRISA = 0;
TRISB = 0;
CMCON = 7;
RA3 = 0;

	lcd_init();
	RA7 = 1;	

	int day = eeprom_read(0x0);
	int hour = eeprom_read(0x1);
	int min = eeprom_read(0x2);
	int sec = eeprom_read(0x3);
	int cen = eeprom_read(0x4);

	__delay_ms(8);

	int i = 0;
	while (1) {
		if (cen ==0) {
			cen = 9;			
			if (sec == 0) {
				sec = 59;
				if (min == 0) {
					min = 59;
					if (hour ==0) {
						hour = 23;
						day--;
						
					}
					else hour--;
				} else
					min--;
			} else
				sec--;
		} else
			cen--;
	

		lcd_home();

		char buf [16];
		if ((day > -1) && ((sec % 10) != 0)) {
			if ((sec % 2) == 1)
				RA7 = 1;
			else
				RA7 = 0;
			sprintf(buf,"%3dj %02d:%02d:%02d:%01d",day,hour,min,sec,cen);
		} else {
			RA7 = 1;
			sprintf(buf,"   I <3 FEDE    ");			
		}

		lcd_puts(buf);
		lcd_goto(0x40);
		lcd_puts(&buf[8]);

		__delay_ms(85);
	}
}


