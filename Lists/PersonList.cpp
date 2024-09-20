//
// Created by varga on 19/9/2024.
//

#include "PersonList.h"

PersonList::PersonList() {
    this->head = nullptr;
}

void PersonList::insert(const int id, const string& name, const string& lastname, const int age) {
    if (this->head == nullptr) {
        this->head = new Person(id, name, lastname, age);
        this->length++;
        return;
    }

    if (id < this->head->id) {
        const auto newNode = new Person(id, name, lastname, age);
        newNode->next = this->head;
        this->head->prev = newNode;
        this->head = newNode;
        this->length++;
        return;
    }

    Person* currentNode = this->head;

    while (currentNode != nullptr) {
        if (id == currentNode->id) throw std::exception();

        if (id < currentNode->id) {
            const auto newNode = new Person(id, name, lastname, age);
            newNode->next = currentNode;
            newNode->prev = currentNode->prev;
            currentNode->prev->next = newNode;
            currentNode->prev = newNode;
            this->length++;
            break;
        }

        if (currentNode->next == nullptr) {
            const auto newNode = new Person(id, name, lastname, age);
            newNode->prev = currentNode;
            currentNode->next = newNode;
            ++this->length;
            break;
        }

        currentNode = currentNode->next;
    }
}

Person* PersonList::remove(int id) {
    Person* currentNode = this->head;

    while (currentNode != nullptr) {
        if (currentNode->id == id) {
            currentNode->prev->next = currentNode->next;
            currentNode->next->prev = currentNode->prev;
            --this->length;
            return currentNode;
        }

        currentNode = currentNode->next;
    }

    return nullptr;
}

Person* PersonList::get(int index) const {
    if (index >= this->getLength()) return nullptr;

    Person* currentNode = this->head;
    for (int i = 0; i < index; i++) {
        currentNode = currentNode->next;
    }

    return currentNode;
}

Person* PersonList::getById(int id) const {
    Person* currentNode = this->head;

    while (currentNode != nullptr) {
        if (currentNode->id == id) return currentNode;
        if (currentNode->id > id) return nullptr;
        currentNode = currentNode->next;
    }

    return nullptr;
}