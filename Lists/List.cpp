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
    do {
        rep += currentNode->name;
        if (currentNode->next && currentNode->next != head) rep += ", ";
        currentNode = currentNode->next;
    } while (currentNode && currentNode != head);

    if (rep.length() > 70) {
        for (int i = 0; i < rep.length(); i++) {
            if (rep.compare(i, 1, ",")) {
                rep.insert(i+1, "\n");
            }
        }
    }

    rep += " }";
    return rep;
}

/**
 * @brief Convierte la lista en una cadena de texto que representa sus elementos.
 *
 * @param fieldExtractor Funcion que determina el string que representará cada nodo de la lista
 * @return Una cadena de texto con los nombres de los nodos en la lista.
 * @author fabian
 */
template <class T>
string List<T>::toString(const function<string(const T&)>& fieldExtractor) const {
    if (head == nullptr) return "{ }";
    string rep = "{ ";
    T* currentNode = head;
    do {
        rep += fieldExtractor(*currentNode);
        if (currentNode->next && currentNode->next != head) rep += ", ";
        currentNode = currentNode->next;
    } while (currentNode && currentNode != head);

    if (rep.length() > 70) {
        for (int i = 0; i < rep.length(); i++) {
            if (rep.at(i) == ',' || rep.at(i) == '{') {
                rep.insert(i+1, "\n\t");
            }
        }
        rep.append("\n");
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
    if (currentNode == nullptr && counter <= maxCounter) throw runtime_error("Indice invalido");
}

/**
 * @brief Filtra los elementos de la lista basándose en una condición y devuelve una nueva lista con los elementos que cumplen la condición.
 *
 * @tparam T Tipo de los elementos en la lista.
 * @param condition Función que define la condición de filtrado. Recibe un objeto de tipo T y devuelve un booleano.
 * @return List<T> Nueva lista que contiene solo los elementos que cumplen con la condición especificada.
 * @author Fabian
 *
 * La función recorre la lista original y aplica la condición a cada elemento. Si el elemento cumple la condición,
 * se crea una copia de él y se inserta en la nueva lista `filteredList`, asegurándose de que no apunte a la lista original.
 */
template <class T>
List<T> List<T>::filter(const std::function<bool(const T&)>& condition) const {
    auto filteredList = List<T>();
    if (head == nullptr) return filteredList;
    T* currentNode = head;
    do {
        if (condition(*currentNode)) {
            T* newNode = new T(*currentNode);
            newNode->next = nullptr;
            filteredList.insertLast(newNode);
        }
        currentNode = currentNode->next;
    } while (currentNode && currentNode != head);
    return filteredList;
}
