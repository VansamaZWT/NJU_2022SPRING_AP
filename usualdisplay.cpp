#include<iostream>
using namespace std;
void init()
{
	cout << "======================================================" << endl;
	cout << "1.管理员登录 2.用户注册 3.用户登录 4.退出程序 5.计算器" << endl;
	cout << "======================================================" << endl;
	cout << endl;
	cout << "输入操作：";
};
char yourchoice()
{
	cout << "输入操作：";
	char choice;
	cin >> choice;
	return choice;
}
void errorwa()
{
	cout << endl;
	cout << "----非法操作，请重新输入！----";
	cout << endl;
	cout << endl;
}
void sellsuccess()
{
	cout << endl;
	cout << "发布商品成功!";
	cout << endl;
	cout << endl;
}
bool isFloat(const char* str)
{
	bool isE = false,
		isPoint = false,
		numBefore = false,
		numBehind = false;

	int index = 0;
	for (; *str != '\0'; str++, index++)
	{
		switch (*str)
		{
		case '0':case'1':case'2':case'3':case'4':case'5':
		case'6':case'7':case'8':case'9':
			if (isE)
			{
				numBehind = true;
			}
			else
			{
				numBefore = true;
			}
			break;
		case '+':case '-':
			if (index != 0)
			{
				return false;
			}
			break;
		case 'e':case 'E':
			if (isE || !numBefore)
			{
				return false;
			}
			else
			{
				isPoint = true;
				index = -1;
				isE = true;
			}
			break;
		case '.':
			if (isPoint)
			{
				return false;
			}
			else
			{
				isPoint = true;
			}
			break;
		default:
			return false;
		}
	}

	if (!numBefore)
	{
		return false;
	}
	else if (isE && !numBehind)
	{
		return false;
	}

	return true;
}bool isInt(const char* str)
{
	bool isNum = false;

	int index = 0;
	for (; *str != '\0'; str++, index++)
	{
		switch (*str)
		{
		case '0':case'1':case'2':case'3':case'4':case'5':
		case'6':case'7':case'8':case'9':
			isNum = true;
			break;
		case '-':case '+':
			if (index != 0)
			{
				return false;
			}
			break;
		default:
			return false;
		}
	}

	if (!isNum)
	{
		return false;
	}

	return true;
}
