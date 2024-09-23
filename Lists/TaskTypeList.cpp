//
// Created by varga on 19/9/2024.
//

#include "TaskTypeList.h"

/**
 * @brief Constructor de la clase TaskTypeList.
 *
 * Inicializa una lista circular vacía de tipos de tarea con el puntero `head` apuntando a `nullptr`.
 *
 * @author fabian
 */
TaskTypeList::TaskTypeList() {
    this->head = nullptr;
}

/**
 * @brief Inserta un nuevo tipo de tarea en la lista de manera circular.
 *
 * Inserta un nuevo nodo `TaskType` en la lista circular. Si la lista está vacía, el nuevo
 * nodo se convierte en el `head` y apunta a sí mismo, formando el comienzo de la lista circular.
 * Si la lista no está vacía, el nuevo nodo se inserta al final, antes del `head`,
 * manteniendo el orden circular.
 *
 * @param name Nombre del tipo de tarea.
 * @param description Descripción del tipo de tarea.
 * @author fabian
 */
void TaskTypeList::insert(const string& name, const string& description) {
    if (this->head == nullptr) {
        this->head = new TaskType(1, name, description);
        this->head->next = this->head;
        this->length = 1;
        return;
    }

    TaskType* currentNode = this->head;

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