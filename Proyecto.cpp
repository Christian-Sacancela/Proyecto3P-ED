#include <iostream>
#include <iomanip>
#include <conio.h> // Para utilizar las teclas de flecha
#include <windows.h> // Para cambiar el color del texto en la consola

using namespace std;

// Tama�o del tablero de Sudoku
const int N = 9;

// Declaraciones de funciones
void imprimirTablero(int tablero[N][N], int filaActual, int columnaActual, bool resaltar[N][N]);
bool esValido(int tablero[N][N], int fila, int columna, int num);
bool resolverSudoku(int tablero[N][N]);
bool encontrarCeldaVacia(int tablero[N][N], int& fila, int& columna);

// Funci�n para imprimir el tablero de Sudoku
void imprimirTablero(int tablero[N][N], int filaActual, int columnaActual, bool resaltar[N][N]) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
system("cls"); // Limpiar la pantalla antes de imprimir el tablero

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (i == filaActual && j == columnaActual) {
                SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE); // Establecer color de texto azul para la posici�n actual
            } else if (resaltar[i][j]) {
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED); // Establecer color de texto rojo para n�meros incorrectos
            } else {
                SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN); // Establecer color de texto verde para n�meros correctos
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

// Funci�n para verificar si un n�mero puede ser colocado en la posici�n dada
bool esValido(int tablero[N][N], int fila, int columna, int num) {
    // Verificar si el n�mero ya est� en la fila o columna
    for (int i = 0; i < N; i++) {
        if (tablero[fila][i] == num || tablero[i][columna] == num)
            return false;
    }
// Verificar si el n�mero est� en el subcuadrado 3x3
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

// Funci�n para resolver el Sudoku utilizando la t�cnica de vuelta atr�s (backtracking)
bool resolverSudoku(int tablero[N][N]) {
    int fila, columna;
// Si no hay celdas vac�as, se ha resuelto el Sudoku
    if (!encontrarCeldaVacia(tablero, fila, columna))
        return true;

    // Probar n�meros del 1 al 9
    for (int num = 1; num <= 9; num++) {
        // Si el n�mero puede ser colocado en la celda actual
        if (esValido(tablero, fila, columna, num)) {
            // Colocar el n�mero en la celda
            tablero[fila][columna] = num;

            // Intentar resolver el Sudoku recursivamente
            if (resolverSudoku(tablero))
                return true;

            // Si no se puede resolver con este n�mero, retroceder
            tablero[fila][columna] = 0;
        }
    }
    // No se encontr� una soluci�n
    return false;
}

// Funci�n para encontrar una celda vac�a en el tablero
bool encontrarCeldaVacia(int tablero[N][N], int& fila, int& columna) {
    for (fila = 0; fila < N; fila++) {
        for (columna = 0; columna < N; columna++) {
            if (tablero[fila][columna] == 0)
                return true;
        }
    }
    return false;
}


// Funci�n principal

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
            case 13: // Tecla Enter para ingresar n�mero en la posici�n actual
                if (tablero[filaActual][columnaActual] == 0) {
                    int num;
                    cout << "Ingrese el numero (1-9) en la fila " << filaActual + 1 << " columna " << columnaActual + 1 << ": ";
                    cin >> num;
                    if (num >= 1 && num <= 9) {
                        tablero[filaActual][columnaActual] = num;
                        resaltar[filaActual][columnaActual] = !esValido(tablero, filaActual, columnaActual, num);
                    } else {
cout << "Numero invalido. Intente nuevamente." << endl;
                    }
                } else {
                    cout << "El numero en esta posicion no se puede cambiar." << endl;
                    Sleep(1000); // Esperar 1 segundo para mostrar el mensaje antes de borrarlo
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


