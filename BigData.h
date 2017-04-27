//BigData.h  文件
#pragma once
#include<string.h>
#include<string>
typedef long long  INT64;

//表示出两个极端值
#define MAXINT64 (INT64)0x7fffffffffffffff 
#define MININT64 (INT64)0x8000000000000000 

class BigData
{
public:
	//三种的构造函数 
	BigData()
		:_value(0)
		,_str(string())
		,_IsOverFlow(false)
	{
		_str.resize(3);
		_str[0] = '+';
		_str[1] ='0';
		_str[2] = 0;
	}
	BigData(const  char *  str);
	BigData(const INT64 value);
	//判断一个数有没有越界
	bool IsOverFlow(const  char  * str);
	//重载实现的  +  -  *  /  %
	BigData operator+(const  BigData& data);	
	BigData operator-(const  BigData& data);	
	BigData operator*(const  BigData& data);	
	BigData operator/(const  BigData& data);
	BigData operator%(const  BigData& data);
	//重载的比较函数
	bool operator>(const  BigData& data);
	bool operator<(const  BigData& data);
	bool operator==(const  BigData& data);
	bool operator!=(const  BigData& data);

protected:
	INT64	_value;			//当前的数 没有溢出，，，表示
	string  _str;			//字符串表示
	bool	_IsOverFlow;	//表示的是当前的数有有没越界
	
};

//str1   长度  大于 str2
//str1  与  str2不戴符号
//实现两个字符串的  四则运算，，，，一般情况下，，str1 长度要大于str2
string   StrAddStr(char *str1,char *str2);
string   StrSubStr(char *str1,char *str2);
string   StrMulStr(char *str1,char *str2);
string   StrDivStr(char *str1,char *str2);
string   StrRemStr(char *str1,char *str2);



//测试用例
void TestBigData();