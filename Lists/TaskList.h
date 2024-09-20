//
// Created by varga on 19/9/2024.
//

#ifndef TASKLIST_H
#define TASKLIST_H

#include "Structures.h"

class TaskList : public List<Task> {
public:
    TaskList() = default;
    void insert(Task* task);
};

#include "TaskList.cpp"
#endif // TASKLIST_H

