#include<stdio.h>
#include<ctype.h>
#include"Nbasic.h"

int IReadOneNum(int onenum) {		//凡带I的为实用版 
	if (onenum>9 || onenum<0) return 0;
	if (onenum == 0)	printf("零");
	else if (onenum == 1)	printf("一");
	else if (onenum == 2)	printf("二");
	else if (onenum == 3)	printf("三");
	else if (onenum == 4)	printf("四");
	else if (onenum == 5)	printf("五");
	else if (onenum == 6)	printf("六");
	else if (onenum == 7)	printf("七");
	else if (onenum == 8)	printf("八");
	else if (onenum == 9)	printf("九");
	return 1;
}

int ICountZerosEnd(int gao, int di, int qianwei[]) {//返回末尾0的个数 
	int zerosnum;
	for (zerosnum = 0; gao >= di; di++) {
		if (qianwei[di] == 0)	zerosnum++;
		else return zerosnum;
	}
	return zerosnum;
}

int IZerosBtw(int gao, int di, int qianwei[]) {//最多判断4位！ 
	if (gao - di<3)	return 0;
	if (qianwei[gao - 1] != 0)	return 0;
	if (qianwei[gao] == 0) {
		if (qianwei[gao - 2] == 0 && qianwei[di] == 0)	return 0;
		return 1;
	}
	if (qianwei[gao] != 0) {
		if (qianwei[gao - 2] == 0 && qianwei[di] != 0)	return 1;
		return 0;
	}
}

int IReadQian(int gao, int di, int qianwei[]) {
	int tailzerosnum, havebtwzeros;
	if (gao<di || gao>di + 3)	return 0;
	if (gao == di)	IReadOneNum(qianwei[gao]);
	else if (gao - 1 == di) {
		if (qianwei[gao] != 1)	IReadOneNum(qianwei[gao]);
		printf("十");
		gao--;
		if (qianwei[gao] != 0) IReadOneNum(qianwei[gao]);
	}
	else if (gao - 2 == di) {
		tailzerosnum = ICountZerosEnd(gao, di, qianwei);
		if (tailzerosnum == 0) {
			IReadOneNum(qianwei[gao]);
			printf("百");
			gao--;
			IReadOneNum(qianwei[gao]);
			if (qianwei[gao] != 0) printf("十");
			gao--;
			IReadOneNum(qianwei[gao]);
		}
		else if (tailzerosnum == 1) {
			IReadOneNum(qianwei[gao]);
			printf("百");
			gao--;
			IReadOneNum(qianwei[gao]);
			printf("十");

		}
		else if (tailzerosnum == 2) {
			IReadOneNum(qianwei[gao]);
			printf("百");
		}
	}
	else if (gao - 3 == di) {
		tailzerosnum = ICountZerosEnd(gao, di, qianwei);
		if (tailzerosnum == 4)	return 1;
		else if (tailzerosnum == 3) {
			IReadOneNum(qianwei[gao]);
			printf("千");
		}
		else if (tailzerosnum == 2) {
			IReadOneNum(qianwei[gao]);
			if (qianwei[gao] != 0)	printf("千");
			gao--;
			IReadOneNum(qianwei[gao]);
			printf("百");
		}
		else if (tailzerosnum == 1) {
			havebtwzeros = IZerosBtw(gao, di, qianwei);
			IReadOneNum(qianwei[gao]);
			if (qianwei[gao] != 0) printf("千");
			gao--;
			if (havebtwzeros == 1) {
				gao--;
				IReadOneNum(qianwei[gao]);
				printf("十");
				return 1;
			}
			IReadOneNum(qianwei[gao]);
			if (qianwei[gao] != 0) printf("百");
			gao--;
			IReadOneNum(qianwei[gao]);
			printf("十");
		}
		else {
			havebtwzeros = IZerosBtw(gao, di, qianwei);
			if (havebtwzeros == 1) {
				IReadOneNum(qianwei[gao]);
				if (qianwei[gao] != 0) {
					printf("千零");
					gao -= 3;
					IReadOneNum(qianwei[gao]);
					return 1;
				}
				gao -= 2;
				if (qianwei[gao] != 0) {
					IReadOneNum(qianwei[gao]);
					printf("十");
					gao--;
					IReadOneNum(qianwei[gao]);
					return 1;
				}
				gao--;
				IReadOneNum(qianwei[gao]);
				return 1;
			}
			IReadOneNum(qianwei[gao]);
			if (qianwei[gao] != 0) printf("千");
			gao--;
			IReadOneNum(qianwei[gao]);
			if (qianwei[gao] != 0)	printf("百");
			gao--;
			IReadOneNum(qianwei[gao]);
			if (qianwei[gao] != 0)	printf("十");
			gao--;
			IReadOneNum(qianwei[gao]);
		}
	}
	return 1;
}

int IReadNum(int TransNum) {
	int zeros;
	if (TransNum == 0) {
		printf("零");
		return 1;
	}
	int gewei[20] = { 0 };
	int i = 0, num, weishu = 0;
	if (TransNum >= 0) {
		num = TransNum;
		gewei[0] = 0;
	}
	else {
		num = -TransNum;
		gewei[0] = 1;
	}
	for (i = 1; num>0; i++) {
		gewei[i] = num % 10;
		num = num / 10;
		weishu++;
	}
	if (gewei[0] == 1)	printf("负");
	if (weishu <= 4)	IReadQian(weishu, 1, gewei);
	else if (weishu <= 8) {
		IReadQian(weishu, 5, gewei);
		printf("万");
		IReadQian(4, 1, gewei);
	}
	else if (weishu <= 10) {
		IReadQian(weishu, 9, gewei);
		printf("亿");
		IReadQian(8, 5, gewei);
		zeros = ICountZerosEnd(8, 5, gewei);
		if (zeros != 4)	printf("万");
		IReadQian(4, 1, gewei);
	}
	else {
		printf("数字过大，不能识别！");
		return 0;
	}
	return 1;
}

Status ReadOneNum(char onenum) {		
	//函数会跳过非数字，因此123.56 \0可以利用循环全部用此函数读出，结果为一二三五六
	if (isdigit(onenum) == 0) return ERROR;
	if (onenum == '0')	printf("零");
	else if (onenum == '1')	printf("一");
	else if (onenum == '2')	printf("二");
	else if (onenum == '3')	printf("三");
	else if (onenum == '4')	printf("四");
	else if (onenum == '5')	printf("五");
	else if (onenum == '6')	printf("六");
	else if (onenum == '7')	printf("七");
	else if (onenum == '8')	printf("八");
	else if (onenum == '9')	printf("九");
	return OK;
}

int CountZerosEnd(int gao, int di, char qianwei[]) {//返回末尾0的个数 
	int zerosnum;
	for (zerosnum = 0; gao >= di; di++) {
		if (qianwei[di] == '0')	zerosnum++;
		else return zerosnum;
	}
	return zerosnum;
}

Status ZerosBtw(int gao, int di, char qianwei[]) {
	//最多判断4位！
	//4位的情况共有16种
	// XXXX X0XX 0XXX 00XX
	// XXX0 X0X0 0XX0 00X0
	// XX0X X00X 0X0X 000X
	// XX00 X000 0X00 0000
	//其中的  00XX 00X0 X00X 000X返回YES
	//1-3位只会返回NO 
	if (gao - di<3)	return NO;
	if (qianwei[gao - 1] != '0')	return NO;
	//第二位不是0的话一定不符合条件
	//此时只剩下了8种情况
	// X0XX  00XX
	// X0X0  00X0
	// X00X  000X
	// X000  0000
	//如果第一位是0，那么只需判断最后两位是否都是0，是则NO，不是则返回YES
	if (qianwei[gao] == '0') {
		if (qianwei[gao - 2] == '0'&&qianwei[di] == '0')	return NO;
		return YES;
	}
	//如果第一位不是0，那么只需判断最后两位是否是0X，是则YES，不是则NO
	if (qianwei[gao] != '0') {
		if (qianwei[gao - 2] == '0'&&qianwei[di] != '0')	return YES;
		return NO;
	}
}

//使用说明：反读，最开头是从0开始，若123并输入gao=3 di=0则会读作千三百二十一
Status ReadQian(int gao, int di, char qianwei[]) {
	//必须注意，ReadQian函数不能读除0外0开头的数字 

	int tailzerosnum, havebtwzeros;

	if (gao<di || gao>di + 3)	return ERROR;

	if (gao == di)	ReadOneNum(qianwei[gao]);//一位就直接念出来 

	else if (gao - 1 == di) {	//如果是两位数，首位一定非零，且一条判断即可解决十零问题 
		if (qianwei[gao] != '1')	ReadOneNum(qianwei[gao]);//解决12读作十二而非一十二的问题 
		printf("十");
		gao--;
		if (qianwei[gao] != '0') ReadOneNum(qianwei[gao]);//解决十零的问题 
	}

	else if (gao - 2 == di) {//三位数同样不存在连零问题。但此时需要判断末尾零的个数方便读数。

		tailzerosnum = CountZerosEnd(gao, di, qianwei);	//记录每级尾部零的个数 

		if (tailzerosnum == 0) {	//X0X XXX
			ReadOneNum(qianwei[gao]);
			printf("百");
			gao--;
			ReadOneNum(qianwei[gao]);
			if (qianwei[gao] != '0') printf("十");
			gao--;
			ReadOneNum(qianwei[gao]);
		}
		else if (tailzerosnum == 1) {	//XX0  
			ReadOneNum(qianwei[gao]);
			printf("百");
			gao--;
			ReadOneNum(qianwei[gao]);
			printf("十");
		}
		else if (tailzerosnum == 2) {	//X00 
			ReadOneNum(qianwei[gao]);
			printf("百");
		}
	}

	else if (gao - 3 == di) {	//此时既存在连零问题，也存在尾零问题，也存在一十二问题 

		tailzerosnum = CountZerosEnd(gao, di, qianwei);
		//记录每级尾部零的个数 

		//4位的情况共有16种

		// XXXX X0XX 0XXX 00XX
		// XXX0 X0X0 0XX0 00X0
		// XX0X X00X 0X0X 000X
		// XX00 X000 0X00 0000

		//连零的情况有00XX 00X0 X00X 000X
		if (tailzerosnum == 4)	return OK;//全是零，不用读 

		else if (tailzerosnum == 3) {	//后面有3个零，只能是X000形式 
			ReadOneNum(qianwei[gao]);
			printf("千");
		}

		else if (tailzerosnum == 2) {//后面有两个零，可能是XX00 0X00 
			ReadOneNum(qianwei[gao]);
			if (qianwei[gao] != '0')	printf("千");
			gao--;
			ReadOneNum(qianwei[gao]);
			printf("百");
		}

		else if (tailzerosnum == 1) { //后面有一个零，情况有XXX0 X0X0 0XX0 00X0 

			havebtwzeros = ZerosBtw(gao, di, qianwei);	//此时需要使用ZerosBtw记录级中是否存在连零 

			ReadOneNum(qianwei[gao]);
			if (qianwei[gao] != '0') printf("千");
			gao--;
			if (havebtwzeros == YES) {	//此时为00X0的情况 
				gao--;
				ReadOneNum(qianwei[gao]);
				printf("十");	//此时10读作一十而非10，因为零一十更符合读法。只有某级为单纯的两位数才省略一。 
				return OK;
			}

			//此时还剩XXX0 X0X0 0XX0
			ReadOneNum(qianwei[gao]);
			if (qianwei[gao] != '0') printf("百");
			gao--;
			ReadOneNum(qianwei[gao]);//十位可直读 
			printf("十");	//至此解决 
		}

		else {

			//后面没有0，情况有八种：
			//XXXX 0XXX X0XX 00XX XX0X 0X0X X00X 000X
			//其中 00XX X00X 000X为连零正确情况 
			//XXXX 0XXX X0XX XX0X 0X0X为普通情况，普通读法代码可直接解决 

			havebtwzeros = ZerosBtw(gao, di, qianwei);	//记录连零。 

			if (havebtwzeros == YES) {
				//此时还剩 00XX X00X 000X 需要读，最后一位一定非零。
				ReadOneNum(qianwei[gao]);//读第一位 
				if (qianwei[gao] != '0') {//如果是X00X 
					printf("千零");
					gao -= 3;
					ReadOneNum(qianwei[gao]);
					return OK;
				}
				//第一位为0,情况为00XX 000X
				gao -= 2;
				if (qianwei[gao] != '0') {
					ReadOneNum(qianwei[gao]);
					printf("十");
					gao--;
					ReadOneNum(qianwei[gao]);
					return OK;
				}
				//000X
				gao--;
				ReadOneNum(qianwei[gao]);
				return OK;
			}
			ReadOneNum(qianwei[gao]);
			if (qianwei[gao] != '0') printf("千");
			gao--;
			ReadOneNum(qianwei[gao]);
			if (qianwei[gao] != '0')	printf("百");
			gao--;
			ReadOneNum(qianwei[gao]);
			if (qianwei[gao] != '0')	printf("十");
			gao--;
			ReadOneNum(qianwei[gao]);//最后一位一定不为0可直读。 
		}
	}
	return OK;
}

Status readwan(char TransNum[], int zuigao) {
	int zeros;

	ReadQian(zuigao - 1, 4, TransNum);
	zeros = CountZerosEnd(7, 4, TransNum);
	if (zeros != 4)	printf("万");

	ReadQian(3, 0, TransNum);
	return OK;
}

Status readyi(char TransNum[], int zuigao) {//修改时，改名字，改<=数，>数，printf，最后的readXXX 
	int zeros;

	if (zuigao <= 8 || zuigao>12)	return ERROR;

	ReadQian(zuigao - 1, 8, TransNum);
	zeros = CountZerosEnd(zuigao - 1, 8, TransNum);
	if (zeros != 4) printf("亿");

	readwan(TransNum, 8);

	return OK;
}

void Brilliantan() {
	int MyNameIsGengHaoRan;
}

Status OnlyPrintNum(char character) {
	if (isdigit(character)) {
		printf("%c", character);
		return OK;
	}
	return ERROR;
}
