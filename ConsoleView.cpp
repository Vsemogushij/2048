#include "ConsoleView.h"
#include <iostream>
#include <Windows.h>
#include "Application.h"

using namespace std;

void ConsoleView::show()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	cout << "\t\t2048 GAME!!!" << endl;
	system("pause");
}

void ConsoleView::onUpdate()
{
	
	Player user = Application::Initilize()->getPlayer();
	system("cls");
	cout << "\t\t2048 GAME!!!" << endl;
	cout << "Игрок: " << user.name << endl;
	cout << "Текущий рекорд: " << user.currentScore << endl;

	int* field = Application::Initilize()->getFieldValues();
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++)
		{
			cout.width(5);
			cout << *(field + i + j * 4) << " ";
		}
		cout << endl;
	}
	delete field;
	char x;
	cout << "u - вверх d - вниз l - влево r - вправо t - таблица рекордов q - выход" << endl;
	cin >> x;
	if (x == 'u')
		onUp();
	if (x == 'd')
		onDown();
	if (x == 'l')
		onLeft();
	if (x == 'r')
		onRight();
	if (x == 'q')
		Application::Initilize()->onQuit();
	if (x == 't')
		Application::Initilize()->onShowScoreTable();
}

void ConsoleView::showWin()
{
	system("cls");
	cout << "\t\tCONGRATULATIONS, YOU WIN!!!" << endl;
	cout << "You record: " << Application::Initilize()->getPlayer().currentScore << endl;
}

void ConsoleView::showLoose()
{
	system("cls");
	cout << "\t\tYOU Loose!!!" << endl;
	cout << "You record: " << Application::Initilize()->getPlayer().currentScore << endl;
}

void ConsoleView::showScoreTable(std::vector<std::string> records)
{
	system("cls");
	cout << "\t\tSCORE TABLE" << endl;
	for (int i = 0; i < records.size(); i++)
	{
		cout << i << ". " << records[i] << endl;
	}
	system("pause");
}

std::string ConsoleView::getUsername()
{
	string user;
	system("cls");
	cout << "\t\t2048 GAME!!!" << endl;
	cout << "Введите ваше имя: ";
	cin >> user;
	return user;
}

bool ConsoleView::loadLastGame()
{
	system("cls");
	cout << "Загрузить последнюю игру(y/n)? " << endl;
	char x;
	cin >> x;
	if (x == 'y')
		return true;
	else
		return false;
}
