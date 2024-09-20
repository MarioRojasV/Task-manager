//
// Created by fabian on 19/9/2024.
//

#include "Person.h"
#include "../Lists/TaskList.h"

/**
 * @brief Constructor de la clase Person.
 *
 * Inicializa una nueva instancia de la clase `Person` con los valores especificados
 * para el identificador, nombre, apellido, y edad. También inicializa las listas de
 * tareas activas y completadas y los punteros de navegación a `nullptr`.
 *
 * @param id Identificador único de la persona.
 * @param name Nombre de la persona.
 * @param lastname Apellido de la persona.
 * @param age Edad de la persona.
 * @author fabian
 */
Person::Person(const int id, const string & name, const string & lastname, const int age) {
    this->id = id;
    this->name = name;
    this->lastname = lastname;
    this->age = age;
    this->next = nullptr;
    this->prev = nullptr;
    this->activeTasks = TaskList();
    this->completedTasks = TaskList();
}