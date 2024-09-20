//
// Created by varga on 19/9/2024.
//

#include <ctime>
#include "TaskList.h"

using namespace std;

void TaskList::insert(Task* task) {
    if (!this->head) {
        this->head = task;
    } else {
        Task* currentNode = this->head;

        while (currentNode != nullptr) {
            if (task->date == currentNode->date) {
                if (task->time == currentNode->time) {
                    task->next = currentNode->next;
                    currentNode->next = task;
                    break;
                } else if (task->time < currentNode->time) {
                    task->next = currentNode;
                    if (currentNode == this->head) {
                        this->head = task;
                    } else {
                        // Insert in sorted order (time comparison handling)
                    }
                    break;
                }
            } else if (task->date > currentNode->date) {
                // Handle inserting by date order
            }

            currentNode = currentNode->next;
        }
    }
}

