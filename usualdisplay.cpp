#include<iostream>
using namespace std;
void init()
{
	cout << "======================================================" << endl;
	cout << "1.����Ա��¼ 2.�û�ע�� 3.�û���¼ 4.�˳����� 5.������" << endl;
	cout << "======================================================" << endl;
	cout << endl;
	cout << "���������";
};
char yourchoice()
{
	cout << "���������";
	char choice;
	cin >> choice;
	return choice;
}
void errorwa()
{
	cout << endl;
	cout << "----�Ƿ����������������룡----";
	cout << endl;
	cout << endl;
}
void sellsuccess()
{
	cout << endl;
	cout << "������Ʒ�ɹ�!";
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
