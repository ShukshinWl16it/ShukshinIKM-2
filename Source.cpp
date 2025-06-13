#include<iostream>
#include"Header.h"
#include<string>
#include<vector>
#include<fstream>
#include<sstream>
#include<Windows.h>
using namespace std;
//реализация функций списка

void DoubleLinkedList::Push(const string& value) 
{
	Node* newNode = new Node(value);
	if (!head) {
		head = tail=newNode;
	}
	else
	{
		tail->next = newNode;
		newNode->prev = tail;
		tail = newNode;
	}
}
void DoubleLinkedList::DeleteLastNode() 
{
	if (!tail||!head) return;
	Node* toDelete = tail;
	if (head==tail)
	{
		head = tail = nullptr;
	}
	else
	{
		tail = tail->prev;
		if(tail) tail->next = nullptr;
	}
	delete toDelete;
	toDelete = nullptr;
}
void DoubleLinkedList::DeleteAll()
{
	while (!IsEmpty())
	{
		DeleteLastNode();
	}
	head = tail = nullptr;
}
vector<string> DoubleLinkedList::Print()const//создает вектор для вывода результата
{
	vector<string> result;
	Node* current = head;
	while (current) 
	{
		result.push_back(current->name);
		current = current->next;
	}
	return result;
}
string DoubleLinkedList::Back() const//возвращает последний элемент списка 
{
	return tail ? tail->name : "";
}
size_t DoubleLinkedList::GetSize()const//получает размер списка 
{
	size_t count = 0;
	Node* current = head;
	while (current)
	{
		count++;
		current = current->next;
	}
	return count;
}
//реализация функций игры со словами 

void WordGame::CutWords(const string& input)//разделает строку на слова 
{
	words.clear();
	istringstream iss(input);
	string word;
	while (iss >> word)
	{
		words.push_back(word);
	}
}

void WordGame::InputFromFile(const string& filename)//считывает с файла 
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	ifstream file(filename);
	if (!file.is_open()) 
	{
		cerr << "Файл не открылся!" << endl;
		return;
	}
	string line;
	getline(file, line);
	cout <<"Исходная строка: " << line << endl;
	CutWords(line);
	file.close();
}

char WordGame::GetLastChar(const string& word)//получает последний символ(с учетом мягкого знака)
{
	if (word.empty()) return '\0';//проверка на пустую строку
	char last = word.back();
	if (last == 'ь' && word.size() > 1)
	{
		return word[word.size() - 2];
	}
	return last;
}
bool WordGame::BuildChain()
{
	if (chain.GetSize() == words.size())
	{
		return chain.Print()[0][0] == GetLastChar(chain.Back());//смотрим, если слово последнее, то посленяя буква этого слова должна быть такой же, как у первого слова в цепочке
	}
	char lastChar = GetLastChar(chain.Back());//получение последнего символа
	for (size_t i = 0; i < words.size(); i++) 
	{
		if (!used[i] && words[i][0] == lastChar)
		{
			used[i] = true;//помечает слово как использованное 
			chain.Push(words[i]);//добавляет его в цепочку
			if (BuildChain())//рекрсивно продолжается построение
			{
				return true;
			}
			//откатываем изменения 
			chain.DeleteLastNode();
			used[i] = false;
		}
	}
	return false;
}
DoubleLinkedList WordGame::Solution() 
{
	chain.DeleteAll();
	if (words.empty())
	{
		cout << "Нет слов для построения цепочки" << endl;
		return DoubleLinkedList();
	}
	for (size_t start = 0; start < words.size(); start++)
	{
		used = vector<bool>(words.size(), false);//сбрасываются метки использования
		chain.Push(words[start]);//пробуем начать с каждого слова
		used[start] = true;
		if (BuildChain())//пытаемся построить цепочку
		{
			return chain;
		}
		 chain.DeleteLastNode();
	}
	return DoubleLinkedList();
}
void WordGame::WriteSolutionFile(const string& filename, const DoubleLinkedList& solution) const//выводит в консоль результат и записывает его в файл 
{
	if (solution.IsEmpty())
	{
		cout << endl;
		cout << "Решение не найдено" << endl;
		return;
	}
	vector<string> words = solution.Print();
	cout << "Решение: ";
	for (size_t i = 0; i < words.size();i++) //в консоль
	{
		if (i!=0) 
		{
			cout << " ";
		}
		cout << words[i];
	}
	cout << endl;
	ofstream outFile(filename);
	if (!outFile.is_open())
	{
		cerr << "Файл не открылся!" << endl;
		return;
	}
	for (size_t i = 0; i < words.size(); i++)//в файл
	{
		if (i != 0)
		{
			outFile << " ";
		}
		outFile << words[i];
	}
	outFile << endl;
	outFile.close();
	cout << "Результат записан в файл " << filename << endl;
}
