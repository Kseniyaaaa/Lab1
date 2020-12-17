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
	this->items = this->readItemsFile();
}


vector<Account>* AccountStorage::readItemsFile()
{
	vector<Account>* items = new vector<Account>();

	ifstream fin(FILE_OF_ACCOUNTS, ios::in);
	if (!fin.is_open()) {
		Account* account = this->createFirstAdmin();
		ofstream fout(FILE_OF_ACCOUNTS, ios::out);
		fout << account->login << " "
			<< account->hash_password << " "
			<< account->salt << " "
			<< account->role << " "
			<< account->access;
		fout.close();
		items->push_back(*account);
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
			items->push_back(*account);
		}
	}
	fin.close();
	return items;
}


void AccountStorage::writeToFile()
{
	ofstream fout(FILE_OF_ACCOUNTS, ios::out);
	for (int i = 0; i < items->size(); i++)
	{
		fout << items->at(i).login << " "
			<< items->at(i).hash_password << " "
			<< items->at(i).salt << " "
			<< items->at(i).role << " "
			<< items->at(i).access;
		if (i < items->size() - 1)
		{
			fout << endl;
		}
	}
	fout.close();
}


void AccountStorage::writeToEndOfFile(Account account)
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
	for (int i = 0; i < items->size(); i++)
	{
		if (items->at(i).login == login) {
			return &items->at(i);
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

	this->items->push_back(*account);
	writeToEndOfFile(*account);
}


void AccountStorage::addAccount(Account* account)
{
	this->items->push_back(*account);
	writeToEndOfFile(*account);
}


void AccountStorage::editAccount(Account* accountToEdit, Account* editedAccount)
{
	this->deleteAccount(accountToEdit->login);
	this->addAccount(editedAccount);
	writeToFile();
}


void AccountStorage::deleteAccount(string login)
{
	for (int i = 0; i < items->size(); i++)
	{
		if (login == items->at(i).login)
		{
			items->erase(items->begin() + i);
			writeToFile();
			return;
		}
	}

	//if no account to delete 
	throw "Такого аккаунта не существует.";
}


vector<Account>* AccountStorage::getAccounts()
{
	return this->items;
}
