//
// Created by fabian on 19/9/2024.
//

#ifndef TASK_H
#define TASK_H

#include "SubTask.h"
#include "TaskType.h"

struct Task {
    int id{};
    string description;
    string importance;
    tm date{};
    tm time{};
    TaskType* type{};
    List<SubTask> subTasks{};
    Task* next;

    Task(const string & description, const string & importance, const string & date, const string & time, TaskType * type);
    void setDate(const string & date);
    void setTime(const string & time);
    [[nodiscard]] auto getDate() const;
    [[nodiscard]] auto getTime() const;
};

#include "Task.cpp"
#endif //TASK_H
