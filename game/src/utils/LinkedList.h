#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include<iostream>

using namespace std;

template<typename T>
class Node {
	public:
		Node<T>* next;
		T value;
		Node(T val) : next(nullptr), value(val) {}
};

template<typename T>
class LinkedList {
	private:
		Node<T>* head;
		Node<T>* last;
		Node<T>* current;
		int size;
		Node<T>* getElementByIndex(int index, string err_msg);
	public:
		LinkedList() : head(nullptr), last(nullptr) , current(nullptr), size(0) {}
		~LinkedList() {
			Node<T>* tmp;
			if(head == nullptr) return;
			for(tmp = head; tmp->next != nullptr; tmp = tmp->next) delete tmp;
		}
		void add(T val);
		T get(int index);
		T get();
		T* getPtr();
		T* getPtr(int index);
		int getSize();
		void resetCurrent();
		void set(int index, T value);
};

template<typename T>
Node<T>* LinkedList<T>::getElementByIndex(int index, string err_msg) {
	int i = 0;
	Node<T>* node;
	for(node = head; i < index && node != nullptr; i++) node = node->next;
	if(node == nullptr) {
		cerr << err_msg << "\nindex: " << index << endl;
		exit(EXIT_FAILURE);
	}
	return node;
}

template<typename T>
void LinkedList<T>::add(T val) {
	Node<T>* node = new Node<T>(val);
	size++;
	if(head == nullptr) {
		head = last = current = node;
		return ;
	}
	last->next = node;
	last = node;
	return ;
}

template<typename T>
T LinkedList<T>::get(int index) {
	Node<T>* node = getElementByIndex(index, "Index out of length in get().");
	return node->value;
}

template<typename T>
T LinkedList<T>::get() {
	Node<T>* node = current;
	if(current->next != nullptr) current = current->next;
	return node->value;
}

template<typename T>
T* LinkedList<T>::getPtr() {
	Node<T>* node = current;
	if(current->next != nullptr) current = current->next;
	return &(node->value);
}

template<typename T>
T* LinkedList<T>::getPtr(int index) {
	Node<T>* node = getElementByIndex(index, "Index out of length in get().");
	return &(node->value);
}

template<typename T>
int LinkedList<T>::getSize() { return size; }

template<typename T>
void LinkedList<T>::resetCurrent() { current = head; }

template<typename T>
void LinkedList<T>::set(int index, T value) {
	Node<T>* node = getElementByIndex(index, "Index out of length in set().");
	node->value = value;
}

#endif
