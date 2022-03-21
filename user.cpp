#include "user.h"
#include "main.h"
extern stack<char> opt;
extern stack<float> val;
User::User(User* users)
{
	
	while (true)
	{
		cout << "请设置您的用户名：";
		char name1[101];
		cin >> name1;
		bool flag = false;
		for (int i=0;i<UID;i++)
		{
			if (strcmp(users[i].name, name1) == 0)
			{
				cout << "******该用户名已被占用！请重试！******"<<endl;
				flag = true;
			}
		}
		if (flag == false)
		{
			strncpy(name, name1, 10);
			name[10] = '\0';
			break;
		}
	}
	exist = true;
	cout << "请设置您的密码:";
	char secret1[101];
	cin>>secret1; 
	strncpy(secret, secret1, 20);
	secret[20] = '\0';
	cout << "请设置您的联系方式：";
	char phone1[101];
	cin>>phone1;
	strncpy(phone, phone1, 20);
	phone[20] = '\0';
	cout << "请设置您的收获地址：";
	char address1[101];
	cin>>address1;
	strncpy(address, address1, 40);
	address[40] = '\0';
	cout << "您要充值的初始数额：";
	while (true)
	{
		char mon[101];
		cin >> mon;
		if (isFloat(mon))
		{
			float the_mon;
			sscanf(mon, "%f", &the_mon);
			if (the_mon <= 1000000)
			{
				money = the_mon;
				break;
			}
			else {
			}
		}
		cout << "******这是一个不合适的金额，请重新输入！******" << endl;
		cout << "请输入金额：";
	}
	for (int i = 3; i >= 1; i--)
	{
		int num = UID;
		for (int j = 1; j < 4 - i; j++)
		{
			num = num / 10;
		}
		uid[i] = '0' + num % 10;
	}
	uid[4] = '\0';
	UID++;
	cout << endl;
	cout << "******注册成功！******" << endl;
	cout << endl;
}
User User::userload(User* users)
{
	char your_name[101];
	char your_secret[101];
	cout << "请输入用户名：";
	cin>>your_name;
	cout << "请输入密码：";
	cin>>your_secret;
	bool flag = false;
	int i = 0;
	for (; i < UID; i++)
	{
		if (strcmp(your_name, users[i].name) == 0 && strcmp(your_secret, users[i].secret) == 0&&users[i].exist)
		{
			flag = true;
		}
		if (flag == true)
		{
			break;
		}
	}
	if (flag)
	{
		cout << "******登陆成功！******" << endl;
		cout << endl;
		cout << endl;
		return users[i];
	}
	else
	{
		cout << "******登陆失败！即将返回主菜单******"<<endl;
		cout << endl;
		cout << endl;
		return users[100];
	}
}
void User::usermenu()
{
	cout << "===============================================" << endl;
	cout << "1.我是买家 2.我是卖家 3.个人信息管理 4.注销登录" << endl;
	cout << "===============================================" << endl;
	cout << endl;
	cout << endl;
	cout << "请输入选择：";
}
void User::usermessagemenu()
{
	cout << "===========================================" << endl;
	cout << "1.返回用户界面 2.修改信息 3.查看信息 4.充值" << endl;
	cout << "===========================================" << endl;
	cout << endl;
	cout << endl;
	cout << "请输入选择：";
}
void User::recharge(User* users)
{
		cout << "请输入您想要充值的金额：";
		while (true)
		{
			char mon[101];
			cin >> mon;
			if (isFloat(mon))
			{
				float the_mon;
				sscanf(mon, "%f", &the_mon);
				if (the_mon <= 1000000)
				{
					money+= the_mon;
					break;
				}
				else {
				}
			}
			cout << "******这是一个不合适的金额，请重新输入！******" << endl;
			cout << "请输入金额：";
		}
		int i = uid[3] - '0' + (uid[2] - '0') * 10;
		users[i] = *this;
		cout << "******充值成功！您的余额为：" <<setiosflags(ios::fixed) << setprecision(1) << money << "元******";
		cout << endl;
		cout << endl;
}
void User::self_message()
{
		cout << "****************************" << endl;
		cout << "用户名：" << name << endl;
		cout << "联系方式：" << phone << endl;
		cout << "地址：" << address << endl;
		string test;
		char res[20];
		sprintf(res, "%f", money);
		for (int i = 0; i < strlen(res); i++)
		{
			if (res[i] == '.')
			{
				if (res[i + 1] == '0')
				{
					res[i] = '\0';
					break;
				}
				res[i + 2] = '\0';
				break;
			}
		}
		test += res;
		test += '+';
		test += '(';
		test += res;
		test += '+';
		test += res;
		test += ')';
		test += "- 2 *";
		test += res;
		string a=calculator(test);
		cout << "钱包余额：" << setiosflags(ios::fixed) << setprecision(1) << money << endl;
		cout << "用户ID：" << uid<< endl;
		cout << "****************************" << endl;
		cout << endl;
		cout << endl;
}
void User::changemessage(User* users)
{
	while (true)
	{
		cout << "请选择修改的属性(1.用户名 2.联系方式 3.地址)：";
		char a[101];
		cin >> a;
		if (strcmp(a, "1") == 0)
		{
			cout << "请输入修改后的用户名：";
			char new_name[101];
			cin>>new_name;
			bool flag = true;
			for (int i = 0; i < UID; i++)
			{
				if (strcmp(uid, users[i].uid) != 0 && strcmp(new_name, users[i].name) == 0)
				{
					flag = false;
				}
			}
			if (flag == true)
			{
				strncpy(name, new_name,10);
				cout << "******修改成功！******" << endl;
				cout << endl;
				cout << endl;
				int i = uid[3] - '0' + (uid[2] - '0') * 10;
				users[i] = *this;
			}
			else
			{
				cout << "******该用户名已存在！******" << endl;
				cout << endl;
				cout << endl;
			}
			break;
		}
		else if (strcmp(a, "2") == 0)
		{
			char new_phone[101];
			cout << "请输入修改后的联系方式：";
			cin >> new_phone;
			strncpy(phone, new_phone,20);
			cout << "******修改成功！******" << endl;
			int i = uid[3]-'0' +( uid[2] - '0')*10;
			users[i] = *this;
			cout << endl;
			cout << endl;
			break;
		}
		else if (strcmp(a, "3") == 0)
		{
			char new_address[101];
			cout << "请输入修改后的地址：";
			cin>>new_address;
			strncpy(address, new_address,40);
			cout << "******修改成功！******" << endl;
			int i = uid[3] - '0' + (uid[2] - '0') * 10;;
			users[i] = *this;
			cout << endl;
			cout << endl;
			break;
		}
		else
		{
			cout << "******没有这一属性！请重新选择！******" << endl;
			cout << endl;
			cout << endl;
		}
	}
}
void User::extrasjk(Deal* deals, Good* goods, User* users)
{
	//you don't need do anything
}