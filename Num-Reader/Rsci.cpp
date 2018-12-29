#include<stdio.h>
#include"Nbasic.h"


Status SciReadNum(char shuru[]) {								
	//科学计数法模式主体代码
	//科学计数法模式下，对shuru扫描一遍即可输出读法。
	//这里也是使用了初代IReadNum函数来读幂次，因为该函数对输入的要求为int 
	int i = 0, n = 0, j = 0, fuhaonum;	//i用于光标，j用于底层小循环 
	int xiaonum = 0, zerosnum = 0;
	int xszs;	//小数专杀，用于解决00.  00  0  .0001   0.000123的bug
	for (i = 0; shuru[i] == ' ' || shuru[i] == '\t'; i++);	//将光标移过空白字符 
	for (fuhaonum = 0; shuru[i] == '-'; i++)	fuhaonum++;	//统计负号数量，将光标移过负号 
	if (shuru[i] == '\0') {		//如果只有空白字符和负号 
		printf("  不是指令！");
		return ERROR;
	}
	for (xszs = i; '0' == shuru[xszs]; xszs++);
	if ('.' == shuru[xszs]) xszs++;
	if ('\0' == shuru[xszs]) {
		printf("零");
		return OK;
	}
	//三五七，三八三九二十一


	zerosnum = 0;
	if (shuru[i] == '.') {	//如果移过开头之后直接就是小数点了 
		do {
			i++;
			n++;
		} while (shuru[i] == '0');
		if (shuru[i] == '\0') {
			printf("零");
			if (n>1) {
				printf("点");
				for (j = 0; j<n - 1; j++) {
					printf("零");
					xiaonum++;
				}
			}
			if (xiaonum>10) printf("\n  该数的小数部分共有%d位", xiaonum);
			return OK;	//解决.000问题 
		}
		//printf("  ");
		if (fuhaonum % 2 == 1)	printf("负");
		ReadOneNum(shuru[i]);
		i++;
		if (shuru[i] != '\0') {
			printf("点");
			for (; shuru[i] != '\0'; i++) {
				ReadOneNum(shuru[i]);
				xiaonum++;
			}
		}
		printf("乘十的");
		n = -n;
		IReadNum(n);
		printf("次方");
		xiaonum -= n;
		if (xiaonum>10) printf("\n  该数的小数部分共有%d位", xiaonum);
		return OK;		//解决.001问题 
	}
	else {	//否则的话一定是0或者其他数字开头，如0000, 00.0, 100, 0.335 , 100.0等 
		while (shuru[i] == '0') i++;	//先将光标移过可能的零
		if (i>0) { 		//当可以后退时 
			if (shuru[i] == '.' || shuru[i] == '\0') i--;	//如果光标指向的是结束符或小数点，则后退 
		}
		j = i;
		//shuru[j]为第一个非零数字 
		//去头零完成
		//下面目标是，扫描去头零后的数字，遇到.或EOF退出扫描 
		while (1) {	//只要不是小数点或EOF，就继续... 
			if (shuru[i] == '.')	break;
			if (shuru[i] == '\0') 	break;
			n++;
			i++;
		}
		//跳出来的时候shuru[i]不是.就是EOF 
		if (shuru[i] == '\0') {	//如果是EOF，说明没有小数点 
			//printf("  ");
			if (shuru[j] != '0') {	//不要把条件写成0 
				if (fuhaonum % 2 == 1)	printf("负");
			}
			ReadOneNum(shuru[j]);
			j++;
			for (i = j; shuru[i] != '\0'; i++);
			if (shuru[--i] != '0') {	//不是0结尾的 
				if (shuru[j] != '\0') {
					printf("点");
					for (; shuru[j] != '\0'; j++) {
						ReadOneNum(shuru[j]);
					}
					printf("乘十的");		//放在里面可以避免一乘十的零次方问题 
					IReadNum(n - 1);
					printf("次方");
				}
			}
			else {
				for (; shuru[i] == '0'; i--)	zerosnum++;
				if (zerosnum + 1 == n) {
					printf("乘十的");
					IReadNum(n - 1);
					printf("次方");
				}
				else {
					printf("点");
					for (i = 0; i<n - zerosnum - 1; i++) {
						ReadOneNum(shuru[j]);
						j++;
					}
					printf("乘十的");		//放在里面可以避免一乘十的零次方问题 
					IReadNum(n - 1);
					printf("次方");
				}
			}
			if (n>10) printf("\n  该数的整数部分共有%d位", n);
			return OK;		//解决123问题 
		}
		//否则的话说明有小数点，且shuru[i]就是小数点 
		//printf("  ");
		if (shuru[j] != '0') {		//不要把条件写成0 
			if (fuhaonum % 2 == 1)	printf("负");
		}
		i++;
		if (shuru[i] == '\0') {	//如果是小数点结尾的 
			ReadOneNum(shuru[j]);
			j++;
			for (i = j; shuru[i] != '.'; i++);
			if (shuru[--i] != '0') {	//不是0结尾的 
				if (shuru[j] != '\0') {
					printf("点");
					for (; shuru[j] != '.'; j++) {
						ReadOneNum(shuru[j]);
					}
					printf("乘十的");		//放在里面可以避免一乘十的零次方问题 
					IReadNum(n - 1);
					printf("次方");
				}
			}
			else {
				for (; shuru[i] == '0'; i--)	zerosnum++;
				if (zerosnum + 1 == n) {
					printf("乘十的");
					IReadNum(n - 1);
					printf("次方");
				}
				else {
					printf("点");
					for (i = 0; i<n - zerosnum - 1; i++) {
						ReadOneNum(shuru[j]);
						j++;
					}
					printf("乘十的");		//放在里面可以避免一乘十的零次方问题 
					IReadNum(n - 1);
					printf("次方");
				}
			}
			if (n>10) printf("\n  该数的整数部分共有%d位", n);
			return OK;		//解决123.问题 
		}
		//现在就剩下123.35 0.000 -0.000型数字需要读
		ReadOneNum(shuru[j]);	//读出1
		printf("点");	//直接打点 
		j++;
		for (; shuru[j] != '.'; j++) {
			ReadOneNum(shuru[j]);	//顺序读完整数部分 
		}
		j++;
		for (; shuru[j] != '\0'; j++) {
			ReadOneNum(shuru[j]);	//顺序读完小数部分并统计位数 
			xiaonum++;
		}
		if (n != 1) {				//根据n值也可以避免免一乘十的零次方问题  
			printf("乘十的");
			IReadNum(n - 1);
			printf("次方");
		}
		if (n>10 && xiaonum>10)	printf("\n  该数的整数部分共有%d位，小数部分共有%d位", n, xiaonum);
		else if (n>10) printf("\n  该数的整数部分共有%d位", n);
		else if (xiaonum>10) printf("\n  该数的小数部分共有%d位", xiaonum);
		return OK;		//解决123.5问题 
	}
}

/*Status SciReadNum(char shuru[]) {		//越改越崩。直接放弃，用初版
	//科学计数法模式主体代码
	//科学计数法模式下，对shuru扫描一遍即可输出读法。
	//这里也是使用了初代IReadNum函数来读幂次，因为该函数对输入的要求为int 
	int i = 0, n = 0, j = 0, fuhaonum;	//i用于光标，j用于底层小循环 
	int xiaonum = 0, zerosnum = 0;
	int spc = 0, XiaoShuKaiTouZeros = 0;	//普通变量spc，小数开头zeros
	int iszero;
	for (i = 0; shuru[i] == ' ' || shuru[i] == '\t'; i++);	//将光标移过空白字符 
	for (fuhaonum = 0; shuru[i] == '-'; i++)	fuhaonum++;	//统计负号数量，将光标移过负号 
	if (shuru[i] == '\0') {		//如果只有空白字符和负号 
		printf("不是指令！");
		return ERROR;
	}
	if (shuru[i] == '.') {	//如果移过开头之后直接就是小数点了 
		do {
			i++;
			n++;
		} while (shuru[i] == '0');
		if (shuru[i] == '\0') {
			printf("零");
			if (n>1) {
				printf("点");
				for (j = 0; j<n - 1; j++) {
					printf("零");
					xiaonum++;
				}
			}
			if (xiaonum>10) printf("\n  该数的小数部分共有%d位", xiaonum);
			return OK;	//解决.000问题 
		}

		//printf("  ");
		if (fuhaonum % 2 == 1)	printf("负");

		ReadOneNum(shuru[i]);
		i++;
		if (shuru[i] != '\0') {
			printf("点");
			for (; shuru[i] != '\0'; i++) {
				ReadOneNum(shuru[i]);
				xiaonum++;
			}
		}
		printf("乘十的");
		n = -n;
		IReadNum(n);
		printf("次方");
		xiaonum -= n;
		if (xiaonum>10) printf("\n  该数的小数部分共有%d位", xiaonum);
		return OK;		//解决.001问题 
	}
	else {	//否则的话一定是0或者其他数字开头，如0000, 00.0, 100, 0.335 , 100.0等 
		//0000 00. 会出问题
		//.00 0.00 00.0不会出问题
		while (shuru[i] == '0') i++;	//先将光标移过可能的零
		if (i>0) { 		//当可以后退时 
			if (shuru[i] == '.' || shuru[i] == '\0') i--;	//如果光标指向的是结束符或小数点，则后退 
		}
		iszero = i;
		//shuru[i]为第一个非零数字
		//去头零完成
		if (shuru[iszero] == '0') {
			iszero++;
			if (shuru[iszero] == '.') iszero++;
			if (shuru[iszero] == '\0') {
				printf("零");
				return OK;
			}
		}
		//下面目标是，扫描去头零后的数字，遇到.或EOF退出扫描 
		while (1) {	//只要不是小数点或EOF，就继续... 
			if (shuru[i] == '.')	break;
			if (shuru[i] == '\0') 	break;
			n++;
			i++;
		}
		//跳出来的时候shuru[i]不是.就是EOF 
		if (shuru[i] == '\0') {	//如果是EOF，说明没有小数点 
			//printf("  ");
			if (shuru[j] != '0') {	//不要把条件写成0 
				if (fuhaonum % 2 == 1)	printf("负");
			}
			ReadOneNum(shuru[j]);
			j++;
			for (i = j; shuru[i] != '\0'; i++);
			if (shuru[--i] != '0') {	//不是0结尾的 
				if (shuru[j] != '\0') {
					printf("点");
					for (; shuru[j] != '\0'; j++) {
						ReadOneNum(shuru[j]);
					}
					printf("乘十的");		//放在里面可以避免一乘十的零次方问题 
					IReadNum(n - 1);
					printf("次方");
				}
			}
			else {		//没有小数点，而且是0结尾
				for (; shuru[i] == '0'; i--)	zerosnum++;	//遇到0000或0时就要出bug
				if (zerosnum + 1 == n) {	
					printf("乘十的");
					IReadNum(n - 1);
					printf("次方");
				}
				else {
					printf("点");	///////////////////////////
					for (i = 0; i<n - zerosnum - 1; i++) {
						ReadOneNum(shuru[j]);
						j++;
					}
					printf("乘十的");		//放在里面可以避免一乘十的零次方问题 
					IReadNum(n - 1);
					printf("次方");
				}
			}
			if (n>10) printf("\n  该数的整数部分共有%d位", n);
			return OK;		//解决123问题 
		}
		//否则的话说明有小数点，且shuru[i]就是小数点 
		//printf("  ");
		if (shuru[j] != '0') {		//不要把条件写成0 
			if (fuhaonum % 2 == 1)	printf("负");
		}
		i++;
		if (shuru[i] == '\0') {	//如果是小数点结尾的 
			ReadOneNum(shuru[j]);
			j++;
			for (i = j; shuru[i] != '.'; i++);
			if (shuru[--i] != '0') {	//不是0结尾的 
				if (shuru[j] != '\0') {
					printf("点");
					for (; shuru[j] != '.'; j++) {
						ReadOneNum(shuru[j]);
					}
					printf("乘十的");		//放在里面可以避免一乘十的零次方问题 
					IReadNum(n - 1);
					printf("次方");
				}
			}
			else {
				for (; shuru[i] == '0'; i--)	zerosnum++;
				if (zerosnum + 1 == n) {
					printf("乘十的");
					IReadNum(n - 1);
					printf("次方");
				}
				else {
					printf("点");
					for (i = 0; i<n - zerosnum - 1; i++) {
						ReadOneNum(shuru[j]);
						j++;
					}
					printf("乘十的");		//放在里面可以避免一乘十的零次方问题 
					IReadNum(n - 1);
					printf("次方");
				}
			}
			if (n>10) printf("\n  该数的整数部分共有%d位", n);
			return OK;		//解决123.问题 
		}
		//现在就剩下123.35 0.000 -0.000型数字需要读
		if (shuru[j] == '0') {
			xiaonum = 0;
			XiaoShuKaiTouZeros++;
			for (spc = j + 2; shuru[spc] == '0'; spc++)	XiaoShuKaiTouZeros++;
			if (shuru[spc] == '\0') {
				printf("零");
				if (XiaoShuKaiTouZeros > 1) {
					printf("点");
					for (i = 1; i < XiaoShuKaiTouZeros; i++) printf("零");
				}
				return 0;
			}
			for (spc = j + 2; shuru[spc] != '\0'; spc++)	xiaonum++;
			j = j + XiaoShuKaiTouZeros + 1;
			if (fuhaonum % 2 == 1)	printf("负");
			ReadOneNum(shuru[j]);
			if (shuru[++j] != '\0') printf("点");
			for (; shuru[j] != '\0'; j++) ReadOneNum(shuru[j]);
			printf("乘十的负");
			IReadNum(XiaoShuKaiTouZeros);
			printf("次方");
			if (xiaonum>10) printf("\n  该数的小数部分共有%d位", xiaonum);
			return OK;
		}
		ReadOneNum(shuru[j]);	//读出最高位
		printf("点");	//直接打点 
		j++;
		for (; shuru[j] != '.'; j++) {
			ReadOneNum(shuru[j]);	//顺序读完整数部分 
		}
		j++;
		for (; shuru[j] != '\0'; j++) {
			ReadOneNum(shuru[j]);	//顺序读完小数部分并统计位数 
			xiaonum++;
		}
		if (n != 1) {				//根据n值也可以避免免一乘十的零次方问题  
			printf("乘十的");
			IReadNum(n - 1);
			printf("次方");
		}
		if (n>10 && xiaonum>10)	printf("\n  该数的整数部分共有%d位，小数部分共有%d位", n, xiaonum);
		else if (n>10) printf("\n  该数的整数部分共有%d位", n);
		else if (xiaonum>10) printf("\n  该数的小数部分共有%d位", xiaonum);
		return OK;		//解决123.5问题 
	}
}*/