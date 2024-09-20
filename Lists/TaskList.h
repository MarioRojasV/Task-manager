//
// Created by varga on 19/9/2024.
//

#ifndef TASKLIST_H
#define TASKLIST_H

#include "List.h"
#include "../Structures/Task.h"

class TaskList : public List<Task> {
public:
    TaskList() = default;
    void insert(Task* task);
private:
    static bool compareDates(const tm& lhs, const tm& rhs);
    static bool compareTimes(const tm& lhs, const tm& rhs);
    static bool isSameDateTime(const tm& date1, const tm& time1, const tm& date2, const tm& time2);
};

#include "TaskList.cpp"
#endif // TASKLIST_H

