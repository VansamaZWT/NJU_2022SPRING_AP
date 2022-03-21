#include "user.h"
#include "main.h"
extern stack<char> opt;
extern stack<float> val;
User::User(User* users)
{
	
	while (true)
	{
		cout << "�����������û�����";
		char name1[101];
		cin >> name1;
		bool flag = false;
		for (int i=0;i<UID;i++)
		{
			if (strcmp(users[i].name, name1) == 0)
			{
				cout << "******���û����ѱ�ռ�ã������ԣ�******"<<endl;
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
	cout << "��������������:";
	char secret1[101];
	cin>>secret1; 
	strncpy(secret, secret1, 20);
	secret[20] = '\0';
	cout << "������������ϵ��ʽ��";
	char phone1[101];
	cin>>phone1;
	strncpy(phone, phone1, 20);
	phone[20] = '\0';
	cout << "�����������ջ��ַ��";
	char address1[101];
	cin>>address1;
	strncpy(address, address1, 40);
	address[40] = '\0';
	cout << "��Ҫ��ֵ�ĳ�ʼ���";
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
		cout << "******����һ�������ʵĽ����������룡******" << endl;
		cout << "�������";
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
	cout << "******ע��ɹ���******" << endl;
	cout << endl;
}
User User::userload(User* users)
{
	char your_name[101];
	char your_secret[101];
	cout << "�������û�����";
	cin>>your_name;
	cout << "���������룺";
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
		cout << "******��½�ɹ���******" << endl;
		cout << endl;
		cout << endl;
		return users[i];
	}
	else
	{
		cout << "******��½ʧ�ܣ������������˵�******"<<endl;
		cout << endl;
		cout << endl;
		return users[100];
	}
}
void User::usermenu()
{
	cout << "===============================================" << endl;
	cout << "1.������� 2.�������� 3.������Ϣ���� 4.ע����¼" << endl;
	cout << "===============================================" << endl;
	cout << endl;
	cout << endl;
	cout << "������ѡ��";
}
void User::usermessagemenu()
{
	cout << "===========================================" << endl;
	cout << "1.�����û����� 2.�޸���Ϣ 3.�鿴��Ϣ 4.��ֵ" << endl;
	cout << "===========================================" << endl;
	cout << endl;
	cout << endl;
	cout << "������ѡ��";
}
void User::recharge(User* users)
{
		cout << "����������Ҫ��ֵ�Ľ�";
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
			cout << "******����һ�������ʵĽ����������룡******" << endl;
			cout << "�������";
		}
		int i = uid[3] - '0' + (uid[2] - '0') * 10;
		users[i] = *this;
		cout << "******��ֵ�ɹ����������Ϊ��" <<setiosflags(ios::fixed) << setprecision(1) << money << "Ԫ******";
		cout << endl;
		cout << endl;
}
void User::self_message()
{
		cout << "****************************" << endl;
		cout << "�û�����" << name << endl;
		cout << "��ϵ��ʽ��" << phone << endl;
		cout << "��ַ��" << address << endl;
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
		cout << "Ǯ����" << setiosflags(ios::fixed) << setprecision(1) << money << endl;
		cout << "�û�ID��" << uid<< endl;
		cout << "****************************" << endl;
		cout << endl;
		cout << endl;
}
void User::changemessage(User* users)
{
	while (true)
	{
		cout << "��ѡ���޸ĵ�����(1.�û��� 2.��ϵ��ʽ 3.��ַ)��";
		char a[101];
		cin >> a;
		if (strcmp(a, "1") == 0)
		{
			cout << "�������޸ĺ���û�����";
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
				cout << "******�޸ĳɹ���******" << endl;
				cout << endl;
				cout << endl;
				int i = uid[3] - '0' + (uid[2] - '0') * 10;
				users[i] = *this;
			}
			else
			{
				cout << "******���û����Ѵ��ڣ�******" << endl;
				cout << endl;
				cout << endl;
			}
			break;
		}
		else if (strcmp(a, "2") == 0)
		{
			char new_phone[101];
			cout << "�������޸ĺ����ϵ��ʽ��";
			cin >> new_phone;
			strncpy(phone, new_phone,20);
			cout << "******�޸ĳɹ���******" << endl;
			int i = uid[3]-'0' +( uid[2] - '0')*10;
			users[i] = *this;
			cout << endl;
			cout << endl;
			break;
		}
		else if (strcmp(a, "3") == 0)
		{
			char new_address[101];
			cout << "�������޸ĺ�ĵ�ַ��";
			cin>>new_address;
			strncpy(address, new_address,40);
			cout << "******�޸ĳɹ���******" << endl;
			int i = uid[3] - '0' + (uid[2] - '0') * 10;;
			users[i] = *this;
			cout << endl;
			cout << endl;
			break;
		}
		else
		{
			cout << "******û����һ���ԣ�������ѡ��******" << endl;
			cout << endl;
			cout << endl;
		}
	}
}
void User::extrasjk(Deal* deals, Good* goods, User* users)
{
	//you don't need do anything
}