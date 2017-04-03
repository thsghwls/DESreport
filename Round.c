/*
 * Round.c
 *
 *  Created on: 2017. 3. 31.
 *      Author: 컴퓨터
 */

#include "DES.h"

// >> plainText와 해당 Round에 필요한 Round Key 48bit를 매개변수로 받음 <<
void Round(WORD *dWord, WORD RoundKey1, WORD RoundKey0)
{
//	>> 라운드를 수행하기 위해 필요한 변수 정의 <<
/*	32bit의 우측에 해당하는 plainText[0]을 참조하여 48bit로 확장하기 위해
	EP를 수행하여 얻는 48bit의 데이터를 24bit씩 나눠저장하기위한 공간(tmp) */
	WORD tmp[2]= {0};

//	>> 확장순열을 수행해 32bit의 plainText[0]을 참조하여 48bit로 확장, 확장된 결과를 받기위해 tmp도 같이 parameter로 넘겨줌 <<
	ExpansionPermutation(dWord[0], tmp);

	// 확장순열을 통해 48bit로 확장된 데이터가 넘어왔다.(24bit 두개)
	//	확장된 48bit 데이터와 Round Key(48bit)를 XOR 해준다.
	tmp[1] = tmp[1] ^ RoundKey1;
	tmp[0] = tmp[0] ^ RoundKey0;

	//	라운드 키와 XOR한 48bit 데이터를 S-Box를 통해 32bit 데이터로 축소한다.
	tmp[0] = SubstitutionChoice(tmp);

	//	32bit로 축소한 데이터를 순열 함수를 통해 재배치 한다.
	tmp[0] = PermutationFunction(tmp[0]);

	//	32bit 데이터와 plainText[1]를 XOR 한다.
	tmp[0] = tmp[0] ^ dWord[1];

	//	>> Left와 Right를 서로 바꾸기 <<
	//	plainText[0]을 plainText[1]에 넣는다. [ Right를 Left에 넣음 ]
	dWord[1] = dWord[0];

	//	plainText[0]에 tmp[0]를 넣는다. [ 라운드를 통해 얻은 수정된 Left를 Right에 넣은다. ]
	dWord[0] = tmp[0];
}
