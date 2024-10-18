#include <iostream>
#include <cstdlib> // Para rand() y srand()
#include <ctime>   // Para time()
#include <chrono> //para chrono
using namespace std;
void llenarArreglo(int* arr, int size) {
    // Llenar el arreglo con numeros aleatorios entre 1 y 100
    for (int i = 0; i < size; ++i) {
        arr[i] = rand() % 100 + 1; // Genera un numero entre 1 y 100
    }
}

void mostrarArreglo(int* arr, int size) {
    // Mostrar los valores del arreglo
    for (int i = 0; i < size; ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

//-----------selection sort------------------------
void cambio_variables(int *xp, int *yp) {
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void seleccion(int arr[], int n) {
    int i, j, min;

    for (i = 0; i < n - 1; i++) {
        min = i;
        for (j = i + 1; j < n; j++) {
            if (arr[j] < arr[min]) {
                min = j;
            }
        }

        cambio_variables(&arr[min], &arr[i]);
    }
}

//-----------quick-sort------------------------
int particion(int *arreglo, int minimo, int maximo) {
    int pivote = arreglo[maximo];
    int i = (minimo - 1);
    for (int j = minimo; j < maximo; j++) {
        if (arreglo[j] <= pivote) {
            i++;
            cambio_variables(&arreglo[i], &arreglo[j]);
        }
    }

    cambio_variables(&arreglo[i + 1], &arreglo[maximo]); // Corrección aquí
    return (i + 1);
}

void QuickSort(int *arreglo, int minimo, int maximo) {
    if (minimo < maximo) {
        int pivote = particion(arreglo, minimo, maximo);

        QuickSort(arreglo, minimo, pivote - 1);

        QuickSort(arreglo, pivote + 1, maximo);
    }
}

int main(int argc, char **argv) {
    if (argc < 3){
        cout << "Por favor, ingrese los 2 parametros correspondientes como argumento.\n";
        return 1;
    }
    const int SIZE = atoi(argv[1]); // TAMANO DEL ARREGLO

    char caracter = argv[2][0]; // VERIFICACION DE MOSTRAR LOS ARREGLOS O NO
    if (caracter != 'n' || caracter != 's'){
        cout << "No añadiste uno de los parametros para mostrar el arreglo\nUSA -n- PARA NO MOSTRAR EL ARREGLO Y -s- PARA MOSTRAR EL ARREGLO\n " << endl;
        return 1;
    }

    int arr1[SIZE];

    // Inicializa la semilla para números aleatorios
    srand(static_cast<unsigned int>(time(0)));

    // Funciones para llenar e imprimir el arreglo
    llenarArreglo(arr1, SIZE);

    cout << "Arreglo de números enteros (antes de SelectionSort):\n";
    mostrarArreglo(arr1, SIZE);

    // Mide el tiempo de ejecución de SelectionSort
    auto start = chrono::high_resolution_clock::now();
    seleccion(arr1, SIZE);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> duration = end - start; // Milisegundos
    cout << "Duración del método SelectionSort: " << duration.count() << " ms\n";

    cout << "Arreglo después de SelectionSort:\n";
    mostrarArreglo(arr1, SIZE);

    //----------- QuickSort ------------------------
    int arr2[SIZE];
    llenarArreglo(arr2, SIZE);

    cout << "\nArreglo de números enteros (antes de QuickSort):\n";
    mostrarArreglo(arr2, SIZE);

    // Mide el tiempo de ejecución de QuickSort
    start = chrono::high_resolution_clock::now();
    QuickSort(arr2, 0, SIZE - 1); // Corrección aquí
    end = chrono::high_resolution_clock::now();
    duration = end - start;
    cout << "Duración del método QuickSort: " << duration.count() << " ms\n";

    cout << "Arreglo después de QuickSort:\n";
    mostrarArreglo(arr2, SIZE);

    return 0;
}