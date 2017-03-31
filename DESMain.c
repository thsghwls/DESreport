/*
 * DES.c
 *
 *  Created on: 2017. 3. 28.
 *      Author: Computer
 */

#include "DES.h"
//	16진수 0x00000000의 뒤의 숫자0 8개가 각각 2진수 4bit씩 나타낸다.

int main (void) {
	WORD plainText[2] = {0x55555555, 0x12312312};		//plainText[1] : left ,  plainText[0] : right
	char key[8]		 = {'a','b','c','d','e','f','g','h'};	//key[1] : left , key[0] : right
	WORD roundKey[32] = {0};
	int i;

	//평문확인
	puts("==== plainText_64bit ====");
	viewBlock4x8(plainText[1]);
	viewBlock4x8(plainText[0]);
	puts("");

	//DES 암호화 알고리즘
	puts("================ 암호화 ================");
	//1.IP 초기순열
	InitialPermutation(plainText);
	puts("==== 초기순열(IP) 결과 ====");
	viewBlock4x8(plainText[1]);
	viewBlock4x8(plainText[0]);
	puts("");

	//2.라운드 키 생성
	KeySchedule(key, roundKey);

	//3.16라운드
	for(i = 0 ; i < 16 ; i++)
		Round(plainText[1], roundKey[i+1],roundKey[i]);

	//4.라운드 마지막에 스왑
	swap32bit(plainText);

	//5.IIP 역순열
	InverseInitialPermutation(plainText);
	puts("==== 역 순열(IIP) 결과 ====");
	viewBlock4x8(plainText[1]);
	viewBlock4x8(plainText[0]);
	puts("");

	puts("================ 암호화 완료================");
	return 0;
}




