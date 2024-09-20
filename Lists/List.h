#ifndef LIST_H
#define LIST_H

#include <string>
using namespace std;

template <class T>
class List {
public:
    T *head;

    List();

    void insertLast(T* newNode);
    void insertFirst(T* newNode);

    [[nodiscard]] T* get(int index) const;
    [[nodiscard]] T* findById(int id) const;

    T* removeById(int id);

    [[nodiscard]] string toString() const;
    [[nodiscard]] int getLength() const;

protected:
    int length{};

    static void recorrer(T*& currentNode, int const maxCounter);
};

#include "List.cpp" // Include implementation for templates
#endif // LIST_H
