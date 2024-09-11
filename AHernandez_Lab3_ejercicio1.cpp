#include <iostream>

using namespace std;

struct Pila {
    static const int max = 5; // Tamaño máximo del arreglo
    int tope;
    int datos[max];

};

// Función para verificar si la pila está vacía
bool pila_vacia(const Pila& pila) {
    return pila.tope == -1;
}

// Función para verificar si la pila está llena
bool pila_llena(const Pila& pila) {
    return pila.tope == Pila::max - 1;
}

// Función para agregar un elemento a la pila
void push(Pila& pila, int dato) {
    if (pila_llena(pila)) {
        cout << "La pila está llena, no puedes agregar más elementos" << endl;
    } else {
        pila.datos[++pila.tope] = dato;
        cout << "Dato ingresado: " << dato << endl;
    }
}

// Función para eliminar un elemento de la pila
void pop(Pila& pila) {
    if (pila_vacia(pila)) {
        cout << "La pila está vacía, no puedes eliminar elementos porque no hay ninguno" << endl;
    } else {
        cout << "Elemento eliminado: " << pila.datos[pila.tope--] << endl;
    }
}

// Función para imprimir los datos de la pila
void imprimir_datos(const Pila& pila) {
    cout << "Elementos en la pila:" << endl;
    for (int i = pila.tope; i >= 0; --i) {
        cout << pila.datos[i] << endl;
    }
}

int main() {
    Pila pila; // Crear una instancia de Pila
    pila.tope = -1;




    char eleccion;
    int dato;
    while(true){
        cout << "Agregar/push [1]" << endl;
        cout << "Remover/pop [2]" << endl;
        cout << "ver pila [3]" << endl;
        cout << "----------------" << endl;
        cout << "Opcion: ";
        cin >> eleccion;
        cin.get();

        switch(eleccion){

            case '1':
                //push
                cout << "Que numero quieres agregar a la pila: " ;
                cin >> dato;
                push(pila, dato);
                cin.get();
                break;

            case '2':
                //pop
                pop(pila);
                break;

            case '3':
                //imprimir
                imprimir_datos(pila);
                break;

            default:
                cout << "Opcion no valida, intentelo de nuevo";
                continue;
        }

    }

}
