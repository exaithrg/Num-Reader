#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<Windows.h>
#include"Nbasic.h"

//输入汉字会崩掉
//希望改善只输入回车的情况，让它继续打印>>而非先出现不是指令

//最终版本应有如下模式
//1. 常用模式。
//2. 十九级无量数模式
//3. 科学计数模式
//4. 千进位模式（新版作国际单位词头模式）
//5. 以常用模式为准的发音模式 
//以上模式可随时通过输入指令进行切换 

//拓展：对4.5k类型数字的支持  对1.5*10^3类型数字的支持

int main() {
	char bignumber[502];
	int numlen, i = 0, flag = 0, zhiling = 0, mode = 2;
	memset(bignumber, '\0', 502);//对bignumber进行初始化 
	system("color 0F");
	printf("          ********************* 读数程序MARK V启动！ *************************\n");
	printf("          ************* 输入info查看程序说明，输入exit退出程序。 *************\n");
	printf(">>请输入数字或指令\n");
	while (1) {
		printf(">>");
		while (1) {
			bignumber[i] = getchar();
			if (bignumber[i] == '\n') {
				break;
			}
			if (i>500) {
				printf("  检测到输入字符超过500位，跳过读数，请重新输入。\n");
				flag = 1;
				//fflush(stdin);	//此命令已经不再被支持，应换成下面的玩意
				scanf("%*[^\n]%*c");
				//％〔^\n〕将逐个读取缓冲区中的’\n’字符之前的其它字符，
				//％后面的表示将读取的这些字符丢弃，前遇到’\n’字符时便停止读取操作，
				//此时，缓冲区中尚有一个’\n’字符遗留，
				//所以后面的％*c将读取并丢弃这个遗留的换行符，
				//这里的星号和前面的星号作用相同。
				//由于所有从键盘的输入都是以回车结束的，而回车会产生一个’\n’字符，
				//所以将’\n’连同它之前的字符全部读取并丢弃之后，也就相当于清除了输入缓冲区
				memset(bignumber, '\0', 502);
				break;
			}
			i++;
		}
		bignumber[i] = '\0';
		i = 0;
		if (flag == 1) {
			flag = 0;
			continue;
		}
		//以上为自写gets函数。问题在于，只要输入中文就会崩掉。
		numlen = strlen(bignumber);
		if (numlen>100 && mode != 2) {
			memset(bignumber, '\0', 502);
			printf("  检测到输入字符超过100位，跳过读数，请重新输入。\n");
			continue;
		}

		//预处理函数Pretreatment
		Pretreatment(bignumber, zhiling, mode);

		if (zhiling == 1) {
			printf("  ");
			if (mode == 0)			DoubleReadNum(bignumber);
			else if (mode == 1)		InfiReadNum(bignumber);
			else if (mode == 2)		SciReadNum(bignumber);
			else if (mode == 3)		SipreReadNum(bignumber);
			else if (mode == 4)		SpeakNumber(bignumber);
			printf("\n");
		}
		else if (zhiling == 2) {	//2为退出程序指令 
			printf("  程序退出!\n");
			//printf("%c[2K", 27);	//不知道是干嘛的
			Sleep(1000);
			return 0;
		}
	}
}