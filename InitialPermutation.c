/*
 * InitialPermutation.c
 *
 *  Created on: 2017. 3. 30.
 *      Author: 컴퓨터
 */

#include "DES.h"

BIT IP[] = {58, 50, 42, 34, 26, 18, 10, 2,
		60, 52, 44, 36, 28, 20, 12, 4,
		62, 54, 46, 38, 30, 22, 14, 6,
		64, 56, 48, 40, 32, 24, 16, 8,
		57, 49, 41, 33, 25, 17,  9, 1,
		59, 51, 43, 35, 27, 19, 11, 3,
		61, 53, 45, 37, 29, 21, 13, 5,
		63, 55, 47, 39, 31, 23, 15, 7};

//	IP[i]가 1~32일때 tmpMask를 32-IP[i]만큼 비트를 좌측으로 옮기게 되면 IP[i]의 위치에 있는 plainText의 값을 검출할 수 있다.
void InitialPermutation(WORD *Data)
{
	//	>> 사용할 변수 정의 <<
	int i;
	//	plainText의 IP에 해당하는 비트 검출위해 사용
	WORD tmpMask;
	//	NewData 즉, 초기순열 이후의 plainText값을 우측부터 좌측순으로 넣기위해 사용 [ ex) 좌측<< 00000000 ...00000001 <<우측 ]
	WORD setMask;
	//	plainText의 평문을 비교하며 초기순열을 만들어야하기때문에 빈 공간인 NewData 생성 후 마지막에 plainText값을 변경하기위해 사용
	WORD NewData[2]= {0};

	//	>> 평문을 32bit씩 끊어서 Left와 Right로 나눴기 때문에 PI[0]~PI[31]과 PI[32]~PI[63]를 나눠 Initial Permutation 한다.

	//	>> IP[]의 4 x 8 (PI[0]~PI[31])에 해당하는 32bit를 검출하는데, IP[i]에 해당하는 위치에 있는(*참고로 여기서 해당위치는 좌측기준이다.)
	//		 plainText의 bit가 1일경우만 NewData[1]의 해당위치에 1을 저장한다. (NewData는 이미 0으로 초기화 되어있기 때문)
	//		 그리고 NewData[1]의 해당위치는 setMask가 R부터 L순으로 가르키기 때문에 우측기준이다. <<
	for(i = 31 ; i >= 0 ; i--)
	{
		tmpMask = 0x00000001; // 좌측기준으로 IP[i]의 숫자에 해당하는 위치의 비트를 가리킨다. 그 위치의 plainText가 1일경우 and연산으로
										 // True가 된다.
		setMask = 0x00000001<<(31-i);	// NewData[1]의 우측부터 좌측으로 i만큼 이동하며 가리킨다. (만약 검출된 plainText bit가 1일경우 Set)
		if((IP[i] <= 32) && (Data[1] & (tmpMask << (32-IP[i])))) {
			NewData[1] = NewData[1] | setMask;
		}else if((IP[i] > 32) && (Data[0] & (tmpMask << (64-IP[i])))){
			NewData[1] = NewData[1] | setMask;
		}
		// 위처럼 if , else if로 32이상과 32미만을 나누는 이유는 평문을 32bit씩 나누었기 때문
	}

	//	>> 위와 동일한데 이번에는 plainTextd에서 IP[]의 4 x 8 (PI[0]~PI[31])에 해당하는 위치에 있는 32bit를 검출하여
	//		 NewData[0]에 우측부터 넣는다. <<
	for(i = 63 ; i >=32 ; i--)
	{
		tmpMask = 0x00000001;
		setMask = 0x00000001<<(63-i);
		if((IP[i] <= 32) && (Data[1] & (tmpMask << (32-IP[i])))) {
			NewData[0] = NewData[0] | setMask;
		}else if((IP[i] > 32) && (Data[0] & (tmpMask << (64-IP[i])))) {
			NewData[0] = NewData[0] | setMask;
		}
	}
	// 초기 순열 된 값을 plainText에 각각 넣는다. [ IP END ]
	Data[1] = NewData[1];
	Data[0] = NewData[0];
}


//	어쩌다보니 처음에 헤매다가 만들었는데 잘된다.
void InitialPermutation_2 (WORD* data) {
	int i;
	WORD newdata[2] = {0};
	WORD tempMask; //temp 뜻 : 임시직원
	WORD setMask;
	for(i = 0 ; i <32 ; i++) {
		tempMask = 0x00000001;
		setMask = 0x00000001<<(31-i); //비트연산자를 통해 최우측비트가 한자리수가 높아지면(1씩증가하면) 2진수 한자리씩 가져오게된다.

		//		동작부분
		if((IP[i]<= 32) && (data[1] & setMask))
			newdata[1] |= (tempMask << (32-IP[i]));
		else if((IP[i]>32 && (data[1] & setMask)))
			newdata[0] |= (tempMask << (64-IP[i]));
	}
	//		동작부분
	for(i = 32 ; i < 64 ; i++) {
		tempMask = 0x00000001;
		setMask = 0x00000001<<(63-i); //비트연산자를 통해 최우측비트가 한자리수가 높아지면(1씩증가하면) 2진수 한자리씩 가져오게된다.

		if((IP[i]<= 32) && (data[0] & setMask))
			newdata[1] |=(tempMask << (32-IP[i]));
		else if((IP[i]>32 && (data[0] & setMask)))
			newdata[0] |=(tempMask << (64-IP[i]));

	}
	data[1]=newdata[1];		//left   32-bit
	data[0]=newdata[0];		//right 32-bit
	newdata[1]=0;
	newdata[0]=0;
	puts(">>>>IP 완료! <<<<");

}

