/*
 * Swap32.c
 *
 *  Created on: 2017. 3. 30.
 *      Author: ��ǻ��
 */

#include "DES.h"

void swap32bit(WORD *Data)
{
	//	16���带 ��� �����Ͽ� ��µ� 64bit �������� ���ʰ� �������� �ٲ��ش�.
	WORD temp;
	temp = Data[0];
	Data[0] = Data[1];
	Data[1] = temp;
}
