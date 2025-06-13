#pragma once
#include<iostream>
#include <vector>
#include<string>
using namespace std;
class Node //класс узла для списка
{
public:
	string name;//поле данных
    Node* prev;//указатель на пред узел
	Node* next;//указатель на след узел 
	Node(const string& val) :name(val),prev(nullptr), next(nullptr) {};
};
class DoubleLinkedList //реализация двусвязного списка
{
private:
    Node* head;
    Node* tail;
public:
    DoubleLinkedList():head(nullptr), tail(nullptr) {};
    bool IsEmpty() const{return head == nullptr;}//проверяет список на существование
    void Push(const string& value);
	void DeleteLastNode();
    void DeleteAll();
	vector<string> Print() const;
	string Back()const;
	size_t GetSize() const;
};

class WordGame //реализация самой игры 
{
private:
	vector <string> words;//вектор для хранения считанных слов
	vector<bool> used;//вектор для простмотра использованных слов
	DoubleLinkedList chain;
	void CutWords(const string& input);
	char GetLastChar(const string& word);
	bool BuildChain();
public:
	void InputFromFile(const string& filename);
	DoubleLinkedList Solution();
	void WriteSolutionFile(const string& filename, const DoubleLinkedList& solution) const;
};
