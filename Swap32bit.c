/*
 * Swap32.c
 *
 *  Created on: 2017. 3. 30.
 *      Author: 컴퓨터
 */

#include "DES.h"

void swap32bit(WORD *Data)
{
	//	16라운드를 모두 수행하여 출력된 64bit 데이터의 왼쪽과 오른쪽을 바꿔준다.
	WORD temp;
	temp = Data[0];
	Data[0] = Data[1];
	Data[1] = temp;
}
