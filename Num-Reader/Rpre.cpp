#include<stdio.h>
#include<string.h>
#include<Windows.h>
#include"Nbasic.h"

//v5预处理函数的功能要求
//1. 判断输入是否为数字，是则将zhiling的值改为1并返回OK 
//2. 如果输入不是数字但是为特定指令，则将zhiling置为大于1的特定值并返回OK 
//3. 若输入既非数字又非指令，则将zhiling置为0并返回ERROR 

//Pretreatment认可的数字：
//若干空格或Tab+若干负号+若干0作为开头
//开头后面紧跟数字或小数点，且小数点只出现一次
//除开头外其余任何位置不出现空白字符 

Status Pretreatment(char numarray[], int &zhiling, int &mode) {
	int flag = 0, i = 0;		//flag用于判断小数点个数  
	static int color = 0, turnoff = 0;

	if (numarray[0] == '\0') {
		zhiling = 0;
		return ERROR;
	}

	if (strcmp(numarray, "exit") == 0) {	//控制指令从2开始 
		//Beep(1200, 200);
		zhiling = 2;
		return OK;
	}
	else if (strcmp(numarray, "ordi") == 0) {			//0
		printf("  进入普通读数模式\n");
		//Beep(700, 350);
		mode = 0;
		zhiling = 0;
		return OK;
	}
	else if (strcmp(numarray, "infi") == 0) {			//1
		printf("  进入十九级无量数读数模式\n");
		//Beep(800, 350);
		mode = 1;
		zhiling = 0;
		return OK;
	}
	else if (strcmp(numarray, "sci") == 0) {				//2
		printf("  进入科学计数法读数模式\n");
		//Beep(900, 350);
		mode = 2;
		zhiling = 0;
		return OK;
	}
	else if (strcmp(numarray, "sipre") == 0) {				//2
		printf("  进入国际单位词头模式\n");
		//Beep(1000, 350);
		mode = 3;
		zhiling = 0;
		return OK;
	}
	else if (strcmp(numarray, "speak") == 0) {				//2
		printf("  进入发音模式\n");
		Beep(1200, 400);
		mode = 4;
		zhiling = 0;
		return OK;
	}
	else if (strcmp(numarray, "modeinfo") == 0) {
		zhiling = 3;
		printf("  *------------------------------------------------------------------------------------------------------\n");
		printf("  * 普通读数模式(ordi)下，最高可输出整数部分不超过16位，小数部分最高不超过99位的数字的中文读法。\n");
		printf("  *------------------------------------------------------------------------------------------------------\n");
		printf("  * 发音模式(speak)与普通读数模式对输入的要求一致。\n");
		printf("  * 此模式下，输入的数字会通过扬声器按中文读法读出。在读数的过程中不可以中断，不可以输入指令。\n");
		printf("  *------------------------------------------------------------------------------------------------------\n");
		printf("  * 科学计数法模式(sci)下，最高允许数字位数为500位。\n");
		printf("  * 应注意的是，此模式会忽略以零结尾的整数最后的零，对于其它数字将保留所有有效数字。\n");
		printf("  * 科学计数法是一种计数方法，把一个数表示成a(1<=a<10)与10的整数次幂相乘的形式。\n");
		printf("  * 此方法的主要优势在于当我们需要标记某个位数较多的数时，可以带来时间和空间上的便利。\n");
		printf("  *------------------------------------------------------------------------------------------------------\n");
		printf("  * 国际单位词头模式(sipre)下，最高允许整数数字位数为27位。\n");
		printf("  * 本模式的依据为国际单位制中用于构成十进倍数和分数单位的词头。\n");
		printf("  * 首先给出按词头转换后的数字，然后给出中文读法。具体词头名称如下表：\n");
		printf("  * 尧[它](Y 10^24) 泽[它](Z 10^21) 艾[可萨](E 10^18) 拍[它](P 10^15) 太[拉](T 10^12) 吉[咖](G 10^9)\n");
		printf("  * 兆(M 10^6) 千(k) 百(h) 十(da) 分(d) 厘(c) 毫(m) 微(μ10^-6) 纳[诺](n 10^-9) 皮[可](p 10^-12)\n");
		printf("  * 飞[母托](f 10^-15) 阿[托](a 10^-18) 仄[普托](z 10^-21) 幺[科托](y 10^-24)\n");
		printf("  * 埃(符号为A上面加一个小圈 10^-10)虽然常用，但因其不是国际单位，故忽略。\n");
		printf("  * 请注意，本模式下10^-1读作分，10^-2读作厘，10^-3读作毫，这一点与钱币所用的元角分厘不同，请注意区别。\n");
		printf("  *------------------------------------------------------------------------------------------------------\n");
		printf("  * 十九级无量数模式(infi)下，数字整数部分最高允许位数为100位，可读位数为76位，小数位数最高不超过99位。\n");
		printf("  * 该模式采用的是中数进位方法的十九级无量数表示法。整数、小数部分数字过多的还会同时给出数字位数。\n");
		printf("  * 无量数来自古印度计数法，共分为19级，依次为：\n");
		printf("  * 个 万 亿 兆 京 垓 秭 穰 沟 涧 正 载 极 恒河沙 阿僧祗 那由他 不可思议 无量 大数\n");
		printf("  * 而中数的进位方法，则是表示以上各级每级相差4位数字，如万万为亿，万亿为兆，万兆为京。\n");
		printf("  * 进位方法还有上数、下数。\n  * 其中，上数表示各级相差前一级的平方位数字，如万万为亿，亿亿为兆，兆兆为京。\n");
		printf("  *------------------------------------------------------------------------------------------------------\n");
		return OK;
	}
	else if (strcmp(numarray, "byebye") == 0) {
		if (zhiling != -1)	printf("  关机倒计时60秒！输入cancel取消...\n");
		else	printf("  ");
		zhiling = -1;
		turnoff = 1;
		system("shutdown -s -t 60");
		return OK;
	}
	else if (strcmp(numarray, "cancel") == 0) {
		if (turnoff == 1) {
			system("shutdown -a");
			printf("  中止关机成功\n");
			turnoff = 0;
			zhiling = -2;
			return OK;
		}
		printf("  因为没有任何进行中的关机过程，所以无法中止系统关机\n");
		turnoff = 0;
		return OK;
	}
	else if (strcmp(numarray, "info") == 0) {
		zhiling = 4;
		printf("                               -------------程序说明-------------\n");
		printf("  *------------------------------------------------------------------------------------------------------\n");
		printf("  * 本程序的主要功能为：给出一个阿拉伯数字按某种规则得到的中文读法。\n");
		printf("  * 直接在程序窗口中输入数字并回车即可输出数字读法。\n");
		printf("  * 程序共设5种读数模式，默认为普通读数模式。对于程序所有的模式，认可的数字特点为：\n");
		printf("  * [若干空格或Tab+若干负号+若干0]+数字或小数点，[]中的内容可有可无，小数点最多出现一次。\n");
		printf("  * 样例：100 / 10.2 /			-0.07 / 99980001. / . / .123 / ---000523 / --------.0  \n");
		printf("  *------------------------------------------------------------------------------------------------------\n");
		printf("  * 常用指令表：\n");
		printf("  * exit	退出程序		byebye		60秒倒计时关机(cancel取消)\n");
		printf("  * hello	欢迎仪式		clear		清屏\n");
		printf("  * reverse	窗口反色		ruler		位数尺\n");
		printf("  * modeinfo	各模式介绍		mode		查看当前模式\n");
		printf("  * ordi	普通读数模式		sci		科学计数法模式\n");
		printf("  * infi	十九级无量数模式	sipre		国际单位词头模式\n");
		printf("  * speak	发音模式		about		关于信息\n");
		printf("  *------------------------------------------------------------------------------------------------------\n");
		return OK;
	}
	else if (strcmp(numarray, "ruler") == 0) {
		zhiling = 5;
		printf("  1***2***3***4***5**|6***7***8***9***0**|1***2***3***4***5**|6***7***8***9*|M***|****|****|****|****|---\n");
		return OK;
	}
	else if (strcmp(numarray, "clear") == 0) {
		zhiling = 6;
		system("cls");	//清屏函数 
		printf("          ******************** 读数程序MARK IV启动！ *************************\n");
		printf("          ************* 输入info查看程序说明，输入exit退出程序。 *************\n");
		//Beep(1050, 500);
		printf(">>请输入\n");
		return OK;
	}
	else if (strcmp(numarray, "about") == 0) {
		zhiling = 7;
		printf("  作    者：Brilliantan\n");
		printf("  修改日期：2018.9.6\n");
		printf("  版    本：v4.985\n");
		printf("  本程序只供学习使用，未经作者许可，不得用于其它任何用途\n");
		printf("  All rights reserved\n");
	}
	else if (strcmp(numarray, "mode") == 0) {
		zhiling = 8;
		printf("  当前模式为");
		if (mode == 1)	printf("十九级无量数读数模式\n");
		else if (mode == 0)	printf("普通读数模式\n");
		else if (mode == 2)	printf("科学计数法读数模式\n");
		else if (mode == 3)	printf("国际单位词头模式\n");
		else if (mode == 4)	printf("发音模式\n");
		return OK;
	}
	else if (strcmp(numarray, "reverse") == 0) {				//2
		zhiling = 9;
		if (color == 0) {
			system("color F0");
			color = 1;
			return OK;
		}
		color = 0;
		system("color 0F");
		return OK;
	}
	else if (strcmp(numarray, "hello") == 0) {				//2
		zhiling = 10;
		int sleeptime = 140, i;
		//int freq = 500, dura = 200;
		//Beep(freq, dura); freq += 50;
		//Beep(freq, dura); freq += 50;
		//Beep(freq, dura); freq += 50;
		//Beep(freq, dura); freq += 50;
		//Beep(freq, dura); freq += 50;
		//Beep(freq, dura); freq += 50;
		//Beep(freq, dura); freq += 50;
		//Beep(freq, dura); freq += 50;
		//Beep(freq, dura); freq += 50;
		//Beep(freq, dura); freq += 50;
		//Beep(freq, dura); freq += 50;
		//Beep(freq, dura); freq += 50;
		//Beep(freq, dura); freq += 50;
		//Beep(freq, dura); freq += 50;
		//Beep(freq, dura); freq += 50;
		//Beep(freq, dura); freq += 50;
		//Beep(1500, 700);
		//Beep(1750, 700);
		//Beep(2000, 800);
		for (i = 0; i < 1; i++) {
			system("color 0F"); Sleep(sleeptime);
			system("color 1E"); Sleep(sleeptime);
			system("color 2D"); Sleep(sleeptime);
			system("color 3C"); Sleep(sleeptime);
			system("color 4B"); Sleep(sleeptime);
			system("color 5A"); Sleep(sleeptime);
			system("color 69"); Sleep(sleeptime);
			system("color 78"); Sleep(sleeptime);
			system("color 87"); Sleep(sleeptime);
			system("color 96"); Sleep(sleeptime);
			system("color A5"); Sleep(sleeptime);
			system("color B4"); Sleep(sleeptime);
			system("color C3"); Sleep(sleeptime);
			system("color D2"); Sleep(sleeptime);
			system("color E1"); Sleep(sleeptime);
			system("color F0"); Sleep(sleeptime);
		}
		if (color == 0) system("color 0F");
		else if (color == 1) system("color F0");
		return OK;
	}
	else {
		while (numarray[i] == ' ' || numarray[i] == '\t')	i++;	//从开头开始，将i置为第一个不是空格或tab的字符处
		while (numarray[i] == '-')	i++;	//如果空格后为负号，光标继续前进，将i置为第一个既非空格又非负号的字符处
											//上述代码的作用为跳过符号开头 
		while (numarray[i] != '\0') {
			if (numarray[i] == '.') {
				flag++;
				if (flag>1) {
					i = 0;
					break;
				}
			}
			else if (isdigit(numarray[i]) == 0) {
				i = 0;
				break;
			}
			i++;
		}
		if (i == 0) {
			zhiling = 0;
			printf("  不是指令！\n");
			return ERROR;	//数字将被放在最后进行判断，因此只要不是数字即可直接return ERROR 
		}
		zhiling = 1;
	}
	return OK;
}

