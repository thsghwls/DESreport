/*
 * DES.c
 *
 *  Created on: 2017. 3. 28.
 *      Author: Computer
 */
#include <stdio.h>

typedef unsigned char  BIT;
typedef unsigned long WORD;

void viewBlock (WORD);
void encodeData (WORD*, WORD*);
void decodeData (WORD*, WORD*);

BIT IP[] = {58, 50, 42, 34, 26, 18, 10, 2,
		60, 52, 44, 36, 28, 20, 12, 4,
		62, 54, 46, 38, 30, 22, 14, 6,
		64, 56, 48, 40, 32, 24, 16, 8,
		57, 49, 41, 33, 25, 17,  9, 1,
		59, 51, 43, 35, 27, 19, 11, 3,
		61, 53, 45, 37, 29, 21, 13, 5,
		63, 55, 47, 39, 31, 23, 15, 7};

BIT IIP[] = {40, 8, 48, 16, 56, 24, 64, 32,
		39, 7, 47, 15, 55, 23, 63, 31,
		38, 6, 46, 14, 54, 22, 62, 30,
		37, 5, 45, 13, 53, 21, 61, 29,
		36, 4, 44, 12, 52, 20, 60, 28,
		35, 3, 43, 11, 51, 19, 59, 27,
		34, 2, 42, 10, 50, 18, 58, 26,
		33, 1, 41, 9, 49, 17, 57, 25};

int main (void) {
	//	16���� 0x00000000�� ���� ����0 8���� ���� 2���� 4bit�� ��Ÿ����.
	//	�̹� 64bit�� 32bit�� �����ٰ� ����
	//	left(data[1]) : 0010010 00110001 00100011 00010010 , right(data[0]) : 01010101 01010101 01010101 01010101
	WORD data[2] = {/*right*/0x55555555, /*left*/0x12312312};
	WORD newdata[2] = {0};
	int i;

	puts("==== data[1] ====");
	viewBlock(data[1]);
	puts("==== data[0] ====");
	viewBlock(data[0]);

	//encode
	encodeData(data, newdata);

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
	decodeData(data, newdata);

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
void viewBlock (WORD data) {
	int i;
	WORD mask;
	WORD temp;
	printf(">>  %x  <<\n" , data);
	puts(" =====================");
	for(i = 31 ; i >= 0 ; i--) {
		temp = 0;
		mask = 0x00000001 << i;
		temp = mask & data;
		temp = temp>> i;

		if(i!=31&&(i+1)%8==0)
			puts("");
		printf(" %d ", temp);
	}
	puts("\n =====================");
	puts("");
}

void encodeData (WORD* data, WORD* newdata) {
	int i, j;
	WORD buf;
	WORD tempMask,mask; //temp �� : �ӽ�����
	WORD setMask;
	for(i = 0 ; i <32 ; i++) {
		tempMask = 0x00000001;
		setMask = 0x00000001<<(31-i); //��Ʈ�����ڸ� ���� �ֿ�����Ʈ�� ���ڸ����� ��������(1�������ϸ�) 2���� ���ڸ��� �������Եȴ�.

		//		���ۺκ�
		if((IP[i]<= 32) && (data[1] & setMask))
			newdata[1] |= (tempMask << (32-IP[i]));
		else if((IP[i]>32 && (data[1] & setMask)))
			newdata[0] |= (tempMask << (64-IP[i]));

		//		Ȯ�κκ�
		printf("tempMask : %32x\n", tempMask << (32-IP[i]));
		printf("setMask  : %32x\n", setMask);
		printf("         : 1000000000 0000000000 0000000000\n");
		printf(" IP[%d]  : %d [%s]\n",i, IP[i], IP[i]>32 ? " >32 " : " <=32 ");
		if((IP[i]<= 32) && (data[1] & setMask)) {
			printf("newdata[1]:");
			for(j = 31 ; j >= 0 ; j--) {
				mask=0x00000001 << j;
				buf = (newdata[1] & mask)>> j;
				printf("%d",buf);
			}
			puts("");
			viewBlock(newdata[1]);
			puts("");
		}
		else if((IP[i]>32 && (data[1] & setMask))) {
			printf("newdata[0]:");
			for(j = 31 ; j >= 0 ; j--) {
				mask=0x00000001 << j;
				buf = (newdata[0] & mask)>> j;
				printf("%d",buf);
			}
			puts("");
			viewBlock(newdata[0]);
			puts("");
		}
	}
	//		���ۺκ�
	for(i = 32 ; i < 64 ; i++) {
		tempMask = 0x00000001;
		setMask = 0x00000001<<(63-i); //��Ʈ�����ڸ� ���� �ֿ�����Ʈ�� ���ڸ����� ��������(1�������ϸ�) 2���� ���ڸ��� �������Եȴ�.

		if((IP[i]<= 32) && (data[0] & setMask))
			newdata[1] |=(tempMask << (32-IP[i]));
		else if((IP[i]>32 && (data[0] & setMask)))
			newdata[0] |=(tempMask << (64-IP[i]));

		//		Ȯ�κκ�
		printf("tempMask : %32x\n", tempMask << (32-IP[i]));
		printf("setMask  : %32x\n", setMask);
		printf("         : 1000000000 0000000000 0000000000\n");
		printf(" IP[%d]  : %d [%s]\n",i, IP[i], IP[i]>32 ? " >32 " : " <=32 ");
		if((IP[i]<= 32) && (data[1] & setMask)) {
			printf("newdata[1]:");
			for(j = 31 ; j >= 0 ; j--) {
				mask=0x00000001 << j;
				buf = (newdata[1] & mask)>> j;
				printf("%d",buf);
			}
			puts("");
			viewBlock(newdata[1]);
			puts("");
		}
		else if((IP[i]>32 && (data[1] & setMask))) {
			printf("newdata[0]:");
			for(j = 31 ; j >= 0 ; j--) {
				mask=0x00000001 << j;
				buf = (newdata[0] & mask)>> j;
				printf("%d",buf);
			}
			puts("");
			viewBlock(newdata[0]);
			puts("");
		}
	}
	puts(">>>>���ڵ� �Ϸ�! <<<<");
}
void decodeData (WORD* data , WORD* newdata) {
	int i, j;
	WORD buf;
	WORD tempMask,mask; //temp �� : �ӽ�����
	WORD setMask;
	for(i = 0 ; i <32 ; i++) {
		tempMask = 0x00000001;
		setMask = 0x00000001<<(31-i); //��Ʈ�����ڸ� ���� �ֿ�����Ʈ�� ���ڸ����� ��������(1�������ϸ�) 2���� ���ڸ��� �������Եȴ�.

		//		���ۺκ�
		if((IIP[i]<= 32) && (data[1] & setMask))
			newdata[1] |= (tempMask << (32-IIP[i]));
		else if((IIP[i]>32 && (data[1] & setMask)))
			newdata[0] |= (tempMask << (64-IIP[i]));

		//		Ȯ�κκ�
		printf("tempMask : %32x\n", tempMask << (32-IIP[i]));
		printf("setMask  : %32x\n", setMask);
		printf("         : 1000000000 0000000000 0000000000\n");
		printf(" IIP[%d]  : %d [%s]\n",i, IIP[i], IIP[i]>32 ? " >32 " : " <=32 ");
		if((IP[i]<= 32) && (data[1] & setMask)) {
			printf("newdata[1]:");
			for(j = 31 ; j >= 0 ; j--) {
				mask=0x00000001 << j;
				buf = (newdata[1] & mask)>> j;
				printf("%d",buf);
			}
			puts("");
			viewBlock(newdata[1]);
			puts("");
		}
		else if((IIP[i]>32 && (data[1] & setMask))) {
			printf("newdata[0]:");
			for(j = 31 ; j >= 0 ; j--) {
				mask=0x00000001 << j;
				buf = (newdata[0] & mask)>> j;
				printf("%d",buf);
			}
			puts("");
			viewBlock(newdata[0]);
			puts("");
		}
	}
	//		���ۺκ�
	for(i = 32 ; i < 64 ; i++) {
		tempMask = 0x00000001;
		setMask = 0x00000001<<(63-i); //��Ʈ�����ڸ� ���� �ֿ�����Ʈ�� ���ڸ����� ��������(1�������ϸ�) 2���� ���ڸ��� �������Եȴ�.

		if((IIP[i]<= 32) && (data[0] & setMask))
			newdata[1] |=(tempMask << (32-IIP[i]));
		else if((IIP[i]>32 && (data[0] & setMask)))
			newdata[0] |=(tempMask << (64-IIP[i]));

		//		Ȯ�κκ�
		printf("tempMask : %32x\n", tempMask << (32-IIP[i]));
		printf("setMask  : %32x\n", setMask);
		printf("         : 1000000000 0000000000 0000000000\n");
		printf(" IP[%d]  : %d [%s]\n",i, IIP[i], IIP[i]>32 ? " >32 " : " <=32 ");
		if((IP[i]<= 32) && (data[1] & setMask)) {
			printf("newdata[1]:");
			for(j = 31 ; j >= 0 ; j--) {
				mask=0x00000001 << j;
				buf = (newdata[1] & mask)>> j;
				printf("%d",buf);
			}
			puts("");
			viewBlock(newdata[1]);
			puts("");
		}
		else if((IIP[i]>32 && (data[1] & setMask))) {
			printf("newdata[0]:");
			for(j = 31 ; j >= 0 ; j--) {
				mask=0x00000001 << j;
				buf = (newdata[0] & mask)>> j;
				printf("%d",buf);
			}
			puts("");
			viewBlock(newdata[0]);
			puts("");
		}
	}
	puts(">>>>���ڵ� �Ϸ�! <<<<");
}
