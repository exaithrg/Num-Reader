#include<stdio.h>
#include<string.h>
#include"Nbasic.h"

//个 万 亿 兆 京 垓gai 秭zi 穰rang 沟 涧 正 载 极 恒河沙 阿僧祗 那由他 不可思议 无量 大数  

Status readzhao(char TransNum[], int zuigao) {//修改时，改名字，改<=数，>数，printf，最后的readXXX 
	int zeros;

	if (zuigao <= 12 || zuigao>16)	return ERROR;

	ReadQian(zuigao - 1, 12, TransNum);
	zeros = CountZerosEnd(zuigao - 1, 12, TransNum);
	if (zeros != 4) printf("兆");

	readyi(TransNum, 12);

	return OK;
}

Status readjing(char TransNum[], int zuigao) {
	int zeros;

	if (zuigao <= 16 || zuigao>20)	return ERROR;

	ReadQian(zuigao - 1, 16, TransNum);
	zeros = CountZerosEnd(zuigao - 1, 16, TransNum);
	if (zeros != 4) printf("京");

	readzhao(TransNum, 16);

	return OK;
}

Status readgai(char TransNum[], int zuigao) {
	int zeros;

	if (zuigao <= 20 || zuigao>24)	return ERROR;

	ReadQian(zuigao - 1, 20, TransNum);
	zeros = CountZerosEnd(zuigao - 1, 20, TransNum);
	if (zeros != 4) printf("垓");

	readjing(TransNum, 20);

	return OK;
}

Status readzi(char TransNum[], int zuigao) {
	int zeros;

	if (zuigao <= 24 || zuigao>28)	return ERROR;

	ReadQian(zuigao - 1, 24, TransNum);
	zeros = CountZerosEnd(zuigao - 1, 24, TransNum);
	if (zeros != 4) printf("秭");

	readgai(TransNum, 24);

	return OK;
}

Status readrang(char TransNum[], int zuigao) {
	int zeros;

	if (zuigao <= 28 || zuigao>32)	return ERROR;

	ReadQian(zuigao - 1, 28, TransNum);
	zeros = CountZerosEnd(zuigao - 1, 28, TransNum);
	if (zeros != 4) printf("穰");

	readzi(TransNum, 28);

	return OK;
}

Status readgou(char TransNum[], int zuigao) {//修改时，改<=数，>数，printf，最后的readXXX 
	int zeros;

	if (zuigao <= 32 || zuigao>36)	return ERROR;

	ReadQian(zuigao - 1, 32, TransNum);
	zeros = CountZerosEnd(zuigao - 1, 32, TransNum);
	if (zeros != 4) printf("沟");

	readrang(TransNum, 32);

	return OK;
}

Status readjian(char TransNum[], int zuigao) {//修改时，改名字，改<=数，>数，printf，最后的readXXX 
	int zeros;

	if (zuigao <= 36 || zuigao>40)	return ERROR;

	ReadQian(zuigao - 1, 36, TransNum);
	zeros = CountZerosEnd(zuigao - 1, 36, TransNum);
	if (zeros != 4) printf("涧");

	readgou(TransNum, 36);

	return OK;
}

Status readzheng(char TransNum[], int zuigao) {//修改时，改名字，改<=数，>数，printf，最后的readXXX 
	int zeros;

	if (zuigao <= 40 || zuigao>44)	return ERROR;

	ReadQian(zuigao - 1, 40, TransNum);
	zeros = CountZerosEnd(zuigao - 1, 40, TransNum);
	if (zeros != 4) printf("正");

	readjian(TransNum, 40);

	return OK;
}

Status readzai(char TransNum[], int zuigao) {//修改时，改名字，改<=数，>数，printf，最后的readXXX 
	int zeros;

	if (zuigao <= 44 || zuigao>48)	return ERROR;

	ReadQian(zuigao - 1, 44, TransNum);
	zeros = CountZerosEnd(zuigao - 1, 44, TransNum);
	if (zeros != 4) printf("载");

	readzheng(TransNum, 44);

	return OK;
}

Status readji(char TransNum[], int zuigao) {//修改时，改名字，改<=数，>数，printf，最后的readXXX 
	int zeros;

	if (zuigao <= 48 || zuigao>52)	return ERROR;

	ReadQian(zuigao - 1, 48, TransNum);
	zeros = CountZerosEnd(zuigao - 1, 48, TransNum);
	if (zeros != 4) printf("极");

	readzai(TransNum, 48);

	return OK;
}

Status readhenghesha(char TransNum[], int zuigao) {//修改时，改名字，改<=数（4个），>数，printf，最后的readXXX 
	int zeros;

	if (zuigao <= 52 || zuigao>56)	return ERROR;

	ReadQian(zuigao - 1, 52, TransNum);
	zeros = CountZerosEnd(zuigao - 1, 52, TransNum);
	if (zeros != 4) printf("恒河沙");

	readji(TransNum, 52);

	return OK;
}

Status readasengzhi(char TransNum[], int zuigao) {//修改时，改名字，改<=数（4个），>数，printf，最后的readXXX 
	int zeros;

	if (zuigao <= 56 || zuigao>60)	return ERROR;

	ReadQian(zuigao - 1, 56, TransNum);
	zeros = CountZerosEnd(zuigao - 1, 56, TransNum);
	if (zeros != 4) printf("阿僧祗");

	readhenghesha(TransNum, 56);

	return OK;
}

Status readnayouta(char TransNum[], int zuigao) {//修改时，改名字，改<=数（4个），>数，printf，最后的readXXX 
	int zeros;

	if (zuigao <= 60 || zuigao>64)	return ERROR;

	ReadQian(zuigao - 1, 60, TransNum);
	zeros = CountZerosEnd(zuigao - 1, 60, TransNum);
	if (zeros != 4) printf("那由他");

	readasengzhi(TransNum, 60);

	return OK;
}

Status readbukesiyi(char TransNum[], int zuigao) {//修改时，改名字，改<=数（4个），>数，printf，最后的readXXX 
	int zeros;

	if (zuigao <= 64 || zuigao>68)	return ERROR;

	ReadQian(zuigao - 1, 64, TransNum);
	zeros = CountZerosEnd(zuigao - 1, 64, TransNum);
	if (zeros != 4) printf("不可思议");

	readnayouta(TransNum, 64);

	return OK;
}

Status readwuliang(char TransNum[], int zuigao) {//修改时，改名字，改<=数（4个），>数，printf，最后的readXXX 
	int zeros;

	if (zuigao <= 68 || zuigao>72)	return ERROR;

	ReadQian(zuigao - 1, 68, TransNum);
	zeros = CountZerosEnd(zuigao - 1, 68, TransNum);
	if (zeros != 4) printf("无量");

	readbukesiyi(TransNum, 68);

	return OK;
}

Status readdashu(char TransNum[], int zuigao) {//修改时，改名字，改<=数（4个），>数，printf，最后的readXXX 
	int zeros;

	if (zuigao <= 72 || zuigao>76)	return ERROR;

	ReadQian(zuigao - 1, 72, TransNum);
	zeros = CountZerosEnd(zuigao - 1, 72, TransNum);
	if (zeros != 4) printf("大数");

	readwuliang(TransNum, 72);

	return OK;
}

//输入InfiReadNum函数的将是Pretreatment函数所认为的数字，如" 	----.350000" 
//为了实现程序功能，InfiReadNum函数应做到：
//1. 删掉无用的空白字符
//2. 统计负号数量，奇数则打印负，偶数不作处理。而后删掉负号
//3. 将数字开头部分的0全部删光，直至只剩一个0或以1-9及.开头为止 
//4. 将整数部分单独摘出来，计算整数部分长度得到numlen，按普通方法读出整数部分 
//5. 利用最简单的ReadOneNum念完小数部分
//6. 特别的，如果是无量大数，那么小数部分就不念了 

Status InfiReadNum(char shuru[]) {
	int i, fuhaonum, numlen, xiaonumlen, zerosend;
	char zhengshu[103], zhongjie[103], xiaoshu[103];
	memset(zhengshu, '\0', 103);
	memset(zhongjie, '\0', 103);
	memset(xiaoshu, '\0', 103);

	for (i = 0; shuru[i] == ' ' || shuru[i] == '\t'; i++);	//将光标移过空白字符 

	for (fuhaonum = 0; shuru[i] == '-'; i++)	fuhaonum++;	//统计负号数量，将光标移过负号 

	if (shuru[i] == '\0') {		//如果只有空白字符和负号 
		printf("不是指令！");
		return ERROR;
	}

	if (shuru[i] == '.') {	//如果移过开头之后直接就是小数点了 
		zhengshu[0] = '0';
		zhengshu[1] = '\0';
		strcpy(xiaoshu, shuru + i + 1);	//注意，单独一个小数点=0，那么啥也不会拷贝过去 
	}
	else {	//否则的话一定是0或者其他数字开头，如0000, 00.0, 100, 0.335 , 100.0等 
		while (shuru[i] == '0') i++;	//先将光标移过可能的零
		if (i>0) { 		//当可以后退时 
			if (shuru[i] == '.' || shuru[i] == '\0') i--;	//如果光标指向的是结束符或小数点，则后退 
		}
		strcpy(zhongjie, shuru + i);	//中介数组就是去头零的数字
										//下面是把中介数组拆成zhengshu和xiaoshu
		for (i = 0; zhongjie[i] != '.'&&zhongjie[i] != '\0'; i++);	//寻找小数点。语句执行完后要么指向.要么指向\0
		if (zhongjie[i] == '\0') {	//如果没有小数点，那么直接拷贝即可。注意，zhengshu数组可能是空的 
			strcpy(zhengshu, zhongjie);
		}
		else {	//此时一定是数字+小数点(+数字)形式 且zhongjie[i]为小数点 
			strncpy(zhengshu, zhongjie, i);	//拷贝整数部分 
			zhengshu[i] = '\0';	//手动添加结束符 
			strcpy(xiaoshu, zhongjie + i + 1);	//拷贝小数部分 
		}
	}

	//至此我们得到了独立的整数部分和小数部分，但小数部分有可能是空的。 

	strrev(zhengshu);	//为了适应ReadQian等函数的需求，反转zhengshu数组 
	numlen = strlen(zhengshu);
	xiaonumlen = strlen(xiaoshu);

	//printf("  ");
	if (numlen == 1 && xiaonumlen == 0) {	//解决负零的问题 
		if (zhengshu[0] == '0') {
			fuhaonum = 0;
		}
	}
	else if (numlen == 1 && xiaonumlen != 0) {	//解决负零点零零的问题 
		for (i = 0, zerosend = 1; xiaoshu[i] != '\0'; i++) {
			if (xiaoshu[i] != '0')	zerosend = 0;
		}
		if (zerosend)	fuhaonum = 0;
	}

	if (fuhaonum % 2 == 1)	printf("负");

	if (numlen <= 4)	ReadQian(numlen - 1, 0, zhengshu);
	else if (numlen <= 8) { readwan(zhengshu, numlen); }
	else if (numlen <= 12) { readyi(zhengshu, numlen); }
	else if (numlen <= 16) { readzhao(zhengshu, numlen); }
	else if (numlen <= 20) { readjing(zhengshu, numlen); }
	else if (numlen <= 24) { readgai(zhengshu, numlen); }
	else if (numlen <= 28) { readzi(zhengshu, numlen); }
	else if (numlen <= 32) { readrang(zhengshu, numlen); }
	else if (numlen <= 36) { readgou(zhengshu, numlen); }
	else if (numlen <= 40) { readjian(zhengshu, numlen); }
	else if (numlen <= 44) { readzheng(zhengshu, numlen); }
	else if (numlen <= 48) { readzai(zhengshu, numlen); }
	else if (numlen <= 52) { readji(zhengshu, numlen); }
	else if (numlen <= 56) { readhenghesha(zhengshu, numlen); }
	else if (numlen <= 60) { readasengzhi(zhengshu, numlen); }
	else if (numlen <= 64) { readnayouta(zhengshu, numlen); }
	else if (numlen <= 68) { readbukesiyi(zhengshu, numlen); }
	else if (numlen <= 72) { readwuliang(zhengshu, numlen); }
	else if (numlen <= 76) { readdashu(zhengshu, numlen); }
	else {
		printf("无量大数");
		printf("\n  该数整数部分共有%d位", numlen);
		if (xiaonumlen == 0)	printf("，无小数部分");
		else	printf(",小数部分共有%d位", xiaonumlen);
		return ERROR;
	}

	if (xiaoshu[0] != '\0') {	//要是有小数部分 
		printf("点");
		for (i = 0; xiaoshu[i] != '\0'; i++)
			ReadOneNum(xiaoshu[i]);
	}

	if (numlen>12 && xiaonumlen >= 10) {
		printf("\n  该数整数部分共有%d位，小数部分共有%d位", numlen, xiaonumlen);
	}
	else if (numlen>12 && xiaonumlen == 0) {
		printf("\n  该数共有%d位", numlen);
	}
	else if (numlen <= 12 && xiaonumlen >= 10) {
		printf("\n  该数小数部分共有%d位", xiaonumlen);
	}
	return OK;

}