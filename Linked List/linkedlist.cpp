#pragma once
#include "linkedlist.h"

template<class T>
linkedlist<T>::linkedlist()
{
	this->size = 0;
	this->head = nullptr;
}

template<class T>
linkedlist<T>::~linkedlist()
{
	clear();
}

template<class T>
void linkedlist<T>::push_back(T data)
{
	if (this->head == nullptr)
	{
		this->head = new Node(data);
	}
	else
	{
		Node* current = this->head;

		while (current->pNext != nullptr)
		{
			current = current->pNext;
		}
		current->pNext = new Node(data);
	}
	++size;
}

template<class T>
void linkedlist<T>::push_front(T data)
{
	head = new Node(data, head);
	size++;
}

template<class T>
void linkedlist<T>::pop_back()
{
	remove_at(this->get_size() - 1);
}

template<class T>
void linkedlist<T>::pop_front()
{
	Node* front = head;

	head = head->pNext;
	delete front;

	size--;
}

template<class T>
void linkedlist<T>::inseart(T data, int index)
{
	if (index == 0)
	{
		push_front(data);
	}
	else
	{
		Node* previous = this->head;
		for (int i = 0; i < index - 1; i++)
		{
			previous = previous->pNext;
		}

		Node* NewItem = new Node(data, previous->pNext);
		previous->pNext = NewItem;

		size++;
	}
}

template<class T>
void linkedlist<T>::remove_at(int index)
{
	if (index == 0)
	{
		pop_front();
	}
	else
	{
		Node* previous = this->head;

		for (int i = 0; i < index - 1; i++)
			previous = previous->pNext;

		Node* toDelete = previous->pNext;

		previous->pNext = toDelete->pNext;
		delete toDelete;

		size--;
	}
}

template<class T>
void linkedlist<T>::clear()
{
	while (size)
		pop_front();
}

template<class T>
T& linkedlist<T>::operator[](const int index)
{
	int count = 0;
	Node* current = this->head;

	while (current != nullptr)
	{
		if (count == index)
			return current->data;

		count++;
		current = current->pNext;
	}
}

template<class T>
linkedlist<T>& linkedlist<T>::operator=(linkedlist<T>& object)
{
	this->clear();
	for (int i = 0; i < object.get_size(); i++)
		this->push_back(object[i]);
	return *this;
}
