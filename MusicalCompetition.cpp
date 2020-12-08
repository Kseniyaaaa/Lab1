#include <iostream>
#include <time.h>

#include "MusicalCompetition.h"

using namespace std;

MusicalCompetition::MusicalCompetition()
{
	this->aStorage = new AccountStorage();
	this->pStorage = new ParticipantStorage();
}


Account* MusicalCompetition::login(string login, string password)
{
	Account* account = aStorage->getAccount(login);

	if (account == NULL) {
		throw "Такого аккаунта не существует.";
	}
	else if (account->hash_password != hashPassword(password, account->salt)) {
		throw "Неверный пароль.";
	}

	if (account->access == 0) {
		throw "Вы не можете войти в аккаунт. Ожидайте подтверждения администратора.";
	}

	this->current_account = account;
	return this->current_account;
}


void MusicalCompetition::registerAccount(string login, string password)
{
	Account* account = aStorage->getAccount(login);

	if (account != NULL) {
		throw "Аккаунт с таким логином уже существует!";
	}
	
	this->aStorage->addAccount(login, password, 0, 0);
}


Account* MusicalCompetition::getAccount(string login)
{
	return this->aStorage->getAccount(login);
}


long long int MusicalCompetition::hashPassword(string password, string salt)
{
	return this->aStorage->hashPassword(password, salt);
}


void MusicalCompetition::addAccount(string login, string password, int role, int access)
{
	this->aStorage->addAccount(login, password, role, access);
}


void MusicalCompetition::editAccount(Account* accountToEdit, Account* editedAccount)
{
	return this->aStorage->editAccount(accountToEdit, editedAccount);
}


void MusicalCompetition::deleteAccount(string login)
{
	this->aStorage->deleteAccount(login);
}


vector<Account>* MusicalCompetition::getAccounts()
{
	return this->aStorage->getAccounts();
}


vector<Participant>* MusicalCompetition::getRecords()
{
	return this->pStorage->getRecords();
}


void MusicalCompetition::addRecord(string name, int year, string country, string instrument, int place)
{
	this->pStorage->addRecord(name, year, country, instrument, place);
}


void MusicalCompetition::editRecord(int recordToEdit, Participant* editedRecord)
{
	this->pStorage->editRecord(recordToEdit, editedRecord);
}


Participant* MusicalCompetition::findRecordByName(string name)
{
	return this->pStorage->findRecordByName(name);
}


Participant* MusicalCompetition::findRecordByYear(int year)
{
	return this->pStorage->findRecordByYear(year);
}


Participant* MusicalCompetition::findRecordByPlace(int place)
{
	return this->pStorage->findRecordByPlace(place);
}


void MusicalCompetition::sortRecordsByName()
{
	this->pStorage->sortRecordsByName();
}


void MusicalCompetition::sortRecordsByYear()
{
	this->pStorage->sortRecordsByYear();
}


void MusicalCompetition::sortRecordsByPlace()
{
	this->pStorage->sortRecordsByPlace();
}


void MusicalCompetition::deleteRecord(int i)
{
	this->pStorage->deleteRecord(i);
}


void MusicalCompetition::clearAll()
{
	this->pStorage->clearAll();
}