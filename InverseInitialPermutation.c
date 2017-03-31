/*
 * InverseInitialPermutation.c
 *
 *  Created on: 2017. 3. 30.
 *      Author: ÄÄÇ»ÅÍ
 */

#include "DES.h"

BIT IIP[] = {40, 8, 48, 16, 56, 24, 64, 32,
		39, 7, 47, 15, 55, 23, 63, 31,
		38, 6, 46, 14, 54, 22, 62, 30,
		37, 5, 45, 13, 53, 21, 61, 29,
		36, 4, 44, 12, 52, 20, 60, 28,
		35, 3, 43, 11, 51, 19, 59, 27,
		34, 2, 42, 10, 50, 18, 58, 26,
		33, 1, 41, 9, 49, 17, 57, 25};


void InverseInitialPermutation(WORD *Data)
{
	int i;
	WORD tmpMask;
	WORD setMask;
	WORD NewData[2]= {0, };
	for(i = 31 ;i >= 0 ; i--)
	{
		tmpMask = 0x00000001;
		setMask = 0x00000001<<(31-i);
		if((IIP[i] <= 32) && (Data[1] & (tmpMask << (32-IIP[i])))) {
			NewData[1] = NewData[1] | setMask;
		}else if((IIP[i] > 32) && (Data[0] & (tmpMask << (64-IIP[i])))) {
			NewData[1] = NewData[1] | setMask;
		}
	}
	for(i = 63 ; i >=32 ; i--)
	{
		tmpMask = 0x00000001;
		setMask = 0x00000001<<(63-i);
		if((IIP[i] <= 32) && (Data[1] & (tmpMask << (32-IIP[i])))) {
			NewData[0] = NewData[0] | setMask;
		}else if((IIP[i] > 32) && (Data[0] & (tmpMask << (64-IIP[i])))) {
			NewData[0] = NewData[0] | setMask;
		}
	}
	Data[1] = NewData[1];
	Data[0] = NewData[0];
}
