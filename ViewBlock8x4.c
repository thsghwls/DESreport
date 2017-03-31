/*
 * ViewBlock8x4.c
 *
 *  Created on: 2017. 3. 30.
 *      Author: ÄÄÇ»ÅÍ
 */

#include "DES.h"

void viewBlock8x4 (WORD data) {
	int i;
	WORD mask;
	WORD temp;
	printf(">>  %x  <<\n" , data);
	puts(" =====================");
	for(i = 31 ; i >= 0 ; i--) {
		temp = 0;
		mask = 0x00000001 << i;
		temp = mask & data;
		temp = temp>> i;

		if(i!=31&&(i+1)%4==0)
			puts("");
		printf(" %d ", temp);
	}
	puts("\n =====================");
	puts("");
}
