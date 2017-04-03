/*
 * PermutedChoice2.c
 *
 *  Created on: 2017. 3. 30.
 *      Author: ��ǻ��
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

//	>> PC_2[0]~PC_2[23]����(3x8)�� �ش��ϴ� ��ġ�� bit�� ã�� 1�̸� ���� �ְ� 0�̸� Pass. �������� IntialPermutation���� ������ ��İ� ���� <<
	for(int i = 0 ; i < 24 ; i++)
	{
//		>> ���� 8bit�� �����ϰ� ������ 24bit ��ġ�� ���ʺ��� ���������� bit�� ���� <<
		KeyMask = 0x00800000 >> i;
		if((PC_2[i] <= 28) && (Key[1] & (tmpMask << (28-PC_2[i])))) {
			NewKey[1] = NewKey[1] | KeyMask;
		}else if((PC_2[i] > 28) && (Key[0] & (tmpMask << (56-PC_2[i])))) {
			NewKey[1] = NewKey[1] | KeyMask;
		}
	}
//	>> PC_2[24]~PC_2[47]����(3x8)�� �ش��ϴ� ��ġ�� bit�� ã�� 1�̸� ���� �ְ� 0�̸� Pass. �������� IntialPermutation���� ������ ��İ� ���� <<
	for(i = 24 ; i < 48 ; i++)
	{
		KeyMask = 0x00800000 >> (i-24);		// i���� 24~47���� i-24�� �ϸ� 0~23���� NewKey[0]�� ���� 8�� bit�� ������ 24�� bit�� �����͸� ���� �� ����
		if((PC_2[i] <= 28) && (Key[1] & (tmpMask << (28-PC_2[i])))) {
			NewKey[0] = NewKey[0] | KeyMask;
		}else if((PC_2[i] > 28) &&
				(Key[0] & (tmpMask << (56-PC_2[i])))) {
			NewKey[0] = NewKey[0] | KeyMask;
		}
	}
//	>> ��������� ��������2�� ������ ��� key ���̰� 56bit -> 48bit�� ���� <<
	Key[0] = NewKey[0];
	Key[1] = NewKey[1];
}
