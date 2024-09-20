//
// Created by varga on 19/9/2024.
//

#include "TaskTypeList.h"

TaskTypeList::TaskTypeList() {
    this->head = nullptr;
}

void TaskTypeList::insert(const string& name, const string& description) {
    if (this->head == nullptr) {
        this->head = new TaskType(1, name, description);
        this->head->next = this->head;
        return;
    }

    TaskType* currentNode = this->head;

    while (true) {
        if (currentNode->next == this->head) {
            auto* const newNode = new TaskType(currentNode->id + 1, name, description);
            newNode->next = this->head;
            currentNode->next = newNode;
            this->length++;
            break;
        }
        currentNode = currentNode->next;
    }
}