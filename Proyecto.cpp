#include <iostream>
#include <iomanip>
#include <conio.h> 
#include <windows.h>

using namespace std;

// Tamaño del tablero de Sudoku
const int N = 9;

void imprimirTablero(int tablero[N][N]);
bool esValido(int tablero[N][N], int fila, int columna, int num);
bool resolverSudoku(int tablero[N][N]);
bool encontrarCeldaVacia(int tablero[N][N], int& fila, int& columna);

// Función para imprimir el tablero de Sudoku
void imprimirTablero(int tablero[N][N], int filaActual, int columnaActual, bool resaltar[N][N]) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    system("cls"); // Limpiar la pantalla antes de imprimir el tablero

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (i == filaActual && j == columnaActual) {
                SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE); // Establecer color de texto azul para la posición actual
            } else if (resaltar[i][j]) {
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED); // Establecer color de texto rojo para números incorrectos
            } else {
                SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN); // Establecer color de texto verde para números correctos
            }
            cout << setw(2) << tablero[i][j] << " ";
            if ((j + 1) % 3 == 0 && j < N - 1)
                cout << "| ";
        }
        cout << endl;
        if ((i + 1) % 3 == 0 && i < N - 1) {
            for (int k = 0; k < N + 2; k++)
                cout << "--";
            cout << endl;
        }
    }
    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED); // Restablecer color a blanco (por defecto)
}

// Función para verificar si un número puede ser colocado en la posición dada
bool esValido(int tablero[N][N], int fila, int columna, int num) {
    // Verificar si el número ya está en la fila o columna
    for (int i = 0; i < N; i++) {
        if (tablero[fila][i] == num || tablero[i][columna] == num)
            return false;
    }
    // Verificar si el número está en el subcuadrado 3x3
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

// Función para resolver el Sudoku utilizando la técnica de vuelta atrás (backtracking)
bool resolverSudoku(int tablero[N][N]) {
    int fila, columna;

    // Si no hay celdas vacías, se ha resuelto el Sudoku
    if (!encontrarCeldaVacia(tablero, fila, columna))
        return true;

    // Probar números del 1 al 9
    for (int num = 1; num <= 9; num++) {
        // Si el número puede ser colocado en la celda actual
        if (esValido(tablero, fila, columna, num)) {
            // Colocar el número en la celda
            tablero[fila][columna] = num;

            // Intentar resolver el Sudoku recursivamente
            if (resolverSudoku(tablero))
                return true;

            // Si no se puede resolver con este número, retroceder
            tablero[fila][columna] = 0;
        }
    }
    // No se encontró una solución
    return false;
}

// Función para encontrar una celda vacía en el tablero
bool encontrarCeldaVacia(int tablero[N][N], int& fila, int& columna) {
    for (fila = 0; fila < N; fila++) {
        for (columna = 0; columna < N; columna++) {
            if (tablero[fila][columna] == 0)
                return true;
        }
    }
    return false;
}

// Función principal
int main() {
    int tablero[N][N] = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };

    bool resaltar[N][N] = {false};
    int filaActual = 0, columnaActual = 0;

    imprimirTablero(tablero, filaActual, columnaActual, resaltar);

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
            case 13: // Tecla Enter para ingresar número en la posición actual
                int num;
                cout << "Ingrese el numero (1-9) en la fila " << filaActual + 1 << " columna " << columnaActual + 1 << ": ";
                cin >> num;
                if (num >= 1 && num <= 9) {
                    tablero[filaActual][columnaActual] = num;
                    resaltar[filaActual][columnaActual] = !esValido(tablero, filaActual, columnaActual, num);
                } else {
                    cout << "Numero invalido. Intente nuevamente." << endl;
                }
                break;
            case 27: // Tecla Escape para salir del programa
                return 0;
            default:
                continue;
        }

        imprimirTablero(tablero, filaActual, columnaActual, resaltar);
    }
    return 0;
}
