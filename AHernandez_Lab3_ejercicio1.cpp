#include <iostream>

using namespace std;

struct Pila {
    int maximo; // Tamaño maximo del arreglo
    int tope;   // Indice del tope de la pila
    int* datos; // Usamos un puntero para manejar el array dinamicamente

    // Constructor para inicializar la pila
    Pila(int max) : maximo(max), tope(-1) {
        datos = new int[maximo]; // Asignamos memoria para el array
    }

    // Destructor para liberar la memoria
    ~Pila() {
        delete[] datos; // Liberar la memoria asignada
    }
};

// Funcion para verificar si la pila esta vacia
bool pila_vacia(const Pila& pila) {
    return pila.tope == -1; // Si tope es -1, la pila esta vacia
}

// Funcion para verificar si la pila esta llena
bool pila_llena(const Pila& pila) {
    return pila.tope == pila.maximo - 1; // Si tope es igual a maximo - 1, la pila esta llena
}

// Funcion para agregar un elemento a la pila
void push(Pila& pila, int dato) {
    if (pila_llena(pila)) {
        cout << "La pila esta llena, no puedes agregar mas elementos." << endl;
    } else {
        pila.datos[++pila.tope] = dato; // Incrementar tope y agregar dato
        cout << "Dato ingresado: " << dato << endl;
    }
}

// Funcion para eliminar un elemento de la pila
void pop(Pila& pila) {
    if (pila_vacia(pila)) {
        cout << "La pila esta vacia, no puedes eliminar elementos porque no hay ninguno." << endl;
    } else {
        cout << "Elemento eliminado: " << pila.datos[pila.tope--] << endl; // Obtener el elemento y decrementar tope
    }
}

// Funcion para imprimir los datos de la pila
void imprimir_datos(const Pila& pila) {
    cout << "Elementos en la pila:" << endl;
    for (int i = pila.tope; i >= 0; --i) {
        cout << pila.datos[i] << endl; // Imprimir desde el tope hacia abajo
    }
}

int main() {
    int n; // Numero maximo de contenedores por pila
    cout << "Ingrese el numero maximo de contenedores por pila (n): ";
    cin >> n;

    Pila pila(n); // Crear una instancia de Pila
    char eleccion;

    while (true) {
        cout << "Agregar/push [1]" << endl;
        cout << "Remover/pop [2]" << endl;
        cout << "Ver pila [3]" << endl;
        cout << "Salir [4]" << endl;
        cout << "----------------" << endl;
        cout << "Opcion: ";
        cin >> eleccion;

        switch (eleccion) {
            case '1': {
                // push
                int dato;
                cout << "¿Que numero quieres agregar a la pila? ";
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
                cout << "Opcion no valida, intente de nuevo." << endl;
                break;
        }
    }
}
