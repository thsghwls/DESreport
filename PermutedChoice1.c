/*
 * PermutedChoice1.c
 *
 *  Created on: 2017. 3. 30.
 *      Author: ÄÄÇ»ÅÍ
 */

#include "DES.h"

BIT PC_1[]= {
		57, 49, 41, 33, 25, 17,  9,
		1, 58, 50, 42, 34, 26, 18,
		10,  2, 59, 51, 43, 35, 27,
		19, 11,  3, 60, 52, 44, 36,
		63, 55, 47, 39, 31, 23, 15,
		7, 62, 54, 46, 38, 30, 22,
		14,  6, 61, 53, 45, 37, 29,
		21, 13,  5, 28, 20, 12,  4
};

void PermutedChoice1(WORD *Key)
{
	int i;
	WORD tmpMask;
	WORD KeyMask;
	WORD NewKey[2]= {0,0 };
	tmpMask = 0x00000001;

	for( i = 0 ; i < 28 ; i++)
	{
		KeyMask = 0x08000000 >> i;

		if((PC_1[i] <= 32) && (Key[1] & (tmpMask << (32-PC_1[i])))) {
			NewKey[1] = NewKey[1] | KeyMask;
		}else if((PC_1[i] > 32) &&
				(Key[0] & (tmpMask << (64-PC_1[i])))) {
			NewKey[1] = NewKey[1] | KeyMask;
		}
	}

	for(   i = 28 ; i < 56 ; i++)
	{
		KeyMask = 0x08000000>>(i-28);

		if((PC_1[i] <= 32) && (Key[1] & (tmpMask << (32-PC_1[i])))) {
			NewKey[0] = NewKey[0] | KeyMask;
		}else if((PC_1[i] > 32) &&
				(Key[0] & (tmpMask << (64-PC_1[i])))) {
			NewKey[0] = NewKey[0] | KeyMask;
		}
	}

	Key[0] = NewKey[0];
	Key[1] = NewKey[1];
}
