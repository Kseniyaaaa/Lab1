#include "AccountStorage.h"
#include "Account.h"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <time.h>

const string FILE_OF_ACCOUNTS = "accounts.txt";
const int SALT_LENGTH = 7;

AccountStorage::AccountStorage()
{
	this->accounts = this->readAccountsFile();
}


vector<Account>* AccountStorage::readAccountsFile()
{
	vector<Account>* accounts = new vector<Account>();

	ifstream fin(FILE_OF_ACCOUNTS, ios::in);
	if (!fin.is_open()) {
		Account* account = this->createFirstAdmin();
		ofstream fout(FILE_OF_ACCOUNTS, ios::out);
		fout << account->login << " "
			<< account->hash_password << " "
			<< account->salt << " "
			<< account->role << " "
			<< account->access << endl;
		fout.close();
		accounts->push_back(*account);
	}

	else
	{
		while (!fin.eof())
		{
			Account* account = new Account;
			fin >> account->login
				>> account->hash_password
				>> account->salt
				>> account->role
				>> account->access;
			accounts->push_back(*account);
		}
	}
	fin.close();
	return accounts;
}


void AccountStorage::writeAccountFile()
{
	ofstream fout(FILE_OF_ACCOUNTS, ios::out);
	for (int i = 0; i < accounts->size(); i++)
	{
		fout << accounts->at(i).login << " "
			<< accounts->at(i).hash_password << " "
			<< accounts->at(i).salt << " "
			<< accounts->at(i).role << " "
			<< accounts->at(i).access << endl;
		if (i < accounts->size() - 1)
		{
			fout << endl;
		}
	}
	fout.close();
}


void AccountStorage::writeToEndAccountFile(Account account)
{
	ofstream fadd(FILE_OF_ACCOUNTS, ios::app);
	fadd << endl;
	fadd << account.login << " "
		<< account.hash_password << " "
		<< account.salt << " "
		<< account.role << " "
		<< account.access;
	fadd.close();
}


Account* AccountStorage::getAccount(string login)
{
	for (int i = 0; i < accounts->size(); i++)
	{
		if (accounts->at(i).login == login) {
			return &accounts->at(i);
		}
	}
	return NULL;
}


Account* AccountStorage::createFirstAdmin()
{
	Account* account = new Account;
	account->login = "admin";
	account->salt = getSalt();
	account->hash_password = hashPassword("admin", account->salt);
	account->role = 1;
	account->access = 1;

	return account;
}


string AccountStorage::getSalt()
{
	srand(time(NULL));
	string alphabet = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	string salt = "";
	for (int i = 0; i < SALT_LENGTH; ++i) {
		salt += alphabet[rand() % (sizeof(alphabet) - 1)];
	}

	return salt;
}


long long int AccountStorage::hashPassword(string password, string salt)
{
	string password_with_salt = password + salt;
	const int p = 33;
	long long hash = 0, p_pow = 1;
	for (int i = 0; i < password_with_salt.length(); ++i)
	{
		hash = (hash + ((int)password_with_salt.at(i) - (int)'a' + 1) * p_pow) % LONG_MAX;
		p_pow *= p;
	}

	return hash;
}


void AccountStorage::addAccount(string login, string password, int role, int access)
{
	Account* account = new Account;
	account->login = login;
	account->salt = getSalt();
	account->hash_password = hashPassword(password, account->salt);
	account->role = role;
	account->access = access;

	this->accounts->push_back(*account);
	writeToEndAccountFile(*account);
}


void AccountStorage::addAccount(Account* account)
{
	this->accounts->push_back(*account);
	writeToEndAccountFile(*account);
}


void AccountStorage::editAccount(Account* accountToEdit, Account* editedAccount)
{
	this->deleteAccount(accountToEdit->login);
	this->addAccount(editedAccount);
	writeAccountFile();
}


void AccountStorage::deleteAccount(string login)
{
	vector<Account>* accounts = getAccounts();

	for (int i = 0; i < accounts->size(); i++)
	{
		if (login == accounts->at(i).login)
		{
			accounts->erase(accounts->begin() + i);
			writeAccountFile();
			return;
		}
	}

	//if no account to delete 
	throw "Такого аккаунта не существует.";
}


vector<Account>* AccountStorage::getAccounts()
{
	return this->accounts;
}
