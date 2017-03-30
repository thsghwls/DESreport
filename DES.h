/*
 * DES.h
 *
 *  Created on: 2017. 3. 30.
 *      Author: 컴퓨터
 */

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

void viewBlock (WORD);														//1
void InitialPermutation (WORD* data, WORD* newdata);				//2
void InverseInitialPermutation (WORD* data , WORD* newdata);	//3

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
void InitialPermutation (WORD* data, WORD* newdata) {
	int i, j;
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
	puts(">>>>IP 완료! <<<<");
}

//3
void InverseInitialPermutation (WORD* data , WORD* newdata) {
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
}

