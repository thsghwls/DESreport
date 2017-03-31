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

void InverseInitialPermutation (WORD* data) {
	WORD newdata[2] = {0};
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
		//		printf("tempMask : %32x\n", tempMask << (32-IIP[i]));
		//		printf("setMask  : %32x\n", setMask);
		//		printf("         : 1000000000 0000000000 0000000000\n");
		//		printf(" IIP[%d]  : %d [%s]\n",i, IIP[i], IIP[i]>32 ? " >32 " : " <=32 ");
		//		if((IP[i]<= 32) && (data[1] & setMask)) {
		//			printf("newdata[1]:");
		//			for(j = 31 ; j >= 0 ; j--) {
		//				mask=0x00000001 << j;
		//				buf = (newdata[1] & mask)>> j;
		//				printf("%d",buf);
		//			}
		//			puts("");
		//			viewBlock(newdata[1]);
		//			puts("");
		//		}
		//		else if((IIP[i]>32 && (data[1] & setMask))) {
		//			printf("newdata[0]:");
		//			for(j = 31 ; j >= 0 ; j--) {
		//				mask=0x00000001 << j;
		//				buf = (newdata[0] & mask)>> j;
		//				printf("%d",buf);
		//			}
		//			puts("");
		//			viewBlock(newdata[0]);
		//			puts("");
		//		}
	}
	//		���ۺκ�
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
