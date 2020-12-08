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
		if (isNumberNumeric())
		{
			break;
		}
		else
		{
			cout << "Некорректный ввод данных!" << endl;
			cout << "Введите числовые данные" << endl;
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
		ch = _getwch();                                                                 // считывание нажатия клавиши

		if (ch == 13)                                                                  // код Enter
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


//string getSalt() 
//{
//	srand(time(NULL));
//	string alphabet = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
//	string salt = "";
//	for (int i = 0; i < SALT_LENGTH; ++i) {
//		salt += alphabet[rand() % (sizeof(alphabet) - 1)];
//	}
//
//	return salt;
//}
//
//
//long long int hashPassword(string password, string salt)
//{
//	string password_with_salt = password + salt;
//	const int p = 33;
//	long long hash = 0, p_pow = 1;
//	for (int i = 0; i < password_with_salt.length(); ++i)
//	{
//		hash = (hash + ((int)password_with_salt.at(i) - (int)'a' + 1) * p_pow) % LONG_MAX;
//		p_pow *= p;
//	}
//
//	return hash;
//}


int getCurrentYear()
{
	struct tm localtime;
	time_t now = time(NULL);
	localtime_s(&localtime, &now);

	return 1900 + localtime.tm_year;
}