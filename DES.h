/*
 * DES.h
 *
 *  Created on: 2017. 3. 30.
 *      Author: 컴퓨터
 */
#include<stdio.h>

#ifndef DES_H_
#define DES_H_

#endif /* DES_H_ */

typedef unsigned char  BIT;
typedef unsigned short HWORD;	//Half Word
typedef unsigned long WORD;		//Word

BIT IP[] = {58, 50, 42, 34, 26, 18, 10, 2,
		60, 52, 44, 36, 28, 20, 12, 4,
		62, 54, 46, 38, 30, 22, 14, 6,
		64, 56, 48, 40, 32, 24, 16, 8,
		57, 49, 41, 33, 25, 17,  9, 1,
		59, 51, 43, 35, 27, 19, 11, 3,
		61, 53, 45, 37, 29, 21, 13, 5,
		63, 55, 47, 39, 31, 23, 15, 7};

BIT IIP[] = {40, 8, 48, 16, 56, 24, 64, 32,
		39, 7, 47, 15, 55, 23, 63, 31,
		38, 6, 46, 14, 54, 22, 62, 30,
		37, 5, 45, 13, 53, 21, 61, 29,
		36, 4, 44, 12, 52, 20, 60, 28,
		35, 3, 43, 11, 51, 19, 59, 27,
		34, 2, 42, 10, 50, 18, 58, 26,
		33, 1, 41, 9, 49, 17, 57, 25};

BIT SBox_DES[8][4][16] = {
		{
				{14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7 },
				{0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8 },
				{4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0 },
				{15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13 }
		},

		{
				{15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10 },
				{3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5 },
				{0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15 },
				{13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9 }
		},

		{
				{10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8 },
				{13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1 },
				{13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7 },
				{1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12 }
		},

		{
				{7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15 },
				{13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9 },
				{10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4 },
				{3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14 }
		},

		{
				{2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9 },
				{14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6 },
				{4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14 },
				{11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3 }
		},

		{
				{12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11 },
				{10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8 },
				{9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6 },
				{4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13 }
		},

		{
				{4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1 },
				{13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6 },
				{1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2 },
				{6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12 }
		},

		{
				{13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7 },
				{1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2 },
				{7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8 },
				{2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11 }
		}
};

BIT PC_1[]= {
		57, 49, 41, 33, 25, 17,  9,
		1, 58, 50, 42, 34, 26, 18,
		10,  2, 59, 51, 43, 35, 27,
		19, 11,  3, 60, 52, 44, 36,
		63, 55, 47, 39, 31, 23, 15,
		7, 62, 54, 46, 38, 30, 22,
		14,  6, 61, 53, 45, 37, 29,
		21, 13,  5, 28, 20, 12,  4
};

BIT PC_2[]= {
		14, 17, 11, 24,  1,  5,  3, 28,
		15,  6, 21, 10, 23, 19, 12,  4,
		26,  8, 16,  7, 27, 20, 13,  2,
		41, 52, 31, 37, 47, 55, 30, 40,
		51, 45, 33, 48, 44, 49, 39, 56,
		34, 53, 46, 42, 50, 36, 29, 32,
};

unsigned char P[]= {
	16,  7, 20, 21, 29, 12, 28, 17,
	 1, 15, 23, 26,  5, 18, 31, 10,
	 2,  8, 24, 14, 32, 27,  3,  9,
	19, 13, 30,  6, 22, 11,  4, 25
};

void viewBlock (WORD);								//1
void InitialPermutation (WORD* data);				//2
void InverseInitialPermutation (WORD* data);	//3
void ExpansionPermutation (WORD RightHalf, WORD *eWord); //4
void PermutedChoice1(WORD *Key); //5
void PermutedChoice2(WORD *Key); //6
WORD SubstitutionChoice(WORD *eWord); //7
WORD PermutationFunction(WORD dWord); //8
void swap32bit(WORD *Data); //9

//1
void viewBlock (WORD data) {
	int i;
	WORD mask;
	WORD temp;
	printf(">>  %x  <<\n" , data);
	puts(" =====================");
	for(i = 31 ; i >= 0 ; i--) {
		temp = 0;
		mask = 0x00000001 << i;
		temp = mask & data;
		temp = temp>> i;

		if(i!=31&&(i+1)%8==0)
			puts("");
		printf(" %d ", temp);
	}
	puts("\n =====================");
	puts("");
}

//2
void InitialPermutation (WORD* data) {
	int i, j;
	WORD newdata[2] = {0};
	WORD buf;
	WORD tempMask,mask; //temp 뜻 : 임시직원
	WORD setMask;
	for(i = 0 ; i <32 ; i++) {
		tempMask = 0x00000001;
		setMask = 0x00000001<<(31-i); //비트연산자를 통해 최우측비트가 한자리수가 높아지면(1씩증가하면) 2진수 한자리씩 가져오게된다.

		//		동작부분
		if((IP[i]<= 32) && (data[1] & setMask))
			newdata[1] |= (tempMask << (32-IP[i]));
		else if((IP[i]>32 && (data[1] & setMask)))
			newdata[0] |= (tempMask << (64-IP[i]));

		//		확인부분
		printf("tempMask : %32x\n", tempMask << (32-IP[i]));
		printf("setMask  : %32x\n", setMask);
		printf("         : 1000000000 0000000000 0000000000\n");
		printf(" IP[%d]  : %d [%s]\n",i, IP[i], IP[i]>32 ? " >32 " : " <=32 ");
		if((IP[i]<= 32) && (data[1] & setMask)) {
			printf("newdata[1]:");
			for(j = 31 ; j >= 0 ; j--) {
				mask=0x00000001 << j;
				buf = (newdata[1] & mask)>> j;
				printf("%d",buf);
			}
			puts("");
			viewBlock(newdata[1]);
			puts("");
		}
		else if((IP[i]>32 && (data[1] & setMask))) {
			printf("newdata[0]:");
			for(j = 31 ; j >= 0 ; j--) {
				mask=0x00000001 << j;
				buf = (newdata[0] & mask)>> j;
				printf("%d",buf);
			}
			puts("");
			viewBlock(newdata[0]);
			puts("");
		}
	}
	//		동작부분
	for(i = 32 ; i < 64 ; i++) {
		tempMask = 0x00000001;
		setMask = 0x00000001<<(63-i); //비트연산자를 통해 최우측비트가 한자리수가 높아지면(1씩증가하면) 2진수 한자리씩 가져오게된다.

		if((IP[i]<= 32) && (data[0] & setMask))
			newdata[1] |=(tempMask << (32-IP[i]));
		else if((IP[i]>32 && (data[0] & setMask)))
			newdata[0] |=(tempMask << (64-IP[i]));

		//		확인부분
		printf("tempMask : %32x\n", tempMask << (32-IP[i]));
		printf("setMask  : %32x\n", setMask);
		printf("         : 1000000000 0000000000 0000000000\n");
		printf(" IP[%d]  : %d [%s]\n",i, IP[i], IP[i]>32 ? " >32 " : " <=32 ");
		if((IP[i]<= 32) && (data[1] & setMask)) {
			printf("newdata[1]:");
			for(j = 31 ; j >= 0 ; j--) {
				mask=0x00000001 << j;
				buf = (newdata[1] & mask)>> j;
				printf("%d",buf);
			}
			puts("");
			viewBlock(newdata[1]);
			puts("");
		}
		else if((IP[i]>32 && (data[1] & setMask))) {
			printf("newdata[0]:");
			for(j = 31 ; j >= 0 ; j--) {
				mask=0x00000001 << j;
				buf = (newdata[0] & mask)>> j;
				printf("%d",buf);
			}
			puts("");
			viewBlock(newdata[0]);
			puts("");
		}
	}
	data[1]=newdata[1];		//left   32-bit
	data[0]=newdata[0];		//right 32-bit
	newdata[1]=0;
	newdata[0]=0;
	puts(">>>>IP 완료! <<<<");

}

//3
void InverseInitialPermutation (WORD* data) {
	WORD newdata[2] = {0};
	int i, j;
	WORD buf;
	WORD tempMask,mask; //temp 뜻 : 임시직원
	WORD setMask;
	for(i = 0 ; i <32 ; i++) {
		tempMask = 0x00000001;
		setMask = 0x00000001<<(31-i); //비트연산자를 통해 최우측비트가 한자리수가 높아지면(1씩증가하면) 2진수 한자리씩 가져오게된다.

		//		동작부분
		if((IIP[i]<= 32) && (data[1] & setMask))
			newdata[1] |= (tempMask << (32-IIP[i]));
		else if((IIP[i]>32 && (data[1] & setMask)))
			newdata[0] |= (tempMask << (64-IIP[i]));

		//		확인부분
		printf("tempMask : %32x\n", tempMask << (32-IIP[i]));
		printf("setMask  : %32x\n", setMask);
		printf("         : 1000000000 0000000000 0000000000\n");
		printf(" IIP[%d]  : %d [%s]\n",i, IIP[i], IIP[i]>32 ? " >32 " : " <=32 ");
		if((IP[i]<= 32) && (data[1] & setMask)) {
			printf("newdata[1]:");
			for(j = 31 ; j >= 0 ; j--) {
				mask=0x00000001 << j;
				buf = (newdata[1] & mask)>> j;
				printf("%d",buf);
			}
			puts("");
			viewBlock(newdata[1]);
			puts("");
		}
		else if((IIP[i]>32 && (data[1] & setMask))) {
			printf("newdata[0]:");
			for(j = 31 ; j >= 0 ; j--) {
				mask=0x00000001 << j;
				buf = (newdata[0] & mask)>> j;
				printf("%d",buf);
			}
			puts("");
			viewBlock(newdata[0]);
			puts("");
		}
	}
	//		동작부분
	for(i = 32 ; i < 64 ; i++) {
		tempMask = 0x00000001;
		setMask = 0x00000001<<(63-i); //비트연산자를 통해 최우측비트가 한자리수가 높아지면(1씩증가하면) 2진수 한자리씩 가져오게된다.

		if((IIP[i]<= 32) && (data[0] & setMask))
			newdata[1] |=(tempMask << (32-IIP[i]));
		else if((IIP[i]>32 && (data[0] & setMask)))
			newdata[0] |=(tempMask << (64-IIP[i]));

		//		확인부분
		printf("tempMask : %32x\n", tempMask << (32-IIP[i]));
		printf("setMask  : %32x\n", setMask);
		printf("         : 1000000000 0000000000 0000000000\n");
		printf(" IP[%d]  : %d [%s]\n",i, IIP[i], IIP[i]>32 ? " >32 " : " <=32 ");
		if((IP[i]<= 32) && (data[1] & setMask)) {
			printf("newdata[1]:");
			for(j = 31 ; j >= 0 ; j--) {
				mask=0x00000001 << j;
				buf = (newdata[1] & mask)>> j;
				printf("%d",buf);
			}
			puts("");
			viewBlock(newdata[1]);
			puts("");
		}
		else if((IIP[i]>32 && (data[1] & setMask))) {
			printf("newdata[0]:");
			for(j = 31 ; j >= 0 ; j--) {
				mask=0x00000001 << j;
				buf = (newdata[0] & mask)>> j;
				printf("%d",buf);
			}
			puts("");
			viewBlock(newdata[0]);
			puts("");
		}
	}
	puts(">>>>IIP 완료! <<<<");
	data[1]=newdata[1];		//left   32-bit
	data[0]=newdata[0];		//right 32-bit
	newdata[1]=0;
	newdata[0]=0;
}
//4
void ExpansionPermutation(WORD RightHalf, WORD *eWord)
{
	WORD New[2] = {0,0};

	// 32th bit -> first bit of first word
	New[1] |= ((RightHalf & 0x00000001) << 23); viewBlock (New[1]);

	// 1,2,3,4,5 bit -> 2,3,4,5,6 bit
	New[1] |=(((RightHalf & 0xF8000000) >> 9) & 0x007C0000); viewBlock (New[1]);
	New[1] |= ((RightHalf & 0x1F800000) >> 11); viewBlock (New[1]);
	New[1] |= ((RightHalf & 0x01F80000) >> 13); viewBlock (New[1]);
	New[1] |= ((RightHalf & 0x001F8000) >> 15); viewBlock (New[1]);

	New[0] |= ((RightHalf & 0x0001F800) << 7); viewBlock (New[0]);
	New[0] |= ((RightHalf & 0x00001F80) << 5); viewBlock (New[0]);
	New[0] |= ((RightHalf & 0x000001F8) << 3); viewBlock (New[0]);
	New[0] |= ((RightHalf & 0x0000001F) << 1); viewBlock (New[0]);
	New[0] |= (((RightHalf & 0x80000000) >>31)&0x00000001); viewBlock (New[0]);

	eWord[1] = New[1];
	eWord[0] = New[0];
}
//5
void PermutedChoice1(WORD *Key)
{
	int i;
	WORD tmpMask;
	WORD KeyMask;
	WORD NewKey[2]= {0,0 };
	tmpMask = 0x00000001;

	for( i = 0 ; i < 28 ; i++)
	{
		KeyMask = 0x08000000 >> i;

		if((PC_1[i] <= 32) && (Key[1] & (tmpMask << (32-PC_1[i])))) {
			NewKey[1] = NewKey[1] | KeyMask; viewBlock (NewKey[1]);
		}else if((PC_1[i] > 32) &&
				(Key[0] & (tmpMask << (64-PC_1[i])))) {
			NewKey[1] = NewKey[1] | KeyMask; viewBlock (NewKey[1]);
		}
	}

	for(   i = 28 ; i < 56 ; i++)
	{
		KeyMask = 0x08000000>>(i-28);

		if((PC_1[i] <= 32) && (Key[1] & (tmpMask << (32-PC_1[i])))) {
			NewKey[0] = NewKey[0] | KeyMask; viewBlock (NewKey[0]);
		}else if((PC_1[i] > 32) &&
				(Key[0] & (tmpMask << (64-PC_1[i])))) {
			NewKey[0] = NewKey[0] | KeyMask; viewBlock (NewKey[0]);
		}
	}

	Key[0] = NewKey[0];
	Key[1] = NewKey[1];
}

//6
void PermutedChoice2(WORD *Key)
{
	int i;
	WORD tmpMask;
	WORD KeyMask;
	WORD NewKey[2] = {0,0 };

	tmpMask = 0x00000001;
	for(int i = 0 ; i < 24 ; i++)
	{
		KeyMask = 0x00800000 >> i;
		if((PC_2[i] <= 28) && (Key[1] & (tmpMask << (28-PC_2[i])))) {
			NewKey[1] = NewKey[1] | KeyMask; viewBlock (NewKey[1]);
		}else if((PC_2[i] > 28) && (Key[0] & (tmpMask << (56-PC_2[i])))) {
			NewKey[1] = NewKey[1] | KeyMask; viewBlock (NewKey[1]);
		}
	}
	for(i = 24 ; i < 48 ; i++)
	{
		KeyMask = 0x00800000 >> (i-24);

		if((PC_2[i] <= 28) && (Key[1] & (tmpMask << (28-PC_2[i])))) {
			NewKey[0] = NewKey[0] | KeyMask; viewBlock (NewKey[0]);
		}else if((PC_2[i] > 28) &&
				(Key[0] & (tmpMask << (56-PC_2[i])))) {
			NewKey[0] = NewKey[0] | KeyMask; viewBlock (NewKey[0]);
		}
	}
	Key[0] = NewKey[0];
	Key[1] = NewKey[1];
}

//7
WORD SubstitutionChoice(WORD *eWord)
{
	int row,col;
	WORD tmp0, tmp1;
	tmp0 = eWord[0];
	tmp1 = eWord[1];
	int shift;

	eWord[0] = 0;
	eWord[1] = 0;

	for(int i = 0 ; i < 4 ; i++)
	{
		shift = (4*(3-i));
		tmp1 <<= 6;
		row = ((tmp1 & 0x20000000) >> 28)|((tmp1&0x01000000) >> 24);
		col =  (tmp1 & 0x1E000000) >> 25;
		eWord[1] |= (SBox_DES[i  ][row][col] << shift);
		tmp0 <<= 6;
		row = ((tmp0 & 0x20000000) >> 28)|((tmp0 & 0x01000000) >> 24);
		col =  (tmp0 & 0x1E000000) >> 25;
		eWord[0] |= (SBox_DES[i+4][row][col] << shift);
	}
	eWord[0] |= (eWord[1] << 16);
	return eWord[0];
}

//8
WORD PermutationFunction(WORD dWord)
{
	WORD tmpMask = 0x00000001;
	WORD keyMask = 0x00000001;
	WORD dwTmp = 0;
	for(int i = 0 ; i < 32 ; i++)
	{
		if(dWord & (tmpMask << (32-P[i])))
			dwTmp |= (keyMask << (31-i));
	}
	return dwTmp;
}

//9
void swap32bit(WORD *Data)

{
	WORD temp;
	temp = Data[0];
	Data[0] = Data[1];
	Data[1] = temp;
}


