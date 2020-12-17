#include "ConsoleApp.h"
#include "MusicalCompetition.h"
#include "validation.h"

#include <iostream>
#include <iomanip>
#include <map>
#include <algorithm>

using namespace std;

void ConsoleApp::start()
{
	this->authorize();
}


ConsoleApp::ConsoleApp()
{
	this->musicalCompetition = new MusicalCompetition();
}


void ConsoleApp::authorizationMenu()
{
	cout << "---------------------------------------------------����� ����������!---------------------------------------------------" << endl;
	cout << "�����������: " << endl
		<< "1. ����� " << endl
		<< "2. ������������������ " << endl
		<< "0. �����" << endl;
	cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
}


void ConsoleApp::authorize()
{
	int item;
	while (true)
	{
		this->authorizationMenu();
		cout << "�� ������: ";
		item = getNumber();

		switch (item)
		{
		case 0:
			return;

		case 1:
			login();
			break;

		case 2:
			registerAccount();
			break;

		default:
			cout << "�������� ��� ���" << endl;
			break;
		}
	}
}


void ConsoleApp::showAccounts()
{
	vector<Account>* accounts = this->musicalCompetition->getAccounts();

	for (int i = 0; i < accounts->size(); i++)
	{
		Account account = accounts->at(i);
		cout << i + 1 << ". "
			<< account.login << " "
			<< account.access << " ";

		if (account.role == 0)
		{
			cout << "������������" << endl;
		}
		if (account.role == 1)
		{
			cout << "�������������" << endl;
		}
	}
}


void ConsoleApp::additionAccountMenu()
{
	string login, password;
	int role;

	cout << "������� �����: ";
	cin >> login;
	cout << "������� ������: ";
	password = transformPassword();
	cout << "������������(0) ��� �������������(1)? : ";
	role = getNumber();

	this->musicalCompetition->addAccount(login, password, role, 1);
	cout << endl << "������� ������� ��������!" << endl;
}


void ConsoleApp::editionAccountMenu(Account* account)
{
	string login, password;
	int item, role, access;

	Account* editedAccount = new Account();
	editedAccount->login = account->login;
	editedAccount->password = account->password;
	editedAccount->role = account->role;
	editedAccount->access = account->access;

	while (true)
	{
		cout << endl << "1 - ��������������� ����� " << endl
			<< "2 - ��������������� ������ " << endl
			<< "3 - �������� ���� " << endl
			<< "4 - �������� ������ " << endl
			<< "5 - ��������� ���������" << endl
			<< "0 - �����" << endl;
		cout << "��������, ��� ������ �������: ";
		item = getNumber();
		cout << endl;

		switch (item)
		{
		case 0:
			return;

		case 1:
			cout << "������� ����� �����: ";
			cin >> editedAccount->login;
			break;

		case 2:
			cout << "������� ����� ������: ";
			cin >> editedAccount->password;
			break;

		case 3:
			cout << "�������� ����: ";
			cin >> editedAccount->role;
			break;

		case 4:
			cout << "�������� ������: ";
			cin >> editedAccount->access;
			break;
		case 5:
			this->musicalCompetition->editAccount(account, editedAccount);
			break;

		default:
			cout << "�������� ��� ���." << endl;
			break;
		}
	}
	cout << "������� ������� ��������������!" << endl;
}


void ConsoleApp::chooseAccountToEdit()
{
	string login;
	cout << "������� ����� ��������, ������� ������ ���������������: ";
	cin >> login;

	Account* account = this->musicalCompetition->getAccount(login);

	if (account != NULL)
	{
		editionAccountMenu(account);
	}
	else cout << "������ �������� �� ����������." << endl;
}


void ConsoleApp::deleteAccountMenu()
{
	string login, cur_login;
	cout << "������� ����� ��������, ������� ������ �������: ";
	cin >> login;

	cur_login = this->musicalCompetition->current_account->login;
	if (login == cur_login) {
		cout << "��� ������� �� ����� ���� ������." << endl;
	}
	else {
		try
		{
			this->musicalCompetition->deleteAccount(login);
			cout << "������� ������� ������!" << endl;
		}
		catch (const char* exMessage) {
			cout << exMessage << endl;
			return;
		}
	}
}


void ConsoleApp::showAdminAccountMenu()
{
	int item;

	while (true)
	{
		cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
		cout << "1. ����������� ������� ������ " << endl
			<< "2. �������� ������� ������ " << endl
			<< "3. ��������������� ������� ������ " << endl
			<< "4. ������� ������� ������" << endl
			<< "0. �����" << endl;
		cout << endl << "��������, ��� ������ �������: ";
		item = getNumber();
		cout << endl;

		switch (item)
		{
		case 0:
			return;

		case 1:
			showAccounts();
			break;

		case 2:
			additionAccountMenu();
			break;

		case 3:
			chooseAccountToEdit();
			break;

		case 4:
			deleteAccountMenu();
			break;

		default:
			cout << "�������� ��� ���" << endl;
			break;
		}
	}
}


void ConsoleApp::showRecord(Participant* record)
{
	cout << record->name << setw(20)
		<<  record->country << setw(10)
		<< record->year << setw(15)
		<< record->instrument << setw(10)
		<< record->place << " �����" << endl;
}


void ConsoleApp::showData()
{
	vector<Participant>* records = this->musicalCompetition->getRecords();

	for (int i = 0; i < records->size(); i++)
	{
		cout << i + 1 << ". ";
		showRecord(&records->at(i));
	}
}


void ConsoleApp::additionRecordMenu()
{
	string name, country, instrument;
	int year, place;

	cout << "������� ��� ���������: ";
	getline(cin, name);
	cout << "������� ������, ������� ��/��� ������������: ";
	getline(cin, country);

	cout << "������� ���/� ��� ��������: ";
	while (true) {
		year = getNumber();
		if (year < getCurrentYear()) {
			break;
		}
		else {
			cout << "������� ���������� ��� �������� (<" << getCurrentYear() << "): ";
		}
	}

	cout << "������� ����������, �� ������� ��/��� ������: ";
	getline(cin, instrument);
	cout << "������� ������� ��/�� �����: ";
	place = getNumber();
	cout << endl;

	this->musicalCompetition->addRecord(name, year, country, instrument, place);
	cout << "������ ������� ���������!" << endl;
}


void ConsoleApp::editionRecordMenu(Participant* record, int i)
{
	string name, country, instrument;
	int item, year, place;

	Participant* editedRecord = new Participant();
	editedRecord->name = record->name;
	editedRecord->country = record->country;
	editedRecord->year = record->year;
	editedRecord->instrument = record->instrument;
	editedRecord->place = record->place;

	while (true)
	{
		cout << endl <<  "1 - �������� ��� " << endl
			<< "2 - �������� ������ " << endl
			<< "3 - �������� ��� �������� " << endl
			<< "4 - �������� ���������� " << endl
			<< "5 - �������� ������� ����� " << endl
			<< "6 - ��������� ���������" << endl
			<< "0 - �����" << endl;
		cout << endl << "��������, ��� ������ �������: ";
		item = getNumber();
		cout << endl;

		switch (item)
		{
		case 0:
			return;

		case 1:
			cout << "������� ���: ";
			getline(cin, editedRecord->name);
			break;

		case 2:
			cout << "������� ������: ";
			getline(cin, editedRecord->country);
			break;

		case 3:
			cout << "�������� ��� ��������: ";
			cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
			editedRecord->year = getNumber();
			break;

		case 4:
			cout << "�������� ����������: ";
			getline(cin, editedRecord->instrument);
			break;

		case 5:
			cout << "�������� ������� �����: ";
			cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
			editedRecord->place = getNumber();
			break;

		case 6:
			this->musicalCompetition->editRecord(i, editedRecord);
			cout << "������ ������� ���������������!" << endl;
			break;

		default:
			cout << "�������� ��� ���." << endl;
			break;
		}
	}
}


void ConsoleApp::chooseRecordToEdit()
{
	int i;
	cout << "������� ����� ��������, ������� ������ ���������������: ";
	i = getNumber() - 1;

	vector<Participant>* records = this->musicalCompetition->getRecords();
	Participant record = records->at(i);

	if (i >= 0 && i < records->size())
	{
		editionRecordMenu(&record, i);
	}

	else cout << "������ ��������� ���." << endl;
}


void ConsoleApp::findByName()
{
	string name;
	cout << "������� ��� �������� ���������: ";
	getline(cin, name);
	cout << endl;

	vector<Participant>* r_vector = this->musicalCompetition->findRecordByName(name);
	
	if (r_vector != NULL)
	{
		cout << "����� ������� ��������: " << endl;
		for (int i = 0; i < r_vector->size(); i++)
		{
			showRecord(&r_vector->at(i));
		}
	}
	else {
		cout << "����� ��������: " << endl;
		cout << "����� ���������� ���" << endl;
	}
}


void ConsoleApp::findByYear()
{
	int year;
	cout << "������� ��� �������� �������� ���������: ";
	year = getNumber();
	cout << endl;

	vector<Participant>* r_vector = this->musicalCompetition->findRecordByYear(year);

	if (r_vector != NULL)
	{
		cout << "����� ������� ��������: " << endl;
		for (int i = 0; i < r_vector->size(); i++)
		{
			showRecord(&r_vector->at(i));
		}
	}
	else {
		cout << "����� ��������: " << endl;
		cout << "����� ���������� ���" << endl;
	}
}


void ConsoleApp::findByPlace()
{
	int place;
	cout << "������� ������� ������� ���������� �����: ";
	place = getNumber();
	cout << endl;

	vector<Participant>* r_vector = this->musicalCompetition->findRecordByPlace(place);

	if (r_vector != NULL)
	{
		cout << "����� ������� ��������: " << endl;
		for (int i = 0; i < r_vector->size(); i++)
		{
			showRecord(&r_vector->at(i));
		}
	}
	else {
		cout << "����� ��������: " << endl;
		cout << "����� ���������� ���" << endl;
	}
}


void ConsoleApp::showFindingMenu()
{
	int item;

	while (true)
	{
		cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
		cout << "1 - ����� �� ����� " << endl
			<< "2 - ����� �� ���� �������� " << endl
			<< "3 - ����� �� �������� ����� " << endl
			<< "0 - �����" << endl;
		cout << endl << "�������� �������� ������: ";
		item = getNumber();
		cout << endl;

		switch (item)
		{
		case 0:
			return;

		case 1:
			findByName();
			break;

		case 2:
			findByYear();
			break;

		case 3:
			findByPlace();
			break;

		default:
			cout << "�������� ��� ���" << endl;
			break;
		}
	}
}


void ConsoleApp::sortByName()
{
	this->musicalCompetition->sortRecordsByName();
	cout << "���������� ���������:" << endl;
	showData();
}


void ConsoleApp::sortByYear()
{
	this->musicalCompetition->sortRecordsByYear();
	cout << "���������� ���������:" << endl;
	showData();
}


void ConsoleApp::sortByPlace()
{
	this->musicalCompetition->sortRecordsByPlace();
	cout << "���������� ���������:" << endl;
	showData();
}


void ConsoleApp::showSortingMenu()
{
	int item;

	while (true)
	{
		cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
		cout << "1 - ������������� �� ����� " << endl
			<< "2 - ������������� �� ���� �������� " << endl
			<< "3 - ������������� �� �������� ����� " << endl
			<< "0 - �����" << endl;
		cout << endl << "�������� �������� ����������: ";
		item = getNumber();
		cout << endl;

		switch (item)
		{
		case 0:
			return;

		case 1:
			sortByName();
			break;

		case 2:
			sortByYear();
			break;

		case 3:
			sortByPlace();
			break;

		default:
			cout << "�������� ��� ���" << endl;
			break;
		}
	}
}


void ConsoleApp::deleteRecordMenu()
{
	int i;
	cout << "������� ����� ���������, �������� ������ �������: ";
	i = getNumber() - 1;

	try
	{
		this->musicalCompetition->deleteRecord(i);
		cout << "������ �������!" << endl;
	}
	catch (const char* exMessage) {
		cout << exMessage << endl;
		return;
	}
}


void ConsoleApp::task()
{
	// �� ������� ������ ����������� ������������ ������� ������ ������ ���� ���� � ��������� �������� �����������
	task1();

	// ���������� �� 12 ���
	task2();
}


void ConsoleApp::task1()
{
	vector<Participant>* records = this->musicalCompetition->getRecords();

	map<string, vector<Participant>> list;
	for (int i = 0; i < records->size(); i++)
	{
		map <string, vector<Participant>> ::iterator it = list.find(records->at(i).instrument);

		if (it == list.end()) {
			vector<Participant> v;
			list[records->at(i).instrument] = v;
			list[records->at(i).instrument].push_back(records->at(i));
		}
		else {
			it->second.push_back(records->at(i));
		}
	}

	for (map <string, vector<Participant>> ::iterator it = list.begin(); it != list.end(); it++)
	{
		cout << it->first << endl;
		sort(it->second.begin(), it->second.end(), PlaceComparator);

		for (int i = 0; i < it->second.size(); i++)
		{
			Participant p = it->second.at(i);
			cout << endl;
			cout << i + 1 << ". "  << p.name << " "
				<< p.country << " " << p.year << "(" << getCurrentYear() - p.year << " ���/���/�)" << " "
				<< p.instrument << " " << p.place << " �����" << endl;
			cout << "  ---------------------------------------------------------------------------------------------- " << endl;
		}
		cout << endl;
	}
}


void ConsoleApp::task2()
{
	bool flag = false;

	vector<Participant>* records = this->musicalCompetition->getRecords();

	sort(records->begin(), records->end(), YearDescComparator);
	cout << "��� ���������� �� 12 ���: " << endl;
	for (int i = 0; i < records->size(); i++)
	{
		if (records->at(i).year >= getCurrentYear() - 12) {
			cout << endl;
			Participant p = records->at(i);
			cout << i + 1 << ". " << p.name
				<< p.country << " " << p.year << "(" << getCurrentYear() - p.year << " ���/���/�)" << " "
				<< p.instrument << " " << p.place << " �����" << endl;
			cout << "  ---------------------------------------------------------------------------------------------- " << endl;
			flag = true;
		}
	}
	if (!flag) {
		cout << "����� ���������� ���." << endl;
	}
}


void ConsoleApp::clearAllMenu()
{
	this->musicalCompetition->clearAll();
}


void ConsoleApp::showAdminDataMenu()
{
	int item;

	while (true)
	{
		cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
		cout << "1. ����������� ������ � ��������" << endl
			<< "2. �������� ���������/�� �������� " << endl
			<< "3. ��������������� ������ � ��������" << endl
			<< "4. ����� ��������� ��������" << endl
			<< "5. ������������� ������ " << endl
			<< "6. ��������� �������������� ������� " << endl
			<< "7. ������� ������ ���������" << endl
			<< "8. ������� ��� ������" << endl
			<< "0. �����" << endl;
		cout << endl << "��������, ��� ������ �������: ";
		item = getNumber();
		cout << endl;

		switch (item)
		{
		case 0:
			return;

		case 1:
			showData();
			break;

		case 2:
			additionRecordMenu();
			break;

		case 3:
			chooseRecordToEdit();
			break;

		case 4:
			showFindingMenu();
			break;

		case 5:
			showSortingMenu();
			break;

		case 6:
			task();
			break;

		case 7:
			deleteRecordMenu();
			break;

		case 8:
			clearAllMenu();
			break;

		default:
			cout << "�������� ��� ���" << endl;
			break;
		}
	}
}


void ConsoleApp::showAdminMenu()
{
	int item;
	while (true)
	{
		cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
		cout << "1 - ������ � �������� �������� " << endl
			<< "2 - ������ � ������� " << endl
			<< "0 - �����" << endl;
		cout << endl << "�������� ����� ������: ";
		item = getNumber();
		cout << endl;

		switch (item)
		{
		case 0:
			return;

		case 1:
			showAdminAccountMenu();
			break;

		case 2:
			showAdminDataMenu();
			break;

		default:
			cout << "�������� ��� ���" << endl;
			break;
		}
	}
}


void ConsoleApp::showUserMenu()
{
	int item;
	while (true)
	{
		cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
		cout << "1 - ����������� ������ � ��������" << endl
			<< "2 - ����� ��������� ��������" << endl
			<< "3 - ������������� ������ " << endl
			<< "4 - ��������� �������������� ������� " << endl
			<< "0 - �����" << endl;
		cout << "��������, ��� ������ �������: ";
		item = getNumber();

		switch (item)
		{
		case 0:
			return;

		case 1:
			showData();
		break;

		case 2:
			showFindingMenu();
		break;

		case 3:
			showSortingMenu();
		break;

		case 4:
			task();
		break;

		default:
			cout << "�������� ��� ���" << endl;
			break;
		}
	}
}


void ConsoleApp::login()
{
	string login, password;
	cout << "������� �����: ";
	cin >> login;
	cout << "������� ������: ";
	password = transformPassword();
	cout << endl;

	Account* account;
	try {
		account = this->musicalCompetition->login(login, password);
	}
	catch (const char* exMessage) {
		cout << exMessage << endl;
		cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
		return;
	}

	if (account->role == 1) {
		cout << "�� �������������." << endl;
		cout << "���� �������� �������." << endl;
		showAdminMenu();
	}
	else {
		cout << "�� ������������." << endl;
		cout << "���� �������� �������." << endl;
		showUserMenu();
	}
}


void ConsoleApp::registerAccount()
{
	string login, password, password2;
	cout << "������� �����: ";
	cin >> login;
	do {
		cout << "������� ������: ";
		password = transformPassword();
		cout << "����������� ������: ";
		password2 = transformPassword();
		cout << endl;
	} while (password != password2);

	try {
		this->musicalCompetition->registerAccount(login, password);
		cout << "�� ������� ������������������!" << endl;
	}
	catch (const char* exMessage) {
		cout << exMessage << endl;
		cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
		return;
	}
}
