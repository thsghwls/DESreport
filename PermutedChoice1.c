/*
 * PermutedChoice1.c
 *
 *  Created on: 2017. 3. 30.
 *      Author: ��ǻ��
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

	//	>> PC_1[0]���� PC_1[27]����(4x7)�� �ش��ϴ� ��ġ�� �ִ� ��Ʈ���� ���������� ���� ��ġ�ϰ� ���� 4bit�� ������.
	for( i = 0 ; i < 28 ; i++)
	{
		KeyMask = 0x08000000 >> i;

		//	PC_1[i]�� �ش��ϴ� ��ġ(��������)�� Key���� 1�ϰ�� �����Ͽ� NewKey�� �����ϴµ� �̶� KeyMask�� ���������̶�
		// NewKey�� �������� ä������. �������� InitialPermutation������ ������ ����.
		if((PC_1[i] <= 32) && (Key[1] & (tmpMask << (32-PC_1[i])))) {
			NewKey[1] = NewKey[1] | KeyMask;
		}else if((PC_1[i] > 32) &&
				(Key[0] & (tmpMask << (64-PC_1[i])))) {
			NewKey[1] = NewKey[1] | KeyMask;
		}
	}

	//	>> PC_1[28]���� PC_1[55]����(4x7)�� �ش��ϴ� ��ġ�� �ִ� ��Ʈ���� ���������� ���� ��ġ�ϰ� ���� 4bit�� ������
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
	//	��������1�� �ϰ��� �ᱹ 8x8���� ������ ���� 1���� �ش��ϴ� 1byte(8bit)�� ������. �� ��� 64bit -> 56bit�� �ȴ�.

	Key[0] = NewKey[0];
	Key[1] = NewKey[1];
}
