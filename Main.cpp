#include <iostream>

using namespace std;

template <class T>
class List {
  public:
    T *head;

    List() {
      this->head = nullptr;
    }

    void insertLast(T *newNode) {
      if (this->head == nullptr) {
        this->head = newNode;
      } else {
        T *currentNode = head;
        this->recorrer(currentNode);
        currentNode->next = newNode;
      }

      ++ this->length;
    }

    void insertFirst(T *newNode) {
      newNode->next = head;
      head = newNode;
      ++ this->length;
    }

    T *get(const int index) {
      T *currentNode = this->head;
      this->recorrer(currentNode, index);
      return currentNode;
    };

    int getLength() {
      return this->length;
    }

  private:
    int length = 0;

    static void recorrer(T *currentNode) {
      while (currentNode != nullptr) {
        currentNode = currentNode->next;
      }
    }
    static void recorrer(T *currentNode, const int maxCounter) {
      int counter = 0;
      while (currentNode != nullptr && counter <= maxCounter) {
        currentNode = currentNode->next;
        counter ++;
      }
    }
};

struct TaskType {
  // Circular
  int id;
  string name;
  string description;
  TaskType* next;

  TaskType(const int id, const string & name, const string & description) {
    this->id = id;
    this->name = name;
    this->description = description;
    this->next = this;
  }
};

struct SubTask {
  // Simple
  string name;
  string comments;
  float progress;
  bool completed;
  SubTask *next;

  SubTask(const string & name, const string & comments, const float progress) {
    this->name = name;
    this->comments = comments;
    this->progress = progress;
    this->next = nullptr;

    if(this->progress == 100) {
      this->completed = true;
    } else {
      this->completed = false;
    }
  }
};

struct Task {
  // Simple
  int id;
  string description;
  string importance;
  string date;
  string time;
  TaskType* type;
  List<SubTask>* subTasks;
  Task* next;

  Task(const int id, const string & description, const string & importance, const string & date, const string & time, TaskType * type) {
    this->id = id;
    this->description = description;
    this->importance = importance;
    this->date = date;
    this->time = time;
    this->type = type;
    this->next = nullptr;

    if (this->type->name == "Estudio") {
      this->subTasks = new List<SubTask>();
    }
  }
};

struct Person {
  // Double
  int id;
  string name;
  string lastname;
  int age;
  Person* next;
  Person* prev;
  List<Task> activeTasks;
  List<Task> completedTasks;

  Person(const int id, const string & name, const string & lastname, const int age) {
    this->id = id;
    this->name = name;
    this->lastname = lastname;
    this->age = age;
    this->next = nullptr;
    this->prev = nullptr;
    this->activeTasks = List<Task>();
    this->completedTasks = List<Task>();
  }

  void insert(Person head, const int id, const string & name, const string & lastname, const int age) {
    Person *currentNode = head;

    while(currentNode != nullptr) {
      if(id == currentNode->id) throw exception();
      if(id < currentNode->id) {
        cout << "Insertando " << name;
        const auto newNode = new Person(id, name, lastname, age);
        newNode->next = currentNode;
        newNode->prev = currentNode->prev;
        currentNode->prev = newNode;
        break;
      }
      if(currentNode->next == nullptr) {
        cout << "Insertando al final";
        const auto newNode = new Person(id, name, lastname, age);
        newNode->prev = currentNode;
        currentNode->next = newNode;
      }

      currentNode = currentNode->next;
    }
  }

  Person* get(const int index) {
    Person* currentNode = this;
    int counter = 0;

    while(counter < index && currentNode != nullptr) {
      cout << "Intento: " << counter << " | " << currentNode->name;
      currentNode = currentNode->next;
      counter++;
    }

    return currentNode;
  }
};

class CircularList : public List<TaskType> {
  public:
    CircularList() {
      this->head = nullptr;
    }
};

class DoubleList: public List<Person> {
  public:
    DoubleList() {
      this->head = nullptr;
    }
};

int main() {
  auto people = Person(208620694, "Fabian", "Vargas", 19);

  people.insert(207600357, "Mauricio", "Rojas", 47);

  cout << people.get(0)->name;

  return 0;
}