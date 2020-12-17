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
	cout << "---------------------------------------------------Добро пожаловать!---------------------------------------------------" << endl;
	cout << "Авторизация: " << endl
		<< "1. Войти " << endl
		<< "2. Зарегистрироваться " << endl
		<< "0. ВЫХОД" << endl;
	cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
}


void ConsoleApp::authorize()
{
	int item;
	while (true)
	{
		this->authorizationMenu();
		cout << "Вы хотите: ";
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
			cout << "Выберите еще раз" << endl;
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
			cout << "пользователь" << endl;
		}
		if (account.role == 1)
		{
			cout << "администратор" << endl;
		}
	}
}


void ConsoleApp::additionAccountMenu()
{
	string login, password;
	int role;

	cout << "Введите логин: ";
	cin >> login;
	cout << "Введите пароль: ";
	password = transformPassword();
	cout << "Пользователь(0) или администратор(1)? : ";
	role = getNumber();

	this->musicalCompetition->addAccount(login, password, role, 1);
	cout << endl << "Аккаунт успешно добавлен!" << endl;
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
		cout << endl << "1 - Отредактировать логин " << endl
			<< "2 - Отредактировать пароль " << endl
			<< "3 - Изменить роль " << endl
			<< "4 - Изменить доступ " << endl
			<< "5 - Сохранить изменения" << endl
			<< "0 - ВЫХОД" << endl;
		cout << "Выберите, что хотите сделать: ";
		item = getNumber();
		cout << endl;

		switch (item)
		{
		case 0:
			return;

		case 1:
			cout << "Введите новый логин: ";
			cin >> editedAccount->login;
			break;

		case 2:
			cout << "Введите новый пароль: ";
			cin >> editedAccount->password;
			break;

		case 3:
			cout << "Измените роль: ";
			cin >> editedAccount->role;
			break;

		case 4:
			cout << "Измените доступ: ";
			cin >> editedAccount->access;
			break;
		case 5:
			this->musicalCompetition->editAccount(account, editedAccount);
			break;

		default:
			cout << "Выберите еще раз." << endl;
			break;
		}
	}
	cout << "Аккаунт успешно отредактирован!" << endl;
}


void ConsoleApp::chooseAccountToEdit()
{
	string login;
	cout << "Введите логин аккаунта, который хотите отредактировать: ";
	cin >> login;

	Account* account = this->musicalCompetition->getAccount(login);

	if (account != NULL)
	{
		editionAccountMenu(account);
	}
	else cout << "Такого акканута не существует." << endl;
}


void ConsoleApp::deleteAccountMenu()
{
	string login, cur_login;
	cout << "Введите логин аккаунта, который хотите удалить: ";
	cin >> login;

	cur_login = this->musicalCompetition->current_account->login;
	if (login == cur_login) {
		cout << "Ваш аккаунт не может быть удален." << endl;
	}
	else {
		try
		{
			this->musicalCompetition->deleteAccount(login);
			cout << "Аккаунт успешно удален!" << endl;
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
		cout << "1. Просмотреть учетные записи " << endl
			<< "2. Добавить учетную запись " << endl
			<< "3. Отредактировать учетную запись " << endl
			<< "4. Удалить учетную запись" << endl
			<< "0. ВЫХОД" << endl;
		cout << endl << "Выберите, что хотите сделать: ";
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
			cout << "Выберите еще раз" << endl;
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
		<< record->place << " место" << endl;
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

	cout << "Введите ФИО участника: ";
	getline(cin, name);
	cout << "Введите страну, которую он/она представляет: ";
	getline(cin, country);

	cout << "Введите его/её год рождения: ";
	while (true) {
		year = getNumber();
		if (year < getCurrentYear()) {
			break;
		}
		else {
			cout << "Введите правильный год рождения (<" << getCurrentYear() << "): ";
		}
	}

	cout << "Введите инструмент, на котором он/она играет: ";
	getline(cin, instrument);
	cout << "Введите занятое им/ей место: ";
	place = getNumber();
	cout << endl;

	this->musicalCompetition->addRecord(name, year, country, instrument, place);
	cout << "Запись успешно добавлена!" << endl;
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
		cout << endl <<  "1 - Изменить ФИО " << endl
			<< "2 - Изменить страну " << endl
			<< "3 - Изменить год рождения " << endl
			<< "4 - Изменить инструмент " << endl
			<< "5 - Изменить занятое место " << endl
			<< "6 - Сохранить изменения" << endl
			<< "0 - ВЫХОД" << endl;
		cout << endl << "Выберите, что хотите сделать: ";
		item = getNumber();
		cout << endl;

		switch (item)
		{
		case 0:
			return;

		case 1:
			cout << "Введите ФИО: ";
			getline(cin, editedRecord->name);
			break;

		case 2:
			cout << "Введите страну: ";
			getline(cin, editedRecord->country);
			break;

		case 3:
			cout << "Измените год рождения: ";
			cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
			editedRecord->year = getNumber();
			break;

		case 4:
			cout << "Измените инструмент: ";
			getline(cin, editedRecord->instrument);
			break;

		case 5:
			cout << "Измените занятое место: ";
			cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
			editedRecord->place = getNumber();
			break;

		case 6:
			this->musicalCompetition->editRecord(i, editedRecord);
			cout << "Запись успешно отредактирована!" << endl;
			break;

		default:
			cout << "Выберите еще раз." << endl;
			break;
		}
	}
}


void ConsoleApp::chooseRecordToEdit()
{
	int i;
	cout << "Введите номер аккаунта, который хотите отредактировать: ";
	i = getNumber() - 1;

	vector<Participant>* records = this->musicalCompetition->getRecords();
	Participant record = records->at(i);

	if (i >= 0 && i < records->size())
	{
		editionRecordMenu(&record, i);
	}

	else cout << "Такого участника нет." << endl;
}


void ConsoleApp::findByName()
{
	string name;
	cout << "Введите ФИО искомого участника: ";
	getline(cin, name);
	cout << endl;

	vector<Participant>* r_vector = this->musicalCompetition->findRecordByName(name);
	
	if (r_vector != NULL)
	{
		cout << "Поиск успешно завершен: " << endl;
		for (int i = 0; i < r_vector->size(); i++)
		{
			showRecord(&r_vector->at(i));
		}
	}
	else {
		cout << "Поиск завершен: " << endl;
		cout << "Таких участников нет" << endl;
	}
}


void ConsoleApp::findByYear()
{
	int year;
	cout << "Введите год рождения искомого участника: ";
	year = getNumber();
	cout << endl;

	vector<Participant>* r_vector = this->musicalCompetition->findRecordByYear(year);

	if (r_vector != NULL)
	{
		cout << "Поиск успешно завершен: " << endl;
		for (int i = 0; i < r_vector->size(); i++)
		{
			showRecord(&r_vector->at(i));
		}
	}
	else {
		cout << "Поиск завершен: " << endl;
		cout << "Таких участников нет" << endl;
	}
}


void ConsoleApp::findByPlace()
{
	int place;
	cout << "Введите занятое искомым участником место: ";
	place = getNumber();
	cout << endl;

	vector<Participant>* r_vector = this->musicalCompetition->findRecordByPlace(place);

	if (r_vector != NULL)
	{
		cout << "Поиск успешно завершен: " << endl;
		for (int i = 0; i < r_vector->size(); i++)
		{
			showRecord(&r_vector->at(i));
		}
	}
	else {
		cout << "Поиск завершен: " << endl;
		cout << "Таких участников нет" << endl;
	}
}


void ConsoleApp::showFindingMenu()
{
	int item;

	while (true)
	{
		cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
		cout << "1 - Найти по имени " << endl
			<< "2 - Найти по году рождения " << endl
			<< "3 - Найти по занятому месту " << endl
			<< "0 - ВЫХОД" << endl;
		cout << endl << "Выберите параметр поиска: ";
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
			cout << "Выберите еще раз" << endl;
			break;
		}
	}
}


void ConsoleApp::sortByName()
{
	this->musicalCompetition->sortRecordsByName();
	cout << "Сортировка завершена:" << endl;
	showData();
}


void ConsoleApp::sortByYear()
{
	this->musicalCompetition->sortRecordsByYear();
	cout << "Сортировка завершена:" << endl;
	showData();
}


void ConsoleApp::sortByPlace()
{
	this->musicalCompetition->sortRecordsByPlace();
	cout << "Сортировка завершена:" << endl;
	showData();
}


void ConsoleApp::showSortingMenu()
{
	int item;

	while (true)
	{
		cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
		cout << "1 - Отсортировать по имени " << endl
			<< "2 - Отсортировать по году рождения " << endl
			<< "3 - Отсортировать по занятому месту " << endl
			<< "0 - ВЫХОД" << endl;
		cout << endl << "Выберите параметр сортировки: ";
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
			cout << "Выберите еще раз" << endl;
			break;
		}
	}
}


void ConsoleApp::deleteRecordMenu()
{
	int i;
	cout << "Введите номер участника, которого хотите удалить: ";
	i = getNumber() - 1;

	try
	{
		this->musicalCompetition->deleteRecord(i);
		cout << "Запись удалена!" << endl;
	}
	catch (const char* exMessage) {
		cout << exMessage << endl;
		return;
	}
}


void ConsoleApp::task()
{
	// По каждому классу музыкальных инструментов вывести список первых трех мест с указанием возраста победителей
	task1();

	// Победители до 12 лет
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
				<< p.country << " " << p.year << "(" << getCurrentYear() - p.year << " лет/год/а)" << " "
				<< p.instrument << " " << p.place << " место" << endl;
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
	cout << "Все победители до 12 лет: " << endl;
	for (int i = 0; i < records->size(); i++)
	{
		if (records->at(i).year >= getCurrentYear() - 12) {
			cout << endl;
			Participant p = records->at(i);
			cout << i + 1 << ". " << p.name
				<< p.country << " " << p.year << "(" << getCurrentYear() - p.year << " лет/год/а)" << " "
				<< p.instrument << " " << p.place << " место" << endl;
			cout << "  ---------------------------------------------------------------------------------------------- " << endl;
			flag = true;
		}
	}
	if (!flag) {
		cout << "Таких участников нет." << endl;
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
		cout << "1. Просмотреть данные о конкурсе" << endl
			<< "2. Добавить участника/ов конкурса " << endl
			<< "3. Отредактировать данные о конкурсе" << endl
			<< "4. Найти участника конкурса" << endl
			<< "5. Отсортировать данные " << endl
			<< "6. Выполнить индивидуальное задание " << endl
			<< "7. Удалить данные участника" << endl
			<< "8. Удалить все данные" << endl
			<< "0. ВЫХОД" << endl;
		cout << endl << "Выберите, что хотите сделать: ";
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
			cout << "Выберите еще раз" << endl;
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
		cout << "1 - Работа с учетными записями " << endl
			<< "2 - Работа с данными " << endl
			<< "0 - ВЫХОД" << endl;
		cout << endl << "Выберите режим работы: ";
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
			cout << "Выберите еще раз" << endl;
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
		cout << "1 - Просмотреть данные о конкурсе" << endl
			<< "2 - Найти участника конкурса" << endl
			<< "3 - Отсортировать данные " << endl
			<< "4 - Выполнить индивидуальное задание " << endl
			<< "0 - ВЫХОД" << endl;
		cout << "Выберите, что хотите сделать: ";
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
			cout << "Выберите еще раз" << endl;
			break;
		}
	}
}


void ConsoleApp::login()
{
	string login, password;
	cout << "Введите логин: ";
	cin >> login;
	cout << "Введите пароль: ";
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
		cout << "Вы администратор." << endl;
		cout << "Вход выполнен успешно." << endl;
		showAdminMenu();
	}
	else {
		cout << "Вы пользователь." << endl;
		cout << "Вход выполнен успешно." << endl;
		showUserMenu();
	}
}


void ConsoleApp::registerAccount()
{
	string login, password, password2;
	cout << "Введите логин: ";
	cin >> login;
	do {
		cout << "Введите пароль: ";
		password = transformPassword();
		cout << "Подтвердите пароль: ";
		password2 = transformPassword();
		cout << endl;
	} while (password != password2);

	try {
		this->musicalCompetition->registerAccount(login, password);
		cout << "Вы успешно зарегистрировались!" << endl;
	}
	catch (const char* exMessage) {
		cout << exMessage << endl;
		cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
		return;
	}
}
