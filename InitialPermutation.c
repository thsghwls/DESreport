/*
 * InitialPermutation.c
 *
 *  Created on: 2017. 3. 30.
 *      Author: ÄÄÇ»ÅÍ
 */

#include "DES.h"

BIT IP[] = {58, 50, 42, 34, 26, 18, 10, 2,
		60, 52, 44, 36, 28, 20, 12, 4,
		62, 54, 46, 38, 30, 22, 14, 6,
		64, 56, 48, 40, 32, 24, 16, 8,
		57, 49, 41, 33, 25, 17,  9, 1,
		59, 51, 43, 35, 27, 19, 11, 3,
		61, 53, 45, 37, 29, 21, 13, 5,
		63, 55, 47, 39, 31, 23, 15, 7};

void InitialPermutation(WORD *Data)
{
	int i;
	WORD tmpMask;
	WORD setMask;
	WORD NewData[2]= {0, };
	for(i = 31; i >= 0; i--)
	{
		tmpMask = 0x00000001;
		setMask = 0x00000001<<(31-i);
		if((IP[i] <= 32) && (Data[1] & (tmpMask << (32-IP[i])))) {
			NewData[1] = NewData[1] | setMask;
		}else if((IP[i] > 32) && (Data[0] & (tmpMask << (64-IP[i])))){
			NewData[1] = NewData[1] | setMask;
		}
	}
	for(i = 63 ; i >=32 ; i--)
	{
		tmpMask = 0x00000001;
		setMask = 0x00000001<<(63-i);
		if((IP[i] <= 32) && (Data[1] & (tmpMask << (32-IP[i])))) {
			NewData[0] = NewData[0] | setMask;
		}else if((IP[i] > 32) && (Data[0] & (tmpMask << (64-IP[i])))) {
			NewData[0] = NewData[0] | setMask;
		}
	}
	Data[1] = NewData[1];
	Data[0] = NewData[0];
}
