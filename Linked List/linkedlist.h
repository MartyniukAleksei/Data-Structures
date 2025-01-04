#pragma once

#include<iostream>
using namespace std;

template<class T>
class linkedlist
{
private:
	class Node
	{
	public:
		Node* pNext;
		T data;
		Node(T data = T(), Node* pNext = nullptr)
		{
			this->data = data;
			this->pNext = pNext;
		}
	};
	int size;
	Node* head;

public:
	linkedlist();
	~linkedlist();

	void push_back(T data);
	void push_front(T data);
	void pop_back();
	void pop_front();
	void inseart(T data, int index);
	void remove_at(int index);
	void clear();
	const int get_size() { return size; }
	bool empty() { return get_size() == 0; }

	Node* begin() { return head; };
	Node* end()
	{
		Node* current = head;
		for (int i = 0; i < get_size() - 1; i++)
			current = current->pNext;

		return current;
	};

	T& operator[](const int index);
	linkedlist<T>& operator=(linkedlist<T>& object);
};

#include "linkedlist.cpp"
