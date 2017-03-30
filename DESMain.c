/*
 * DES.c
 *
 *  Created on: 2017. 3. 28.
 *      Author: Computer
 */

#include "DES.h"


int main (void) {
	//	16���� 0x00000000�� ���� ����0 8���� ���� 2���� 4bit�� ��Ÿ����.
	//	�̹� 64bit�� 32bit�� �����ٰ� ����
	//	left(data[1]) : 0010010 00110001 00100011 00010010 , right(data[0]) : 01010101 01010101 01010101 01010101
	WORD data[2] = {/*right*/0x55555555, /*left*/0x12312312};
	WORD newdata[2] = {0};

	puts("==== data[1] ====");
	viewBlock(data[1]);
	puts("==== data[0] ====");
	viewBlock(data[0]);

	//encode
	InitialPermutation(data, newdata);

	puts("==== newdata[1] ====");
	viewBlock(newdata[1]);
	puts("==== newdata[0] ====");
	viewBlock(newdata[0]);

	//������ ���� �� �ʱ�ȭ
	data[1]=newdata[1];
	data[0]=newdata[0];
	newdata[1]=0;
	newdata[0]=0;

	//decode
	InverseInitialPermutation(data, newdata);

	puts("==== newdata[1] ====");
	viewBlock(newdata[1]);
	puts("==== newdata[0] ====");
	viewBlock(newdata[0]);

	//������ ���� �� �ʱ�ȭ
	data[1]=newdata[1];
	data[0]=newdata[0];
	newdata[1]=0;
	newdata[0]=0;

	puts("==== data[1] ====");
	viewBlock(data[1]);
	puts("==== data[0] ====");
	viewBlock(data[0]);
}




