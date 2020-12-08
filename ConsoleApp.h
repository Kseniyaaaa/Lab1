#pragma once
#include "MusicalCompetition.h"
#include "AccountStorage.h"

class ConsoleApp
{
private:
	MusicalCompetition* musicalCompetition;

	void authorize();
	void authorizationMenu();

	void login();
	void registerAccount();
	void showAdminMenu();
	void showUserMenu();

	void showAdminAccountMenu();
	void showAdminDataMenu();

	void showAccounts();
	void showData();
	void showRecord(Participant* record);

	void additionAccountMenu();
	void additionRecordMenu();

	void chooseRecordToEdit();
	void editionRecordMenu(Participant* recordToEdit, int i);

	void chooseAccountToEdit();
	void editionAccountMenu(Account* accountToEdit);

	void deleteAccountMenu();
	void deleteRecordMenu();

	void task();
	void task1();
	void task2();

	void clearAllMenu();

	void findByName();
	void findByYear();
	void findByPlace();
	void showFindingMenu();

	void sortByName();
	void sortByYear();
	void sortByPlace();
	void showSortingMenu();

public:
	void start();
	ConsoleApp();
};

