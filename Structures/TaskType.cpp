//
// Created by fabian on 19/9/2024.
//

#include "TaskType.h"

/**
 * @brief Constructor de la clase TaskType.
 *
 * Inicializa una nueva instancia de la clase `TaskType` con los valores especificados
 * para el identificador, nombre y descripción. El puntero `next` se inicializa a `nullptr`.
 *
 * @param id Identificador único del tipo de tarea.
 * @param name Nombre del tipo de tarea.
 * @param description Descripción del tipo de tarea.
 * @author fabian
 */
TaskType::TaskType(const int id, const string & name, const string & description) {
    this->id = id;
    this->name = name;
    this->description = description;
    this->next = nullptr;
}