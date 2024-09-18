#include <iostream>
#include <iomanip>
#include <sstream>
#include <ctime>
#include <string>

using namespace std;

struct Task;
struct SubTask;
struct Person;
struct TaskType;

template <class T>
class List {
  public:
    T *head;

    List() {
      this->head = nullptr;
      this->length = 0;
    }

    void insertLast(T* newNode) {
      if (!head) head = newNode;
      else {
        T* lastNode = get(-1);
        lastNode->next = newNode;
      }
      ++length;
    }

    void insertFirst(T* newNode) {
      newNode->next = head;
      head = newNode;
      ++length;
    }

    [[nodiscard]] T* get(int index) const {
      if (index < 0) index = length + index;
      T* currentNode = head;
      recorrer(currentNode, index);
      return currentNode;
    }

    [[nodiscard]] T* findById(int id) const {
      T* currentNode = head;
      while (currentNode) {
        if (currentNode->id == id) return currentNode;
        currentNode = currentNode->next;
      }
      return nullptr;
    }

    T* removeById(int id) {
      if (!head) return nullptr;

      if (head->id == id) {
        T* removedNode = head;
        head = head->next;
        --length;
        return removedNode;
      }

      T* currentNode = head;
      while (currentNode->next) {
        if (currentNode->next->id == id) {
          T* removedNode = currentNode->next;
          currentNode->next = currentNode->next->next;
          --length;
          return removedNode;
        }
        currentNode = currentNode->next;
      }

      return nullptr;
    }

    [[nodiscard]] string toString() const {
      string rep = "{ ";
      T* currentNode = head;
      while (currentNode) {
        rep += currentNode->name;
        if (currentNode->next) rep += ", ";
        currentNode = currentNode->next;
      }
      rep += " }";
      return rep;
    }

    [[nodiscard]] int getLength() const { return this->length; }

  protected:
    int length{};

    static void recorrer(T*& currentNode, int const maxCounter) {
      int counter = 0;
      while (currentNode && counter < maxCounter) {
        currentNode = currentNode->next;
        ++counter;
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
  tm date{};
  tm time{};
  TaskType* type;
  List<SubTask> subTasks;
  Task* next;

  Task(const int id, const string & description, const string & importance, const string & date, const string & time, TaskType * type) {
    this->id = id;
    this->description = description;
    this->importance = importance;
    this->type = type;
    this->next = nullptr;
    this->date = {};
    this->time = {};

    if (this->type->name == "Estudio") {
      this->subTasks = List<SubTask>();
    }

    setDate(date);
    setTime(time);
  }

  void setDate(const string & date) {
    istringstream dateStream(date);
    dateStream >> get_time(&this->date, "%d-%m-%Y");
    if (dateStream.fail()) throw runtime_error("Formato de fecha incorrecto. (dd-mm-YYYY)");
  }

  void setTime(const string & time) {
    istringstream timeStream(time);
    timeStream >> get_time(&this->time, "%H:%M:%S");
    if (timeStream.fail()) throw runtime_error("Formato de hora incorrecto. (HH:MM:SS)");
  }

  [[nodiscard]] auto getDate() const {
    return put_time(&this->date, "%d-%m-%Y");
  }

  [[nodiscard]] auto getTime() const  {
    return put_time(&this->time, "%H:%M:%S");
  }
};

class TaskList: public List<Task> {
public:
  TaskList() = default;

  void insert(Task* task) {
    if (!this->head) this->head = task;

    else {
      Task* currentNode = this->head;

      while (currentNode != nullptr) {

        if (task->date == currentNode->date) {
          if (task->time == currentNode->time) {
            task->next = currentNode->next;
            currentNode->next = task;
          } else if {

          }

        }

        if (task->date > currentNode->date) {

        }

        currentNode = currentNode->next;
      }
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

class TaskTypeList : public List<TaskType> {
  public:
    TaskTypeList() {
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
          auto* const newNode = new TaskType(currentNode->id + 1, name, description);
          newNode->next = this->head;
          currentNode->next = newNode;
          this->length++;
          break;
        }
        currentNode = currentNode->next;
      }
    }
};

class PersonList: public List<Person> {
  public:
    PersonList() {
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
          --this->length;
          return currentNode;
        }

        currentNode = currentNode->next;
      }

      return nullptr;
    }

    [[nodiscard]] Person* get(const int index) const {
      if (index >= this->getLength()) return nullptr;

      Person* currentNode = this->head;
      for(int i = 0; i < index; i++) {
        currentNode = currentNode->next;
      }

      return currentNode;
    }

    [[nodiscard]] Person* getById(const int id) const {
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

auto people = PersonList();
auto taskTypes = TaskTypeList();

void addTask(const int personId, Task* task) {
    Person* person = people.findById(personId);
    if (!person) throw runtime_error("Persona no encontrada");
    person->activeTasks.insertLast(task);
}

void addSubTask(const int personId, const int taskIndex, SubTask* subTask) {
    Person* person = people.findById(personId);
    if (!person) throw runtime_error("Persona no encontrada");
    Task* task = person->activeTasks.get(taskIndex);
    if (!task) throw runtime_error("Tarea no encontrada");

    if (task->type->name == "Estudio") {
        task->subTasks.insertLast(subTask);
    } else {
        delete subTask;
    }
}

void modifyActiveTask(const int personId, const int taskId, const string& newDate, const string& newTime) {
    Person* person = people.findById(personId);
    if (!person) throw runtime_error("Persona no encontrada");
    Task* task = person->activeTasks.get(taskId - 1);
    if (!task) throw runtime_error("Tarea no encontrada");

    task->setDate(newDate);
    task->setTime(newTime);
}

void completeTask(const int personId, const int taskId) {
    Person* person = people.findById(personId);
    if (!person) throw runtime_error("Persona no encontrada");
    Task* task = person->activeTasks.removeById(taskId);
    if (!task) throw runtime_error("Tarea no encontrada");

    person->completedTasks.insertLast(task);
}

void completeSubTask(const int personId, const int taskId, const int subTaskIndex) {
    Person* person = people.findById(personId);
    if (!person) throw runtime_error("Persona no encontrada");
    Task* task = person->activeTasks.findById(taskId);
    if (!task) throw runtime_error("Tarea no encontrada");

    SubTask* subTask = task->subTasks.get(subTaskIndex);
    if (!subTask) throw runtime_error("Subtarea no encontrada");

    subTask->completed = true;
    subTask->progress = 100;
}

void subTaskProgress(const int personId, const int taskId, const int subTaskIndex, const float newProgress) {
    Person* person = people.findById(personId);
    if (!person) throw runtime_error("Persona no encontrada");
    Task* task = person->activeTasks.findById(taskId);
    if (!task) throw runtime_error("Tarea no encontrada");

    SubTask* subTask = task->subTasks.get(subTaskIndex);
    if (!subTask) throw runtime_error("Subtarea no encontrada");

    subTask->progress = newProgress;
}

void cargarDatos() {
  cout << "Cargando datos" << endl;

  taskTypes.insert("Estudio", "Tareas y examenes");
  taskTypes.insert("Hogar", "Tareas de la casa");

  people.insert(208620694, "Fabian", "Vargas", 19);
  people.insert(208620696, "Juan", "Perez", 20);
  people.insert(208620693, "Pedro", "Gonzalez", 21);
  people.insert(208620695, "Maria", "Lopez", 22);

  addTask(208620694, new Task(1, "Examenes", "Medio", "01-09-2024", "12:00:00", taskTypes.get(0)));
  addTask(208620694, new Task(2, "Proyecto Estructuras", "Alto", "20-09-2024", "08:00:00", taskTypes.get(0)));
  addSubTask(208620694, 0, new SubTask("Calculo", "Estudiar ultimo tema", 65.3));
  addSubTask(208620694, 1, new SubTask("Listas", "Listas de datos", 90));
}

void testing() {
  cout << "Testeando funciones" << endl;
  cout << people.get(0)->name << endl;
  cout << people.get(1)->name << endl;
  cout << people.get(2)->name << endl;
  cout << people.get(3)->name << endl;

  cout << people.getById(208620694)->name << endl;
  cout << people.getById(208620696)->name << endl;
  cout << people.getById(208620693)->name << endl;
  cout << people.getById(208620695)->name << endl;

  cout << people.remove(208620695)->name << endl;
  cout << people.getById(208620695) << endl; // Retora null/0

  cout << people.getById(208620694)->activeTasks.get(0)->subTasks.get(0)->name << endl;
  cout << people.getById(208620694)->activeTasks.get(0)->getTime() << endl;
  modifyActiveTask(208620694, 1, "02-09-2024", "12:30:00");
  cout << people.getById(208620694)->activeTasks.get(0)->getTime() << endl;

  completeTask(208620694, 1);
  cout << people.getById(208620694)->activeTasks.getLength() << endl; // Se espera 0 porque se completo la unica tarea que habia;
  cout << people.getById(208620694)->completedTasks.get(0)->description << endl;

  cout << people.getById(208620694)->completedTasks.get(0)->subTasks.toString();
}

int main() {
  cargarDatos();
  testing();

  return 0;
}