/*
 * Round.c
 *
 *  Created on: 2017. 3. 31.
 *      Author: ÄÄÇ»ÅÍ
 */

#include "DES.h"

Round(WORD *dWord, WORD RoundKey1, WORD RoundKey0)
{
	WORD tmp[2]= {0,0 };
	ExpansionPermutation(dWord[0], tmp);

	tmp[1] = tmp[1] ^ RoundKey1;
	tmp[0] = tmp[0] ^ RoundKey0;
	tmp[0] = SubstitutionChoice(tmp);
	tmp[0] = PermutationFunction(tmp[0]);
	tmp[0] = tmp[0] ^ dWord[1];

	dWord[1] = dWord[0];
	dWord[0] = tmp[0];
}
