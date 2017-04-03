/*
 * ExpansionPermutation.c
 *
 *  Created on: 2017. 3. 30.
 *      Author: 컴퓨터
 */

#include "DES.h"

void ExpansionPermutation(WORD RightHalf, WORD *exData)
{
	WORD New[2] = {0,0};
//	32th bit -> first bit of first word
//	우측 32bit의 우측에서 첫번째 bit를 좌측8bit를 제외한 첫번째 bit위치(우측에서 9번째)에 옮긴다.
	New[1] |= ((RightHalf & 0x00000001) << 23);

//	1,2,3,4,5 bit -> 2,3,4,5,6 bit
//	32bit의 좌측에서 1~5번째 비트 5개를 위 1비트 우측에 나란히 나열한다.
	New[1] |=(((RightHalf & 0xF8000000) >> 9) & 0x007C0000);
//	32bit의 좌측에서 4, 5번째 bit를 포함한 6, 7, 8, 9번째 비트 6개를 위 비트 우측(맨위bit가 1번이라 치면 7번부터 12번까지)에 나란히 나열한다.
	New[1] |= ((RightHalf & 0x1F800000) >> 11);
//	위와 동일하게 8, 9번째 bit를 포함한 10, 11, 12, 13번째 비트 6개를 이어서 우측에 나열한다.
//	아래도 동일하다.
	New[1] |= ((RightHalf & 0x01F80000) >> 13);
	New[1] |= ((RightHalf & 0x001F8000) >> 15);
//	완료시 New[1]에는 좌측부터 1~8번째 비트는 비어있고 나머지 9~32번째 비트는 값이 들어있다. 즉, 확장된 48bit의 절반인 24bit를 가진다.

//	New[0]도 위와 하는 방식은 동일하다. 아래에서 << 7을 하면 위 New[1]이 마지막으로 옮긴 bit 6개의 끝 2자리를 포함한 6자리를
//	좌측으로 7자리 옮기면 New[0]의 좌측 8bit를 제외한 첫번째 자리부터 값이 들어가게 된다. 아래도 동일하다.
	New[0] |= ((RightHalf & 0x0001F800) << 7);
	New[0] |= ((RightHalf & 0x00001F80) << 5);
	New[0] |= ((RightHalf & 0x000001F8) << 3);
//	plainText[0]의 좌측기준 5개 bit를 New[0]에서 우측으로 1칸 옮긴값을 OR연산을 통해 넣는다.
	New[0] |= ((RightHalf & 0x0000001F) << 1);
//	마지막은 plainText[0]의 좌측 첫번째 bit를 New[0]의 우측 첫번째 자리에 넣는다.
	New[0] |= (((RightHalf & 0x80000000) >>31)&0x00000001);

//	최종적으로 32bit의 plainText[0]를 참조해 48bit로 확장된 Data를 얻었다.
	exData[1] = New[1];
	exData[0] = New[0];
}
