#include "List.h"
#include <iostream>

template <class T>
List<T>::List() {
    this->head = nullptr;
    this->length = 0;
}

template <class T>
void List<T>::insertLast(T* newNode) {
    if (!head) head = newNode;
    else {
        T* lastNode = get(-1);
        lastNode->next = newNode;
    }
    ++length;
}

template <class T>
void List<T>::insertFirst(T* newNode) {
    newNode->next = head;
    head = newNode;
    ++length;
}

template <class T>
T* List<T>::get(int index) const {
    if (index < 0) index = length + index;
    T* currentNode = head;
    recorrer(currentNode, index);
    return currentNode;
}

template <class T>
T* List<T>::findById(int id) const {
    T* currentNode = head;
    while (currentNode) {
        if (currentNode->id == id) return currentNode;
        currentNode = currentNode->next;
    }
    return nullptr;
}

template <class T>
T* List<T>::removeById(int id) {
    if (!head) return nullptr;

    if (head->id == id) {
        T* removedNode = head;
        head = head->next;
        --length;
        return removedNode;
    }

    T* currentNode = head;
    while (currentNode->next) {
        if (currentNode->next->id == id) {
            T* removedNode = currentNode->next;
            currentNode->next = currentNode->next->next;
            --length;
            return removedNode;
        }
        currentNode = currentNode->next;
    }

    return nullptr;
}

template <class T>
string List<T>::toString() const {
    string rep = "{ ";
    T* currentNode = head;
    while (currentNode) {
        rep += currentNode->name;
        if (currentNode->next) rep += ", ";
        currentNode = currentNode->next;
    }
    rep += " }";
    return rep;
}

template <class T>
int List<T>::getLength() const { return this->length; }

template <class T>
void List<T>::recorrer(T*& currentNode, int const maxCounter) {
    int counter = 0;
    while (currentNode && counter < maxCounter) {
        currentNode = currentNode->next;
        ++counter;
    }
}
