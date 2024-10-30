#include <iostream>
#include <cstdlib> // Para rand() y srand()
#include <ctime> // Para time()

using namespace std;

// Inicializa el arreglo con -1
void inicializar_arreglo_enteros(int *arreglo, int n) {
    for (int contador = 0; contador < n; contador++) {
        arreglo[contador] = -1;
    }
}

// Llena el arreglo con numeros aleatorios
void llenarArreglo(int* arr, int size) {
    srand(static_cast<unsigned int>(time(0))); // Inicializa la semilla de aleatoriedad
    for (int i = 0; i < size; ++i) {
        arr[i] = rand() % 100 + 1; // Genera numeros aleatorios entre 1 y 100
    }
}

// Funcion hash H(K)
int h(int K, int n) {
    return (K % n); // Hash basico con el tamano del arreglo
}

// Funcion hash secundaria H'(D) para doble direccionamiento
int h_nueva(int D, int n) {
    return (D + 1) % n; // Segunda funcion hash con el tamano del arreglo
}

// Muestra el arreglo
void mostrarArreglo(int* arr, int size) {
    cout << "ARREGLO[" << size << "]: ";
    for (int i = 0; i < size; ++i) {
        cout << " " << arr[i] << " ";
    }
    cout << endl;
}

// Reasignacion: Prueba Lineal
void prueba_lineal(int *arreglo, int K, int n) {
    int D = h(K, n); // Direccion inicial
    if (arreglo[D] == -1) {
        arreglo[D] = K;
        cout << "La informacion se inserto en la posicion: " << D << endl;
    } else {
        cout << "Colision en la posicion " << D << " para el valor " << K << endl;
        int dx = D + 1;
        while (dx < n && arreglo[dx] != -1 && dx != D) {
            dx++;
            if (dx == n) {
                dx = 0;
            }
        }
        if (arreglo[dx] == -1) {
            arreglo[dx] = K;
            cout << "La informacion se inserto en la posicion: " << dx << endl;
        } else {
            cout << "No se pudo insertar el valor. No hay espacio disponible." << endl;
        }
    }
}

// Reasignacion: Prueba Cuadratica
void prueba_cuadratica(int *arreglo, int K, int n) {
    int D = h(K, n); // Direccion inicial
    if (arreglo[D] == -1) {
        arreglo[D] = K;
        cout << "La informacion se inserto en la posicion: " << D << endl;
    } else {
        cout << "Colision en la posicion " << D << " para el valor " << K << endl;
        int i = 1;
        int dx = (D + (i * i)) % n;
        while (arreglo[dx] != -1 && dx != D) {
            i++;
            dx = (D + (i * i)) % n;
        }
        if (arreglo[dx] == -1) {
            arreglo[dx] = K;
            cout << "La informacion se inserto en la posicion: " << dx << endl;
        } else {
            cout << "No se pudo insertar el valor. No hay espacio disponible." << endl;
        }
    }
}

// Reasignacion: Doble Direccion
void prueba_doble_direccion(int *arreglo, int K, int n) {
    int D = h(K, n); // Direccion inicial
    if (arreglo[D] == -1) {
        arreglo[D] = K;
        cout << "La informacion se inserto en la posicion: " << D << endl;
    } else {
        cout << "Colision en la posicion " << D << " para el valor " << K << endl;
        int dx = h_nueva(D, n);
        while (arreglo[dx] != -1 && dx != D) {
            dx = h_nueva(dx, n);
        }
        if (arreglo[dx] == -1) {
            arreglo[dx] = K;
            cout << "La informacion se inserto en la posicion: " << dx << endl;
        } else {
            cout << "No se pudo insertar el valor. No hay espacio disponible." << endl;
        }
    }
}

int main(int argc, char **argv) {
    if (argc < 3) {
        cout << "Por favor, ingrese el tamano del arreglo y el tipo de colision {l, c, d}.\n";
        return 1;
    }

    const int SIZE = atoi(argv[1]);
    if (SIZE >= 20) {
        cout << "Por favor ingrese un numero menor que 20 para el tamano del arreglo." << endl;
        return 1;
    }

    char caracter = argv[2][0];
    if (caracter != 'l' && caracter != 'c' && caracter != 'd') {
        cout << "No anadiste uno de los parametros validos para manejar colisiones.\n";
        return 1;
    }

    int* arreglo = new int[SIZE]; // Crear arreglo dinamico con el tamano especificado
    inicializar_arreglo_enteros(arreglo, SIZE);

    // Genera numeros aleatorios y llena el arreglo
    int* numeros = new int[SIZE];
    llenarArreglo(numeros, SIZE);
    mostrarArreglo(numeros, SIZE); // Muestra los numeros generados aleatoriamente

    // Inserta los numeros en el arreglo utilizando el metodo de colision seleccionado
    for (int i = 0; i < SIZE; ++i) {
        cout << "El arreglo es: ";
        mostrarArreglo(arreglo, SIZE);
        if (caracter == 'l') {
            prueba_lineal(arreglo, numeros[i], SIZE); // Prueba lineal
        } else if (caracter == 'c') {
            prueba_cuadratica(arreglo, numeros[i], SIZE); // Prueba cuadratica
        } else if (caracter == 'd') {
            prueba_doble_direccion(arreglo, numeros[i], SIZE); // Doble direccionamiento
        }
    }

    // Muestra el arreglo final
    mostrarArreglo(arreglo, SIZE);

    // Liberar memoria dinamica
    delete[] arreglo;
    delete[] numeros;

    return 0;
}
