//
// Created by fabian on 19/9/2024.
//

#include "SubTask.h"

/**
 * @brief Constructor de la clase SubTask.
 *
 * Inicializa una nueva instancia de la clase `SubTask` con los valores especificados
 * para el nombre, comentarios y progreso. Además, determina si la subtarea está
 * completada en función del progreso y configura el puntero `next` a `nullptr`.
 *
 * @param name Nombre de la subtarea.
 * @param comments Comentarios adicionales sobre la subtarea.
 * @param progress Progreso de la subtarea representado como un valor flotante entre 0 y 100.
 * @author fabian
 */
SubTask::SubTask(const string & name, const string & comments, const float progress) {
    this->name = name;
    this->comments = comments;
    this->progress = progress;
    this->next = nullptr;

    if(this->progress == 100) {
        this->completed = true;
    } else {
        this->completed = false;
    }
}