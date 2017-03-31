/*
 * DES.c
 *
 *  Created on: 2017. 3. 28.
 *      Author: Computer
 */

#include "DES.h"

int main (void) {
	// >> ����� ���� ���� <<
	int i;
	//	64bit �� �غ� [ Left(32bit) = plainText[1] , Right(32bit) = plainText[0] ]
	WORD plainText[2] = {0x45454545 , 0x85664863};
	//	64bit(8 x 8bit)�� key �غ�
	char key[8]		      = {'x','z','e','w','h','k','k','y'};
	//	�� ���忡 �� 48bit�� Round Key �غ� [ key�ϳ��� ���δٸ� 16���� Round key �غ�, 24bit�� ���� �ϹǷ� WORD 32�� ���� ]
	WORD roundKey[32] = {0};

	// >> �� Round�� ����� Round Key ���� << [ ��16�� ]
	puts("=========== >> Round Key ���� << ===========");
	KeySchedule(key, roundKey);

	//	��Ȯ��
	puts("==== plainText_64bit ====");
	viewBlock4x8(plainText[1]);
	viewBlock4x8(plainText[0]);
	puts("");

	//	DES Encryption (��ȣȭ)
	puts("=========== >> ��ȣȭ ���� << ===========");

	//	>> 1. IP �ʱ���� << [ parameter�� ���� ���� ]
	InitialPermutation(plainText);
	puts("==== �ʱ����(IP) ��� ====");
	viewBlock4x8(plainText[1]);
	viewBlock4x8(plainText[0]);
	puts("");

	//	>> 2. Round 16ȸ �ݺ� << [ Round Key�� roundKey[1], [0] ���� roundKey[31], [30]���� ������� ����ϴ� i�� 0���� ���� ]
	puts("==== ���� 16ȸ �ݺ� ====");
	for(i = 0 ; i < 16 ; i++)
		Round(plainText, roundKey[2*i+1],roundKey[2*i]);

	//	>> 3. ���� �������� ���� << [ 16���带 ������ data�� Left �� Right�� �ٲ��ش�. ]
	swap32bit(plainText);
	puts("==== Swap ��� ====");
	viewBlock4x8(plainText[1]);
	viewBlock4x8(plainText[0]);
	puts("");

	//	>> 4. IIP �� ���� <<
	InverseInitialPermutation(plainText);
	puts("==== �� ����(IIP) ��� ====");
	viewBlock4x8(plainText[1]);
	viewBlock4x8(plainText[0]);
	puts("");
	puts("=========== >> ��ȣȭ �Ϸ� << ===========");

	//	DES Decryption (��ȣȭ) [ ��ȣȭ�� ���� ]
	puts("=========== >> ��ȣȭ ���� << ===========");

	//	>> 1. IP �ʱ���� << [ ������(IIP)�� ����(IP)�� �ϸ� IIP������ ���·� ���� ]
	InitialPermutation(plainText);
	puts("==== �ʱ����(IP) ��� ====");
	viewBlock4x8(plainText[1]);
	viewBlock4x8(plainText[0]);
	puts("");

	//	>> 2. Round 16ȸ �ݺ� << [ Round Key�� ��ȣȭ�� �������� ����ϴ� i�� 15���� 1�� ���� ]
	puts("==== ���� 16ȸ �ݺ� ====");
	for(i = 15 ; i >= 0 ; i--)
		Round(plainText, roundKey[2*i+1],roundKey[2*i]);

	//	>> 3. ���� �������� ���� << [ 16���带 ������ data�� Left �� Right�� �ٲ��ش�. ]
	swap32bit(plainText);
	puts("==== Swap ��� ====");
	viewBlock4x8(plainText[1]);
	viewBlock4x8(plainText[0]);
	puts("");

	//	>> 4. IIP �� ���� << [ ����(IP)�� ������(IIP)�� �ϸ� IP������ ���·� ���� ]
	InverseInitialPermutation(plainText);
	puts("==== �� ����(IIP) ��� ====");
	viewBlock4x8(plainText[1]);
	viewBlock4x8(plainText[0]);
	puts("");
	puts("================ ��ȣȭ �Ϸ�================");
	return 0;
}




