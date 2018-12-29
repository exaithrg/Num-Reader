#pragma once

#pragma warning(disable:4996)

//基础宏定义
#define Status int
#define OK	1
#define ERROR 0
#define YES 1
#define NO	0
#define OVERFLOW 2

//预处理函数。用于对输入指令进行初步处理
Status Pretreatment(char numarray[], int &zhiling, int &mode);	//预处理

//通用函数。用于科学计数法模式读指数，也可以移植到其余程序让输出变为汉字。程序初衷。
int IReadNum(int TransNum);		//读int范围内数字 int版模式主体函数
int IReadOneNum(int onenum);	//直读函数 int版
int ICountZerosEnd(int gao, int di, int qianwei[]);		//计算数字末尾0的个数 int版
int IZerosBtw(int gao, int di, int qianwei[]);		//判断是否为间0数字，最多判断4位 int版
int IReadQian(int gao, int di, int qianwei[]);		//读四位以内整数 int版
Status ReadOneNum(char onenum);		//直读函数 char版
int CountZerosEnd(int gao, int di, char qianwei[]);		//计算数字末尾0的个数 char版
Status ZerosBtw(int gao, int di, char qianwei[]);	//判断是否为间0数字，最多判断4位 char版
Status ReadQian(int gao, int di, char qianwei[]);	//读四位以内整数 char版
Status readwan(char TransNum[], int zuigao);	//读万以上数使用
Status readyi(char TransNum[], int zuigao);		//读亿
Status OnlyPrintNum(char character);			//打印且仅打印一位阿拉伯数字

//十九级无量数读数模式专用函数
Status InfiReadNum(char shuru[]);		//按十九级无量数规则读出数字。模式主体函数
Status readzhao(char TransNum[], int zuigao);	//读兆
//--------------------不正常的分界线-------------------------//
Status readjing(char TransNum[], int zuigao);	//读京
Status readgai(char TransNum[], int zuigao);	//读垓
Status readzi(char TransNum[], int zuigao);		//读秭
Status readrang(char TransNum[], int zuigao);	//读穰
Status readgou(char TransNum[], int zuigao);	//读沟
Status readjian(char TransNum[], int zuigao);	//读涧
Status readzheng(char TransNum[], int zuigao);	//读正
Status readzai(char TransNum[], int zuigao);	//读载
Status readji(char TransNum[], int zuigao);		//读极
//---------------------奇葩的分界线-------------------------//
Status readhenghesha(char TransNum[], int zuigao);			//读恒河沙
Status readasengzhi(char TransNum[], int zuigao);			//读阿僧祗
Status readnayouta(char TransNum[], int zuigao);			//读那由他
Status readbukesiyi(char TransNum[], int zuigao);			//读不可思议
Status readwuliang(char TransNum[], int zuigao);			//读无量
Status readdashu(char TransNum[], int zuigao);				//读大数

//普通读数模式专用函数，说白了是自欺欺人
Status DoubleReadNum(char shuru[]);		//普通模式读数

//科学计数法模式专用函数
Status SciReadNum(char shuru[]);		//科学计数法模式读数

//国际单位词头模式专用函数
Status SipreReadNum(char shuru[]);		//国际单位词头模式读数
Status ReadIntPre(int weishu);			//给出某整数所应对应的词头。输入为此整数的位数。
Status ReadDecimalPre(int prezerosnum);	//给出某小数所应对应的词头。输入为此小数开头零的个数。

//发音模式读数
Status SpeakNumber(char shuru[]);		//发音模式读数
