#include<stdio.h>
#include<string.h>
#include"Nbasic.h"

Status ReadIntPre(int zhengshuweishu) {
	if (zhengshuweishu < 0 || zhengshuweishu>26) return ERROR;
	if (zhengshuweishu == 2)	printf("da");
	if (zhengshuweishu == 3)	printf("h");
	if (zhengshuweishu > 3) {
		if (zhengshuweishu <= 6) printf("k");
		else if (zhengshuweishu <= 9) printf("M");
		else if (zhengshuweishu <= 12) printf("G");
		else if (zhengshuweishu <= 15) printf("T");
		else if (zhengshuweishu <= 18) printf("P");
		else if (zhengshuweishu <= 21) printf("E");
		else if (zhengshuweishu <= 24) printf("Z");
		else if (zhengshuweishu <= 27) printf("Y");
	}
	return OK;
}

Status ReadDecimalPre(int prezerosnum) {
	if (prezerosnum < 1 || prezerosnum>24) return ERROR;
	if (prezerosnum == 1) printf("d");
	else if (prezerosnum == 2) printf("c");
	else if (prezerosnum == 3) printf("m");
	else if (prezerosnum <= 6) printf("μ");
	else if (prezerosnum <= 9) printf("n");
	else if (prezerosnum <= 12) printf("p");
	else if (prezerosnum <= 15) printf("f");
	else if (prezerosnum <= 18) printf("a");
	else if (prezerosnum <= 21) printf("z");
	else if (prezerosnum <= 24) printf("y");
	return OK;
}

//注意，可能隐藏越界bug，比如0.0000001 \0 123 \0 会读到后面的一二三
Status SipreReadNum(char love[]) {	
	//国际单位词头模式主体代码 
	//何为数字？数字就是pretreatment认可类型的字符串. 
	//Pretreatment认可的数字：
	//若干空格或Tab+若干负号+若干0作为开头
	//开头后面紧跟数字或小数点，且小数点只出现一次
	//除开头外其余任何位置不出现空白字符 

	//确实存在越位问题。解决方法：重定义......
	/*int ceshi;
	shuru[0] = '0';
	shuru[1] = '.';
	for (ceshi = 2; ceshi < 9; ceshi++) shuru[ceshi] = '0';
	shuru[ceshi] = '1';
	shuru[++ceshi] = '0';
	shuru[++ceshi] = '0';
	shuru[++ceshi] = '\0';
	shuru[++ceshi] = '0';
	shuru[++ceshi] = '1';
	shuru[++ceshi] = '2';
	shuru[++ceshi] = '3';
	shuru[++ceshi] = '4';
	shuru[++ceshi] = '\0';
	shuru[++ceshi] = '\0';*/

	//另一个bug是0.00000001的写法问题。已经解决

	int i = 0, fuhaonum = 0, weishu = 0, endzeros = 0;
	int judge, j, preflag = 0, lingyudian=0;
	char xuyaodu[4],shuru[502];
	memset(shuru, '\0', 502);
	strcpy(shuru, love);
	while (shuru[i] == ' ' || shuru[i] == '\t')	i++;
	while (shuru[i] == '-') {
		fuhaonum++;
		i++;
	}
	while (shuru[i] == '0')	i++;

	//以下代码机智的解决了. 000  0. -. -0. -0的问题，但留下了0.000 -0.000 -.000 的问题
	if (shuru[i] == '.') {
		i++;
		if (shuru[i] == '\0') {
			lingyudian = 1;
		}
		i--;
	}
	else if (shuru[i] == '\0') lingyudian = 1;
	if (lingyudian == 1) {
		printf("记作：0\n  读作：零");
		return OK;
	}

	j = i;		//跳过开头。j是头的个数。
	
	while (shuru[i] != '\0'&&shuru[i] != '.') {
		weishu ++ ;
		i++;
	}		//i为结束符或小数点
	if (weishu > 27) {
		printf("此数字的幂次高于26，跳过读数，请重新输入。");
		return OVERFLOW;
	}
	judge = weishu % 3;
	//printf("  ");

	if (weishu == 0) {	//如果说是0.x和.x的情况
		for (i = j + 1; shuru[i] == '0'; i++);
		if (shuru[i] == '\0') {		//如果全0
			printf("记作：0.");
			for (i = j + 1; shuru[i] == '0'; i++) printf("0");
			printf("\n  读作：零点");
			for (i = j + 1; shuru[i] == '0'; i++) printf("零");
			return OK;
		}
		weishu++;
		//注意，shuru[j]=='.'
		for (j++; shuru[j] == '0'; j++)	weishu++;	//计算非零数字前零的个数
		if (weishu > 24) {
			printf("此数字的幂次低于-24，跳过读数，请重新输入");
			return OVERFLOW;
		}
		if (weishu < 3) {		//解决分和厘的问题，注意没有角这种东西
			i = j;
			printf("记作：");
			if (fuhaonum % 2 == 1)	printf("-");
			printf("%c", shuru[j]);

			if (shuru[++i] != '\0') printf(".");
			for (; shuru[i] != '\0'; i++) OnlyPrintNum(shuru[i]);
			ReadDecimalPre(weishu);

			printf("\n  读作：");
			if (fuhaonum % 2 == 1)	printf("负");
			ReadOneNum(shuru[j]);
			if(shuru[++j]!='\0') printf("点");
			for (; shuru[j] != '\0'; j++) ReadOneNum(shuru[j]);
			if(weishu==1) printf("分");
			else printf("厘");
			return OK;
		}
		judge = weishu % 3;
		if (judge == 1) {
			//shuru[j]为第一个非零数
			xuyaodu[2] = shuru[j];

			if (shuru[j+1] == '\0') xuyaodu[1] = '0';	//小数与整数不同。
			else xuyaodu[1] = shuru[j+1];

			if (shuru[j+2] == '\0') xuyaodu[0] = '0';
			else xuyaodu[0] = shuru[j+2];

			printf("记作：");
			if (fuhaonum % 2 == 1)	printf("-");
			printf("%c%c%c", xuyaodu[2], xuyaodu[1], xuyaodu[0]);

			if (shuru[j + 3] != '\0')	printf(".");
			for (i = j + 3; shuru[i] != '\0'; i++)	OnlyPrintNum(shuru[i]);
			ReadDecimalPre(weishu);
			printf("\n  读作：");
			if (fuhaonum % 2 == 1)	printf("负");

			ReadQian(2, 0, xuyaodu);
			if (shuru[j + 3] != '\0')	printf("点");
			for (i = j + 3; shuru[i] != '\0'; i++)	ReadOneNum(shuru[i]);
		}
		else if (judge == 0) {
			printf("记作：");
			if (fuhaonum % 2 == 1)	printf("-");
			printf("%c", shuru[j]);

			if (shuru[j + 1] != '\0')	printf(".");
			for (i = j + 1; shuru[i] != '\0'; i++)	OnlyPrintNum(shuru[i]);
			ReadDecimalPre(weishu);
			printf("\n  读作：");
			if (fuhaonum % 2 == 1)	printf("负");
			ReadOneNum(shuru[j]);
			if (shuru[j + 1] != '\0')	printf("点");
			for (i = j + 1; shuru[i] != '\0'; i++)	ReadOneNum(shuru[i]);
		}
		else {	//judge=2
			xuyaodu[1] = shuru[j];

			if (shuru[j + 1] == '\0') xuyaodu[0] = '0';
			else xuyaodu[0] = shuru[j + 1];

			printf("记作：");
			if (fuhaonum % 2 == 1)	printf("-");
			printf("%c%c", xuyaodu[1],xuyaodu[0]);

			if (shuru[j + 2] != '\0')	printf(".");
			for (i = j + 2; shuru[i] != '\0'; i++)	printf("%c", shuru[i]);
			ReadDecimalPre(weishu);

			printf("\n  读作：");
			if (fuhaonum % 2 == 1)	printf("负");
			ReadQian(1, 0, xuyaodu);
			if (shuru[j + 2] != '\0')	printf("点");
			for (i = j + 2; shuru[i] != '\0'; i++)	ReadOneNum(shuru[i]);
		}

		if (weishu <= 3) printf("毫");
		else if (weishu <= 6) printf("微");
		else if (weishu <= 9) printf("纳[诺]");
		else if (weishu <= 12) printf("皮[可]");
		else if (weishu <= 15) printf("飞[母托]");
		else if (weishu <= 18) printf("阿[托]");
		else if (weishu <= 21) printf("仄[普托]");
		else if (weishu <= 24) printf("幺[科托]");
	
		return OK;
	}
	
	//printf("judge=%d i=%d j=%d weishu=%d j指向%c", judge, i, j, weishu, shuru[j]);//调试用
	//需要忽略以零结尾的整数最后的零
	if (shuru[i] == '.') {	//带小数点
		i++;
		if (shuru[i] != '\0') {		//如果不是123.形式，也就是说是真小数
			//if (fuhaonum % 2 == 1) printf("负");
			printf("记作：");
			if (judge == 0) {
				xuyaodu[0] = shuru[j + 2];
				xuyaodu[1] = shuru[j + 1];
				xuyaodu[2] = shuru[j];
				if (fuhaonum % 2 == 1) printf("-");
				if (weishu == 3) {
					printf("%c.", xuyaodu[2]);
					for (i = j + 1; shuru[i] != '\0'; i++)	OnlyPrintNum(shuru[i]);
				}
				else {
					printf("%c%c%c.", xuyaodu[2], xuyaodu[1], xuyaodu[0]);
					for (i = j + 3; shuru[i] != '\0'; i++)	OnlyPrintNum(shuru[i]);
				}
				ReadIntPre(weishu);
				printf("\n  读作：");
				if (fuhaonum % 2 == 1) printf("负");
				ReadQian(2, 0, xuyaodu);
				printf("点");
				for (i = j + 3; shuru[i] != '\0'; i++)	ReadOneNum(shuru[i]);
			}
			else if (judge == 1) {		//带有小数点的真正的小数，并且weishu%3=1
				if (fuhaonum % 2 == 1) printf("-");
				//if (weishu == 0)	printf("0");
				printf("%c.", shuru[j]);
				for (i = j + 1; shuru[i] != '\0'; i++)	OnlyPrintNum(shuru[i]);
				ReadIntPre(weishu);
				printf("\n  读作：");
				if (fuhaonum % 2 == 1) printf("负");

				//if (weishu == 0)	printf("零aaaaaaaaaaa");	//这句看不懂，bug？
				ReadOneNum(shuru[j]);
				printf("点");
				for (i = j + 1; shuru[i] != '\0'; i++)	ReadOneNum(shuru[i]);
			}
			else {	//judge=2
				xuyaodu[0] = shuru[j + 1];
				xuyaodu[1] = shuru[j];
				if (fuhaonum % 2 == 1) printf("-");
				if (weishu == 2) {
					printf("%c.", xuyaodu[1]);
					for (i = j + 1; shuru[i] != '\0'; i++)	OnlyPrintNum(shuru[i]);
				}
				else {
					printf("%c%c.",xuyaodu[1], xuyaodu[0]);
					for (i = j + 2; shuru[i] != '\0'; i++)	OnlyPrintNum(shuru[i]);
				}
				ReadIntPre(weishu);
				printf("\n  读作：");
				if (fuhaonum % 2 == 1) printf("负");
				ReadQian(1, 0, xuyaodu);
				printf("点");
				for (i = j + 2; shuru[i] != '\0'; i++)	ReadOneNum(shuru[i]);
			}
			if (weishu > 3) {
				if (weishu <= 6) printf("千");
				else if (weishu <= 9) printf("兆");
				else if (weishu <= 12) printf("吉[咖]");
				else if (weishu <= 15) printf("太[拉]");
				else if (weishu <= 18) printf("拍[它]");
				else if (weishu <= 21) printf("艾[可萨]");
				else if (weishu <= 24) printf("泽[它]");
				else if (weishu <= 27) printf("尧[它]");
			}
			return OK;
		}
	}
	//需解决00000000000012134316读作十二点兆的问题
	//不带小数点或为123.形式
	
	i--;
	if (shuru[i] != '.') i++;
	for (i--; shuru[i] == '0'; i--)	endzeros++;		//算结尾有多少0
	if (judge == 0) {
		xuyaodu[0] = shuru[j + 2];
		xuyaodu[1] = shuru[j + 1];
		xuyaodu[2] = shuru[j];

		printf("记作：");
		if (fuhaonum % 2 == 1) printf("-");
		if (weishu == 3) {
			printf("%c", xuyaodu[2]);
			if (weishu - endzeros > 1) printf(".");
			//j代表的shuru[j]为第一个非零数字
			for (i = j + 1; i < 3 - endzeros + j; i++)	OnlyPrintNum(shuru[i]);
		}
		else {
			printf("%c%c%c", xuyaodu[2], xuyaodu[1], xuyaodu[0]);
			if (weishu - endzeros > 3) printf(".");
			for (i = j + 3; i < weishu - endzeros + j; i++)	OnlyPrintNum(shuru[i]);
		}
		ReadIntPre(weishu);
		printf("\n  读作：");
		if (fuhaonum % 2 == 1) printf("负");

		ReadQian(2, 0, xuyaodu);
		if (weishu - endzeros > 3) printf("点");		//加点条件，很巧妙
		for (i = j + 3; i < weishu - endzeros + j; i++)	ReadOneNum(shuru[i]);
	}
	else if (judge == 1) {

		printf("记作：");
		if (fuhaonum % 2 == 1) printf("-");
		printf("%c", shuru[j]);
		if (weishu - endzeros > 1) printf(".");
		for (i = j + 1; i < weishu - endzeros + j; i++)	OnlyPrintNum(shuru[i]);
		ReadIntPre(weishu);
		printf("\n  读作：");
		if (fuhaonum % 2 == 1) printf("负");

		ReadOneNum(shuru[j]);
		if (weishu - endzeros > 1) printf("点");
		//另一个加点条件，也是很巧妙。考虑if (weishu - 1 != endzeros)
		for (i = j + 1; i < weishu - endzeros + j; i++)	ReadOneNum(shuru[i]);
	}
	else {	//judge=2
		xuyaodu[0] = shuru[j + 1];
		xuyaodu[1] = shuru[j];

		printf("记作：");
		if (fuhaonum % 2 == 1) printf("-");
		if (weishu == 2) {
			printf("%c", xuyaodu[1]);
			if (endzeros < 1) printf(".");
			for (i = j + 1; i < 2 - endzeros + j; i++)	OnlyPrintNum(shuru[i]);
		}
		else {
			printf("%c%c", xuyaodu[1], xuyaodu[0]);
			if (weishu - endzeros > 2) printf(".");
			for (i = j + 2; i < weishu - endzeros + j; i++)	OnlyPrintNum(shuru[i]);
		}
		ReadIntPre(weishu);
		printf("\n  读作：");
		if (fuhaonum % 2 == 1) printf("负");

		ReadQian(1, 0, xuyaodu);
		//printf("j=%d weishu=%d endzeros=%d ", j, weishu, endzeros);
		if (weishu - endzeros > 2) printf("点");		//水到渠成
		for (i = j + 2; i < weishu - endzeros + j; i++)	ReadOneNum(shuru[i]);
	}
	if (weishu > 3) {
		if (weishu <= 6) printf("千");
		else if (weishu <= 9) printf("兆");
		else if (weishu <= 12) printf("吉[咖]");
		else if (weishu <= 15) printf("太[拉]");
		else if (weishu <= 18) printf("拍[它]");
		else if (weishu <= 21) printf("艾[可萨]");
		else if (weishu <= 24) printf("泽[它]");
		else if (weishu <= 27) printf("尧[它]");
	}

	return OK;
}