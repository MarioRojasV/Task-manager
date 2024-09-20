//
// Created by fabian on 19/9/2024.
//

#ifndef PERSON_H
#define PERSON_H

#include "../Lists/TaskList.h"

struct Person {
    int id;
    string name;
    string lastname;
    int age;
    Person* next;
    Person* prev;
    TaskList activeTasks;
    TaskList completedTasks;

    Person(int id, const string & name, const string & lastname, int age);
};

#include "Person.cpp"
#endif //PERSON_H
