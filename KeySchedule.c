/*
 * KeySchedule.c
 *
 *  Created on: 2017. 3. 31.
 *      Author: 컴퓨터
 */

#include "DES.h"

const unsigned char LSHIFT[]= {
		1,1,2,2,
		2,2,2,2,
		1,2,2,2,
		2,2,2,1
};

void KeySchedule(char *Key, WORD *RoundKey)
{
	// >> 사용할 변수 정의 <<
	int i , SHIFT=0;
	WORD dwKey[2]= {0,0 };
	WORD tmp0 = 0, tmp1 = 0;

	//	8bit의 key 8개를 64bit key(여기선 32bit 2개)로 만들기 위해 수행
	for( i = 0 ; i < 4 ; i++)
	{
		//	8byte짜리 키 4개를 32bit로 만드려고 Shitf 사용 [ 24, 16, 8 , 0 의 위치에 해당 key를 넣는다. ]
		SHIFT =((3-i)*8);
		//	Key 8개를 4개씩 32bit공간에 넣는다. XOR연산과 왼쪽 Shift연산을 사용해 32bit 변수 dwkey[1], dwkey[0]에 각각 넣는다.
		//	여기서 Key는 8bit이므로 재대로 XOR하기위해 32bit WORD형으로 강제형변환을 한다.
		dwKey[1] ^= ((WORD)Key[i   ])<<SHIFT;
		dwKey[0] ^= ((WORD)Key[i+4])<<SHIFT;
	}

	// 순열선택 1을 수행하여 64bit(각32bit)의 Key를 56bit(각28bit) Key로 축소한다.
	PermutedChoice1(dwKey);

	// 56bit key를 가지고 왼쪽 환형 시프트를 수행하고 48bit의 Key로 축소한다. 이를 16회 수행하여 RoundKey를 16개 만든다.
	for(i = 0 ; i < 16 ; i++)
	{
		//Left Shift
		if(LSHIFT[i] == 1)
		{
			//	Left 4bit 제외한 좌측 첫번째에 해당하는 dwKey[0]의 bit를 맨 우측으로 보내어 tmp0에 저장한다.
			tmp0 = ((dwKey[0] & 0x08000000) >> 27);
			//	Left 4bit 제외한 좌측 첫번째에 해당하는 dwKey[0]의 bit를 뺀 나머지 bit를 검출하여 우측으로 한칸 옮기고 tmp0와 OR연산한다.
			tmp0 |= ((dwKey[0] & 0x07FFFFFF) << 1);
			//	dwKey[0]의 Left 4bit를 제외한 좌측 첫번째 값을 우측으로 옮긴 값을 dwKey[0]에 저장한다.
			dwKey[0] = tmp0;
			// 위와 동일하다.
			tmp1 = ((dwKey[1] & 0x08000000) >> 27);
			tmp1 |= ((dwKey[1] & 0x07FFFFFF) << 1);
			dwKey[1] = tmp1;
		}else //2bit-shift
		{	// 위와 동일한 방식이지만 Left 4bit를 제외한 좌측 첫번째와 두번째(즉, 2bit)를 우측으로 옮긴다.
			tmp0 = ((dwKey[0] & 0x0c000000) >> 26);
			tmp0 |= ((dwKey[0] & 0x03FFFFFF) << 2);
			dwKey[0] = tmp0;
			tmp1 = ((dwKey[1] & 0x0c000000) >> 26);
			tmp1 |= ((dwKey[1] & 0x03FFFFFF) << 2);
			dwKey[1] = tmp1;
		}

		//LSHIFT[i]의 값에 맞게 왼쪽 환형 시프트 연산이 끝난 56bit의 dwKey를 순열선택2를 통해 48bit로 줄인뒤 Round Key에 저장한다.
		PermutedChoice2(dwKey);

		//	순열선택2의 결과로 얻은 48bit의 i+1 라운드 키를 RoundKey[2*i+1]과 RoundKey[2*i]에 각각 24bit씩 저장.
		// ex) i 가 0이면 1라운드 키를 RoundKey[1]과 RoundKey[0]에 각각 24bit씩 저장.
		RoundKey[2*i+1]   = dwKey[1];
		RoundKey[2*i]     = dwKey[0];
		//	다음 라운드의 Round Key를 얻기위해 56bit의 Key를 48bit로 바꾸기전 56bit Key의 값을 각각 dwKey[1]와 dwKey[0]에 저장한다.
		dwKey[1] = tmp1;
		dwKey[0] = tmp0;
	}
}
