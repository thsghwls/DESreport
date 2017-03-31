/*
 * DES.h
 *
 *  Created on: 2017. 3. 30.
 *      Author: ÄÄÇ»ÅÍ
 */

#include<stdio.h>

#ifndef DES_H_
#define DES_H_

typedef unsigned char  BIT;
typedef unsigned long WORD;

void viewBlock4x8 (WORD);

void KeySchedule(char *Key, WORD *RoundKey);
void PermutedChoice1(WORD *Key);
void PermutedChoice2(WORD *Key);

void InitialPermutation(WORD *Data);
void Round(WORD *dWord, WORD RoundKey1, WORD RoundKey0);
void ExpansionPermutation (WORD RightHalf, WORD *eWord);
WORD SubstitutionChoice(WORD *eWord);
WORD PermutationFunction(WORD dWord);
void swap32bit(WORD *Data);
void InverseInitialPermutation(WORD *Data);

void InitialPermutation_2 (WORD* data);
void InverseInitialPermutation_2 (WORD* data);

#endif /* DES_H_ */
