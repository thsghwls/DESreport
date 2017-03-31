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
	WORD key[2]		 = {0xFFFFFFFF, 0xFFFFFFFF};	//key[1] : left , key[0] : right
	WORD exData[2]   = {0};
	WORD SCtemp = 0; //SBOX이후 L와 XOR하기위한 빈공간
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
	//2. 16라운드 실시
	puts("==== DES 16라운드 시작 ====");
	for(i = 0 ; i <16 ; i++) {
		//2-1. EP : 확장순열 (R)32-> 48
		ExpansionPermutation (plainText[0], exData);
		//각 exData의 상위 8비트는 미사용, 나머지 24비트 더하면 48비트의 확장순열이 된다
		printf("==== %d 라운드 2-1. 확장순열(EP) 결과 ====\n", i+1);
		viewBlock4x8(exData[1]);
		viewBlock4x8(exData[0]);
		puts("");

		//2-2. 64bit KEY에서 8x8행렬상태의 오른쪽 8비트를 버린 후 나머지 56비트를 28 28 비트씩 나눈다.
		printf("==== %d 라운드 2-2-1. PC_1전 KEY ====\n", i+1);
		viewBlock4x8(key[1]);
		viewBlock4x8(key[0]);
		puts("");

		PermutedChoice1(key);
		printf("==== %d 라운드 2-2-2. key를 오른쪽 8비트 버리고 56비트로 만든 결과 ====\n", i+1);
		viewBlock4x8(key[1]);
		viewBlock4x8(key[0]);
		puts("");

		//2-3. 56bit KEY를 48bit의 KEY로 줄인다.
		PermutedChoice2(key);
		printf("==== %d 라운드 2-3. 56bit KEY를 48bit KEY로 바꿈 ====\n", i+1);
		viewBlock4x8(key[1]);
		viewBlock4x8(key[0]);
		puts("");

		//2-4. 48bit KEY를  2-1 EP의 결과인 epdata와 XOR 한다
		exData[1] = exData[1]^key[1];
		exData[0] = exData[0]^key[0];
		printf("==== %d 라운드 2-4. XOR 결과(아직 48bit) ====\n", i+1);
		viewBlock4x8(exData[1]);
		viewBlock4x8(exData[0]);
		puts("");

		//2-5. 48bit를 S-BOX를 통해 32bit로 작아진다.
		SCtemp = SubstitutionChoice(exData);
		printf("==== %d 라운드 2-5. S-BOX사용 하여 48->32bit되기 ====\n", i+1);
		viewBlock4x8(SCtemp);
		viewBlock4x8(SCtemp);
		puts("");

		//2-6. permutation 순열함수 한번더!
		SCtemp = PermutationFunction(SCtemp);
		printf("==== %d 라운드 2-6. 순열함수로 처음처럼 한번더 꼬기 ====\n", i+1);
		viewBlock4x8(SCtemp);
		viewBlock4x8(SCtemp);
		puts("");

		//2-7. 마지막으로 XOR
		plainText[1] = plainText[1]^SCtemp;
		printf("==== %d 라운드 2-7. 마지막과정 Left(32bit)에 Left^SCtemp(XOR) ====\n", i+1);
		viewBlock4x8(plainText[1]);
		puts("");

		printf("==== %d 라운드 2-8-1. 추가로 좌우 바꾸기 전 ====\n", i+1);
		viewBlock4x8(plainText[1]);
		viewBlock4x8(plainText[0]);
		puts("");

		//2-8. 좌우 바꾸기
		swap32bit(plainText);
		printf("==== %d 라운드 2-8-2. 좌우 바꾼 뒤 ====\n", i+1);
		viewBlock4x8(plainText[1]);
		viewBlock4x8(plainText[0]);
		puts("");
		printf("==== %d라운드 종료 ====\n", i+1);
	}
	//3. 마지막에 역 순열 적용
	InverseInitialPermutation(plainText);
	puts("==== 역 순열(IIP) 결과 ====");
	viewBlock4x8(plainText[1]);
	viewBlock4x8(plainText[0]);
	puts("");
	//DES 복호화 알고리즘(역순)
	//	puts("================ 복호화 ================");
	//	//1.IP 초기순열
	//	InitialPermutation(plainText);
	//	puts("==== 초기순열(IP) 결과 ====");
	//	viewBlock4x8(plainText[1]);
	//	viewBlock4x8(plainText[0]);
	//	puts("");
	//	//2. 16라운드 실시
	//	puts("==== DES 16라운드 시작 ====");
	//	for(i = 0 ; i <16 ; i++) {
	//		//2-1. EP : 확장순열 (R)32-> 48
	//		ExpansionPermutation (plainText[0], exData);
	//		//각 exData의 상위 8비트는 미사용, 나머지 24비트 더하면 48비트의 확장순열이 된다
	//		printf("==== %d 라운드 2-1. 확장순열(EP) 결과 ====\n", i+1);
	//		viewBlock4x8(exData[1]);
	//		viewBlock4x8(exData[0]);
	//		puts("");
	//
	//		//2-2. 64bit KEY에서 8x8행렬상태의 오른쪽 8비트를 버린 후 나머지 56비트를 28 28 비트씩 나눈다.
	//		printf("==== %d 라운드 2-2-1. PC_1전 KEY ====\n", i+1);
	//		viewBlock4x8(key[1]);
	//		viewBlock4x8(key[0]);
	//		puts("");
	//
	//		PermutedChoice1(key);
	//		printf("==== %d 라운드 2-2-2. key를 오른쪽 8비트 버리고 56비트로 만든 결과 ====\n", i+1);
	//		viewBlock4x8(key[1]);
	//		viewBlock4x8(key[0]);
	//		puts("");
	//
	//		//2-3. 56bit KEY를 48bit의 KEY로 줄인다.
	//		PermutedChoice2(key);
	//		printf("==== %d 라운드 2-3. 56bit KEY를 48bit KEY로 바꿈 ====\n", i+1);
	//		viewBlock4x8(key[1]);
	//		viewBlock4x8(key[0]);
	//		puts("");
	//
	//		//2-4. 48bit KEY를  2-1 EP의 결과인 epdata와 XOR 한다
	//		exData[1] = exData[1]^key[1];
	//		exData[0] = exData[0]^key[0];
	//		printf("==== %d 라운드 2-4. XOR 결과(아직 48bit) ====\n", i+1);
	//		viewBlock4x8(exData[1]);
	//		viewBlock4x8(exData[0]);
	//		puts("");
	//
	//		//2-5. 48bit를 S-BOX를 통해 32bit로 작아진다.
	//		SCtemp = SubstitutionChoice(exData);
	//		printf("==== %d 라운드 2-5. S-BOX사용 하여 48->32bit되기 ====\n", i+1);
	//		viewBlock4x8(SCtemp);
	//		viewBlock4x8(SCtemp);
	//		puts("");
	//
	//		//2-6. permutation 순열함수 한번더!
	//		SCtemp = PermutationFunction(SCtemp);
	//		printf("==== %d 라운드 2-6. 순열함수로 처음처럼 한번더 꼬기 ====\n", i+1);
	//		viewBlock4x8(SCtemp);
	//		viewBlock4x8(SCtemp);
	//		puts("");
	//
	//		//2-7. 마지막으로 XOR
	//		plainText[1] = plainText[1]^SCtemp;
	//		printf("==== %d 라운드 2-7. 마지막과정 Left(32bit)에 Left^SCtemp(XOR) ====\n", i+1);
	//		viewBlock4x8(plainText[1]);
	//		puts("");
	//
	//		printf("==== %d 라운드 2-8-1. 추가로 좌우 바꾸기 전 ====\n", i+1);
	//		viewBlock4x8(plainText[1]);
	//		viewBlock4x8(plainText[0]);
	//		puts("");
	//
	//		//2-8. 좌우 바꾸기
	//		swap32bit(plainText);
	//		printf("==== %d 라운드 2-8-2. 좌우 바꾼 뒤 ====\n", i+1);
	//		viewBlock4x8(plainText[1]);
	//		viewBlock4x8(plainText[0]);
	//		puts("");
	//		printf("==== %d라운드 종료 ====\n", i+1);
	//	}
	//	//3. 마지막에 역 순열 적용
	//	InverseInitialPermutation(plainText);
	//	puts("==== 역 순열(IIP) 결과 ====");
	//	viewBlock4x8(plainText[1]);
	//	viewBlock4x8(plainText[0]);
	//	puts("");
	return 0;
}




