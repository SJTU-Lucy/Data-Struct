#include<iostream>
using namespace std;

class LongLongInt
{
	friend LongLongInt operator+(const LongLongInt&, const LongLongInt&);                //重载加法
	friend ostream &operator<<(ostream&, const LongLongInt&);                            //重载输出函数
	friend LongLongInt operator-(const LongLongInt&, const LongLongInt&);                //重载减法
private:
	char sign;                                                                           //表示数字符号
	char* num;                                                                           //表示数字数组
public:
	LongLongInt(const char* n = "");                                                     //默认构造函数
	LongLongInt(const LongLongInt&);                                                     //拷贝构造函数
	LongLongInt& operator=(const LongLongInt&);                                          //重载等于
	~LongLongInt()                                                                       //析构函数
	{
		delete num;
	}
};

char* add(const char* s1, const char* s2);                                                //绝对值的加法函数
char* sub(const char* s1, const char* s2);                                                //绝对值的减法函数
bool compare(const char* s1, const char* s2);                                             //比较两数大小的函数

bool compare(const char* s1, const char* s2)                                              //比较绝对值函数的定义
{ 
	int len1 = strlen(s1), len2 = strlen(s2);                                             //保存两数的位数

	if (len1 > len2) return true;                                                     
	else if (len1 < len2) return false;

	for (int i = len1 - 1; i >= 0; --i)                                                   //从高位向低位依次比较
	{
		if (s1[i] > s2[i]) return true;
		else if (s1[i] < s2[i]) return false; 
	}

	return false;
}

LongLongInt::LongLongInt(const char* n)                                                   //构造函数的实现
{
	const char* tmp;                                                                      //保留参数的绝对值
	switch (n[0])
	{
	case '+': sign = '+'; tmp = n + 1; break;                                             //这里的+1将字符串的符号略去
	case '-': sign = '-'; tmp = n + 1; break;
	default: sign = '+'; tmp = n;
	}

	if (strcmp(tmp, "0") == 0) tmp = "";
	int len = strlen(tmp);

	num = new char[len + 1];
	for (int i = 0; i < len; ++i) num[len - i - 1] = tmp[i];
	num[len] = '\0';
}

LongLongInt::LongLongInt(const LongLongInt& other)                                         //拷贝构造函数的实现
{
	sign = other.sign;
	num = new char[strlen(other.num) + 1];
	strcpy(num, other.num);
}

LongLongInt& LongLongInt::operator=(const LongLongInt& right)                              //等于号的重载
{
	if (this == &right) return *this;

	delete num;
	sign = right.sign;
	num = new char[strlen(right.num) + 1];
	strcpy(num, right.num);
	return *this;
}

ostream& operator<<(ostream& os, const LongLongInt& obj)                                  //输出函数的重载
{
	if (strlen(obj.num) == 0) os << 0;
	else
	{
		os << obj.sign;
		for (int i = strlen(obj.num) - 1; i >= 0; --i)
			os << obj.num[i];
		return os;
	}
}

LongLongInt operator+(const LongLongInt& n1, const LongLongInt& n2)                       //重载加号
{
	LongLongInt n;
	delete n.num;
	if (n1.sign == n2.sign)
	{
		n.sign = n1.sign;
		n.num = add(n1.num, n2.num);
	}
	else if (compare(n1.num,n2.num))
	{
		n.sign = n1.sign;
		n.num = sub(n1.num,n2.num);
	}
	else 
	{
		n.sign = n2.sign;
		n.num = sub(n2.num, n1.num);
	}

	return n;
}


LongLongInt operator-(const LongLongInt& n1, const LongLongInt& n2)                      //重载减号
{
	LongLongInt n(n2);
	if (n.sign == '+') n.sign = '-';
	else n.sign = '+';

	return n1 + n;
}

char* add(const char* s1, const char* s2)
{
	int len1 = strlen(s1);
	int len2 = strlen(s2);
	int minLen = (len1 > len2 ? len2 : len1) + 1;
	int len = (len1 > len2 ? len1 : len2) + 1;
	int carry = 0, result, i;                                                             //carry表示需要进位

	char* num = new char[len + 1];

	for (i = 0; i < minLen; i++)
	{
		int num1 = s1[i] - '0';
		int num2 = s2[i] - '0';
		result = num1 + num2 + carry;
		num[i] = result % 10 + '0';
		carry = result % 10;
	}

	while(i<len1)
	{
		result = s1[i] - '0' + carry;
		num[i] = result % 10 + '0';
		carry = result % 10;
		++i;
	}

	while (i < len2)
	{
		result = s2[i] - '0' + carry;
		num[i] = result % 10 + '0';
		carry = result % 10;
		++i;
	}

	if (carry != 0) num[i++] = carry + '0';
	num[i] = '\0';

	return num;
}

char* sub(const char* s1, const char* s2)
{
	int len1 = strlen(s1);
	int len2 = strlen(s2);
	int minus = 0;
	char* tmp = new char[len1 + 1];
	int i;

	for (i = 0; i < len2; ++i)
	{
		tmp[i] = s1[i] - s2[i] - minus;
		if (tmp[i] < 0)
		{
			tmp[i] += 10;
			minus = 1;
		}
		else minus = 0;
		tmp[i] += '0';
	}

	while (i < len1)
	{
		tmp[i] = s1[i] - '0' - minus;
		if (tmp[i] < 0)
		{
			tmp[i] += 10;
			minus = 1;
		}
		else minus = 0;
		tmp[i] += '0';
		++i;
	}

	do 
	{
		--i;
	} while (i >= 0 && tmp[i] == 0);

	tmp[i + 1] = '\0';
	return tmp;
}