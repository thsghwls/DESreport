/*
 * DES.c
 *
 *  Created on: 2017. 3. 28.
 *      Author: Computer
 */

#include "DES.h"
//	16���� 0x00000000�� ���� ����0 8���� ���� 2���� 4bit�� ��Ÿ����.

int main (void) {
	WORD plainText[2] = {0x55555555, 0x12312312};		//plainText[1] : left ,  plainText[0] : right
	char key[8]		 = {'a','b','c','d','e','f','g','h'};	//key[1] : left , key[0] : right
	WORD roundKey[32] = {0};
	int i;

	//��Ȯ��
	puts("==== plainText_64bit ====");
	viewBlock4x8(plainText[1]);
	viewBlock4x8(plainText[0]);
	puts("");

	//DES ��ȣȭ �˰���
	puts("================ ��ȣȭ ================");
	//1.IP �ʱ����
	InitialPermutation(plainText);
	puts("==== �ʱ����(IP) ��� ====");
	viewBlock4x8(plainText[1]);
	viewBlock4x8(plainText[0]);
	puts("");

	//2.���� Ű ����
	KeySchedule(key, roundKey);

	//3.16����
	for(i = 0 ; i < 16 ; i++)
		Round(plainText[1], roundKey[i+1],roundKey[i]);

	//4.���� �������� ����
	swap32bit(plainText);

	//5.IIP ������
	InverseInitialPermutation(plainText);
	puts("==== �� ����(IIP) ��� ====");
	viewBlock4x8(plainText[1]);
	viewBlock4x8(plainText[0]);
	puts("");

	puts("================ ��ȣȭ �Ϸ�================");
	return 0;
}




