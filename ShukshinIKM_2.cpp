#include <iostream>
#include<Windows.h>
#include"Header.h"
using namespace std;
int main()
{
	setlocale(LC_ALL, "Russian");
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	try 
	{
		WordGame game;
		game.InputFromFile("wordgame.txt");
		cout << "Файл считан"<<endl;
		DoubleLinkedList solution = game.Solution();
		if (solution.IsEmpty())
		{
			cout << "Не удалось построить цепочку изи слов" << endl;
		}
		else
		{
			game.WriteSolutionFile("output.txt", solution);
		}
	}
	catch (const exception& e)
	{
		cerr << "Ошибка: " << e.what()<< endl;
	}
	return 0;
}
