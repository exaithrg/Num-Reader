#include<stdio.h>
#include<string.h>
#include"Nbasic.h"

Status DoubleReadNum(char shuru[]) {	//自欺欺人版 
	int i, fuhaonum, numlen, xiaonumlen, zerosend, zeros;
	char zhengshu[103], zhongjie[103], xiaoshu[103];
	int spc;	//spc就是个普通变量，类似i j k这样
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
		for (spc = i + 1; shuru[spc] == '0'; spc++);
		if (shuru[spc] == '\0') {
			printf("零");
			return OK;
		}
		zhengshu[0] = '0';
		zhengshu[1] = '\0';
		strcpy(xiaoshu, shuru + i + 1);	//注意，单独一个小数点=0，那么啥也不会拷贝过去 
	}
	else {	//否则的话一定是0或者其他数字开头，如0000, 00.0, 100, 0.335 , 100.0等 
		for (spc = i; shuru[spc] == '0'; spc++);
		if (shuru[spc] == '.') {
			for (spc++; shuru[spc] == '0'; spc++);
		}
		if (shuru[spc] == '\0') {
			printf("零");
			return OK;
		}
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
	if (fuhaonum % 2 == 1 && numlen <= 16)	printf("负");
	if (numlen <= 4)	ReadQian(numlen - 1, 0, zhengshu);
	else if (numlen <= 8) { readwan(zhengshu, numlen); }
	else if (numlen <= 12) { readyi(zhengshu, numlen); }
	else if (numlen <= 16) {
		ReadQian(numlen - 1, 12, zhengshu);
		printf("万");
		ReadQian(11, 8, zhengshu);
		printf("亿");
		ReadQian(7, 4, zhengshu);
		zeros = CountZerosEnd(7, 4, zhengshu);
		if (zeros != 4)	printf("万");
		ReadQian(3, 0, zhengshu);
	}
	else {
		printf("数字过大！");
		return ERROR;
	}

	if (xiaoshu[0] != '\0') {	//要是有小数部分 
		printf("点");
		for (i = 0; xiaoshu[i] != '\0'; i++)
			ReadOneNum(xiaoshu[i]);
	}
	return OK;
}