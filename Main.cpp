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

  protected:
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
    this->next = nullptr;
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
};

class CircularList : public List<TaskType> {
  public:
    CircularList() {
      this->head = nullptr;
    }

    void insert(const string & name, const string & description) {
      if (this->head == nullptr) {
        this->head = new TaskType(1, name, description);
        this->head->next = this->head;
        return;
      }

      TaskType *currentNode = this->head;

      while (true) {
        if (currentNode->next == this->head) {
          const auto newNode = new TaskType(currentNode->id + 1, name, description);
          newNode->next = this->head;
          currentNode->next = newNode;
          this->length++;
          break;
        }
        currentNode = currentNode->next;
      }
    }
};

class DoubleList: public List<Person> {
  public:
    DoubleList() {
      this->head = nullptr;
    }

    void insert(const int id, const string & name, const string & lastname, const int age) {
      if (this->head == nullptr) {
        this->head = new Person(id, name, lastname, age);
        this->length++;
        return;
      }

       if(id < this->head->id) {
         const auto newNode = new Person(id, name, lastname, age);
         newNode->next = this->head;
         this->head->prev = newNode;
         this->head = newNode;
         this->length++;
         return;
       }

      Person *currentNode = this->head;

      while(currentNode != nullptr) {
        if(id == currentNode->id) throw exception();

        if(id < currentNode->id) {
          const auto newNode = new Person(id, name, lastname, age);
          newNode->next = currentNode;
          newNode->prev = currentNode->prev;
          currentNode->prev->next = newNode;
          currentNode->prev = newNode;
          this->length++;
          break;
        }

        if(currentNode->next == nullptr) {
          const auto newNode = new Person(id, name, lastname, age);
          newNode->prev = currentNode;
          currentNode->next = newNode;
          ++ this->length;
          break;
        }

        currentNode = currentNode->next;
      }
    }

    Person* remove(const int id) {
      Person* currentNode = this->head;

      while (currentNode != nullptr) {
        if (currentNode->id == id) {
          currentNode->prev->next = currentNode->next;
          currentNode->next->prev = currentNode->prev;
          return currentNode;
        }

        currentNode = currentNode->next;
      }

      return nullptr;
    }

    Person* get(const int index) {
      if (index >= this->getLength()) return nullptr;

      Person* currentNode = this->head;
      for(int i = 0; i < index; i++) {
        currentNode = currentNode->next;
      }

      return currentNode;
    }

    Person* getById(const int id) {
      Person* currentNode = this->head;

      while(currentNode != nullptr) {
        if(currentNode->id == id) return currentNode;
        if(currentNode->id > id) return nullptr;
        currentNode = currentNode->next;
      }

      return  nullptr;
    }
};



// Tests

auto people = DoubleList();
auto taskTypes = CircularList();

void cargarDatos() {
  cout << "Cargando datos" << endl;

  people.insert(208620694, "Fabian", "Vargas", 19);
  people.insert(208620696, "Juan", "Perez", 20);
  people.insert(208620693, "Pedro", "Gonzalez", 21);
  people.insert(208620695, "Maria", "Lopez", 22);

  taskTypes.insert("Universidad", "Tareas y examenes");
  taskTypes.insert("Hogar", "Tareas de la casa");
}

int main() {
  cargarDatos();
  cout << people.get(0)->name << endl;
  cout << people.get(1)->name << endl;
  cout << people.get(2)->name << endl;
  cout << people.get(3)->name << endl;

  cout << people.getById(208620694)->name << endl;
  cout << people.getById(208620696)->name << endl;
  cout << people.getById(208620693)->name << endl;
  cout << people.getById(208620695)->name << endl;

  cout << people.remove(208620695)->name << endl;
  cout << people.getById(208620695) << endl; // Retora null

  return 0;
}