#ifndef LINKEDLIST_H
#define LINKEDLIST_H


#include "Arduino.h"


namespace Gib {
	template <class T>
	class LinkedListNode {
	private:
		T& data;
		LinkedListNode<T>* nextNode = nullptr;
	public:
		LinkedListNode(T& obj) : data{obj} {};
		~LinkedListNode();

		const unsigned short childCount();

		void enqueue(T& obj);
		LinkedListNode<T>* dequeue();
		const bool remove(const T& o);

		T& getData() {return data;}
		LinkedListNode<T>* getNextNode() {return nextNode;}
		void setNextNode(LinkedListNode<T>* n) {nextNode = n;} //Be careful! Can easily leak memory.
	};
}


template <class T>
const unsigned short Gib::LinkedListNode<T>::childCount() {
	if(!nextNode) {
		return 1;
	} else {
		return nextNode->childCount() + 1;
	}
}


template <class T>
void Gib::LinkedListNode<T>::enqueue(T& obj) {
	if(nextNode == nullptr) {
		nextNode = new Gib::LinkedListNode<T>(obj); //TODO: Convert to stack
	} else {
		nextNode->enqueue(obj);
	}
}


template <class T>
Gib::LinkedListNode<T>::~LinkedListNode() {
	delete nextNode;
}


template <class T>
Gib::LinkedListNode<T>* Gib::LinkedListNode<T>::dequeue() {
	if(!nextNode->getNextNode()) {
		LinkedListNode<T>* tempReturn = nextNode;
		nextNode = nullptr;
		return tempReturn;
	}

	return nextNode->dequeue();
}



template <class T>
const bool Gib::LinkedListNode<T>::remove(const T& o) {
	if(!nextNode) {
		return false;
	}

	if(o == nextNode->getData()) {
		LinkedListNode<T>* oldChildNode = getNextNode();
		nextNode = oldChildNode->getNextNode();
		oldChildNode->setNextNode(nullptr);
		delete oldChildNode;
		return true;
	} else {
		return nextNode->remove(o);
	}
}



namespace Gib {
	template <class T>
	class LinkedList {
	private:
		Gib::LinkedListNode<T>* head;
	public:
		~LinkedList();

		const unsigned short size();

		Gib::LinkedListNode<T>* getHead() {return head;}

		void enqueue(T& obj);
		T* dequeue();
		const bool remove(const T& obj);
	};
}


template <class T>
Gib::LinkedList<T>::~LinkedList() {
	delete head;
}


template <class T>
const unsigned short Gib::LinkedList<T>::size() {
	if(head == nullptr) {
		return 0;
	}

	return head->childCount();
}


template <class T>
void Gib::LinkedList<T>::enqueue(T& obj) {
	if(head == nullptr) {
		head = new Gib::LinkedListNode<T>(obj); //TODO: Convert to stack
	} else {
		head->enqueue(obj);
	}
}


template <class T>
T* Gib::LinkedList<T>::dequeue() {
	if(head == nullptr) {
		return nullptr;
	}

	if(!head->getNextNode()) {
		Gib::LinkedListNode<T>* tempReturn = head;
		head = nullptr;
		return &tempReturn->getData();
	}

	return &head->dequeue()->getData();
}


template <class T>
const bool Gib::LinkedList<T>::remove(const T& o) {
	if(!head) {
		return false;
	}

	if(o == head->getData()) {
		LinkedListNode<T>* oldHead = head;
		head = oldHead->getNextNode();
		oldHead->setNextNode(nullptr);
		delete oldHead;
		return true;
	} else {
		if(!head->getNextNode()) {
			return false;
		}

		if(o == head->getNextNode()->getData()) {
			LinkedListNode<T>* oldChildNode = head->getNextNode();
			head->setNextNode(oldChildNode->getNextNode());
			oldChildNode->setNextNode(nullptr);
			delete oldChildNode;
			return true;
		}

		return head->remove(o);
	}
}

#endif