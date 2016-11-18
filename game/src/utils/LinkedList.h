#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include<iostream>

// 0 is substitude of NULL.

template<typename T>
class Node {
	public:
		Node<T>* next;
		T value;
		Node(T val) : value(val), next(0) {}
};

template<typename T>
class LinkedList {
	private:
		Node<T>* head;
		Node<T>* last;
		Node<T>* current;
		int size;
		Node<T>* getElementByIndex(int index, char* err_msg);
	public:
		LinkedList() : head(0), last(0) , current(0), size(0) {}
		void add(T val);
		T get(int index);
		T get();
		T* getPtr();
		int getSize();
		void resetCurrent();
		void set(int index, T value);
};

template<typename T>
Node<T>* LinkedList<T>::getElementByIndex(int index, char* err_msg) {
	int i = 0;
	Node<T>* node;
	for(node = head; i < index && node != 0; i++) node = node->next;
	if(node == 0) {
		std::cerr << err_msg << "\nindex: " << index << std::endl;
		std::exit(EXIT_FAILURE);
	}
	return node;
}

template<typename T>
void LinkedList<T>::add(T val) {
	Node<T>* node = new Node<T>(val);
	size++;
	if(head == 0) {
		head = last = current = node;
		size = 0;
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
	if(current->next != 0) current = current->next;
	return current->value;
}

template<typename T>
T* LinkedList<T>::getPtr() {
	Node<T>* node = current;
	if(current->next != 0) current = current->next;
	return &(current->value);
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
