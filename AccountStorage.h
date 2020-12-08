#pragma once

#include <vector>
#include <string>
#include "Account.h"

using namespace std;

class AccountStorage
{
private:
	vector<Account>* accounts;

	vector<Account>* readAccountsFile();
	void writeAccountFile();

	void writeToEndAccountFile(Account account);

public:
	AccountStorage();

	Account* getAccount(string login);
	Account* createFirstAdmin();

	string getSalt();
	long long int hashPassword(string password, string salt);

	void addAccount(string login, string password, int role, int access);
	void addAccount(Account* account);
	void editAccount(Account* accountToEdit, Account* editedAccount);
	void deleteAccount(string login);
	vector<Account>* getAccounts();
};