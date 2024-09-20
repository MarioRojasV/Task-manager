//
// Created by fabian on 19/9/2024.
//

#include "TaskList.h"

using namespace std;

/**
 * @brief Inserta una tarea en la lista en orden ascendente por fecha y hora.
 *
 * Inserta una nueva tarea (`Task`) en la lista manteniendo el orden ascendente según
 * la fecha y la hora. Si la fecha y hora son iguales a las de una tarea existente,
 * inserta la nueva tarea después de la existente.
 *
 * @param task Puntero a la tarea que se va a insertar.
 * @author fabian
 */
void TaskList::insert(Task* task) {
    if (!this->head) {
        this->head = task;
        return;
    }

    Task* currentNode = this->head;
    Task* previousNode = nullptr;

    while (currentNode != nullptr) {
        if (isSameDateTime(task->date, task->time, currentNode->date, currentNode->time)) {
            task->next = currentNode->next;
            currentNode->next = task;
            break;
        }
        if (compareDates(task->date, currentNode->date) || (
            task->date.tm_year == currentNode->date.tm_year &&
            task->date.tm_mon == currentNode->date.tm_mon &&
            task->date.tm_mday == currentNode->date.tm_mday &&
            compareTimes(task->time, currentNode->time))
            )
        {
            task->next = currentNode;
            if (previousNode == nullptr) {
                this->head = task;
            } else {
                previousNode->next = task;
            }
            break;
        }

        previousNode = currentNode;
        currentNode = currentNode->next;
    }

    if (currentNode == nullptr && previousNode) {
        previousNode->next = task;
    }
}

/**
 * @brief Compara dos fechas de tipo `tm`.
 *
 * Compara dos estructuras `tm` para determinar cuál es anterior.
 *
 * @param lhs Fecha a la izquierda en la comparación.
 * @param rhs Fecha a la derecha en la comparación.
 * @return `true` si `lhs` es anterior a `rhs`, de lo contrario `false`.
 * @author fabian
 */
bool TaskList::compareDates(const tm& lhs, const tm& rhs) {
    if (lhs.tm_year != rhs.tm_year) return lhs.tm_year < rhs.tm_year;
    if (lhs.tm_mon != rhs.tm_mon) return lhs.tm_mon < rhs.tm_mon;
    if (lhs.tm_mday != rhs.tm_mday) return lhs.tm_mday < rhs.tm_mday;
    return false;
}

/**
 * @brief Compara dos horas de tipo `tm`.
 *
 * Compara dos estructuras `tm` para determinar cuál es anterior en términos de hora.
 *
 * @param lhs Hora a la izquierda en la comparación.
 * @param rhs Hora a la derecha en la comparación.
 * @return `true` si `lhs` es anterior a `rhs`, de lo contrario `false`.
 * @author fabian
 */
bool TaskList::compareTimes(const tm& lhs, const tm& rhs) {
    if (lhs.tm_hour != rhs.tm_hour) return lhs.tm_hour < rhs.tm_hour;
    if (lhs.tm_min != rhs.tm_min) return lhs.tm_min < rhs.tm_min;
    if (lhs.tm_sec != rhs.tm_sec) return lhs.tm_sec < rhs.tm_sec;
    return false;
}

/**
 * @brief Compara si dos fechas y horas son exactamente iguales.
 *
 * Determina si dos combinaciones de fecha y hora son exactamente iguales comparando
 * todos los campos relevantes de las estructuras `tm`.
 *
 * @param date1 Fecha de la primera tarea.
 * @param time1 Hora de la primera tarea.
 * @param date2 Fecha de la segunda tarea.
 * @param time2 Hora de la segunda tarea.
 * @return `true` si ambas fechas y horas son iguales, de lo contrario `false`.
 * @author fabian
 */
bool TaskList::isSameDateTime(const tm& date1, const tm& time1, const tm& date2, const tm& time2) {
    return (date1.tm_year == date2.tm_year && date1.tm_mon == date2.tm_mon && date1.tm_mday == date2.tm_mday &&
            time1.tm_hour == time2.tm_hour && time1.tm_min == time2.tm_min && time1.tm_sec == time2.tm_sec);
}