/*
 * DES.c
 *
 *  Created on: 2017. 3. 28.
 *      Author: Computer
 */
#include <stdio.h>

typedef unsigned char  BIT;
typedef unsigned long WORD;
BIT IP[] = {58, 50, 42, 34, 26, 18, 10, 2,
		60, 52, 44, 36, 28, 20, 12, 4,
		62, 54, 46, 38, 30, 22, 14, 6,
		64, 56, 48, 40, 32, 24, 16, 8,
		57, 49, 41, 33, 25, 17,  9, 1,
		59, 51, 43, 35, 27, 19, 11, 3,
		61, 53, 45, 37, 29, 21, 13, 5,
		63, 55, 47, 39, 31, 23, 15, 7};

BIT IIP[] = {40, 8, 16, 56, 24, 64, 32, 39,
		39, 7, 47, 15, 55, 23, 63, 31,
		38, 6, 46, 14, 54, 22, 62, 30,
		37, 5, 45, 13, 53, 21, 61, 29,
		36, 4, 44, 12, 52, 20, 60, 28,
		35, 3, 43, 11, 51, 19, 59, 27,
		34, 2, 42, 10, 50, 18, 58, 26,
		33, 1, 41, 9, 49, 17, 57, 25};

int main (void) {
	int i;
	WORD text[2] = {0x55555555, 0x12312312}; //16���� 0x00000000�� ���� ����0 8���� ���� 2���� 4bit�� ��Ÿ����.
	WORD tempMask; //temp �� : �ӽ�����
	WORD setMask;

	WORD data[2] = {0};
	WORD newData[2] = {0};

	printf("text[0](left) : %x // text[1](right) : %x\n", text[0],text[1]);

	//������ �и� 16 + 16 = 32
	for(i = 0 ; i <16 ; i++) {
		setMask   = 0x00000001 << i;
		tempMask = setMask & text;
		//				printf("%x\n",tempMask); //���� ������ Ȯ��
		data[0]|= tempMask; //right
		//		printf("%x\n",data[0]); //���� ������ Ȯ��

	}

	for(i = 16 ; i < 32 ; i++) {
		setMask   = 0x00000001 << i;
		tempMask = setMask & text;
		//		printf("%x\n",tempMask); //���� ������ Ȯ��
		data[1] |= tempMask >> 16; //�̰Ͷ����̿���....................................>> 16... //left
		//		printf("%x\n",data[1]);
	}

	printf("L == data[1] %d %x // R ==data[0] %d %x // %x //\n",data[0]==0x1AE3,data[0],data[1]==0x211D,data[1] , text);
	//�ڲ� ©�����ͼ� ���� test��ü�� dad638e3�̴�.......longlong ���̶� 8����Ʈ������ �ȵǳ���. �׷��� 32��Ʈ�� ��

	for(i = 32 ; i >= 0 ; i--) {
		tempMask = 0x00000001;
		setMask = 0x00000001<<(31-i); //��Ʈ�����ڸ� ���� �ֿ�����Ʈ�� ���ڸ����� ��������(1�������ϸ�) 2���� ���ڸ��� �������Եȴ�.

		if((IP[i]<= 32) && (data[1] & (tempMask << (32-IP[i]))))
			newData[1] |= setMask;
		else if((IP[i]>32 && (data[0] & (tempMask << (64-IP[i])))))
			newData[1] |= setMask;
//		printf("%d : newdata[1] = %x\n",31-i,newData[1]);
	}

	for(i = 63 ; i >= 32 ; i--) {
		tempMask = 0x00000001;
		setMask = 0x00000001<<(31-i); //��Ʈ�����ڸ� ���� �ֿ�����Ʈ�� ���ڸ����� ��������(1�������ϸ�) 2���� ���ڸ��� �������Եȴ�.

		if((IP[i]<= 32) && (data[1] & (tempMask << (32-IP[i]))))
			newData[0] |= setMask;
		else if((IP[i]>32 && (data[0] & (tempMask << (64-IP[i])))))
			newData[0] |= setMask;
//		printf("%d : newdata[0] = %x\n",63-i, newData[0]);
	}

	data[1] = newData[1];
	data[0] = newData[0];
	printf("L == data[1] %d %x // R ==data[0] %d %x // %x //\n",data[0]==0x1AE3,data[0],data[1]==0x211D,data[1] , text);
}
