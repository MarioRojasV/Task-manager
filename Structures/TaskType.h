//
// Created by fabian on 19/9/2024.
//

#ifndef TASKTYPE_H
#define TASKTYPE_H

struct TaskType {
    int id;
    string name;
    string description;
    TaskType* next;

    TaskType(int id, const string & name, const string & description);
};

#include "TaskType.cpp"
#endif //TASKTYPE_H
