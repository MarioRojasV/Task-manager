//
// Created by fabian on 19/9/2024.
//

#include "List.h"
#include <iostream>

/**
 * @brief Constructor de la clase List.
 *
 * Inicializa una lista vacía con `head` apuntando a `nullptr` y longitud igual a 0.
 *
 * @author fabian
 */
template <class T>
List<T>::List() {
    this->head = nullptr;
    this->length = 0;
}

/**
 * @brief Inserta un nuevo nodo al final de la lista.
 *
 * @param newNode Puntero al nuevo nodo que se va a insertar al final.
 * @author fabian
 */
template <class T>
void List<T>::insertLast(T* newNode) {
    if (!head) head = newNode;
    else {
        T* lastNode = get(-1);
        lastNode->next = newNode;
    }
    ++length;
}

/**
 * @brief Inserta un nuevo nodo al principio de la lista.
 *
 * @param newNode Puntero al nuevo nodo que se va a insertar al principio.
 * @author fabian
 */
template <class T>
void List<T>::insertFirst(T* newNode) {
    newNode->next = head;
    head = newNode;
    ++length;
}

/**
 * @brief Obtiene un nodo de la lista en el índice especificado.
 *
 * @param index Índice del nodo a obtener. Si es negativo, cuenta desde el final.
 * @return Puntero al nodo en el índice especificado, o `nullptr` si el índice es inválido.
 * @author fabian
 */
template <class T>
T* List<T>::get(int index) const {
    if (index < 0) index = length + index;
    T* currentNode = head;
    goUp(currentNode, index);
    return currentNode;
}

/**
 * @brief Busca un nodo en la lista por su ID.
 *
 * @param id ID del nodo a buscar.
 * @return Puntero al nodo con el ID especificado, o `nullptr` si no se encuentra.
 * @author fabian
 */
template <class T>
T* List<T>::findById(int id) const {
    T* currentNode = head;
    while (currentNode) {
        if (currentNode->id == id) return currentNode;
        currentNode = currentNode->next;
    }
    return nullptr;
}

/**
 * @brief Elimina un nodo de la lista por su ID.
 *
 * @param id ID del nodo a eliminar.
 * @return Puntero al nodo eliminado, o `nullptr` si no se encuentra.
 * @author fabian
 */
template <class T>
T* List<T>::removeById(int id) {
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

/**
 * @brief Convierte la lista en una cadena de texto que representa sus elementos.
 *
 * @return Una cadena de texto con los nombres de los nodos en la lista.
 * @author fabian
 */
template <class T>
string List<T>::toString() const {
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

/**
 * @brief Obtiene la longitud de la lista.
 *
 * @return Número de nodos en la lista.
 * @author fabian
 */
template <class T>
int List<T>::getLength() const { return this->length; }

/**
 * @brief Recorre la lista hasta un nodo específico.
 *
 * @param currentNode Puntero al nodo actual, que se actualizará durante la función.
 * @param maxCounter Número máximo de pasos a recorrer.
 * @author fabian
 */
template <class T>
void List<T>::goUp(T*& currentNode, int const maxCounter) {
    int counter = 0;
    while (currentNode && counter < maxCounter) {
        currentNode = currentNode->next;
        ++counter;
    }
}
