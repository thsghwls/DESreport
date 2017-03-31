/*
 * InitialPermutation.c
 *
 *  Created on: 2017. 3. 30.
 *      Author: 컴퓨터
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

void InitialPermutation (WORD* data) {
	int i, j;
	WORD newdata[2] = {0};
	WORD buf;
	WORD tempMask,mask; //temp 뜻 : 임시직원
	WORD setMask;
	for(i = 0 ; i <32 ; i++) {
		tempMask = 0x00000001;
		setMask = 0x00000001<<(31-i); //비트연산자를 통해 최우측비트가 한자리수가 높아지면(1씩증가하면) 2진수 한자리씩 가져오게된다.

		//		동작부분
		if((IP[i]<= 32) && (data[1] & setMask))
			newdata[1] |= (tempMask << (32-IP[i]));
		else if((IP[i]>32 && (data[1] & setMask)))
			newdata[0] |= (tempMask << (64-IP[i]));
	}
	//		동작부분
	for(i = 32 ; i < 64 ; i++) {
		tempMask = 0x00000001;
		setMask = 0x00000001<<(63-i); //비트연산자를 통해 최우측비트가 한자리수가 높아지면(1씩증가하면) 2진수 한자리씩 가져오게된다.

		if((IP[i]<= 32) && (data[0] & setMask))
			newdata[1] |=(tempMask << (32-IP[i]));
		else if((IP[i]>32 && (data[0] & setMask)))
			newdata[0] |=(tempMask << (64-IP[i]));

	}
	data[1]=newdata[1];		//left   32-bit
	data[0]=newdata[0];		//right 32-bit
	newdata[1]=0;
	newdata[0]=0;
	puts(">>>>IP 완료! <<<<");

}
