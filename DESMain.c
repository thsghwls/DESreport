/*
 * DES.c
 *
 *  Created on: 2017. 3. 28.
 *      Author: Computer
 */

#include "DES.h"
//	16���� 0x00000000�� ���� ����0 8���� ���� 2���� 4bit�� ��Ÿ����.

int main (void) {
	WORD plainText[2] = {0x55555555, 0x12312312};		//plainText[1] : left ,  plainText[0] : right
	WORD key[2]		 = {0xFFFFFFFF, 0xFFFFFFFF};	//key[1] : left , key[0] : right
	WORD exData[2]   = {0};
	WORD SCtemp = 0; //SBOX���� L�� XOR�ϱ����� �����
	int i;
	//��Ȯ��
	puts("==== plainText_64bit ====");
	viewBlock4x8(plainText[1]);
	viewBlock4x8(plainText[0]);
	puts("");

	//DES ��ȣȭ �˰���
	puts("================ ��ȣȭ ================");
	//1.IP �ʱ����
	InitialPermutation(plainText);
	puts("==== �ʱ����(IP) ��� ====");
	viewBlock4x8(plainText[1]);
	viewBlock4x8(plainText[0]);
	puts("");
	//2. 16���� �ǽ�
	puts("==== DES 16���� ���� ====");
	for(i = 0 ; i <16 ; i++) {
		//2-1. EP : Ȯ����� (R)32-> 48
		ExpansionPermutation (plainText[0], exData);
		//�� exData�� ���� 8��Ʈ�� �̻��, ������ 24��Ʈ ���ϸ� 48��Ʈ�� Ȯ������� �ȴ�
		printf("==== %d ���� 2-1. Ȯ�����(EP) ��� ====\n", i+1);
		viewBlock4x8(exData[1]);
		viewBlock4x8(exData[0]);
		puts("");

		//2-2. 64bit KEY���� 8x8��Ļ����� ������ 8��Ʈ�� ���� �� ������ 56��Ʈ�� 28 28 ��Ʈ�� ������.
		printf("==== %d ���� 2-2-1. PC_1�� KEY ====\n", i+1);
		viewBlock4x8(key[1]);
		viewBlock4x8(key[0]);
		puts("");

		PermutedChoice1(key);
		printf("==== %d ���� 2-2-2. key�� ������ 8��Ʈ ������ 56��Ʈ�� ���� ��� ====\n", i+1);
		viewBlock4x8(key[1]);
		viewBlock4x8(key[0]);
		puts("");

		//2-3. 56bit KEY�� 48bit�� KEY�� ���δ�.
		PermutedChoice2(key);
		printf("==== %d ���� 2-3. 56bit KEY�� 48bit KEY�� �ٲ� ====\n", i+1);
		viewBlock4x8(key[1]);
		viewBlock4x8(key[0]);
		puts("");

		//2-4. 48bit KEY��  2-1 EP�� ����� epdata�� XOR �Ѵ�
		exData[1] = exData[1]^key[1];
		exData[0] = exData[0]^key[0];
		printf("==== %d ���� 2-4. XOR ���(���� 48bit) ====\n", i+1);
		viewBlock4x8(exData[1]);
		viewBlock4x8(exData[0]);
		puts("");

		//2-5. 48bit�� S-BOX�� ���� 32bit�� �۾�����.
		SCtemp = SubstitutionChoice(exData);
		printf("==== %d ���� 2-5. S-BOX��� �Ͽ� 48->32bit�Ǳ� ====\n", i+1);
		viewBlock4x8(SCtemp);
		viewBlock4x8(SCtemp);
		puts("");

		//2-6. permutation �����Լ� �ѹ���!
		SCtemp = PermutationFunction(SCtemp);
		printf("==== %d ���� 2-6. �����Լ��� ó��ó�� �ѹ��� ���� ====\n", i+1);
		viewBlock4x8(SCtemp);
		viewBlock4x8(SCtemp);
		puts("");

		//2-7. ���������� XOR
		plainText[1] = plainText[1]^SCtemp;
		printf("==== %d ���� 2-7. ���������� Left(32bit)�� Left^SCtemp(XOR) ====\n", i+1);
		viewBlock4x8(plainText[1]);
		puts("");

		printf("==== %d ���� 2-8-1. �߰��� �¿� �ٲٱ� �� ====\n", i+1);
		viewBlock4x8(plainText[1]);
		viewBlock4x8(plainText[0]);
		puts("");

		//2-8. �¿� �ٲٱ�
		swap32bit(plainText);
		printf("==== %d ���� 2-8-2. �¿� �ٲ� �� ====\n", i+1);
		viewBlock4x8(plainText[1]);
		viewBlock4x8(plainText[0]);
		puts("");
		printf("==== %d���� ���� ====\n", i+1);
	}
	//3. �������� �� ���� ����
	InverseInitialPermutation(plainText);
	puts("==== �� ����(IIP) ��� ====");
	viewBlock4x8(plainText[1]);
	viewBlock4x8(plainText[0]);
	puts("");
	//DES ��ȣȭ �˰���(����)
	//	puts("================ ��ȣȭ ================");
	//	//1.IP �ʱ����
	//	InitialPermutation(plainText);
	//	puts("==== �ʱ����(IP) ��� ====");
	//	viewBlock4x8(plainText[1]);
	//	viewBlock4x8(plainText[0]);
	//	puts("");
	//	//2. 16���� �ǽ�
	//	puts("==== DES 16���� ���� ====");
	//	for(i = 0 ; i <16 ; i++) {
	//		//2-1. EP : Ȯ����� (R)32-> 48
	//		ExpansionPermutation (plainText[0], exData);
	//		//�� exData�� ���� 8��Ʈ�� �̻��, ������ 24��Ʈ ���ϸ� 48��Ʈ�� Ȯ������� �ȴ�
	//		printf("==== %d ���� 2-1. Ȯ�����(EP) ��� ====\n", i+1);
	//		viewBlock4x8(exData[1]);
	//		viewBlock4x8(exData[0]);
	//		puts("");
	//
	//		//2-2. 64bit KEY���� 8x8��Ļ����� ������ 8��Ʈ�� ���� �� ������ 56��Ʈ�� 28 28 ��Ʈ�� ������.
	//		printf("==== %d ���� 2-2-1. PC_1�� KEY ====\n", i+1);
	//		viewBlock4x8(key[1]);
	//		viewBlock4x8(key[0]);
	//		puts("");
	//
	//		PermutedChoice1(key);
	//		printf("==== %d ���� 2-2-2. key�� ������ 8��Ʈ ������ 56��Ʈ�� ���� ��� ====\n", i+1);
	//		viewBlock4x8(key[1]);
	//		viewBlock4x8(key[0]);
	//		puts("");
	//
	//		//2-3. 56bit KEY�� 48bit�� KEY�� ���δ�.
	//		PermutedChoice2(key);
	//		printf("==== %d ���� 2-3. 56bit KEY�� 48bit KEY�� �ٲ� ====\n", i+1);
	//		viewBlock4x8(key[1]);
	//		viewBlock4x8(key[0]);
	//		puts("");
	//
	//		//2-4. 48bit KEY��  2-1 EP�� ����� epdata�� XOR �Ѵ�
	//		exData[1] = exData[1]^key[1];
	//		exData[0] = exData[0]^key[0];
	//		printf("==== %d ���� 2-4. XOR ���(���� 48bit) ====\n", i+1);
	//		viewBlock4x8(exData[1]);
	//		viewBlock4x8(exData[0]);
	//		puts("");
	//
	//		//2-5. 48bit�� S-BOX�� ���� 32bit�� �۾�����.
	//		SCtemp = SubstitutionChoice(exData);
	//		printf("==== %d ���� 2-5. S-BOX��� �Ͽ� 48->32bit�Ǳ� ====\n", i+1);
	//		viewBlock4x8(SCtemp);
	//		viewBlock4x8(SCtemp);
	//		puts("");
	//
	//		//2-6. permutation �����Լ� �ѹ���!
	//		SCtemp = PermutationFunction(SCtemp);
	//		printf("==== %d ���� 2-6. �����Լ��� ó��ó�� �ѹ��� ���� ====\n", i+1);
	//		viewBlock4x8(SCtemp);
	//		viewBlock4x8(SCtemp);
	//		puts("");
	//
	//		//2-7. ���������� XOR
	//		plainText[1] = plainText[1]^SCtemp;
	//		printf("==== %d ���� 2-7. ���������� Left(32bit)�� Left^SCtemp(XOR) ====\n", i+1);
	//		viewBlock4x8(plainText[1]);
	//		puts("");
	//
	//		printf("==== %d ���� 2-8-1. �߰��� �¿� �ٲٱ� �� ====\n", i+1);
	//		viewBlock4x8(plainText[1]);
	//		viewBlock4x8(plainText[0]);
	//		puts("");
	//
	//		//2-8. �¿� �ٲٱ�
	//		swap32bit(plainText);
	//		printf("==== %d ���� 2-8-2. �¿� �ٲ� �� ====\n", i+1);
	//		viewBlock4x8(plainText[1]);
	//		viewBlock4x8(plainText[0]);
	//		puts("");
	//		printf("==== %d���� ���� ====\n", i+1);
	//	}
	//	//3. �������� �� ���� ����
	//	InverseInitialPermutation(plainText);
	//	puts("==== �� ����(IIP) ��� ====");
	//	viewBlock4x8(plainText[1]);
	//	viewBlock4x8(plainText[0]);
	//	puts("");
	return 0;
}




