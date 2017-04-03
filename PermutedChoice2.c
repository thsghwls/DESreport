/*
 * PermutedChoice2.c
 *
 *  Created on: 2017. 3. 30.
 *      Author: 컴퓨터
 */

#include "DES.h"

BIT PC_2[]= {
		14, 17, 11, 24,  1,  5,  3, 28,
		15,  6, 21, 10, 23, 19, 12,  4,
		26,  8, 16,  7, 27, 20, 13,  2,
		41, 52, 31, 37, 47, 55, 30, 40,
		51, 45, 33, 48, 44, 49, 39, 56,
		34, 53, 46, 42, 50, 36, 29, 32,
};

void PermutedChoice2(WORD *Key)
{
	int i;
	WORD tmpMask = 0x00000001;;
	WORD KeyMask;
	WORD NewKey[2] = {0,0 };

//	>> PC_2[0]~PC_2[23]까지(3x8)에 해당하는 위치에 bit를 찾아 1이면 값을 넣고 0이면 Pass. 나머지는 IntialPermutation에서 설명한 방식과 동일 <<
	for(int i = 0 ; i < 24 ; i++)
	{
//		>> 왼쪽 8bit를 제외하고 나머지 24bit 위치에 왼쪽부터 순차적으로 bit를 넣음 <<
		KeyMask = 0x00800000 >> i;
		if((PC_2[i] <= 28) && (Key[1] & (tmpMask << (28-PC_2[i])))) {
			NewKey[1] = NewKey[1] | KeyMask;
		}else if((PC_2[i] > 28) && (Key[0] & (tmpMask << (56-PC_2[i])))) {
			NewKey[1] = NewKey[1] | KeyMask;
		}
	}
//	>> PC_2[24]~PC_2[47]까지(3x8)에 해당하는 위치에 bit를 찾아 1이면 값을 넣고 0이면 Pass. 나머지는 IntialPermutation에서 설명한 방식과 동일 <<
	for(i = 24 ; i < 48 ; i++)
	{
		KeyMask = 0x00800000 >> (i-24);		// i값이 24~47범위 i-24를 하면 0~23으로 NewKey[0]의 우측 8개 bit를 제외한 24개 bit에 데이터를 넣을 수 있음
		if((PC_2[i] <= 28) && (Key[1] & (tmpMask << (28-PC_2[i])))) {
			NewKey[0] = NewKey[0] | KeyMask;
		}else if((PC_2[i] > 28) &&
				(Key[0] & (tmpMask << (56-PC_2[i])))) {
			NewKey[0] = NewKey[0] | KeyMask;
		}
	}
//	>> 결과적으로 순열선택2를 수행한 결과 key 길이가 56bit -> 48bit로 감소 <<
	Key[0] = NewKey[0];
	Key[1] = NewKey[1];
}
