/*
 * PermutationFunction.c
 *
 *  Created on: 2017. 3. 30.
 *      Author: 컴퓨터
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

//	>> S-box에서 추출된 32bit 데이터를 순열함수 테이블에 따라 재배치 한다. <<
	for(int i = 0 ; i < 32 ; i++)
	{
		if(dWord & (tmpMask << (32-P[i])))
//			dWord가 1이면 P[i]에 해당하는 값의 위치에 dwTmp에 1을 저장하는데, 위치는 좌측비트부터 + i 만큼의 우측 공간에 저장한다.
			dwTmp |= (keyMask << (31-i));
	}
	return dwTmp;
}
