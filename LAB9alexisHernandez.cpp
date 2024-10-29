#include <iostream>
#include <cstdlib> // Para rand() y srand()
#include <ctime> // Para time()

using namespace std;

// Llena el arreglo con números aleatorios
void llenarArreglo(int* arr, int size) {
    for (int i = 0; i < size; ++i) {
        arr[i] = rand() % 100 + 1;
    }
}

// Muestra el arreglo
void mostrarArreglo(int* arr, int size) {
    cout << "ARREGLO[ " << size << " ]: ";
    for (int i = 0; i < size; ++i) {
        cout << " " << arr[i] << " ";
    }
    cout << endl;
}

// Inicializa el arreglo con -1
void inicializar_arreglo_enteros(int *arreglo, int n) {
    for (int contador = 0; contador < n; contador++) {
        arreglo[contador] = -1;
    }
}

// Función para determinar si un número es primo
bool esPrimo(int num) {
    if (num <= 1) return false;
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) return false;
    }
    return true;
}

// Busca el primo más cercano a un número dado
int buscarPrimoCercano(int &numero) {
    int menor = numero;
    int mayor = numero;

    while (menor > 1 && !esPrimo(menor)) {
        menor--;
    }

    while (!esPrimo(mayor)) {
        mayor++;
    }

    if (numero - menor <= mayor - numero) {
        return menor;
    } else {
        return mayor;
    }
}

// Función hash (h(K))
int h(int K, int numero_primo) {
    return K % numero_primo;
}

// Doble hashing (H_prime)
int H_nueva(int K, int numero_primo) {
    return 1 + (K % (numero_primo - 1));
}

// Función para manejar colisiones
void colisiones(int numero, int *arreglo, int indice, int tamaño, char caracter, int numero_primo) {
    if (caracter == 'l') { // Prueba lineal
        while (arreglo[indice] != -1 && indice < tamaño) {
            indice++;
            if (indice >= tamaño) {
                indice = 0;
            }
        }
        arreglo[indice] = numero;
    } else if (caracter == 'c') { // Prueba cuadrática
        int j = 1;
        while (arreglo[indice] != -1 && j < tamaño) {
            indice = (indice + j * j) % tamaño;
            j++;
        }
        arreglo[indice] = numero;
    } else if (caracter == 'd') { // Doble direccionamiento
        int j = 1;
        while (arreglo[indice] != -1 && j < tamaño) {
            indice = (indice + H_nueva(numero, numero_primo) * j) % tamaño;
            j++;
        }
        arreglo[indice] = numero;
    }
}

// Función para ingresar un número en el arreglo
void ingresa_numero_arreglo(int numero, int *arreglo, int indice, int tamaño, char caracter, int numero_primo) {
    if (arreglo[indice] == -1) {
        cout << "La informacion se encuentra en la posicion: " << indice << " del arreglo" <<endl;
        arreglo[indice] = numero;
    } else {
        cout << "El arreglo en esa posición ya está ocupado por otro valor, se buscará el espacio para moverlo." << endl;
        colisiones(numero, arreglo, indice, tamaño, caracter, numero_primo);
    }
}

// Función hash principal que distribuye los elementos
void funcion_hash(int *arreglo, char caracter, int tamaño_arreglo) {
    int indice;
    int i = 0;
    int arreglo_ordenado[tamaño_arreglo];
    inicializar_arreglo_enteros(arreglo_ordenado, tamaño_arreglo);
    const int numero_primo = buscarPrimoCercano(tamaño_arreglo); // Número primo más cercano al tamaño
    cout << "El numero primo mas cercano a " << tamaño_arreglo << " es " << numero_primo << endl;
    while (i < tamaño_arreglo) {
        indice = h(arreglo[i], numero_primo); // Usa h(K)
        ingresa_numero_arreglo(arreglo[i], arreglo_ordenado, indice, tamaño_arreglo, caracter, numero_primo);
        i++;
    }

    // Muestra el arreglo ordenado después de aplicar el hash
    mostrarArreglo(arreglo_ordenado, tamaño_arreglo);
}

int main(int argc, char **argv) {
    if (argc < 3) {
        cout << "Por favor, ingrese los 2 parámetros correspondientes como argumento.\n";
        return 1;
    }

    const int SIZE = atoi(argv[1]);

    if (SIZE > 20) {
        cout << "Por favor ingrese un número menor que 20 para el tamaño del arreglo." << endl;
        return 1;
    }

    char caracter = argv[2][0];
    if (caracter != 'l' && caracter != 'c' && caracter != 'd') {
        cout << "No añadiste uno de los parámetros válidos para manejar colisiones.\n";
        return 1;
    }

    int arr1[SIZE];

    srand(static_cast<unsigned int>(time(0)));

    llenarArreglo(arr1, SIZE);
    mostrarArreglo(arr1, SIZE);
    funcion_hash(arr1, caracter, SIZE);

    return 0;
}
