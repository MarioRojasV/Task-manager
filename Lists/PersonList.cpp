//
// Created by fabian on 19/9/2024.
//

#include "PersonList.h"

/**
 * @brief Constructor de la clase PersonList.
 *
 * Inicializa una lista de personas vacía con el puntero `head` apuntando a `nullptr`.
 *
 * @author fabian
 */
PersonList::PersonList() {
    this->head = nullptr;
}

/**
 * @brief Inserta una nueva persona en la lista en orden ascendente por ID.
 *
 * Crea e inserta un nuevo nodo `Person` en la lista manteniendo el orden ascendente
 * por el identificador. Si el ID ya existe, lanza una excepción.
 *
 * @param id Identificador único de la persona.
 * @param name Nombre de la persona.
 * @param lastname Apellido de la persona.
 * @param age Edad de la persona.
 * @throws std::exception Si el ID ya existe en la lista.
 * @author fabian
 */
void PersonList::insert(const int id, const string& name, const string& lastname, const int age) {
    if (this->head == nullptr) {
        this->head = new Person(id, name, lastname, age);
        this->length++;
        return;
    }

    if (id < this->head->id) {
        const auto newNode = new Person(id, name, lastname, age);
        newNode->next = this->head;
        this->head->prev = newNode;
        this->head = newNode;
        this->length++;
        return;
    }

    Person* currentNode = this->head;

    while (currentNode != nullptr) {
        if (id == currentNode->id) throw std::exception();

        if (id < currentNode->id) {
            const auto newNode = new Person(id, name, lastname, age);
            newNode->next = currentNode;
            newNode->prev = currentNode->prev;
            currentNode->prev->next = newNode;
            currentNode->prev = newNode;
            this->length++;
            break;
        }

        if (currentNode->next == nullptr) {
            const auto newNode = new Person(id, name, lastname, age);
            newNode->prev = currentNode;
            currentNode->next = newNode;
            ++this->length;
            break;
        }

        currentNode = currentNode->next;
    }
}

/**
 * @brief Elimina una persona de la lista por su ID.
 *
 * Busca y elimina el nodo `Person` que tiene el ID especificado.
 * Ajusta los punteros de los nodos adyacentes en la lista.
 *
 * @param id Identificador único de la persona a eliminar.
 * @return Puntero a la persona eliminada, o `nullptr` si no se encuentra.
 * @author fabian
 */
Person* PersonList::remove(int id) {
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

/**
 * @brief Obtiene una persona de la lista por su índice.
 *
 * Retorna el nodo `Person` en la posición especificada por el índice.
 *
 * @param index Índice del nodo a obtener. Debe ser menor que la longitud de la lista.
 * @return Puntero a la persona en el índice especificado, o `nullptr` si el índice es inválido.
 * @author fabian
 */
Person* PersonList::get(int index) const {
    if (index >= this->getLength()) return nullptr;

    Person* currentNode = this->head;
    for (int i = 0; i < index; i++) {
        currentNode = currentNode->next;
    }

    return currentNode;
}

/**
 * @brief Busca una persona en la lista por su ID.
 *
 * Retorna el nodo `Person` que tiene el ID especificado, o `nullptr` si no se encuentra.
 *
 * @param id Identificador único de la persona a buscar.
 * @return Puntero a la persona con el ID especificado, o `nullptr` si no se encuentra.
 * @author fabian
 */
Person* PersonList::getById(int id) const {
    Person* currentNode = this->head;

    while (currentNode != nullptr) {
        if (currentNode->id == id) return currentNode;
        if (currentNode->id > id) return nullptr;
        currentNode = currentNode->next;
    }

    return nullptr;
}