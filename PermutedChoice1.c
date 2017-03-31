/*
 * PermutedChoice1.c
 *
 *  Created on: 2017. 3. 30.
 *      Author: 컴퓨터
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
	WORD tmpMask = 0x00000001;
	WORD KeyMask;
	WORD NewKey[2]= {0,0 };

	//	>> PC_1[0]부터 PC_1[27]까지(4x7)에 해당하는 위치에 있는 비트들을 순열선택을 통해 배치하고 우측 4bit는 버린다.
	for( i = 0 ; i < 28 ; i++)
	{
		KeyMask = 0x08000000 >> i;

		//	PC_1[i]에 해당하는 위치(좌측기준)의 Key값이 1일경우 검출하여 NewKey에 저장하는데 이때 KeyMask는 좌측기준이라
		// NewKey는 좌측부터 채워진다. 나머지는 InitialPermutation에서의 원리와 같다.
		if((PC_1[i] <= 32) && (Key[1] & (tmpMask << (32-PC_1[i])))) {
			NewKey[1] = NewKey[1] | KeyMask;
		}else if((PC_1[i] > 32) &&
				(Key[0] & (tmpMask << (64-PC_1[i])))) {
			NewKey[1] = NewKey[1] | KeyMask;
		}
	}

	//	>> PC_1[28]부터 PC_1[55]까지(4x7)에 해당하는 위치에 있는 비트들을 순열선택을 통해 배치하고 우측 4bit는 버린다
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
	//	순열선택1을 하고나면 결국 8x8에서 봤을때 우측 1열에 해당하는 1byte(8bit)를 버린다. 그 결과 64bit -> 56bit가 된다.

	Key[0] = NewKey[0];
	Key[1] = NewKey[1];
}
