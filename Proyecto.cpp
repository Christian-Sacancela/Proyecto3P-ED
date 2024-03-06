#include <iostream>
#include <iomanip>
#include <conio.h> // Para utilizar las teclas de flecha
#include <windows.h> // Para cambiar el color del texto en la consola
#include <ctime>
#include <cstdlib>

using namespace std;

// Tamaño del tablero de Sudoku
const int N = 9;

// Función para verificar si un número puede ser colocado en la posición dada
bool esValido(int tablero[N][N], int fila, int columna, int num) {
    // Verificar si el número ya está en la fila o columna
    for (int i = 0; i < N; i++) {
        if (tablero[fila][i] == num || tablero[i][columna] == num)
            return false;
    }
    // Verificar si el número esta en el subcuadrado 3x3
    int inicioFila = fila - fila % 3;
    int inicioColumna = columna - columna % 3;
    for (int i = inicioFila; i < inicioFila + 3; i++) {
        for (int j = inicioColumna; j < inicioColumna + 3; j++) {
            if (tablero[i][j] == num)
                return false;
        }
    }
    return true;
}

// Funcion para encontrar una celda vacia en el tablero
bool encontrarCeldaVacia(int tablero[N][N], int& fila, int& columna) {
    for (fila = 0; fila < N; fila++) {
        for (columna = 0; columna < N; columna++) {
            if (tablero[fila][columna] == 0)
                return true;
        }
    }
    return false;
}

// Funcion para resolver el Sudoku utilizando la tecnica de vuelta atras (backtracking)
bool resolverSudoku(int tablero[N][N]) {
    int fila, columna;
    if (!encontrarCeldaVacia(tablero, fila, columna))
        return true;
    int availableNumbers[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    srand(time(nullptr));
    for (int i = 0; i < N; ++i) {
        int j = i + std::rand() % (N - i);
        swap(availableNumbers[i], availableNumbers[j]);
    }
    for (int i = 0; i < N; ++i) {
        int num = availableNumbers[i];
        if (esValido(tablero, fila, columna, num)) {
            tablero[fila][columna] = num;
            if (resolverSudoku(tablero))
                return true;
            tablero[fila][columna] = 0;
        }
    }
    return false;
}

// Funcion para imprimir el tablero de Sudoku
void imprimirTablero(int tablero[N][N], int filaActual, int columnaActual, bool resaltar[N][N], bool ocultar[N][N]) {

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    system("cls"); // Limpiar la pantalla antes de imprimir el tablero

    // Instrucciones
    cout << "\nInstrucciones:\n";
    cout << " 1. Usa las teclas de flecha para moverte por el tablero\n";
    cout << " 2. Presiona Enter para ingresar un numero en la celda actual\n";
    cout << " 3. Si el numero ingresado es correcto, se resaltara en verde\n";
    cout << " 4. Si el numero ingresado es incorrecto, se resaltara en rojo\n";
    cout << " 5. Presiona Escape para salir del juego\n";
    cout << endl;
    cout << endl;


    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (i == filaActual && j == columnaActual) {
                SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE); // Establecer color de texto azul para la posicion actual
            } else if (resaltar[i][j]) {
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED); // Establecer color de texto rojo para números incorrectos
            } else {
                SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN); // Establecer color de texto verde para numeros correctos
            }
            cout << setw(2) << tablero[i][j] << " ";
            if ((j + 1) % 3 == 0 && j < N - 1)
                cout << "| ";
        }
        cout << endl;
        if ((i + 1) % 3 == 0 && i < N - 1) {
            for (int k = 0; k < N + 2; k++)
                cout << "---";
            cout << endl;
        }
    }
    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED); // Restablecer color a blanco (por defecto)


}


void ocultarNumeros(int tablero[N][N], bool ocultar[N][N], int cantidad) {
    int contador = 0;
    while (contador < cantidad) {
        int fila = rand() % N;
        int columna = rand() % N;
        if (tablero[fila][columna] != 0) {
            tablero[fila][columna] = 0;
            ocultar[fila][columna] = true;
            contador++;
        }
    }
}



// Funcion principal
int main() {
    int tablero[N][N] = {0};
    int tableroResuelto[N][N] = {0}; // Aqui guardaremos el sudoku resuelto


    srand(time(nullptr));


    // Generar la primera fila con numeros aleatorios
    int availableNumbers[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    for (int j = 0; j < N; j++) {
        int randIndex = rand() % (N - j) + j;
        int temp = availableNumbers[j];
        availableNumbers[j] = availableNumbers[randIndex];
        availableNumbers[randIndex] = temp;
        tablero[0][j] = availableNumbers[j];
    }

    // Resolver el Sudoku
    resolverSudoku(tablero);

    // Guardar el sudoku resuelto
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            tableroResuelto[i][j] = tablero[i][j];
        }
    }

    // Ocultar algunos numeros
    bool ocultar[N][N] = {false};
    ocultarNumeros(tablero, ocultar, 40); // Cambia el segundo parametro para ajustar la cantidad de numeros ocultos


    // Iniciar el juego
    bool resaltar[N][N] = {false};
    int filaActual = 0, columnaActual = 0;
    imprimirTablero(tablero, filaActual, columnaActual, resaltar, ocultar);


    int tecla;
    while (true) {
        tecla = getch(); // Leer la tecla presionada sin esperar que se presione Enter

        switch (tecla) {
            case 72: // Flecha arriba
                filaActual = (filaActual - 1 + N) % N;
                break;
            case 80: // Flecha abajo
                filaActual = (filaActual + 1) % N;
                break;
            case 75: // Flecha izquierda
                columnaActual = (columnaActual - 1 + N) % N;
                break;
            case 77: // Flecha derecha
                columnaActual = (columnaActual + 1) % N;
                break;
            case 13: // Tecla Enter para ingresar numero en la posicion actual
                if (ocultar[filaActual][columnaActual]) {
                    int num;
                    cout << endl;
                    cout << "Ingrese el numero (1-9) en la fila " << filaActual + 1 << " columna " << columnaActual + 1 << ": ";
                    cin >> num;
                    if (num >= 1 && num <= 9) {
                        tablero[filaActual][columnaActual] = num;
                        if (tablero[filaActual][columnaActual] == tableroResuelto[filaActual][columnaActual]) {
                            resaltar[filaActual][columnaActual] = false; // Cambiar a verde si el numero ingresado es igual al número en el sudoku resuelto
                        } else {
                            resaltar[filaActual][columnaActual] = true; // Cambiar a rojo si el numero ingresado no es igual al número en el sudoku resuelto
                        }
                    } else {
                        cout << "Numero invalido. Intente nuevamente." << endl;
                    }
                }
                break;
            case 27: // Tecla Escape para salir del programa
                return 0;
            default:
                continue;
        }

        imprimirTablero(tablero, filaActual, columnaActual, resaltar, ocultar);
    }

    return 0;
}
