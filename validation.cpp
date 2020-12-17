#include "validation.h"

#include <iostream>
#include <time.h>

using namespace std;

const int SALT_LENGTH = 7;

bool isNumberNumeric()
{
	if (cin.get() == '\n') return true;
	else
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		return false;
	}
}

double getNumber()
{
	int item;
	while (true)
	{
		cin >> item;
		if (isNumberNumeric() && item >= 0)
		{
			break;
		}
		else if (item < 0) {
			cout << "������� ������������� �����: ";
		}
		else
		{
			cout << "������������ ���� ������!" << endl;
			cout << "������� �������� ������: ";
		}
	}
	return item;
}


string transformPassword()
{
	string password;
	int ch = 0;
	while (true)
	{
		ch = _getwch();                                                                 // ���������� ������� �������

		if (ch == 13)                                                                  // ��� Enter
		{
			break;
		}
		else {
			if (ch == 8)
			{
				if (!password.empty()) {
					cout << (char)8 << ' ' << (char)8;
					password.erase(password.length() - 1);
				}
			}
			else
			{
				cout << "*";
				password += (char)ch;
			}
		}
	}
	cout << endl;
	return password;
}


int getCurrentYear()
{
	struct tm localtime;
	time_t now = time(NULL);
	localtime_s(&localtime, &now);

	return 1900 + localtime.tm_year;
}