/*
 * PermutationFunction.c
 *
 *  Created on: 2017. 3. 30.
 *      Author: ÄÄÇ»ÅÍ
 */

#include "DES.h"

unsigned char P[]= {
		16,  7, 20, 21, 29, 12, 28, 17,
		1, 15, 23, 26,  5, 18, 31, 10,
		2,  8, 24, 14, 32, 27,  3,  9,
		19, 13, 30,  6, 22, 11,  4, 25
};

WORD PermutationFunction(WORD dWord)
{
	WORD tmpMask = 0x00000001;
	WORD keyMask = 0x00000001;
	WORD dwTmp = 0;
	for(int i = 0 ; i < 32 ; i++)
	{
		if(dWord & (tmpMask << (32-P[i])))
			dwTmp |= (keyMask << (31-i));
	}
	return dwTmp;
}
