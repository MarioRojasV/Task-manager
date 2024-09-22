//
// Created by fabian on 19/9/2024.
//

#include "Task.h"
#include "SubTask.h"
#include "TaskType.h"

/**
 * @brief Constructor de la clase Task.
 *
 * Inicializa una nueva instancia de la clase `Task` con los valores especificados
 * para el identificador, descripción, importancia, fecha, hora y tipo de tarea.
 * Si el tipo de tarea es "Estudio", se inicializa la lista de subtareas.
 * La fecha y hora se convierten desde cadenas al formato `tm`.
 *
 * @param description Descripción de la tarea.
 * @param importance Nivel de importancia de la tarea.
 * @param date Fecha de la tarea en formato "dd-mm-YYYY".
 * @param time Hora de la tarea en formato "HH:MM:SS".
 * @param type Puntero al tipo de tarea que describe la categoría de la misma.
 *
 * @throws runtime_error Si la fecha o la hora no tienen el formato correcto.
 * @author fabian
 */
Task::Task(const string & description, const string & importance, const string & date, const string & time, TaskType * type) {
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

/**
 * @brief Establece la fecha de la tarea a partir de una cadena.
 *
 * Convierte una cadena de texto con formato "dd-mm-YYYY" a una estructura `tm`
 * y la asigna al campo de fecha de la tarea.
 *
 * @param date Fecha en formato "dd-mm-YYYY".
 * @throws std::runtime_error Si el formato de la fecha es incorrecto.
 * @author fabian
 */
void Task::setDate(const string & date) {
    istringstream dateStream(date);
    dateStream >> get_time(&this->date, "%d-%m-%Y");
    if (dateStream.fail()) throw runtime_error("Formato de fecha incorrecto. (dd-mm-YYYY)");
}

/**
 * @brief Establece la hora de la tarea a partir de una cadena.
 *
 * Convierte una cadena de texto con formato "HH:MM:SS" a una estructura `tm`
 * y la asigna al campo de hora de la tarea.
 *
 * @param time Hora en formato "HH:MM:SS".
 * @throws runtime_error Si el formato de la hora es incorrecto.
 * @author fabian
 */
void Task::setTime(const string & time) {
    istringstream timeStream(time);
    timeStream >> get_time(&this->time, "%H:%M:%S");
    if (timeStream.fail()) throw runtime_error("Formato de hora incorrecto. (HH:MM:SS)");
}

/**
 * @brief Obtiene la fecha de la tarea en formato "dd-mm-YYYY".
 *
 * @return Una cadena formateada con la fecha de la tarea.
 * @author fabian
 */
[[nodiscard]] auto Task::getDate() const {
    return put_time(&this->date, "%d-%m-%Y");
}

/**
 * @brief Obtiene la hora de la tarea en formato "HH:MM:SS".
 *
 * @return Una cadena formateada con la hora de la tarea.
 * @author fabian
 */
[[nodiscard]] auto Task::getTime() const  {
    return put_time(&this->time, "%H:%M:%S");
}