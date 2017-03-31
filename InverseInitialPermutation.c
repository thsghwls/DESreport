/*
 * InverseInitialPermutation.c
 *
 *  Created on: 2017. 3. 30.
 *      Author: ��ǻ��
 */

#include "DES.h"

BIT IIP[] = {40, 8, 48, 16, 56, 24, 64, 32,
		39, 7, 47, 15, 55, 23, 63, 31,
		38, 6, 46, 14, 54, 22, 62, 30,
		37, 5, 45, 13, 53, 21, 61, 29,
		36, 4, 44, 12, 52, 20, 60, 28,
		35, 3, 43, 11, 51, 19, 59, 27,
		34, 2, 42, 10, 50, 18, 58, 26,
		33, 1, 41, 9, 49, 17, 57, 25};

void InverseInitialPermutation(WORD *Data)
{
	//	�������� �ʱ������ ����� �����ϴ�.
	int i;
	WORD tmpMask;
	WORD setMask;
	WORD NewData[2]= {0, };

	//	IIP[] ���̺��� IIP[31]���� IIP[0]����(4x8) �ش� IIP�� ��ġ�� ���� 1�̸� NewData[1]�� ������������ �·� 31-i�� ��ġ�� 1�� �ִ´�.
	for(i = 31 ;i >= 0 ; i--)
	{
		tmpMask = 0x00000001;
		setMask = 0x00000001<<(31-i);
		if((IIP[i] <= 32) && (Data[1] & (tmpMask << (32-IIP[i])))) {
			NewData[1] = NewData[1] | setMask;
		}else if((IIP[i] > 32) && (Data[0] & (tmpMask << (64-IIP[i])))) {
			NewData[1] = NewData[1] | setMask;
		}
	}
	//	IIP[] ���̺��� IIP[63]���� IIP[32]����(4x8) �ش� IIP�� ��ġ�� ���� 1�̸� NewData[0]�� ������������ �·� 63-i �� ��ġ�� 1�� �ִ´�.

	for(i = 63 ; i >=32 ; i--)
	{
		tmpMask = 0x00000001;
		setMask = 0x00000001<<(63-i);
		if((IIP[i] <= 32) && (Data[1] & (tmpMask << (32-IIP[i])))) {
			NewData[0] = NewData[0] | setMask;
		}else if((IIP[i] > 32) && (Data[0] & (tmpMask << (64-IIP[i])))) {
			NewData[0] = NewData[0] | setMask;
		}
	}
	//	������ �� ���� plainText[1]�� plainText[0]�� ���� �ִ´�.
	Data[1] = NewData[1];
	Data[0] = NewData[0];
}

// ó���� ��Ŵٰ� ��¼�� ���� ����� �Ǿ��µ� �ߵȴ�.
void InverseInitialPermutation_2 (WORD* data) {
	WORD newdata[2] = {0};
	int i;
	WORD tempMask; //temp �� : �ӽ�����
	WORD setMask;
	for(i = 0 ; i <32 ; i++) {
		tempMask = 0x00000001;
		setMask = 0x00000001<<(31-i); //��Ʈ�����ڸ� ���� �ֿ�����Ʈ�� ���ڸ����� ��������(1�������ϸ�) 2���� ���ڸ��� �������Եȴ�.

		if((IIP[i]<= 32) && (data[1] & setMask))
			newdata[1] |= (tempMask << (32-IIP[i]));
		else if((IIP[i]>32 && (data[1] & setMask)))
			newdata[0] |= (tempMask << (64-IIP[i]));
	}

	for(i = 32 ; i < 64 ; i++) {
		tempMask = 0x00000001;
		setMask = 0x00000001<<(63-i); //��Ʈ�����ڸ� ���� �ֿ�����Ʈ�� ���ڸ����� ��������(1�������ϸ�) 2���� ���ڸ��� �������Եȴ�.

		if((IIP[i]<= 32) && (data[0] & setMask))
			newdata[1] |=(tempMask << (32-IIP[i]));
		else if((IIP[i]>32 && (data[0] & setMask)))
			newdata[0] |=(tempMask << (64-IIP[i]));
	}
	puts(">>>>IIP �Ϸ�! <<<<");
	data[1]=newdata[1];		//left   32-bit
	data[0]=newdata[0];		//right 32-bit
	newdata[1]=0;
	newdata[0]=0;
}

