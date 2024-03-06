#include <iostream>
#include <iomanip>
#include <conio.h> // Para utilizar las teclas de flecha
#include <windows.h> // Para cambiar el color del texto en la consola
#include <ctime>
#include <cstdlib>

using namespace std;

// Tamaño del tablero de Sudoku
const int N = 9;

// Función para limpiar la pantalla
void limpiarPantalla() {
    system("cls");
}

// Añadimos un título para el juego
void imprimirTitulo() {
    cout << "************************************" << endl;
    cout << "          Juego de Sudoku           " << endl;
    cout << "************************************" << endl << endl;
}


// Función para imprimir el menú principal
void imprimirMenuPrincipal() {
    cout << "Seleccione la dificultad:" << endl;
    cout << "1. Facil" << endl;
    cout << "2. Medio" << endl;
    cout << "3. Dificil" << endl;
    cout << "0. Salir del juego" << endl << endl;
    cout << "Ingrese el numero correspondiente a la dificultad o 0 para salir: ";
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

// Función para resolver el Sudoku utilizando la técnica de vuelta atrás (backtracking)
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

// Función para imprimir el tablero de Sudoku
void imprimirTablero(int tablero[N][N], int filaActual, int columnaActual, bool resaltar[N][N], bool ocultar[N][N]) {
	
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    system("cls"); // Limpiar la pantalla antes de imprimir el tablero
    
    // Instrucciones
    cout << "\nInstrucciones:\n";
    cout << " - Usa las teclas de flecha para moverte por el tablero.\n";
    cout << " - Presiona Enter para ingresar un numero en la celda actual.\n";
    cout << " - Si el numero ingresado es correcto, se resaltara en verde.\n";
    cout << " - Si el numero ingresado es incorrecto, se resaltara en rojo.\n";
    cout << " - Presiona Escape para volver al menu principal del juego.\n";
    cout << endl;
    cout << endl;
    

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



// Función principal
int main() {
	bool continuarJugando = true;
	
	while(continuarJugando){
	
		limpiarPantalla(); // Limpiar la pantalla antes de imprimir el menú
        
        imprimirTitulo(); // Imprimir el título del juego
        imprimirMenuPrincipal(); // Imprimir el menú principal
		
		// Solicitar al usuario que seleccione la dificultad
	    int dificultad;
	    cin >> dificultad;
	    
	    if (dificultad == 0) {
            cout << "Gracias por jugar Hasta luego." << endl;
            return 0; // Salir del bucle y del juego
        }
	    
	    // Ajustar la cantidad de números ocultos según la dificultad seleccionada
	    int cantidadOcultar;
	    
	    switch (dificultad) {
	        case 1: // Fácil
	            cantidadOcultar = 15;
	            break;
	        case 2: // Medio
	            cantidadOcultar = 20;
	            break;
	        case 3: // Difícil
	            cantidadOcultar = 40;
	            break;
	        default:
	            cout << "Opcion invalida. Seleccionando dificultad facil por defecto." << endl;
	            cantidadOcultar = 15;
	            break;
	    }
	    
	    int tablero[N][N] = {0};
	    int tableroResuelto[N][N] = {0}; // Aquí guardaremos el sudoku resuelto
	    
	    
	    srand(time(nullptr));
	    
	    // Generar la primera fila con números aleatorios
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
	    
	    // Ocultar algunos números
	    bool ocultar[N][N] = {false};
	    ocultarNumeros(tablero, ocultar, cantidadOcultar); // Cambia el segundo parámetro para ajustar la cantidad de números ocultos
	
	
	    // Iniciar el juego
	    bool resaltar[N][N] = {false};
	    int filaActual = 0, columnaActual = 0;
	    imprimirTablero(tablero, filaActual, columnaActual, resaltar, ocultar);

	    int tecla;
	    bool salir = true; 
	    while (salir != false) {
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
	                if (ocultar[filaActual][columnaActual]) {
	                    int num;
	                    cout << endl;
	                    cout << "Ingrese el numero (1-9) en la fila " << filaActual + 1 << " columna " << columnaActual + 1 << ": ";
	                    cin >> num;
	                    
	                    if (num >= 1 && num <= 9) {
	                        tablero[filaActual][columnaActual] = num;
	                        if (tablero[filaActual][columnaActual] == tableroResuelto[filaActual][columnaActual]) {
	                            resaltar[filaActual][columnaActual] = false; // Cambiar a verde si el número ingresado es igual al número en el sudoku resuelto
	                        } else {
	                            resaltar[filaActual][columnaActual] = true; // Cambiar a rojo si el número ingresado no es igual al número en el sudoku resuelto
	                        }
	                    } else {
	                        cout << "Numero invalido. Intente nuevamente." << endl;
	                    }
	                }
	                break;
	            case 27: // Tecla Escape para volver al menú principal
				    cout << "Volviendo al menu principal..." << endl;
				    salir = false;
				    break; // Salir del bucle y volver al menú principal
	            default:
	                continue;
	        }
	
	        imprimirTablero(tablero, filaActual, columnaActual, resaltar, ocultar);
	    	
	    	// Verificar si el Sudoku se ha completado
            bool sudokuCompleto = true;
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < N; j++) {
                    if (tablero[i][j] == 0) {
                        sudokuCompleto = false;
                        break;
                    }
                }
                if (!sudokuCompleto) {
                    break;
                }
            }
            if (sudokuCompleto) {
            	cout << endl;
            	cout << endl;
                cout << "¡Felicidades! Has completado el Sudoku." << endl;
                break; // Salir del bucle y volver al menú principal
            }
		}
	}
	
	
    return 0;

    
    }

