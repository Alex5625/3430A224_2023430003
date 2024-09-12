#include <iostream>
#include <string>

using namespace std;

// Estructura para representar un contenedor
struct Contenedor {
    int numero; // Numero del contenedor
    string empresa; // Nombre de la empresa propietaria
};

// Estructura para representar una pila de contenedores
struct Pila {
    int maximo; // Capacidad máxima de la pila
    int tope; // Indice del tope de la pila
    Contenedor* valores; // Usamos un puntero para manejar el array de manera dinamica

    // Constructor para inicializar la pila
    Pila(int max) : maximo(max), tope(-1) {
        valores = new Contenedor[maximo]; // Asignamos memoria para el array
    }

    // Destructor para liberar la memoria
    ~Pila() {
        delete[] valores; // Liberar la memoria asignada
    }

    // Funcion para verificar si la pila esta vacia
    bool vacia() const {
        return tope == -1; // Si tope es -1, la pila esta vacia
    }

    // Función para verificar si la pila esta llena
    bool llena() const {
        return tope == maximo - 1; // Si tope es igual a maximo - 1, la pila esta llena
    }

    // Función para agregar un contenedor a la pila
    void ingresarContenedor(int numero, const string& empresa) {
        if (llena()) {
            cout << "La pila esta llena, no puedes agregar mas elementos." << endl;
        } else {
            valores[++tope] = Contenedor{numero, empresa}; // Incrementar tope y agregar dato
            cout << "Contenedor " << numero << "/" << empresa << " ingresado en la pila." << endl;
        }
    }

    // Función para retirar un contenedor
    void retirarContenedor(int numero) {
        if (vacia()) {
            cout << "La pila esta vacia, no puedes eliminar elementos." << endl;
            return;
        }

        // Pila temporal para almacenar contenedores mientras buscamos el deseado
        Contenedor temp[maximo];
        int tempTope = -1;
        bool encontrado = false;

        // Mover contenedores de la pila original a la pila temporal
        while (!vacia()) {
            Contenedor cont = valores[tope--];

            if (cont.numero == numero) {
                cout << "Contenedor " << cont.numero << "/" << cont.empresa << " retirado de la pila." << endl;
                encontrado = true;
                break; // Salir del bucle si se encontro el contenedor
            }

            temp[++tempTope] = cont; // Mover contenedor a la pila temporal
        }

        // Devolver los contenedores a la pila original
        for (int i = tempTope; i >= 0; --i) {
            valores[++tope] = temp[i];
        }

        if (!encontrado) {
            cout << "Contenedor " << numero << " no encontrado en la pila." << endl;
        }
    }

    // Funcion para mostrar el estado de la pila
    void mostrarEstado() const {
        cout << "Estado de la pila:" << endl;
        if (vacia()) {
            cout << "La pila esta vacia." << endl;
        } else {
            for (int i = 0; i <= tope; ++i) {
                cout << valores[i].numero << "/" << valores[i].empresa << endl;
            }
        }
    }
};

int main() {
    int n; // Numero maximo de contenedores por pila
    cout << "Ingrese el número máximo de contenedores por pila (n): ";
    cin >> n;

    Pila pila(n); // Crear una instancia de Pila
    char opcion;
    int numero;
    string empresa;

    while (opcion != '4') {
        cout << "\nOpciones:\n";
        cout << "1. Ingresar contenedor\n";
        cout << "2. Retirar contenedor\n";
        cout << "3. Mostrar estado de la pila\n";
        cout << "4. Salir\n";
        cout << "Ingrese su opción: ";
        cin >> opcion;

        switch (opcion) {
            case '1':
                cout << "Ingrese el número del contenedor: ";
                cin >> numero;
                cout << "Ingrese el nombre de la empresa: ";
                cin >> empresa;
                pila.ingresarContenedor(numero, empresa);
                break;

            case '2':
                cout << "Ingrese el número del contenedor a retirar: ";
                cin >> numero;
                pila.retirarContenedor(numero);
                break;

            case '3':
                pila.mostrarEstado();
                break;

            case '4':
                cout << "Saliendo del programa." << endl;
                break;

            default:
                cout << "Opción no válida. Intente de nuevo." << endl;
        }
    }

    return 0;
}
