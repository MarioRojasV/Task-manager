//
// Created by fabian on 19/9/2024.
//

#ifndef SUBTASK_H
#define SUBTASK_H

struct SubTask {
    string name{};
    string comments{};
    float progress;
    bool completed;
    SubTask *next;

    SubTask(const string & name, const string & comments, float progress);
};

#include "SubTask.cpp"
#endif //SUBTASK_H
