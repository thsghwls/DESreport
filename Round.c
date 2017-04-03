/*
 * Round.c
 *
 *  Created on: 2017. 3. 31.
 *      Author: ��ǻ��
 */

#include "DES.h"

// >> plainText�� �ش� Round�� �ʿ��� Round Key 48bit�� �Ű������� ���� <<
void Round(WORD *dWord, WORD RoundKey1, WORD RoundKey0)
{
//	>> ���带 �����ϱ� ���� �ʿ��� ���� ���� <<
/*	32bit�� ������ �ش��ϴ� plainText[0]�� �����Ͽ� 48bit�� Ȯ���ϱ� ����
	EP�� �����Ͽ� ��� 48bit�� �����͸� 24bit�� ���������ϱ����� ����(tmp) */
	WORD tmp[2]= {0};

//	>> Ȯ������� ������ 32bit�� plainText[0]�� �����Ͽ� 48bit�� Ȯ��, Ȯ��� ����� �ޱ����� tmp�� ���� parameter�� �Ѱ��� <<
	ExpansionPermutation(dWord[0], tmp);

	// Ȯ������� ���� 48bit�� Ȯ��� �����Ͱ� �Ѿ�Դ�.(24bit �ΰ�)
	//	Ȯ��� 48bit �����Ϳ� Round Key(48bit)�� XOR ���ش�.
	tmp[1] = tmp[1] ^ RoundKey1;
	tmp[0] = tmp[0] ^ RoundKey0;

	//	���� Ű�� XOR�� 48bit �����͸� S-Box�� ���� 32bit �����ͷ� ����Ѵ�.
	tmp[0] = SubstitutionChoice(tmp);

	//	32bit�� ����� �����͸� ���� �Լ��� ���� ���ġ �Ѵ�.
	tmp[0] = PermutationFunction(tmp[0]);

	//	32bit �����Ϳ� plainText[1]�� XOR �Ѵ�.
	tmp[0] = tmp[0] ^ dWord[1];

	//	>> Left�� Right�� ���� �ٲٱ� <<
	//	plainText[0]�� plainText[1]�� �ִ´�. [ Right�� Left�� ���� ]
	dWord[1] = dWord[0];

	//	plainText[0]�� tmp[0]�� �ִ´�. [ ���带 ���� ���� ������ Left�� Right�� ������. ]
	dWord[0] = tmp[0];
}
