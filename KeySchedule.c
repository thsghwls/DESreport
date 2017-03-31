/*
 * KeySchedule.c
 *
 *  Created on: 2017. 3. 31.
 *      Author: ��ǻ��
 */

#include "DES.h"

const unsigned char LSHIFT[]= {
		1,1,2,2,
		2,2,2,2,
		1,2,2,2,
		2,2,2,1
};

void KeySchedule(char *Key, WORD *RoundKey)
{
	// >> ����� ���� ���� <<
	int i , SHIFT=0;
	WORD dwKey[2]= {0,0 };
	WORD tmp0 = 0, tmp1 = 0;

	//	8bit�� key 8���� 64bit key(���⼱ 32bit 2��)�� ����� ���� ����
	for( i = 0 ; i < 4 ; i++)
	{
		//	8byte¥�� Ű 4���� 32bit�� ������� Shitf ��� [ 24, 16, 8 , 0 �� ��ġ�� �ش� key�� �ִ´�. ]
		SHIFT =((3-i)*8);
		//	Key 8���� 4���� 32bit������ �ִ´�. XOR����� ���� Shift������ ����� 32bit ���� dwkey[1], dwkey[0]�� ���� �ִ´�.
		//	���⼭ Key�� 8bit�̹Ƿ� ���� XOR�ϱ����� 32bit WORD������ ��������ȯ�� �Ѵ�.
		dwKey[1] ^= ((WORD)Key[i   ])<<SHIFT;
		dwKey[0] ^= ((WORD)Key[i+4])<<SHIFT;
	}

	// �������� 1�� �����Ͽ� 64bit(��32bit)�� Key�� 56bit(��28bit) Key�� ����Ѵ�.
	PermutedChoice1(dwKey);

	// 56bit key�� ������ ���� ȯ�� ����Ʈ�� �����ϰ� 48bit�� Key�� ����Ѵ�. �̸� 16ȸ �����Ͽ� RoundKey�� 16�� �����.
	for(i = 0 ; i < 16 ; i++)
	{
		//Left Shift
		if(LSHIFT[i] == 1)
		{
			//	Left 4bit ������ ���� ù��°�� �ش��ϴ� dwKey[0]�� bit�� �� �������� ������ tmp0�� �����Ѵ�.
			tmp0 = ((dwKey[0] & 0x08000000) >> 27);
			//	Left 4bit ������ ���� ù��°�� �ش��ϴ� dwKey[0]�� bit�� �� ������ bit�� �����Ͽ� �������� ��ĭ �ű�� tmp0�� OR�����Ѵ�.
			tmp0 |= ((dwKey[0] & 0x07FFFFFF) << 1);
			//	dwKey[0]�� Left 4bit�� ������ ���� ù��° ���� �������� �ű� ���� dwKey[0]�� �����Ѵ�.
			dwKey[0] = tmp0;
			// ���� �����ϴ�.
			tmp1 = ((dwKey[1] & 0x08000000) >> 27);
			tmp1 |= ((dwKey[1] & 0x07FFFFFF) << 1);
			dwKey[1] = tmp1;
		}else //2bit-shift
		{	// ���� ������ ��������� Left 4bit�� ������ ���� ù��°�� �ι�°(��, 2bit)�� �������� �ű��.
			tmp0 = ((dwKey[0] & 0x0c000000) >> 26);
			tmp0 |= ((dwKey[0] & 0x03FFFFFF) << 2);
			dwKey[0] = tmp0;
			tmp1 = ((dwKey[1] & 0x0c000000) >> 26);
			tmp1 |= ((dwKey[1] & 0x03FFFFFF) << 2);
			dwKey[1] = tmp1;
		}

		//LSHIFT[i]�� ���� �°� ���� ȯ�� ����Ʈ ������ ���� 56bit�� dwKey�� ��������2�� ���� 48bit�� ���ε� Round Key�� �����Ѵ�.
		PermutedChoice2(dwKey);

		//	��������2�� ����� ���� 48bit�� i+1 ���� Ű�� RoundKey[2*i+1]�� RoundKey[2*i]�� ���� 24bit�� ����.
		// ex) i �� 0�̸� 1���� Ű�� RoundKey[1]�� RoundKey[0]�� ���� 24bit�� ����.
		RoundKey[2*i+1]   = dwKey[1];
		RoundKey[2*i]     = dwKey[0];
		//	���� ������ Round Key�� ������� 56bit�� Key�� 48bit�� �ٲٱ��� 56bit Key�� ���� ���� dwKey[1]�� dwKey[0]�� �����Ѵ�.
		dwKey[1] = tmp1;
		dwKey[0] = tmp0;
	}
}
