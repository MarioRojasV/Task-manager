#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <windows.h>
#include <cstdlib>

#include "Structures/Person.h"
#include "Structures/Task.h"
#include "Structures/SubTask.h"
#include "Lists/List.h"
#include "Lists/TaskTypeList.h"
#include "Lists/PersonList.h"
#include "utils/utils.h"

using namespace std;

auto people = PersonList();
auto taskTypes = TaskTypeList();
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

/**
 * @brief Agrega una tarea activa a una persona.
 *
 * Busca a la persona por su ID y agrega una tarea a su lista de tareas activas.
 *
 * @param personId Identificador de la persona a la que se le agregará la tarea.
 * @param task Puntero a la tarea que se va a agregar.
 * @throws runtime_error Si la persona no se encuentra.
 * @author fabian
 */
void addTask(const int personId, Task* task) {
    Person* person = people.findById(personId);
    if (!person) throw runtime_error("Persona no encontrada");
    person->activeTasks.insertLast(task);
}

/**
 * @brief Agrega una subtarea a una tarea específica de una persona.
 *
 * Busca a la persona y su tarea por ID e índice, respectivamente. Si la tarea es del tipo "Estudio",
 * la subtarea se agrega a la lista de subtareas de la tarea. Si no, la subtarea se elimina.
 *
 * @param personId Identificador de la persona.
 * @param taskIndex Índice de la tarea dentro de las tareas activas.
 * @param subTask Puntero a la subtarea que se va a agregar.
 * @throws runtime_error Si la persona o la tarea no se encuentran.
 * @author fabian
 */
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

/**
 * @brief Modifica la fecha y hora de una tarea activa de una persona.
 *
 * Busca la persona y la tarea por sus IDs y modifica la fecha y hora de la tarea.
 *
 * @param personId Identificador de la persona.
 * @param taskId Identificador de la tarea.
 * @param newDate Nueva fecha en formato "dd-mm-YYYY".
 * @param newTime Nueva hora en formato "HH:MM:SS".
 * @throws runtime_error Si la persona o la tarea no se encuentran.
 * @author fabian
 */
void modifyActiveTask(const int personId, const int taskId, const string& newDate, const string& newTime) {
    Person* person = people.findById(personId);
    if (!person) throw runtime_error("Persona no encontrada");
    Task* task = person->activeTasks.get(taskId - 1);
    if (!task) throw runtime_error("Tarea no encontrada");

    task->setDate(newDate);
    task->setTime(newTime);
}

/**
 * @brief Marca una tarea activa como completada y la mueve a la lista de tareas completadas.
 *
 * Busca y elimina una tarea activa de una persona y la mueve a la lista de tareas completadas.
 *
 * @param personId Identificador de la persona.
 * @param taskId Identificador de la tarea.
 * @throws runtime_error Si la persona o la tarea no se encuentran.
 * @author fabian
 */
void completeTask(const int personId, const int taskId) {
    Person* person = people.findById(personId);
    if (!person) throw runtime_error("Persona no encontrada");
    Task* task = person->activeTasks.removeById(taskId);
    if (!task) throw runtime_error("Tarea no encontrada");

    person->completedTasks.insertLast(task);
}

/**
 * @brief Marca una subtarea de una tarea activa como completada.
 *
 * Busca la persona, la tarea y la subtarea por sus IDs y las marca como completadas.
 *
 * @param personId Identificador de la persona.
 * @param taskId Identificador de la tarea.
 * @param subTaskIndex Índice de la subtarea dentro de la tarea.
 * @throws runtime_error Si la persona, la tarea o la subtarea no se encuentran.
 * @author fabian
 */
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

/**
 * @brief Modifica el progreso de una subtarea específica de una tarea activa de una persona.
 *
 * Busca la persona, la tarea y la subtarea por sus IDs e índice, respectivamente, y modifica el progreso de la subtarea.
 *
 * @param personId Identificador de la persona.
 * @param taskId Identificador de la tarea.
 * @param subTaskIndex Índice de la subtarea dentro de la tarea.
 * @param newProgress Nuevo progreso de la subtarea (0-100).
 * @throws runtime_error Si la persona, la tarea o la subtarea no se encuentran.
 * @author fabian
 */
void subTaskProgress(const int personId, const int taskId, const int subTaskIndex, const float newProgress) {
    Person* person = people.findById(personId);
    if (!person) throw runtime_error("Persona no encontrada");
    Task* task = person->activeTasks.findById(taskId);
    if (!task) throw runtime_error("Tarea no encontrada");

    SubTask* subTask = task->subTasks.get(subTaskIndex);
    if (!subTask) throw runtime_error("Subtarea no encontrada");

    subTask->progress = newProgress;
}

/**
 * @brief Carga datos iniciales de personas y tipos de tareas para pruebas.
 *
 * Carga algunos datos iniciales de personas, tipos de tareas y tareas para realizar pruebas de las funcionalidades
 *
 * @author fabian.
 */
void cargarDatos() {
  cout << "Cargando datos" << endl;

  taskTypes.insert("Estudio", "Tareas y examenes");
  taskTypes.insert("Hogar", "Tareas de la casa");
  taskTypes.insert("Trabajo", "Tareas laborales");

  people.insert(208620694, "Fabian", "Vargas", 19);
  people.insert(208620696, "Juan", "Perez", 20);
  people.insert(208620693, "Pedro", "Gonzalez", 21);
  people.insert(208620695, "Maria", "Lopez", 22);

  addTask(208620694, new Task(1, "Examenes", "Medio", "01-09-2024", "12:00:00", taskTypes.get(0)));
  addTask(208620694, new Task(2, "Proyecto Estructuras", "Alto", "20-09-2024", "08:00:00", taskTypes.get(0)));
  addTask(208620696, new Task(3, "Tareas de la casa", "Bajo", "10-09-2024", "18:00:00", taskTypes.get(1)));
  addTask(208620693, new Task(3, "Tareas de la casa", "Bajo", "10-09-2024", "18:00:00", taskTypes.get(1)));
  addSubTask(208620694, 0, new SubTask("Calculo", "Estudiar ultimo tema", 65.3));
  addSubTask(208620694, 1, new SubTask("Listas", "Listas de datos", 90));
}

/**
 * @brief Realiza pruebas sobre las funciones implementadas para verificar su correcto funcionamiento.
 *
 * Ejecuta una serie de pruebas sobre las operaciones de inserción, modificación y completado de tareas y subtareas.
 *
 * @author fabian
 */
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

/**
 * @brief Encuentra la pesona con mas tareas activas.
 * 1. ¿Cuál es la persona que tiene más tareas activas?
 * Recorre toda la lista de personas y almacena la cantidad de tareas activas, si hay una cantidad mayor, la actualizara
 * y guardara el indice de la persona en la lista para ser mostrado posteriormente.
 *
 * @author Joseph
 */
void showMostActiveTasksPerson(int index=0,int maxTasks=0,int selectedIndex=0){
    if(people.get(index)==nullptr){
        if (index==0){
            cout << "No hay personas registradas" << endl;
        }else{
            cout << "Persona con mas tareas activas: " << people.get(selectedIndex)->name << endl;
            cout << "Tareas registradas: " << people.get(selectedIndex)->activeTasks.getLength() << endl;
        }return;
    }else{
        int tasks = people.get(index)->activeTasks.getLength();
        if (tasks>maxTasks){
            selectedIndex = index;
            maxTasks = tasks;
        }
        showMostActiveTasksPerson(index+1,maxTasks,selectedIndex);
    }
}

/**
 * @brief Muestra la persona con mayor cantidad de tareas de un tipo especificado.
 * 2. ¿Cuál es la persona que tiene más tareas activas de un tipo X?
 * .
 *
 * @author Joseph
 */
string selectTask(int opt = 0) {
    if (taskTypes.getLength() == 0) {
        return "empty";
    }
    string strOpt;
    cout << "Selecciona el tipo de tarea:\n(Muevete con las flechas (up & down); presiona ESPACIO para seleccionar)\n";
    COORD posText = getCursorPosition(hConsole);

    bool selection = false;
    while (!selection) {
        // Actualizar y mostrar la opción actual
        strOpt = taskTypes.get(opt)->name;
        moveCursor(15, posText.Y, hConsole);
        deleteLine(hConsole);
        moveCursor(posText.X, posText.Y, hConsole);
        cout << "Tipo de tarea: " << strOpt <<endl;

        // Verificar entradas de teclado
        if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
            return "empty";
        } else if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
            opt++;
            while (GetAsyncKeyState(VK_DOWN) & 0x8000) { Sleep(50); }
        } else if (GetAsyncKeyState(VK_UP) & 0x8000) {
            opt--;
            while (GetAsyncKeyState(VK_UP) & 0x8000) { Sleep(50); }
        } else if (GetAsyncKeyState(VK_SPACE) & 0x8000) {
            while (GetAsyncKeyState(VK_SPACE) & 0x8000) { Sleep(50); }
            FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
            selection = true;
            break;
        }
        if (opt < 0) { opt = taskTypes.getLength(); }
        else if (opt > taskTypes.getLength()) { opt = 0; }

        Sleep(10); 
    }
    return strOpt;
}


void showMostSpecificActiveTasksPerson(){
  string respuesta=selectTask();
  if (respuesta!="empty"){
    int index=0;
    int maxTasks=0;
    int selectedIndex=0;
    while(people.get(index)!=nullptr){
      int tasks = 0;
      for (int i = 0; i < people.get(index)->activeTasks.getLength(); i++) {
        if (people.get(index)->activeTasks.get(i)->type->name == respuesta) {
          tasks++;
        }
      }
      if (tasks > maxTasks) {
        selectedIndex = index;
        maxTasks = tasks;
      }
      index++;
    }
    if (maxTasks > 0) {
      cout << "Persona con mas tareas activas de tipo " << respuesta << ": " << people.get(selectedIndex)->name << endl;
      cout << "Tareas registradas: " << maxTasks << endl;
    }
    else {
      cout << "No hay tareas activas de tipo " << respuesta << endl;
    }
  }
  else{
    cout << "No existe ningun tipo de tarea en este momento.";
  }
}

void queryMenu(){
  COORD pos = getCursorPosition(hConsole);
  int option=0;
  while (true) {
    system("cls");
    cout << "Consultas\n";
    cout << "1. Cual es la persona que tiene mas tareas activas?\n";
    cout << "2. Cual es la persona que tiene mas tareas activas de un tipo X?\n";
    cout << "3. Que tipo de tarea es el mas comun? En caso de empate indicarlo.\n";
    cout << "4. Cual es la persona que tiene mas tareas vencidas de un tipo X dado una fecha Y?\n";
    cout << "5. Cual es el tipo de tareas mas comun que se vence sin completarse, dado una fecha Y?\n";
    cout << "6. Cual es el tipo de importancia mas usado por las personas?\n";
    cout << "7. Que es el tipo de tarea mas comun en tareas activas de importancia media?\n";
    cout << "8. Que es el tipo de tarea mas comun en tareas realizadas de importancia Alta?\n";
    cout << "9. Salir\n";
    cout << "Seleccione una opcion: ";
    cin >> option;
    switch (option) {
      case 1:
        showMostActiveTasksPerson();
        cout << "Presione enter para continuar...";
        waitEnter();
        break;
      case 2:
        showMostSpecificActiveTasksPerson();
        cout << "Presione enter para continuar...";
        waitEnter();
        break;
      case 9:
        return;
      default:
        verifyInputType();
        moveCursorAndDeleteLine(23, pos.Y, hConsole);
        moveCursor(pos.X, pos.Y, hConsole);
        break;
    }
  }
}

void menu() {
  int option=0;
  while(true){
    system("cls");
    cout << "Menu" << endl;
    cout << "1. Actualizacion de informacion" << endl;
    cout << "2. Consultas" << endl;
    cout << "3. Informes" << endl;
    cout << "4. Salir" << endl;
    cout << "Seleccione una opcion: ";
    COORD pos = getCursorPosition(hConsole);
    cin >> option;
    switch (option) {
      case 2:
        system("cls");
        queryMenu();
        break;
      case 4:
        return;
      default:
        verifyInputType();
        moveCursorAndDeleteLine(23, pos.Y, hConsole);
        moveCursor(pos.X, pos.Y, hConsole);
        break;
    }
  }
}

int main() {
  cargarDatos();
  //showMostSpecificActiveTasksPerson();
  menu();	
  // testing();



  return 0;
}