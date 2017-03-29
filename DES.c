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
	WORD text[2] = {0x55555555, 0x12312312}; //16진수 0x00000000의 뒤의 숫자0 8개가 각각 2진수 4bit씩 나타낸다.
	WORD tempMask; //temp 뜻 : 임시직원
	WORD setMask;

	WORD data[2] = {0};
	WORD newData[2] = {0};

	printf("text[0](left) : %x // text[1](right) : %x\n", text[0],text[1]);

	//데이터 분리 16 + 16 = 32
	for(i = 0 ; i <16 ; i++) {
		setMask   = 0x00000001 << i;
		tempMask = setMask & text;
		//				printf("%x\n",tempMask); //재대로 들어가는지 확인
		data[0]|= tempMask; //right
		//		printf("%x\n",data[0]); //재대로 들어가는지 확인

	}

	for(i = 16 ; i < 32 ; i++) {
		setMask   = 0x00000001 << i;
		tempMask = setMask & text;
		//		printf("%x\n",tempMask); //재대로 들어가는지 확인
		data[1] |= tempMask >> 16; //이것때문이였다....................................>> 16... //left
		//		printf("%x\n",data[1]);
	}

	printf("L == data[1] %d %x // R ==data[0] %d %x // %x //\n",data[0]==0x1AE3,data[0],data[1]==0x211D,data[1] , text);
	//자꾸 짤려나와서 보니 test자체가 dad638e3이다.......longlong 형이라 8바이트이지만 안되나봄. 그래서 32비트로 함

	for(i = 32 ; i >= 0 ; i--) {
		tempMask = 0x00000001;
		setMask = 0x00000001<<(31-i); //비트연산자를 통해 최우측비트가 한자리수가 높아지면(1씩증가하면) 2진수 한자리씩 가져오게된다.

		if((IP[i]<= 32) && (data[1] & (tempMask << (32-IP[i]))))
			newData[1] |= setMask;
		else if((IP[i]>32 && (data[0] & (tempMask << (64-IP[i])))))
			newData[1] |= setMask;
//		printf("%d : newdata[1] = %x\n",31-i,newData[1]);
	}

	for(i = 63 ; i >= 32 ; i--) {
		tempMask = 0x00000001;
		setMask = 0x00000001<<(31-i); //비트연산자를 통해 최우측비트가 한자리수가 높아지면(1씩증가하면) 2진수 한자리씩 가져오게된다.

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
