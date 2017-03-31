/*
 * DES.c
 *
 *  Created on: 2017. 3. 28.
 *      Author: Computer
 */

#include "DES.h"

int main (void) {
	// >> 사용할 변수 정의 <<
	int i;
	//	64bit 평문 준비 [ Left(32bit) = plainText[1] , Right(32bit) = plainText[0] ]
	WORD plainText[2] = {0x45454545 , 0x85664863};
	//	64bit(8 x 8bit)의 key 준비
	char key[8]		      = {'x','z','e','w','h','k','k','y'};
	//	각 라운드에 들어갈 48bit의 Round Key 준비 [ key하나로 서로다른 16개의 Round key 준비, 24bit씩 들어가야 하므로 WORD 32개 선언 ]
	WORD roundKey[32] = {0};

	// >> 각 Round에 사용할 Round Key 생성 << [ 총16개 ]
	puts("=========== >> Round Key 생성 << ===========");
	KeySchedule(key, roundKey);

	//	평문확인
	puts("==== plainText_64bit ====");
	viewBlock4x8(plainText[1]);
	viewBlock4x8(plainText[0]);
	puts("");

	//	DES Encryption (암호화)
	puts("=========== >> 암호화 과정 << ===========");

	//	>> 1. IP 초기순열 << [ parameter로 평문을 전달 ]
	InitialPermutation(plainText);
	puts("==== 초기순열(IP) 결과 ====");
	viewBlock4x8(plainText[1]);
	viewBlock4x8(plainText[0]);
	puts("");

	//	>> 2. Round 16회 반복 << [ Round Key를 roundKey[1], [0] 부터 roundKey[31], [30]까지 순서대로 써야하니 i는 0부터 시작 ]
	puts("==== 라운드 16회 반복 ====");
	for(i = 0 ; i < 16 ; i++)
		Round(plainText, roundKey[2*i+1],roundKey[2*i]);

	//	>> 3. 라운드 마지막에 스왑 << [ 16라운드를 수행한 data의 Left 와 Right를 바꿔준다. ]
	swap32bit(plainText);
	puts("==== Swap 결과 ====");
	viewBlock4x8(plainText[1]);
	viewBlock4x8(plainText[0]);
	puts("");

	//	>> 4. IIP 역 순열 <<
	InverseInitialPermutation(plainText);
	puts("==== 역 순열(IIP) 결과 ====");
	viewBlock4x8(plainText[1]);
	viewBlock4x8(plainText[0]);
	puts("");
	puts("=========== >> 암호화 완료 << ===========");

	//	DES Decryption (복호화) [ 암호화의 역순 ]
	puts("=========== >> 복호화 과정 << ===========");

	//	>> 1. IP 초기순열 << [ 역순열(IIP)에 순열(IP)을 하면 IIP이전의 상태로 복귀 ]
	InitialPermutation(plainText);
	puts("==== 초기순열(IP) 결과 ====");
	viewBlock4x8(plainText[1]);
	viewBlock4x8(plainText[0]);
	puts("");

	//	>> 2. Round 16회 반복 << [ Round Key를 암호화의 역순으로 써야하니 i는 15부터 1씩 감소 ]
	puts("==== 라운드 16회 반복 ====");
	for(i = 15 ; i >= 0 ; i--)
		Round(plainText, roundKey[2*i+1],roundKey[2*i]);

	//	>> 3. 라운드 마지막에 스왑 << [ 16라운드를 수행한 data의 Left 와 Right를 바꿔준다. ]
	swap32bit(plainText);
	puts("==== Swap 결과 ====");
	viewBlock4x8(plainText[1]);
	viewBlock4x8(plainText[0]);
	puts("");

	//	>> 4. IIP 역 순열 << [ 순열(IP)에 역순열(IIP)을 하면 IP이전의 상태로 복귀 ]
	InverseInitialPermutation(plainText);
	puts("==== 역 순열(IIP) 결과 ====");
	viewBlock4x8(plainText[1]);
	viewBlock4x8(plainText[0]);
	puts("");
	puts("================ 복호화 완료================");
	return 0;
}




