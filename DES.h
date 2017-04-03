/*
 * DES.h
 *
 *  Created on: 2017. 3. 30.
 *      Author: 컴퓨터
 */

#include<stdio.h>

#ifndef DES_H_
#define DES_H_

typedef unsigned char  BIT;
typedef unsigned long WORD;

void viewBlock4x8 (WORD block);

//	>> 각 Round에 사용할 Round Key 생성 << [ 총16개 ]
void KeySchedule(char *Key, WORD *RoundKey);
void PermutedChoice1(WORD *Key);
void PermutedChoice2(WORD *Key);

//	>> 1. IP 초기순열 << [ parameter로 평문을 전달 ]
void InitialPermutation(WORD *Data);
//	>> 2. Round 16회 반복 << [ Round Key를 roundKey[1], [0] 부터 roundKey[31], [30]까지 순서대로 써야하니 i는 0부터 시작 ]
void Round(WORD *dWord, WORD RoundKey1, WORD RoundKey0);
void ExpansionPermutation (WORD RightHalf, WORD *eWord);
WORD SubstitutionChoice(WORD *eWord);
WORD PermutationFunction(WORD dWord);
//	>> 3. 라운드 마지막에 스왑 << [ 16라운드를 수행한 data의 Left 와 Right를 바꿔준다. ]
void swap32bit(WORD *Data);
void InverseInitialPermutation(WORD *Data);

// 처음에 헤매다 만들었는데 잘된다.
void InitialPermutation_2 (WORD* data);
void InverseInitialPermutation_2 (WORD* data);

#endif /* DES_H_ */
