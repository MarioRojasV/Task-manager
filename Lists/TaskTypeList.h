//
// Created by varga on 19/9/2024.
//

#ifndef TASKTYPELIST_H
#define TASKTYPELIST_H

#include "List.h"
#include "Structures.h"

class TaskTypeList : public List<TaskType> {
public:
    TaskTypeList();
    void insert(const string& name, const string& description);
};

#include "TaskTypeList.cpp"
#endif //TASKTYPELIST_H
