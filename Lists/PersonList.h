//
// Created by varga on 19/9/2024.
//

#ifndef PERSONLIST_H
#define PERSONLIST_H

#include "List.h"
#include "Structures.h"

class PersonList : public List<Person> {
public:
    PersonList();
    void insert(int id, const string& name, const string& lastname, int age);
    Person* remove(int id);
    [[nodiscard]] Person* get(int index) const;
    [[nodiscard]] Person* getById(int id) const;
};

#include "PersonList.cpp"
#endif //PERSONLIST_H
