/*
 * ExpansionPermutation.c
 *
 *  Created on: 2017. 3. 30.
 *      Author: ÄÄÇ»ÅÍ
 */

#include "DES.h"

void ExpansionPermutation(WORD RightHalf, WORD *exData)
{
	WORD New[2] = {0,0};

	// 32th bit -> first bit of first word
	New[1] |= ((RightHalf & 0x00000001) << 23); viewBlock4x8(New[1]);

	// 1,2,3,4,5 bit -> 2,3,4,5,6 bit
	New[1] |=(((RightHalf & 0xF8000000) >> 9) & 0x007C0000); viewBlock4x8(New[1]);
	New[1] |= ((RightHalf & 0x1F800000) >> 11); viewBlock4x8(New[1]);
	New[1] |= ((RightHalf & 0x01F80000) >> 13); viewBlock4x8(New[1]);
	New[1] |= ((RightHalf & 0x001F8000) >> 15); viewBlock4x8(New[1]);

	New[0] |= ((RightHalf & 0x0001F800) << 7);
	New[0] |= ((RightHalf & 0x00001F80) << 5);
	New[0] |= ((RightHalf & 0x000001F8) << 3);
	New[0] |= ((RightHalf & 0x0000001F) << 1);
	New[0] |= (((RightHalf & 0x80000000) >>31)&0x00000001);

	exData[1] = New[1];
	exData[0] = New[0];
}
