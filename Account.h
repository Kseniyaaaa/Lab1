#pragma once

#include <string>

using namespace std;

class Account
{
public:
	string password;
	long long hash_password;
	string salt;
	string login;
	int access;
	int role;
};

