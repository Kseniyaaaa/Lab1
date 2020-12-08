#pragma once

#include <vector>
#include <string>
#include "Account.h"
#include "AccountStorage.h"
#include "ParticipantStorage.h"

using namespace std;

class MusicalCompetition
{
private:
	AccountStorage* aStorage;
	ParticipantStorage* pStorage;

public:
	MusicalCompetition();
	Account* current_account;

	Account* login(string login, string password);
	void registerAccount(string login, string password);

	Account* getAccount(string login);

	long long int hashPassword(string password, string salt);

	void addAccount(string login, string password, int role, int access);
	void editAccount(Account* accountToEdit, Account* editedAccount);
	void deleteAccount(string login);

	vector<Account>* getAccounts();
	vector<Participant>* getRecords();

	void addRecord(string name, int year, string country, string instrument, int place);
	void editRecord(int recordToEdit, Participant* editedRecord);

	Participant* findRecordByName(string name);
	Participant* findRecordByYear(int year);
	Participant* findRecordByPlace(int place);

	void sortRecordsByName();
	void sortRecordsByYear();
	void sortRecordsByPlace();

	void deleteRecord(int i);
	void clearAll();
};

