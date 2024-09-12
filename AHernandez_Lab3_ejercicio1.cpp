#include <iostream>

using namespace std;

struct Pila {
    int maximo; // Tamaño máximo del arreglo
    int tope;   // Índice del tope de la pila
    int* datos; // Usamos un puntero para manejar el array dinámicamente

    // Constructor para inicializar la pila
    Pila(int max) : maximo(max), tope(-1) {
        datos = new int[maximo]; // Asignamos memoria para el array
    }

    // Destructor para liberar la memoria
    ~Pila() {
        delete[] datos; // Liberar la memoria asignada
    }
};

// Función para verificar si la pila está vacía
bool pila_vacia(const Pila& pila) {
    return pila.tope == -1; // Si tope es -1, la pila está vacía
}

// Función para verificar si la pila está llena
bool pila_llena(const Pila& pila) {
    return pila.tope == pila.maximo - 1; // Si tope es igual a maximo - 1, la pila está llena
}

// Función para agregar un elemento a la pila
void push(Pila& pila, int dato) {
    if (pila_llena(pila)) {
        cout << "La pila está llena, no puedes agregar más elementos." << endl;
    } else {
        pila.datos[++pila.tope] = dato; // Incrementar tope y agregar dato
        cout << "Dato ingresado: " << dato << endl;
    }
}

// Función para eliminar un elemento de la pila
void pop(Pila& pila) {
    if (pila_vacia(pila)) {
        cout << "La pila está vacía, no puedes eliminar elementos porque no hay ninguno." << endl;
    } else {
        cout << "Elemento eliminado: " << pila.datos[pila.tope--] << endl; // Obtener el elemento y decrementar tope
    }
}

// Función para imprimir los datos de la pila
void imprimir_datos(const Pila& pila) {
    cout << "Elementos en la pila:" << endl;
    for (int i = pila.tope; i >= 0; --i) {
        cout << pila.datos[i] << endl; // Imprimir desde el tope hacia abajo
    }
}

int main() {
    int n; // Número máximo de contenedores por pila
    cout << "Ingrese el número máximo de contenedores por pila (n): ";
    cin >> n;

    Pila pila(n); // Crear una instancia de Pila
    char eleccion;

    while (true) {
        cout << "Agregar/push [1]" << endl;
        cout << "Remover/pop [2]" << endl;
        cout << "Ver pila [3]" << endl;
        cout << "Salir [4]" << endl;
        cout << "----------------" << endl;
        cout << "Opción: ";
        cin >> eleccion;

        switch (eleccion) {
            case '1': {
                // push
                int dato;
                cout << "¿Qué número quieres agregar a la pila? ";
                cin >> dato;
                push(pila, dato);
                break;
            }
            case '2':
                // pop
                pop(pila);
                break;

            case '3':
                // imprimir
                imprimir_datos(pila);
                break;

            case '4':
                cout << "Saliendo del programa." << endl;
                return 0; // Terminar el programa

            default:
                cout << "Opción no válida, intente de nuevo." << endl;
                break;
        }
    }
}
