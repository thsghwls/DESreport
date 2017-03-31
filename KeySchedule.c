/*
 * KeySchedule.c
 *
 *  Created on: 2017. 3. 31.
 *      Author: ÄÄÇ»ÅÍ
 */

#include "DES.h"

const unsigned char LSHIFT[]= {
	1,1,2,2,
	2,2,2,2,
	1,2,2,2,
	2,2,2,1
};

KeySchedule(char *Key, WORD *RoundKey)
{
	int i , SHIFT=0;
	WORD dwKey[2]= {0,0 };
	WORD tmp0, tmp1;

    for( i = 0 ; i < 4 ; i++)
	{
		SHIFT =((3-i)*8);
		dwKey[1] ^= ((WORD)Key[i   ])<<SHIFT;
		dwKey[0] ^= ((WORD)Key[i+4 ])<<SHIFT;
	}
	PermutedChoice1(dwKey);

    for(i = 0 ; i < 16 ; i++)
	{
		//Left Shift
		if(LSHIFT[i] == 1)
		{
			tmp0 = ((dwKey[0] & 0x08000000) >> 27);
			tmp0 |= ((dwKey[0] & 0x07FFFFFF) << 1);
			dwKey[0] = tmp0;
			tmp1 = ((dwKey[1] & 0x08000000) >> 27);
			tmp1 |= ((dwKey[1] & 0x07FFFFFF) << 1);
			dwKey[1] = tmp1;
		}else //2bit-shift
		{
			tmp0 = ((dwKey[0] & 0x0c000000) >> 26);
			tmp0 |= ((dwKey[0] & 0x03FFFFFF) << 2);
			dwKey[0] = tmp0;
			tmp1 = ((dwKey[1] & 0x0c000000) >> 26);
			tmp1 |= ((dwKey[1] & 0x03FFFFFF) << 2);
			dwKey[1] = tmp1;
		}
		PermutedChoice2(dwKey);

		RoundKey[2*i+1]   = dwKey[1];
		RoundKey[2*i]     = dwKey[0];

		dwKey[1] = tmp1;
		dwKey[0] = tmp0;
	}
}
