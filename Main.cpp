#include <iostream>
#include <iomanip>
#include <limits>
#include <sstream>
#include <string>
#include <windows.h>
#include <cstdlib>
#include <conio.h>

#include "Structures/Person.h"
#include "Structures/Task.h"
#include "Structures/SubTask.h"
#include "Lists/List.h"
#include "Lists/TaskTypeList.h"
#include "Lists/PersonList.h"
#include "utils/utils.h"

using namespace std;

PersonList people = PersonList();
TaskTypeList taskTypes = TaskTypeList();
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

    if (const Task* lastTask = person->activeTasks.get(-1))
        task->id = lastTask->id + 1;
    else task->id = 1;

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
 * @param taskIndex Identificador de la tarea.
 * @param newDate Nueva fecha en formato "dd-mm-YYYY".
 * @param newTime Nueva hora en formato "HH:MM:SS".
 * @throws runtime_error Si la persona o la tarea no se encuentran.
 * @author fabian
 */
void modifyActiveTask(const int personId, const int taskIndex, const string& newDate, const string& newTime) {
    Person* person = people.findById(personId);
    if (!person) throw runtime_error("Persona no encontrada");
    Task* task = person->activeTasks.get(taskIndex);
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
 * Al completar la subtarea, se valida si todas las subtareas estan completadas, para marcar la tarea como completada en
 * su totalidad
 *
 * @param personId Identificador de la persona.
 * @param taskId Identificador de la tarea.
 * @param subTaskIndex Índice de la subtarea dentro de la tarea.
 * @param newProgress Nuevo progreso de la subtarea (0-100).
 * @throws runtime_error Si la persona, la tarea o la subtarea no se encuentran.
 * @author fabian
 */
void subTaskProgress(const int personId, const int taskId, const int subTaskIndex, const float newProgress) {
    const Person* person = people.findById(personId);
    if (!person) throw runtime_error("Persona no encontrada");
    const Task* task = person->activeTasks.findById(taskId);
    if (!task) throw runtime_error("Tarea no encontrada");

    SubTask* subTask = task->subTasks.get(subTaskIndex);
    if (!subTask) throw runtime_error("Subtarea no encontrada");

    subTask->progress = newProgress;
    if (newProgress == 100) subTask->completed = true;
    else subTask->completed = false;

    for (int i = 0; i < task->subTasks.getLength(); i++) {
        if (!subTask->completed) return;
    }
    completeTask(personId, task->id);
}

/**
 * @brief Carga datos iniciales de personas y tipos de tareas para pruebas.
 *
 * Carga algunos datos iniciales de personas, tipos de tareas y tareas para realizar pruebas de las funcionalidades
 *
 * @author fabian.
 */
void cargarDatos() {
    cout << "Datos Cargados" << endl;

    // Insertar tipos de tareas
    taskTypes.insert("Estudio", "Tareas y exámenes");
    taskTypes.insert("Hogar", "Tareas de la casa");
    taskTypes.insert("Trabajo", "Tareas laborales");
    taskTypes.insert("Ejercicio", "Actividades físicas");
    taskTypes.insert("Ocio", "Tiempo libre");

    // Insertar personas
    people.insert(208620694, "Fabian", "Vargas", 19);
    people.insert(208620695, "Ana", "Martinez", 22);
    people.insert(208620696, "Carlos", "Lopez", 30);
    people.insert(208620697, "Laura", "Jimenez", 25);
    people.insert(208620698, "Jose", "Gonzalez", 28);

    // Insertar tareas
    addTask(208620694, new Task("Examenes", "Medio", "01-09-2024", "12:00:00", taskTypes.get(0)));
    addTask(208620694, new Task("Barrer", "Bajo", "20-09-2024", "08:00:00", taskTypes.get(1)));
    addTask(208620695, new Task("Proyecto", "Alto", "15-09-2024", "14:00:00", taskTypes.get(0)));
    addTask(208620696, new Task("Trabajo", "Alto", "22-09-2024", "09:00:00", taskTypes.get(2)));
    addTask(208620697, new Task("Ejercicio", "Medio", "18-09-2024", "06:00:00", taskTypes.get(3)));

    // Insertar subtareas
    addSubTask(208620694, 0, new SubTask("Calculo", "Estudiar último tema", 65.3));
    addSubTask(208620694, 0, new SubTask("Física", "Revisar apuntes", 40.0));
    addSubTask(208620694, 0, new SubTask("Matemáticas", "Resolver ejercicios", 70.0));
    addSubTask(208620694, 1, new SubTask("Limpieza", "Cocina", 50.0));
    addSubTask(208620695, 0, new SubTask("Investigación", "Recopilar datos", 80.0));
    addSubTask(208620696, 0, new SubTask("Informe", "Redactar conclusiones", 90.0));
    addSubTask(208620697, 0, new SubTask("Planificación", "Definir horarios", 75.0));
}

/**
 * @brief Imprime la lista de personas en fomato "nombre apellido: cédula"
 */
void printPeople() {
    const string peopleString = people.toString([](const Person& p) {
        return p.name + " " + p.lastname + ": " + to_string(p.id);
    });
    cout << "Personas con sus cedulas: " << peopleString << endl;
}

template<class T>
bool isEmpty(T& list) {
    if (list.getLength() <= 0) return true;
    return false;
}

void waitKeyPress() {
    cout << endl <<  "Presiona <ENTER> para volver..." << endl;
    cin.get();
}

/**
 * @brief Realiza pruebas sobre las funciones implementadas para verificar su correcto funcionamiento.
 *
 * Ejecuta una serie de pruebas sobre las operaciones de inserción, modificación y completado de tareas y subtareas.
 *
 * @author fabian
 */
void testing() {
    cout << endl << "***Testeando funciones***" << endl;
    cout << taskTypes.toString() << endl;
    cout << people.toString() << endl;
}

/**
 * @brief Solicita al usuario una entrada y la convierte al tipo especificado T.
 * @tparam T Tipo de dato esperado (int, float, string, etc.).
 * @param message Mensaje para solicitar la entrada al usuario.
 * @param allLine Si es true, utiliza getline para capturar toda la línea (solo para strings).
 * @return Entrada convertida al tipo T.
 * @author Fabian
 */
template <typename T>
T promptInput(const string& message, const bool allLine = false) {
    while (true) {
        try {
            cout << message;
            if constexpr (is_same_v<T, string>) {
                string input;
                if (allLine) {
                    getline(cin, input);
                } else {
                    cin >> input;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                return input;
            } else {
                T input;
                cin >> input;
                if (cin.fail()) {
                    throw runtime_error("Entrada inválida, por favor intente de nuevo.");
                }
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                return input;
            }
        } catch (const runtime_error& e) {
            cout << e.what() << endl;
            cin.clear();  // Limpiar el estado de error de cin
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Descartar la entrada incorrecta
        }
    }
}

/**
 * @brief Muestra una lista y solicita al usuario que seleccione un índice.
 * @param listName Nombre de la lista a mostrar.
 * @param listContent Contenido de la lista a seleccionar.
 * @param length Tamaño de la lista
 * @return Índice seleccionado por el usuario.
 * @author Fabian
 */
int selectIndex(const string& listName, const string& listContent, const int length) {
    cout << listName << ": " << listContent << endl;
    return promptInput<int>("Escoja mediante el indice (0 - " + to_string(length-1) + "): ");
}

/**
 * @brief Inserta un nuevo tipo de tarea solicitando nombre y descripción.
 * @author Fabian
 */
void menuInsertTaskType() {
    cout << "================== Insertar nuevo tipo de tarea ==================" << endl;
    const string name = promptInput<string>("Nombre de la tarea: ", true);
    const string description = promptInput<string>("Descripcion: ", true);
    taskTypes.insert(name, description);
}

/**
 * @brief Inserta una nueva persona pidiendo cédula, nombre, apellido y edad.
 * @author Fabian
 */
void menuInsertPerson() {
    cout << "================== Insertar persona ==================" << endl;
    const int id = promptInput<int>("Cedula: ");
    const string name = promptInput<string>("Nombre: ", true);
    const string lastname = promptInput<string>("Apellido: ", true);
    const int age = promptInput<int>("Edad: ");

    if (age < 0) {
        cout << "Edad no puede ser negativa. Intente de nuevo." << endl;
        return menuInsertPerson();
    }

    people.insert(id, name, lastname, age);
    cout << "Persona insertada correctamente";
}

/**
 * @brief Elimina una persona solicitando la cédula.
 * @author Fabian
 */
void menuDeletePerson() {
    cout << "================== Eliminar persona ==================" << endl;
    printPeople();
    if (isEmpty(people)) {
        cout << "No hay personas, inserte una antes de continuar";
        waitKeyPress();
        return;
    }
    const int id = promptInput<int>("\nCedula: ");
    const Person* deletedPerson = people.removeById(id);
    cout << deletedPerson->name << " eliminado correctamente";
}

/**
 * @brief Asigna una tarea a una persona especificando descripción, importancia, fecha y hora.
 * @author Fabian
 */
void menuInsertTask() {
    cout << "================== Asignar tarea a una persona ==================" << endl;
    if (isEmpty(taskTypes)) {
        cout << "Para crear una tarea se nececita minimo un tipo de tarea." << endl;
        cout << "Por favor cree un tipo de tarea.";
        waitKeyPress();
        return;
    }
    printPeople();
    if (isEmpty(people)) {
        cout << "No hay personas, inserte una antes de continuar";
        waitKeyPress();
        return;
    }
    const int personId = promptInput<int>("Cedula de la persona: ");
    const string description = promptInput<string>("Descripcion de la tarea: ", true);
    const string importance = promptInput<string>("Nivel de importancia (Alto, Medio, Bajo): ");
    const string date = promptInput<string>("Fecha (dd-mm-yyyy): ");
    const string time = promptInput<string>("Hora (hh:mm): ").append(":00");
    const int taskTypeIndex = selectIndex("Tipos de tarea", taskTypes.toString(), taskTypes.getLength());

    try {
        addTask(personId, new Task(description, importance, date, time, taskTypes.get(taskTypeIndex)));
    } catch (const runtime_error& error) {
        cout << error.what();
        cout << "Por favor vuelva a intentarloo..." << endl;
        menuInsertTask();
    }
}

/**
 * @brief Modifica la fecha y hora de una tarea existente de una persona.
 * @author Fabian
 */
void menuModifyTask() {
    cout << "================== Modificar fecha y hora de una tarea ==================" << endl;
    printPeople();
    if (isEmpty(people)) {
        cout << "No hay personas, inserte una antes de continuar";
        waitKeyPress();
        return;
    }
    const int personId = promptInput<int>("Cedula de la persona: ");

    const Person* person = people.getById(personId);

    if (isEmpty(person->activeTasks)) {
        cout << person->name << " no tiene tareas para modificar.";
        waitKeyPress();
        return;
    }

    const string tasksString = person->activeTasks.toString([](const Task& node) { return node.description; });

    const int taskIndex = selectIndex("Tareas activas de " + person->name + ": ", tasksString, person->activeTasks.getLength());
    const string date = promptInput<string>("Nueva fecha (dd-mm-yyyy): ");
    const string time = promptInput<string>("Nueva hora (hh:mm): ").append(":00");
    try {
        modifyActiveTask(personId, taskIndex, date, time);
    } catch (const runtime_error& error) {
        cout << error.what();
        cout << endl << "Por favor vuelva a intentarloo..." << endl;
        menuModifyTask();
    }
}

/**
 * @brief Elimina una tarea seleccionada de la lista de tareas activas de una persona.
 * @author Fabian
 */
void menuDeleteTask() {
    cout << "================== Eliminar una tarea ==================" << endl;
    printPeople();
    if (isEmpty(people)) {
        cout << "No hay personas, inserte una antes de continuar";
        waitKeyPress();
        return;
    }
    const int personId = promptInput<int>("Cedula de la persona: ");

    const Person* person = people.getById(personId);
    TaskList activeTasks = person->activeTasks;

    if (isEmpty(activeTasks)) {
        cout << person->name << " no tiene tareas";
        waitKeyPress();
        return;
    }

    const string tasksString = activeTasks.toString([](const Task& node) { return node.description; });
    const int taskIndex = selectIndex("Tareas activas de " + person->name + ": ", tasksString, activeTasks.getLength());

    try {
        activeTasks.removeById(activeTasks.get(taskIndex)->id);
    } catch (const runtime_error& error) {
        cout << error.what();
        cout << endl << "Por favor vuelva a intentarlo" << endl;
        menuDeleteTask();
    }
}

/**
 * @brief Inserta una subtarea a una tarea tipo "Estudio" en la lista de tareas activas de una persona.
 * @author Fabian
 */
void menuInsertSubtask() {
    cout << "================== Insertar una subtarea en una tarea ==================" << endl;
    printPeople();
    if (isEmpty(people)) {
        cout << "No hay personas, inserte una antes de continuar";
        waitKeyPress();
        return;
    }
    const int personId = promptInput<int>("Cedula de la persona: ");
    const Person* person = people.getById(personId);

    const List<Task> studyTasks = person->activeTasks.filter([](const Task& task) {
        return task.type->name == "Estudio";
    });

    if (isEmpty(studyTasks)) {
        cout << person->name << " no tiene tareas activas.";
        waitKeyPress();
        return;
    }

    const string subtasksString = studyTasks.toString([](const Task& node) {
        return node.description;
    });

    const int taskIndex = selectIndex(
        "Tareas tipo 'Estudio' activas de " + person->name + ": ",
        subtasksString,
        studyTasks.getLength()
    );
    const string name = promptInput<string>("Nombre de la subtarea: ", true);
    const string comments = promptInput<string>("Comentarios de la subtarea: ", true);
    const float progress = promptInput<float>("Progreso de la subtarea: ");

    addSubTask(personId, taskIndex, new SubTask(name, comments, progress));
}

/**
 * @brief Modifica el progreso de una subtarea de una tarea seleccionada.
 * @author Fabian
 */
void menuModifySubtask() {
    cout << "================== Modificar progreso de una subtarea ==================" << endl;
    printPeople();
    if (isEmpty(people)) {
        cout << "No hay personas, inserte una antes de continuar";
        waitKeyPress();
        return;
    }
    const int personId = promptInput<int>("Cedula de la persona: ");
    const Person* person = people.getById(personId);

    const List<Task> tasksWithSubtasks = person->activeTasks.filter([](const Task& task) {
        return task.subTasks.head != nullptr;
    });

    const string subtasksString = tasksWithSubtasks.toString([](const Task& node) {return node.description;});

    if (isEmpty(tasksWithSubtasks)) {
        cout << person->name << " no tiene tareas con subtareas activas";
        waitKeyPress();
        return;
    }

    const int taskIndex = selectIndex("Tareas que contienen subtareas: ", subtasksString, tasksWithSubtasks.getLength());
    const Task* selectedTask = person->activeTasks.get(taskIndex);
    const int subTaskIndex = selectIndex(
        "Subtareas de la tarea " + selectedTask->description + ": ",
        selectedTask->subTasks.toString(),
        selectedTask->subTasks.getLength()
    );
    const SubTask* selectedSubtask = selectedTask->subTasks.get(subTaskIndex);

    cout << "El progreso actual es del " << selectedSubtask->progress << "%" << endl;
    const float newProgress = promptInput<float>("Introduzca un nuevo progreso (100 para marcar como completa): ");

    subTaskProgress(personId, selectedTask->id, subTaskIndex, newProgress);
}

/**
 * @brief Marca una tarea seleccionada como completada.
 * @author Fabian
 */
void menuCompleteTask() {
    cout << "================== Marcar tarea como completa ==================" << endl;
    printPeople();
    if (isEmpty(people)) {
        cout << "No hay personas, inserte una antes de continuar";
        waitKeyPress();
        return;
    }
    const int personId = promptInput<int>("Cedula de la persona: ");
    const Person* person = people.getById(personId);

    if (isEmpty(person->activeTasks)) {
        cout << person->name << " no tiene tareas activas";
        waitKeyPress();
        return;
    }

    const string tasksString = person->activeTasks.toString([](const Task& node) { return node.description; });
    const int taskIndex = selectIndex("Tareas activas de " + person->name + ": ", tasksString, person->activeTasks.getLength());
    try {
        completeTask(personId, person->activeTasks.get(taskIndex)->id);
    } catch (const runtime_error& error) {
        cout << error.what();
        cout << endl << "Por favor vuelva a intentarlo..." << endl;
        menuCompleteTask();
    }

}

/**
 * @brief Muestra el menú principal del programa y ejecuta las opciones seleccionadas.
 * @author Fabian
 */
void editionMenu() {
    while (true) {
        int option = 0;
        system("cls");
        cout << endl << "Bienvenid@ al gestor de tareas" << endl << endl;
        cout << "Opciones" << endl;
        cout << "1. Insertar un nuevo Tipo de tarea" << endl;
        cout << "2. Insertar nueva persona" << endl;
        cout << "3. Eliminar una persona" << endl;
        cout << "4. Insertar tarea a una persona" << endl;
        cout << "5. Modificar una tarea" << endl;
        cout << "6. Eliminar una tarea" << endl;
        cout << "7. Insertar una subtarea" << endl;
        cout << "8. Modificar una subtarea" << endl;
        cout << "9. Marcar tarea como completada" << endl;
        cout << "10. Salir" << endl << endl;
        cout << "Insertar opcion (1 - 10): ";
        cin >> option;
        cin.ignore();

        system("cls");
        switch (option) {
            case 1: menuInsertTaskType(); break;
            case 2: menuInsertPerson(); break;
            case 3: menuDeletePerson(); break;
            case 4: menuInsertTask(); break;
            case 5: menuModifyTask(); break;
            case 6: menuDeleteTask(); break;
            case 7: menuInsertSubtask(); break;
            case 8: menuModifySubtask(); break;
            case 9: menuCompleteTask(); break;
            case 10: return;
            default: break;
        }
    }
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
    system("cls");
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

/**
 * @brief Ordenamiento de tareas activas de un usuario por fecha.
 *
 * Realiza un ordenamiento burbuja de las tareas activas de un usuario en base a la fecha.
 *
 * @author mario
 */
TaskList ordenarPorFecha (TaskList lPTareasActivas) {
    if (lPTareasActivas.head->next == nullptr) {
        return lPTareasActivas; // Si la lista está vacía o solo tiene un elemento
    }
    bool cambios = true;

    while (cambios) {
        Task* tempTareaActiva = lPTareasActivas.head;
        cambios = false;
        Task* anteriorTarea = nullptr;
        while (tempTareaActiva->next != nullptr) {
            Task* siguiente = tempTareaActiva->next;
            if ((tempTareaActiva->date.tm_year > tempTareaActiva->next->date.tm_year) ||
                (tempTareaActiva->date.tm_year == tempTareaActiva->next->date.tm_year &&
                    tempTareaActiva->date.tm_yday > tempTareaActiva->next->date.tm_yday)) {
               if (anteriorTarea == nullptr)
                   lPTareasActivas.head = siguiente;
               else {
                   anteriorTarea->next = siguiente;
               }
                tempTareaActiva->next = siguiente->next;
                siguiente->next = tempTareaActiva;

                cambios = true;

                anteriorTarea = siguiente;
            }
            else {
                // Si no hay cambios avanza con los siguientes dos elementos
                anteriorTarea = tempTareaActiva;
                tempTareaActiva = tempTareaActiva->next;
            }
        }
    }
    return lPTareasActivas;
}

/**
 * @brief Menu de reportes.
 *
 * Muestra el menu de opciones de reportes, además de ejecutar las funciones respectivas a cada opción.
 *
 * @author mario
 */
void menuReportes() {
    system("cls");
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // Se usa para modificar el color de la consola
    string opcionReporte = "0";

    while (opcionReporte != "9") {
        SetConsoleTextAttribute(hConsole, 160); // Se modifica el color de la consola
        cout << "\nMenu de reportes:";
        SetConsoleTextAttribute(hConsole, 10);
        cout << "\n1. Mostrar los tipos de tareas.\n";
        cout << "2. Mostrar todos los usuarios.\n";
        cout << "3. Mostrar usuarios sin tareas activas.\n";
        cout << "4. Mostrar tareas activas de un usuario en especifico (filtradas por fecha).\n";
        cout << "5. Mostrar tareas proximas a vencer (menos de una semana) de una fecha en especifico.\n";
        cout << "6. Mostrar subtareas de una tarea y usuario en especificos.\n";
        cout << "7. Mostrar tareas realizadas por un usuario en especifico.\n";
        cout << "8. Mostrar tareas realizadas al 100%.\n";
        cout << "9. Volver al menu principal.\n";
        SetConsoleTextAttribute(hConsole, 7);
        cout << "Seleccione una opcion [1-9]:";
        cin >> opcionReporte;

        if (opcionReporte == "1") {
            TaskType* actual = taskTypes.head;
            do {
                cout << actual->name << endl;
                actual = actual->next;
            } while (actual != taskTypes.head);
            cout << "Presiones enter para continuar...\n";
            _getch();
        }
        else if (opcionReporte == "2") {
            Person* actual = people.head;
            do {
                cout << actual->name << endl;
                actual = actual->next;
            } while (actual != nullptr);
            cout << "Presiones enter para continuar...\n";
            _getch();
        }
        else if (opcionReporte == "3") {
            Person* actual = people.head;
            do {
                if (actual->activeTasks.head == nullptr)
                    cout << actual->name << endl;
                actual = actual->next;
            } while (actual != nullptr);
            cout << "Presiones enter para continuar...\n";
            _getch();
        }
        else if (opcionReporte == "4") {
            Person* actual = people.head;
            string nombreABuscar;
            cout << "Ingrese el nombre a buscar:";
            cin >> nombreABuscar;
            while (actual->name != nombreABuscar) {
                actual = actual->next;
                if (actual == nullptr)
                    break;
            }
            if (actual == nullptr) {
                cout << "El usuario ingresado no existe! Presiones enter para continuar...\n";
                _getch();
                continue;
            }
            else if (actual->activeTasks.head == nullptr) {
                cout << "El usuario ingresado no tiene tareas pendientes! Presiones enter para continuar...\n";
                _getch();
                continue;
            }
            actual->activeTasks = ordenarPorFecha(actual->activeTasks);
            cout << "Tareas pendientes de " << actual->name << ":\n\n";
            Task* tareaActual = actual->activeTasks.head;
            int contadorTareas = 1;
            do {
                cout << "Tarea #" << contadorTareas << endl;
                cout << "Tipo: " << tareaActual->type->name << endl;
                cout << "ID: " << tareaActual->id << endl;
                cout << "Importancia: " << tareaActual->importance << endl;
                cout << "Fecha: " << tareaActual->getDate() << endl;
                cout << "Hora: " << tareaActual->getTime() << endl;
                cout << "Descripcion: " << tareaActual->description << endl << endl;
                tareaActual = tareaActual->next;

                contadorTareas++;
            } while (tareaActual != nullptr);
            cout << "Presiones enter para continuar...\n";
            _getch();

        }
        else if (opcionReporte == "5") {
            Person* actual = people.head;
            int contadorTareas = 1;
            string yearTemp;
            string mesTemp;
            string diaTemp;

            cout << "\n*FILTRO FECHA*";
            cout << "\nIngrese un a" << static_cast<char>(164) << "o:";
            cin >> yearTemp;
            cout << "Ingrese un mes:";
            cin >> mesTemp;
            cout << "Ingrese un dia:";
            cin >> diaTemp;
            cout << endl;

            string strFechaTemp = diaTemp + "-" + mesTemp + "-" + yearTemp;
            tm contenedorFecha = {};
            istringstream fechaTemp(strFechaTemp);
            fechaTemp >> get_time(&contenedorFecha, "%d-%m-%Y");
            if (fechaTemp.fail()) {
                throw runtime_error("Formato de fecha incorrecto. (dd-mm-YYYY)");
                continue;
            }

            while (actual != nullptr) {
                Task* tareaActual = actual->activeTasks.head;
                while (tareaActual != nullptr) {
                    int restaDias = tareaActual->date.tm_yday - contenedorFecha.tm_yday;
                    if ((tareaActual->date.tm_year == contenedorFecha.tm_year && (restaDias < 8 && restaDias >= 0)) ||
                        (tareaActual->date.tm_year == contenedorFecha.tm_year + 1 && restaDias < -358)) {

                        cout << "Tarea #" << contadorTareas << endl;
                        cout << "Usuario: " << actual->name << endl;
                        cout << "Tipo: " << tareaActual->type->name << endl;
                        cout << "ID: " << tareaActual->id << endl;
                        cout << "Importancia: " << tareaActual->importance << endl;
                        cout << "Fecha: " << tareaActual->getDate() << endl;
                        cout << "Hora: " << tareaActual->getTime() << endl;
                        cout << "Descripcion: " << tareaActual->description << endl << endl;
                        if (actual->completedTasks.getLength() == 1)
                            break;
                        contadorTareas++;

                    }

                    tareaActual = tareaActual->next;

                }
                actual = actual->next;
            }
        }
        else if (opcionReporte == "6") {
            Person* actual = people.head;
            string nombreABuscar;
            cout << "Ingrese el nombre a buscar:";
            cin >> nombreABuscar;
            while (actual->name != nombreABuscar) {
                actual = actual->next;
                if (actual == nullptr)
                    break;
            }
            if (actual == nullptr) {
                cout << "El usuario ingresado no existe! Presiones enter para continuar...\n";
                _getch();
                continue;
            }
            else if (actual->activeTasks.head == nullptr && actual->completedTasks.head == nullptr) {
                cout << "El usuario ingresado no tiene tareas! Presiones enter para continuar...\n";
                _getch();
                continue;
            }
            int tareaABuscar;
            bool noTareasActivas = false;
            cout << "Ingrese el ID de la tarea a buscar:";
            cin >> tareaABuscar;
            Task* tareaActual = actual->activeTasks.head;
            while (tareaActual->id != tareaABuscar) {
                tareaActual = tareaActual->next;
                if (tareaActual == nullptr)
                    noTareasActivas = true;
                break;
            }
            if (noTareasActivas) {
                Task* tareaActual = actual->completedTasks.head;
                while (tareaActual->id != tareaABuscar) {
                    actual = actual->next;
                    if (actual == nullptr)
                        break;
                }
            }
            if (noTareasActivas) {
                cout << "La tarea buscada no esta dentro de las tareas del usuario! Presiones enter para continuar...\n";
                _getch();
                continue;
            }
            SubTask* subTareaActual = tareaActual->subTasks.head;
            if (subTareaActual == nullptr) {
                cout << "La tarea buscada no tiene subtareas! Presiones enter para continuar...\n";
                _getch();
                continue;
            }
            int contaSubTareas = 1;
            while (subTareaActual != nullptr) {
                cout << "\nSubTarea #" << contaSubTareas << endl;
                cout << "Nombre: " << subTareaActual->name << endl;
                cout << "Comentarios: " << subTareaActual->comments << endl;
                cout << "Progreso: " << subTareaActual->progress << "%" << endl << endl;
                subTareaActual = subTareaActual->next;
                contaSubTareas++;
            }
            cout << "Presiones enter para continuar...\n";
            _getch();
        }
        else if (opcionReporte == "7") {
            Person* actual = people.head;
            string nombreABuscar;
            cout << "Ingrese el nombre a buscar:";
            cin >> nombreABuscar;
            while (actual->name != nombreABuscar) {
                actual = actual->next;
                if (actual == nullptr)
                    break;
            }
            if (actual == nullptr) {
                cout << "El usuario ingresado no existe! Presiones enter para continuar...\n";
                _getch();
                continue;
            }
            else if (actual->completedTasks.head == nullptr) {
                cout << "El usuario ingresado no tiene tareas completadas! Presiones enter para continuar...\n";
                _getch();
                continue;
            }
            cout << "Tareas completadas de " << actual->name << ":\n\n";
            Task* tareaActual = actual->completedTasks.head;
            int contadorTareas = 1;
            do {
                cout << "Tarea #" << contadorTareas << endl;
                cout << "Tipo: " << tareaActual->type->name << endl;
                cout << "ID: " << tareaActual->id << endl;
                cout << "Importancia: " << tareaActual->importance << endl;
                cout << "Fecha: " << tareaActual->getDate() << endl;
                cout << "Hora: " << tareaActual->getTime() << endl;
                cout << "Descripcion: " << tareaActual->description << endl << endl;
                if (actual->completedTasks.getLength() == 1)
                    break;
                tareaActual = tareaActual->next;
                contadorTareas++;
            } while (tareaActual != nullptr);
            cout << "Presiones enter para continuar...\n";
            _getch();
        }
        else if (opcionReporte == "8") {
            Person* actual = people.head;
            int contadorTareas = 1;
            while (actual != nullptr) {
                Task* tareaActual = actual->completedTasks.head;
                while (tareaActual != nullptr) {
                    cout << "Tarea #" << contadorTareas << endl;
                    cout << "Usuario: " << actual->name << endl;
                    cout << "Tipo: " << tareaActual->type->name << endl;
                    cout << "ID: " << tareaActual->id << endl;
                    cout << "Importancia: " << tareaActual->importance << endl;
                    cout << "Fecha: " << tareaActual->getDate() << endl;
                    cout << "Hora: " << tareaActual->getTime() << endl;
                    cout << "Descripcion: " << tareaActual->description << endl << endl;
                    if (actual->completedTasks.getLength() == 1)
                        break;
                    tareaActual = tareaActual->next;
                    contadorTareas++;
                }
                actual = actual->next;
            }

        }
        else if (opcionReporte == "9") {
            // Se salta la iteración
        }
        else {
            cout << "Opcion no valida! Presione enter para volver a mostrar el menu...\n";
            _getch();
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
        case 1: editionMenu(); break;
        case 2:
            system("cls");
            queryMenu();
            break;
        case 3: menuReportes();break;
        case 4: return;
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
  menu();
  return 0;
}