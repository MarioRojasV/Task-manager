#include "utils.h"
#include <iostream> // Para std::cerr
#include <string>   // Para std::string
#include <limits>   // Para std::numeric_limits

/**
 * @brief Obtiene la posición actual del cursor en la consola.
 *
 * Esta función utiliza las funciones de la API de Windows para recuperar la posición
 * actual del cursor en la consola. Si no puede obtener la posición, retorna (0, 0).
 *
 * @param hConsole El handle de la consola obtenido con GetStdHandle.
 * @return COORD La posición actual del cursor en la consola.
 *
 * @author Joseph
 */
COORD getCursorPosition(HANDLE hConsole) {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (GetConsoleScreenBufferInfo(hConsole, &csbi)) {
        return csbi.dwCursorPosition;
    }
    // Retorna (0,0) si falla
    return COORD{0, 0};
}

/**
 * @brief Mueve el cursor a una posición específica en la consola y borra la línea.
 *
 * Esta función mueve el cursor a las coordenadas proporcionadas (x, y), obtiene el ancho
 * de la consola, crea una cadena de espacios para sobrescribir la línea en esa posición,
 * imprime los espacios para borrar la línea y vuelve a mover el cursor al inicio de la línea borrada.
 *
 * @param x La coordenada X (columna) a la que se moverá el cursor.
 * @param y La coordenada Y (fila) a la que se moverá el cursor.
 * @param hConsole El handle de la consola obtenido con GetStdHandle.
 *
 * @author Joseph
 */
void moveCursor(int x, int y,HANDLE hConsole) {
    // Mover el cursor a (x, y)
    COORD pos;
    pos.X = x;
    pos.Y = y;
    if (!SetConsoleCursorPosition(hConsole, pos)) {
        std::cerr << "Error al mover el cursor a la posición (" << x << ", " << y << ")." << std::endl;
        return;
    }
    // Mover el cursor
    if (!SetConsoleCursorPosition(hConsole, pos)) {
        std::cerr << "Error al mover el cursor de vuelta a la posición (" << x << ", " << y << ")." << std::endl;
        return;
    }
}

void deleteLine(HANDLE hConsole){
    // Obtener el ancho de la consola para saber cuántos espacios usar
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        if (!GetConsoleScreenBufferInfo(hConsole, &csbi)) {
            std::cerr << "Error al obtener la información del buffer de la consola." << std::endl;
            return;
        }
        int anchoConsola = csbi.dwSize.X;

        // Crear una cadena de espacios para sobrescribir la línea
        std::string espacios(anchoConsola, ' ');

        // Imprimir los espacios para "borrar" la línea
        std::cout << espacios;
}

void moveCursorAndDeleteLine(int x, int y, HANDLE hConsole){
    moveCursor(x, y, hConsole);
    deleteLine(hConsole);
}

void waitEnter() {
    // Limpiar el buffer de entrada previo
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    // Esperar a que el usuario presione Enter
    std::string dummy;
    std::getline(std::cin, dummy);

    // Limpiar cualquier entrada residual (opcional)
    std::cin.clear();
}   


void clearInputBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void verifyInputType(){
    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}
