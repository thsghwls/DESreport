/*
 * InitialPermutation.c
 *
 *  Created on: 2017. 3. 30.
 *      Author: ��ǻ��
 */

#include "DES.h"

BIT IP[] = {58, 50, 42, 34, 26, 18, 10, 2,
		60, 52, 44, 36, 28, 20, 12, 4,
		62, 54, 46, 38, 30, 22, 14, 6,
		64, 56, 48, 40, 32, 24, 16, 8,
		57, 49, 41, 33, 25, 17,  9, 1,
		59, 51, 43, 35, 27, 19, 11, 3,
		61, 53, 45, 37, 29, 21, 13, 5,
		63, 55, 47, 39, 31, 23, 15, 7};

//	IP[i]�� 1~32�϶� tmpMask�� 32-IP[i]��ŭ ��Ʈ�� �������� �ű�� �Ǹ� IP[i]�� ��ġ�� �ִ� plainText�� ���� ������ �� �ִ�.
void InitialPermutation(WORD *Data)
{
	//	>> ����� ���� ���� <<
	int i;
	//	plainText�� IP�� �ش��ϴ� ��Ʈ �������� ���
	WORD tmpMask;
	//	NewData ��, �ʱ���� ������ plainText���� �������� ���������� �ֱ����� ��� [ ex) ����<< 00000000 ...00000001 <<���� ]
	WORD setMask;
	//	plainText�� ���� ���ϸ� �ʱ������ �������ϱ⶧���� �� ������ NewData ���� �� �������� plainText���� �����ϱ����� ���
	WORD NewData[2]= {0};

	//	>> ���� 32bit�� ��� Left�� Right�� ������ ������ PI[0]~PI[31]�� PI[32]~PI[63]�� ���� Initial Permutation �Ѵ�.

	//	>> IP[]�� 4 x 8 (PI[0]~PI[31])�� �ش��ϴ� 32bit�� �����ϴµ�, IP[i]�� �ش��ϴ� ��ġ�� �ִ�(*����� ���⼭ �ش���ġ�� ���������̴�.)
	//		 plainText�� bit�� 1�ϰ�츸 NewData[1]�� �ش���ġ�� 1�� �����Ѵ�. (NewData�� �̹� 0���� �ʱ�ȭ �Ǿ��ֱ� ����)
	//		 �׸��� NewData[1]�� �ش���ġ�� setMask�� R���� L������ ����Ű�� ������ ���������̴�. <<
	for(i = 31 ; i >= 0 ; i--)
	{
		tmpMask = 0x00000001; // ������������ IP[i]�� ���ڿ� �ش��ϴ� ��ġ�� ��Ʈ�� ����Ų��. �� ��ġ�� plainText�� 1�ϰ�� and��������
										 // True�� �ȴ�.
		setMask = 0x00000001<<(31-i);	// NewData[1]�� �������� �������� i��ŭ �̵��ϸ� ����Ų��. (���� ����� plainText bit�� 1�ϰ�� Set)
		if((IP[i] <= 32) && (Data[1] & (tmpMask << (32-IP[i])))) {
			NewData[1] = NewData[1] | setMask;
		}else if((IP[i] > 32) && (Data[0] & (tmpMask << (64-IP[i])))){
			NewData[1] = NewData[1] | setMask;
		}
		// ��ó�� if , else if�� 32�̻�� 32�̸��� ������ ������ ���� 32bit�� �������� ����
	}

	//	>> ���� �����ѵ� �̹����� plainTextd���� IP[]�� 4 x 8 (PI[0]~PI[31])�� �ش��ϴ� ��ġ�� �ִ� 32bit�� �����Ͽ�
	//		 NewData[0]�� �������� �ִ´�. <<
	for(i = 63 ; i >=32 ; i--)
	{
		tmpMask = 0x00000001;
		setMask = 0x00000001<<(63-i);
		if((IP[i] <= 32) && (Data[1] & (tmpMask << (32-IP[i])))) {
			NewData[0] = NewData[0] | setMask;
		}else if((IP[i] > 32) && (Data[0] & (tmpMask << (64-IP[i])))) {
			NewData[0] = NewData[0] | setMask;
		}
	}
	// �ʱ� ���� �� ���� plainText�� ���� �ִ´�. [ IP END ]
	Data[1] = NewData[1];
	Data[0] = NewData[0];
}


//	��¼�ٺ��� ó���� ��Ŵٰ� ������µ� �ߵȴ�.
void InitialPermutation_2 (WORD* data) {
	int i;
	WORD newdata[2] = {0};
	WORD tempMask; //temp �� : �ӽ�����
	WORD setMask;
	for(i = 0 ; i <32 ; i++) {
		tempMask = 0x00000001;
		setMask = 0x00000001<<(31-i); //��Ʈ�����ڸ� ���� �ֿ�����Ʈ�� ���ڸ����� ��������(1�������ϸ�) 2���� ���ڸ��� �������Եȴ�.

		//		���ۺκ�
		if((IP[i]<= 32) && (data[1] & setMask))
			newdata[1] |= (tempMask << (32-IP[i]));
		else if((IP[i]>32 && (data[1] & setMask)))
			newdata[0] |= (tempMask << (64-IP[i]));
	}
	//		���ۺκ�
	for(i = 32 ; i < 64 ; i++) {
		tempMask = 0x00000001;
		setMask = 0x00000001<<(63-i); //��Ʈ�����ڸ� ���� �ֿ�����Ʈ�� ���ڸ����� ��������(1�������ϸ�) 2���� ���ڸ��� �������Եȴ�.

		if((IP[i]<= 32) && (data[0] & setMask))
			newdata[1] |=(tempMask << (32-IP[i]));
		else if((IP[i]>32 && (data[0] & setMask)))
			newdata[0] |=(tempMask << (64-IP[i]));

	}
	data[1]=newdata[1];		//left   32-bit
	data[0]=newdata[0];		//right 32-bit
	newdata[1]=0;
	newdata[0]=0;
	puts(">>>>IP �Ϸ�! <<<<");

}

