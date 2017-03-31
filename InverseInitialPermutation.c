/*
 * InverseInitialPermutation.c
 *
 *  Created on: 2017. 3. 30.
 *      Author: 컴퓨터
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
	//	역순열도 초기순열과 방식은 동일하다.
	int i;
	WORD tmpMask;
	WORD setMask;
	WORD NewData[2]= {0, };

	//	IIP[] 테이블의 IIP[31]부터 IIP[0]까지(4x8) 해당 IIP의 위치에 값이 1이면 NewData[1]의 우측에서부터 좌로 31-i의 위치에 1을 넣는다.
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
	//	IIP[] 테이블의 IIP[63]부터 IIP[32]까지(4x8) 해당 IIP의 위치에 값이 1이면 NewData[0]의 우측에서부터 좌로 63-i 의 위치에 1을 넣는다.

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
	//	역순열 된 값을 plainText[1]과 plainText[0]에 각각 넣는다.
	Data[1] = NewData[1];
	Data[0] = NewData[0];
}

// 처음에 헤매다가 어쩌다 보니 만들게 되었는데 잘된다.
void InverseInitialPermutation_2 (WORD* data) {
	WORD newdata[2] = {0};
	int i;
	WORD tempMask; //temp 뜻 : 임시직원
	WORD setMask;
	for(i = 0 ; i <32 ; i++) {
		tempMask = 0x00000001;
		setMask = 0x00000001<<(31-i); //비트연산자를 통해 최우측비트가 한자리수가 높아지면(1씩증가하면) 2진수 한자리씩 가져오게된다.

		if((IIP[i]<= 32) && (data[1] & setMask))
			newdata[1] |= (tempMask << (32-IIP[i]));
		else if((IIP[i]>32 && (data[1] & setMask)))
			newdata[0] |= (tempMask << (64-IIP[i]));
	}

	for(i = 32 ; i < 64 ; i++) {
		tempMask = 0x00000001;
		setMask = 0x00000001<<(63-i); //비트연산자를 통해 최우측비트가 한자리수가 높아지면(1씩증가하면) 2진수 한자리씩 가져오게된다.

		if((IIP[i]<= 32) && (data[0] & setMask))
			newdata[1] |=(tempMask << (32-IIP[i]));
		else if((IIP[i]>32 && (data[0] & setMask)))
			newdata[0] |=(tempMask << (64-IIP[i]));
	}
	puts(">>>>IIP 완료! <<<<");
	data[1]=newdata[1];		//left   32-bit
	data[0]=newdata[0];		//right 32-bit
	newdata[1]=0;
	newdata[0]=0;
}

