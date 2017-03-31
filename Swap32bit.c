/*
 * Swap32.c
 *
 *  Created on: 2017. 3. 30.
 *      Author: ÄÄÇ»ÅÍ
 */

#include "DES.h"

void swap32bit(WORD *Data)

{
	WORD temp;
	temp = Data[0];
	Data[0] = Data[1];
	Data[1] = temp;
}
