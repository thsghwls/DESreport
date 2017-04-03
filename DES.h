/*
 * DES.h
 *
 *  Created on: 2017. 3. 30.
 *      Author: ��ǻ��
 */

#include<stdio.h>

#ifndef DES_H_
#define DES_H_

typedef unsigned char  BIT;
typedef unsigned long WORD;

void viewBlock4x8 (WORD block);

//	>> �� Round�� ����� Round Key ���� << [ ��16�� ]
void KeySchedule(char *Key, WORD *RoundKey);
void PermutedChoice1(WORD *Key);
void PermutedChoice2(WORD *Key);

//	>> 1. IP �ʱ���� << [ parameter�� ���� ���� ]
void InitialPermutation(WORD *Data);
//	>> 2. Round 16ȸ �ݺ� << [ Round Key�� roundKey[1], [0] ���� roundKey[31], [30]���� ������� ����ϴ� i�� 0���� ���� ]
void Round(WORD *dWord, WORD RoundKey1, WORD RoundKey0);
void ExpansionPermutation (WORD RightHalf, WORD *eWord);
WORD SubstitutionChoice(WORD *eWord);
WORD PermutationFunction(WORD dWord);
//	>> 3. ���� �������� ���� << [ 16���带 ������ data�� Left �� Right�� �ٲ��ش�. ]
void swap32bit(WORD *Data);
void InverseInitialPermutation(WORD *Data);

// ó���� ��Ŵ� ������µ� �ߵȴ�.
void InitialPermutation_2 (WORD* data);
void InverseInitialPermutation_2 (WORD* data);

#endif /* DES_H_ */
