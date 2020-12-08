#include <iostream>
#include <string>
#include <fstream>
#include <Windows.h>
#include "ConsoleApp.h"

using namespace std;


int main()
{
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	ConsoleApp* app = new ConsoleApp();
	app->start();

	system("pause");
}