#include<iostream>
using namespace std;
#include"BigData.h"
#include<assert.h>
//定义极端值的两个字符串  全局
const char  * MAXCHAR64= "+9223372036854775807";
const char  * MINCHAR64= "-9223372036854775807";
//构造函数 
//字符串构造要考虑的情况

// 字符串 "1234568"  "    2325"
//  "000000123" "000123 34"
// "+1234"  "-132"
// "+   780" "+as"
BigData::BigData(const  char *  s)
	:_IsOverFlow(false)
	,_str(string())
	,_value(0)
{
	//传进来的数 是 一个null字符串
	if(s == NULL)
	{
		//数据给上 0 
		_str.resize(3,'0');
		_str[0] = '+';
		_str[1] = '0';
		_str[2]  =0 ;
		return  ;
	}
	char  *  str = (char*)s;
	//清楚 空格  还有   0 
	while(*str == '0'||*str == ' '){++str;}
	
	//symbol表示的是 符号 
	char  symbol  = '+';
	//当前的数是正数
	if(*str  == '+')
	{
		str++;
	}

	//表示的是当前的数是负数
	else if(*str == '-')
	{
		symbol = '-';
		++str;
	}
	while(*str == '0'||*str == ' '){++str;}
	//表示没有数
	if(*str == 0)
	{
		_str.resize(3,'0');
		_str[0] = '+';
		_str[1] = '0';
		_str[2]  =0 ;
		return  ;
	}
	if(*str  >= '0'&&*str <= '9')
	{}
	else
	{
		_str.resize(3,'0');
		_str[0] = '+';
		_str[1] = '0';
		_str[2]  =0 ;
		return  ;
	}

	//将数据读到_str中
	 int size = strlen(str);
	 //size +2  表示字符串 + '\0' +符号
	 _str.resize(size+2,'0');//赋值\0
	 _str[0] =symbol ;//给定符号
	 int idex = 1;
	 INT64 value =  0;
	 while(*str)
	 {
		 if(*str >= '0'&&*str <= '9')
		 {
			 _str[idex] = *str;
			idex++;
			str++;
		 }
		 else
		 {
			 break;
		 }
	 }
	 _str[idex] = 0;
	 //判断传进来的这个字符串，有没有越界
	 _IsOverFlow = IsOverFlow(_str.c_str());
	 //要是没有越界的话   _value 附上值
	 if(_IsOverFlow == false)
	 {
		 char  *  tmp =  (char*)_str.c_str();
		 int num = 1; 
		 if(*tmp == '-')
			 num =-1;
		 ++tmp;
		 while(*tmp)
		 {
			 _value = _value * 10 +*tmp -'0';
			 tmp++;
		 }
	 }
	 if(_str[0] == '-')
		 _value = -_value;
}
//构造函数 使用的是 数字 
//传进来的数字肯定不会越界
BigData::BigData(const INT64 value)
	:_str(string())
	,_value(value)
	,_IsOverFlow(false)
{
	//将数字转换成字符串
	int base = 10;
	int idex = 1;
	INT64 num = abs(value);
	//得到数字的长度   idex
	// 9   <  10  1
	// 10  >= 10  2
	// 100 >= 100 3
	while(num >= base)
	{
		idex++;
		base *= 10;
	}
	base /= 10;
	_str.resize(idex+2,'0');
	if(value > 0)
		_str[0] = '+';
	else
		_str[0] = '-';
	int tmp= 1;
	while(tmp <= idex)
	{
		INT64 data = num/base;
		_str[tmp++] = data+'0';
		num = num%base;
		base /=10;
	}
	_str[idex+1] = 0;
}
//是否越界
bool BigData::IsOverFlow(const  char  *str)
{
	int size1= strlen(str);
	int size2= strlen(MAXCHAR64);
	//要是没超过最长的值
	if(size1 < size2)
		return false;
	if(size1 == size2)
	{
		if(strcmp(str,MAXCHAR64) <= 0 && strcmp(str,MINCHAR64)>=0)
			return  false;
	}
	return  true;
	
	
}


//重载
bool BigData::operator>(const  BigData& data)
{
	char  *  str1  = (char *) _str.c_str();
	char  *  str2  = (char *)data._str.c_str();
	//两个的长度 
	int size1 =  strlen(str1);
	int size2 =  strlen(str2);
	//一个是正一个是负
	if(str1[0] == '+'&&str2[0] == '-')
		return true;
	//两个数都是正数
	if(str1[0] == '+'&&str2[0] == '+')
	{
		if(size1 > size2)
			return true;
		if(size1 == size2)
			return (strcmp(str1,str2) > 0)?true:false;
	}
	//两个数都是负数
	if(str1[0] == '-'&&str2[0] == '-')
	{
		if(size1 < size2)
			return true;
		if(size1 == size2)
			return (strcmp(str1,str2) < 0)?true:false;
	}
	return false;
}
bool BigData::operator<(const  BigData& data)
{
	if(operator>(data) == true)
		return false;
	if(operator==(data) == true)
		return  false;
	return  true;
}
bool BigData::operator==(const  BigData& data)
{
	char  *  str1  = (char *) _str.c_str();
	char  *  str2  = (char *)data._str.c_str();
	if(str1[0] != str2[0])
		return false;
	return  (strcmp(str1,str2) ==  0)?true:false;
}
bool BigData::operator!=(const  BigData& data)
{
	return  (operator==(data) == true)?false:true;
}

//假设传进来的size1>size2

string   StrSubStr(char *str1,char *str2)
{
	int size1 =strlen(str1);
	int size2 =strlen(str2);
	if(strcmp(str1,str2) == 0)
		return string();
	string  tmp;
	tmp.resize(size1+1,'0');

	char * ret  = (char*)tmp.c_str();
	char*  end = ret + size1;
	*end = 0;
	end--;
	char  *end1 = str1+size1-1;
	char  *end2 = str2+size2-1;
	char  borrow  = 0;//表示的是借位
	while(end1 >= str1&& end2>=str2)
	{
		int data  = *end1 -  *end2  - borrow;
		if(data >= 0 )
		{
			*end  =data+'0';
			borrow = 0;
		}
		else
		{
			*end = data+10+'0';
			borrow = 1;
		}
		end1--;
		end2--;
		end--;
	}
	while(end1 >= str1)
	{
		int data  = *end1 - borrow -'0';
		if(data >= 0 )
		{
			*end  =data+'0';
			borrow = 0;
		}
		else
		{
			*end = data+10+'0';
			borrow = 1;
		}
		end1--;
		end--;
	}
	if(borrow == 1)
		assert(false);
	end++;
	string  str(end);
	return str;
}

string   StrAddStr(char *str1,char *str2)
{
	int size1 =strlen(str1);
	int size2 =strlen(str2);
	string  tmp;
	tmp.resize(size1+2,'0');
	char * ret  = (char*)tmp.c_str();
	char*  end = ret + size1+1;
	*end = 0;
	end--;
	char  *end1 = str1+size1-1;
	char  *end2 = str2+size2-1;
	char  carry  = 0;//表示的是借位
	while(end1 >= str1&& end2 >=str2)
	{
		int data = (*end1 -'0')+(*end2 -'0')+carry;
		if(data >= 10)
		{
			*end  = data-10 +'0';
			carry = 1;
		}
		else
		{
			*end = data+'0';
			carry  = 0 ;
		}
		end--;
		end1--;
		end2--;
	}
	while(end1 >=str1)
	{
		int data = *end1 + carry -'0';
		if(data >= 10)
		{
			*end  = data-10 +'0';
			carry = 1;
		}
		else
		{
			*end = data+'0';
			carry  = 0 ;
		}
		end --;
		end1--;
	}
	if(carry == 1)
		*end = '1';
	else
		end++;
	string  str(end);
	return str;
}

string   StrMulStr(char *str1,char *str2)
{
	int size1  =strlen(str1);
	int size2  =strlen(str2);
	string str;
	str.resize(size1+size2+2,'0');
	//end表示的是 新建  字符串的尾
	char *end= (char*)str.c_str() + size1+size2+1;
	*(end--) = 0;
	char *end1 = str1 + size1-1;
	char *end2 = str2 + size2-1;
	int idex = 0;//表示的是 +上几个 0
	while(end2 >= str2)
	{
		char  *tmp  = end1;
		int  carry = 0 ;
		string ch ;
		ch.resize(size1+2+idex,'0');
		*((char * )ch.c_str()+size1+1+idex) = 0;//补上\0
		char * it = (char * )ch.c_str() + size1;
		while(1)
		{
			int data = (*tmp - '0')*(*end2 -'0')+carry;
			carry = data/10;
			*it = data%10 +'0';
			if(tmp == str1)
			{
				if(carry != 0)
				{
					*(--it) = carry+'0';
					break;
				}
				else
				{
					break;
				}
			}
			else
			{
				--it;
			}
			tmp--;
		}
		//得到每次成一位的得到的
		char  * res =(char*)str.c_str(); 
		string  tmp1 =  StrAddStr(res,it);
		memcpy(end-strlen(tmp1.c_str())+1,tmp1.c_str(),strlen(tmp1.c_str()));
		end2--;
		++idex;
	}
	return str; 
}

string   StrDivStr(char *str1,char *str2)
{
	int size1 = strlen(str1);
	int size2 = strlen(str2);
	if(size1 <size2)
	{
		return string("0");
	}
	if(strcmp(str1,str2) == 0)
	{
		return string("1");
	}
	string  ret;//用来保存每次的结果
	string  str(str1,str1+size2);//保存的是每次被除数 
	int idex = size2;//表示的是当前的被除数到了第几位
	//str2表示的是除数
	//str1表示的是被除数
	//str表示的是每次的被除数
	//ret表示每次除后得到的结果
	while(idex <= size1)
	{
		if(strcmp(str.c_str(),str2)== 0)
		{
			ret.push_back('1');
			str.clear();
			if(idex == size1)
			{
				break;
			}
			str.push_back(str1[idex]);
			++idex;
			
		}
		else if((strlen(str.c_str()) == strlen(str2)&&strcmp(str.c_str(),str2) > 0)
			||(strlen(str.c_str()) > strlen(str2)))
		{
			char  tmp[]  = "1";
			string remainder;//表示每次除下来的  余数
			while(1)
			{   
				string  x= StrMulStr(str2,tmp);
				char  * dest = (char*)(x.c_str());
				while(*dest == '0'){++dest;}
				if((strlen(dest)==strlen(str1)&&strcmp(dest,str1) > 0)
					||strlen(dest) >strlen(str1))
				{
					tmp[0]--;
					remainder = StrSubStr((char*)str.c_str(),(char*)StrMulStr(str2,tmp).c_str());
					break;
				}
				else if((strlen(dest)==strlen(str1)&&strcmp(dest,str1)==0))
				{
					break;
				}
				else
				{
					tmp[0]++;
				}
			}
			ret.push_back(tmp[0]);
			str = string(remainder.begin(),remainder.end());
			if(idex == size1)
			{
				break;
			}
			str.push_back(str1[idex]);
			
			++idex;	
		}
		else
		{
			ret.push_back('0');
			if(idex == size1)
			{
				break;
			}
			str.push_back(str1[idex]);
			++idex;	
		}
	}
	return ret;
}

string   StrRemStr(char *str1,char *str2)
{
	int size1 = strlen(str1);
	int size2 = strlen(str2);
	if(size1 <size2)
	{
		return string(str1);
	}
	if(strcmp(str1,str2) == 0)
	{
		return string();
	}
	else
	{
		string  Div = StrDivStr(str1,str2);
		string  Mul = StrMulStr(str2,(char*)Div.c_str());
		return  StrSubStr(str1,(char*)Mul.c_str());
	}
}


BigData BigData::operator+(const BigData& data)
{
	//要是有一个数 0 
	if(_IsOverFlow == false&&_value == 0)
	{
		return data;
	}
	if(data._IsOverFlow == false&&data._value == 0)
	{
		return *this;
	}
	//两个数都没有越界
	if(_IsOverFlow == false&&data._IsOverFlow == false)
	{
		//两个数  正负号相反
		if((_str[0] == '+'&&data._str[0] == '-')
			||(_str[0] == '-'&&data._str[0] == '+'))
			return BigData(_value + data._value);
		//两个数都是正数 ，，，加起来的和是 也没有越界
		if((_str[0] == '+'&&data._str[0] == '+')
			&& MAXINT64 -  _value >= data._value)
			return BigData(_value + data._value);
		//两个数都是负数，加起来的和没有越界
		if((_str[0] == '-'&&data._str[0] == '-')
			&&MININT64 - _value <= data._value)
			return BigData(_value + data._value);
	}
	//剩下的肯定都是越界的处理 

	//字符串的相加 
	//要是两个数 不同号
	char  *  str1  = (char *) _str.c_str();
	char  *  str2  = (char *)data._str.c_str();

	//保证str1 的长度 大于是str2
	if(strlen(str1) <strlen(str2))
	{
		swap(str1,str2);
	}
	else if(strlen(str1) == strlen(str2))
	{
		if(strcmp(str1+1,str2+1) < 0)
			swap(str1,str2);
	}

	//两个数异号   结果符号 为大的数的 符号  也就是是str1
	if((str1[0] == '+'&&str2[0] == '-')
		||(str1[0] == '-'&&str2[0]=='+'))
	{
		string  ret = StrSubStr(str1+1,str2+1);
		char  *str= (char *)ret.c_str();
		char  *tmp = new char[2+strlen(str)];
		tmp[0]= str1[0];
		memcpy(&tmp[1],str,strlen(str)+1);
		BigData value(tmp);
		delete[] tmp;
		return value;
	}
	//两个数同号
	else
	{
		string  ret = StrAddStr(str1+1,str2+1);
		char  *str= (char *)ret.c_str();
		char  *tmp = new char[2+strlen(str)];
		tmp[0]= str1[0];
		memcpy(&tmp[1],str,strlen(str)+1);
		BigData value(tmp);
		delete[] tmp;
		return value;
	}
}

BigData BigData::operator-(const  BigData& data)
{
	//要是有一个数 0 
	if(_IsOverFlow == false&&_value == 0)
	{
		return BigData(-data._value);
	}
	if(data._IsOverFlow == false&&data._value == 0)
	{
		return *this;
	}
	//两个数都没有越界 
	if(_IsOverFlow == false&&data._IsOverFlow == false)
	{
		//减了之后也没有越界
		//两个数同号
		if((_str[0] == '+'&&data._str[0] == '+')
			||(_str[0] == '-'&&data._str[0] == '-'))
		{
			return BigData(_value - data._value);
		}
		// +  - 
		if((_str[0] == '+'&&data._str[0] == '-')
			&&MAXINT64 + data._value >= _value)
		{
			return BigData(_value - data._value);
		}
		//- +
		if((_str[0] == '-'&&data._str[0] == '+')
			&&MININT64 + data._value <= _value)
		{
			return BigData(_value - data._value);
		}
	}

	//表示的是两个数 本身越界，，，或者是减了之后越界
	int symbol = 0;
	char  *  str1  = (char *) _str.c_str();
	char  *  str2  = (char *)data._str.c_str();
	if(strlen(str1) <strlen(str2))
	{
		swap(str1,str2);
		symbol = 1;
	}
	//两个要是相等
	else if(strlen(str1) == strlen(str2))
	{
		if(strcmp(str1+1,str2+1) < 0)
		{
			swap(str1,str2);
			symbol = 1;
		}
	}

	//两个同号
	if((str1[0] == '+'&&str2[0] == '+')
		||(str1[0] == '-'&&str2[0]=='-'))
	{
		string  ret = StrSubStr(str1+1,str2+1);
		char  *str= (char *)ret.c_str();
		char  *tmp = new char[2+strlen(str)];
		if(symbol == 1)
		{
			tmp[0]= '-';
		}
		else
		{
			tmp[0] = '+';
		}
		
		memcpy(&tmp[1],str,strlen(str)+1);
		BigData value(tmp);
		delete[] tmp;
		return value;
	}	
	//两个不同号 
	else
	{
		string  ret = StrAddStr(str1+1,str2+1);
		char  *str= (char *)ret.c_str();
		char  *tmp = new char[2+strlen(str)];
		if(symbol ==1)
		{
			tmp[0] = str2[0];
		}
		else
		{
			tmp[0]= str1[0];
		}
		memcpy(&tmp[1],str,strlen(str)+1);
		BigData value(tmp);
		delete[] tmp;
		return value;
	}


	
}

BigData BigData::operator*(const  BigData& data)
{
	//有一个数 0
	if(_IsOverFlow ==false&&_value == 0)
		return BigData();
	if(data._IsOverFlow == false&&data._value == 0)
		return BigData();
	char  *  str1 = (char *)_str.c_str();
	char  *  str2 = (char *)data._str.c_str();
	//当两个数没有越界的话，，，且相乘之后也没有yuejie
	if(_IsOverFlow == false&&data._IsOverFlow == false)
	{
		if((strlen(str1)+strlen(str2))  < strlen(MAXCHAR64))
			return BigData(_value *data._value);
	}
	//保证str1长度大于是str2
	if(strlen(str1) < strlen(str2))
	{
		swap(str1,str2);
	}
	//当两个数是同号，结果肯定是+
	if((str1[0] == '+'&&str2[0] == '+')
		||(str1[0]=='-'&&str2[0] =='-'))
	{
		string  ret = StrSubStr(str1+1,str2+1);
		return BigData(ret.c_str());
	}
	//两个数是 异号的，，，结果是 -
	else
	{
		string  ret = StrAddStr(str1+1,str2+1);
		char  *str= (char *)ret.c_str();
		char  *tmp = new char[2+strlen(str)];
		tmp[0] = '-';
		memcpy(&tmp[1],str,strlen(str)+1);
		BigData value(tmp);
		delete[] tmp;
		return value;
	}
}

BigData BigData::operator/(const  BigData& data)
{
	if(data._IsOverFlow == false &&data._value == 0)
	{
		throw invalid_argument("除数不能为 0\n");
	}
	if(_IsOverFlow == false&&_value == 0)
		return  BigData();
	if(_IsOverFlow == false&&data._IsOverFlow == false)
		return BigData(_value/data._value);
	
	char  *str1 = (char * )_str.c_str();
	char  *str2 = (char * )data._str.c_str();
	if((str1[0] == '+'&&str2[0] == '+')
		||(str1[0] == '-'&&str2[0] == '-'))
	{
		return BigData(StrDivStr(str1,str2).c_str());
	}
	else
	{
		string  ret = StrDivStr(str1+1,str2+1);
		char  *str= (char *)ret.c_str();
		char  *tmp = new char[2+strlen(str)];
		tmp[0] = '-';
		memcpy(&tmp[1],str,strlen(str)+1);
		BigData value(tmp);
		delete[] tmp;
		return value;
	}
}

BigData BigData::operator%(const  BigData& data)
{
	if(data._IsOverFlow == false &&data._value == 0)
	{
		throw invalid_argument("除数不能为 0\n");
	}
	if(_IsOverFlow == false&&_value == 0)
		return  BigData();
	if(_IsOverFlow == false&&data._IsOverFlow == false)
		return BigData(_value%data._value);

	char  *str1 = (char * )_str.c_str();
	char  *str2 = (char * )data._str.c_str();
	if(str1[0] == '+')
	{
		return BigData(StrRemStr(str1,str2).c_str());
	}
	else
	{
		string  ret = StrRemStr(str1+1,str2+1);
		char  *str= (char *)ret.c_str();
		char  *tmp = new char[2+strlen(str)];
		tmp[0] = '-';
		memcpy(&tmp[1],str,strlen(str)+1);
		BigData value(tmp);
		delete[] tmp;
		return value;
	}
}




void TestBigData()
{
	BigData data("+1234");
	BigData data1;

	BigData data2("-456");
	BigData  data3(1);
	data1 = data%data2;


	string  str = StrRemStr("1234","456");

	
}
