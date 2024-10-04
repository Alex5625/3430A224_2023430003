#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

#define TRUE 1
#define FALSE 0
using namespace std;

//izquierdo = 0
//derecho = 1
enum {IZQUIERDO, DERECHO};

struct Nodo {
    int dato;
    int FE;
    Nodo* derecho;
    Nodo* izquierdo;
    Nodo* padre;
};

typedef Nodo* pNodo;
typedef Nodo* Arbol;

void RotaIzquierdaDerecha(Arbol* raiz, pNodo nodo) {
    pNodo Padre = nodo->padre;
    pNodo P = nodo;
    pNodo Q = P->izquierdo;
    pNodo R = Q->derecho;
    pNodo B = R->izquierdo;
    pNodo C = R->derecho;

    if (Padre){
        if (Padre->derecho == nodo){
            Padre->derecho = R;
        }
        else {
            Padre->izquierdo = R;
        }
    }
    else
        *raiz = R;

    Q->derecho = B;
    P->izquierdo = C;
    R->izquierdo = Q;
    R->derecho = P;

    R->padre = Padre;
    P->padre = Q->padre = R;
    if (B) B->padre = Q;
    if (C) C->padre = P;

    switch (R->FE) {
        case -1: Q->FE = 0; P->FE = 1; break;
        case 0: Q->FE = 0; P->FE = 0; break;
        case 1: Q->FE = -1; P->FE = 0; break;
    }

    R->FE = 0;
}

void RotaDerechaIzquierda(Arbol* a, pNodo nodo) {
    pNodo Padre = nodo->padre;
    pNodo P = nodo;
    pNodo Q = P->derecho;
    pNodo R = Q->izquierdo;
    pNodo B = R->izquierdo;
    pNodo C = R->derecho;

    if (Padre){
        if (Padre->derecho == nodo){
            Padre->derecho = R;
        } else {
            Padre->izquierdo = R;
        }
    }
    else
        *a = R;

    P->derecho = B;
    Q->izquierdo = C;
    R->izquierdo = P;
    R->derecho = Q;

    R->padre = Padre;
    P->padre = Q->padre = R;
    if (B) B->padre = P;
    if (C) C->padre = Q;

    switch (R->FE) {
        case -1: P->FE = 0; Q->FE = 1; break;
        case 0: P->FE = 0; Q->FE = 0; break;
        case 1: P->FE = -1; Q->FE = 0; break;
    }
    R->FE = 0;
}

void RotaIzquierdaIzquierda(Arbol* a, pNodo nodo) {
    pNodo Padre = nodo->padre;
    pNodo P = nodo;
    pNodo Q = P->izquierdo;
    pNodo B = Q->derecho;

    if (Padre){
        if (Padre->derecho == P){
            Padre->derecho = Q;
        }
        else {
            Padre->izquierdo = Q;
        }
    }
    else
        *a = Q;

    P->izquierdo = B;
    Q->derecho = P;

    P->padre = Q;
    if (B) B->padre = P;
    Q->padre = Padre;

    P->FE = 0;
    Q->FE = 0;
}

void RotaDerechaDerecha(Arbol* a, pNodo nodo) {
    pNodo Padre = nodo->padre;
    pNodo P = nodo;
    pNodo Q = P->derecho;
    pNodo B = Q->izquierdo;

    if (Padre){
        if (Padre->derecho == P){
            Padre->derecho = Q;
        }
        else {
            Padre->izquierdo = Q;
        }
    }
    else
        *a = Q;

    P->derecho = B;
    Q->izquierdo = P;

    P->padre = Q;

    if (B){
        B->padre = P;
    }
    Q->padre = Padre;

    P->FE = 0;
    Q->FE = 0;
}


void Equilibrar(Arbol* a, pNodo nodo, int rama, int nuevo) {
    int salir = FALSE;

    while (nodo && !salir) {
        if (nuevo){
            if (rama == IZQUIERDO){
                nodo->FE -= 1;
            } else {
                nodo->FE += 1;
            }
        } else{

            if (rama == IZQUIERDO){
                nodo->FE += 1;
            }
            else {
                nodo->FE -= 1;
            }
        }

        if (nodo->FE == 0)
            salir = TRUE;
        else if (nodo->FE == -2) {
            if (nodo->izquierdo->FE == 1)
                RotaIzquierdaDerecha(a, nodo);
            else
                RotaIzquierdaIzquierda(a, nodo);
            salir = TRUE;
        } else if (nodo->FE == 2) {
            if (nodo->derecho->FE == -1)
                RotaDerechaIzquierda(a, nodo);
            else
                RotaDerechaDerecha(a, nodo);
            salir = TRUE;
        }

        //Retroceder en el arbol, disminuyendo la altura
        if (nodo->padre) {
            if (nodo->padre->derecho == nodo) {
                rama = DERECHO;
            } else {
                rama = IZQUIERDO;
            }
        }
        nodo = nodo->padre;
    }
}

void GenerarGrafo(Arbol ArbolInt) {
    ofstream fp("grafo.txt");

    fp << "digraph G {\n";
    fp << "node [style=filled fillcolor=sienna];\n";

    if (ArbolInt) {
        fp << "nullraiz [shape=point];\n";
        fp << "nullraiz->" << ArbolInt->dato << " [label=" << ArbolInt->FE << "];\n";
        PreOrden(ArbolInt, fp);
    } else {
        cout << "El árbol está vacío. No se puede generar el gráfico.\n";
    }

    fp << "}\n";
    fp.close();

    system("dot -Tpng -ografo.png grafo.txt");
    system("eog grafo.png &");
}

void PreOrden(Arbol a, ofstream &fp) {
    static int nullCount = 0;  // Para numerar los nodos nulos

    if (a) {
        // Escribir el nodo actual
        fp << a->dato << " [style=filled fillcolor=turquoise];\n";

        // Si el hijo izquierdo existe, agregar la arista
        if (a->izquierdo) {
            fp << a->dato << "->" << a->izquierdo->dato << " [label=" << a->izquierdo->FE << "];\n";
            PreOrden(a->izquierdo, fp);
        } else {
            // Si no existe, agregar un nodo nulo
            fp << "null" << nullCount << " [shape=point];\n";
            fp << a->dato << "->null" << nullCount << ";\n";
            nullCount++;
        }

        // Si el hijo derecho existe, agregar la arista
        if (a->derecho) {
            fp << a->dato << "->" << a->derecho->dato << " [label=" << a->derecho->FE << "];\n";
            PreOrden(a->derecho, fp);
        } else {
            // Si no existe, agregar un nodo nulo
            fp << "null" << nullCount << " [shape=point];\n";
            fp << a->dato << "->null" << nullCount << ";\n";
            nullCount++;
        }
    }
}



void Podar(Arbol* a) {
    if (*a) {
        Podar(&(*a)->izquierdo);
        Podar(&(*a)->derecho);
        free(*a);
        *a = nullptr;
    }
}

void Insertar(Arbol* a, int dat) {
    pNodo padre = nullptr;
    pNodo actual = *a;

    //Buscar el nodo que contiene el numero ingresado
    while (actual != nullptr && dat != actual->dato) {
        //Se queda finalmente con el nodo antes del null
        padre = actual;

        if (dat < actual->dato)
            actual = actual->izquierdo;
        else if (dat > actual->dato)
            actual = actual->derecho;
    }
    //cuando no existe el dato
    if (actual != nullptr)
        return;
    //Si el arbol esta vacio
    if (padre == nullptr) {
        *a = new Nodo{dat, 0, nullptr, nullptr, nullptr};
    //Si el dato del nodo padre es MENOR que el numero ingresado
    } else if (dat < padre->dato) {
        actual = new Nodo{dat, 0, nullptr, nullptr, padre};
        padre->izquierdo = actual;
        Equilibrar(a, padre, IZQUIERDO, TRUE);
    //Si el dato del nodo padre es MAYOR que el numero ingresado
    } else if (dat > padre->dato) {
        actual = new Nodo{dat, 0, nullptr, nullptr, padre};
        padre->derecho = actual;
        Equilibrar(a, padre, DERECHO, TRUE);
    }
}

void Eliminar(Arbol* a, int dato){
    pNodo padre = nullptr;
    pNodo actual = *a;

    //Buscar el nodo correspondiente al numero ingresado
    while (actual != nullptr && dato != actual -> dato){
        padre = actual;
        if (dato < actual -> dato){
            actual = actual -> izquierdo;
        } else {
            actual = actual -> derecho;
        }
    }

    //si no se encuentra el dato se cierra el procedimiento
    if (actual == nullptr){
        return;
    }

    //Caso 1: Si el nodo es un nodo hoja
    if (actual -> izquierdo == nullptr && actual -> derecho == nullptr){
        if (padre == nullptr){
            //Si es la raiz
            *a = nullptr;
        } else if (padre -> izquierdo == actual){
            padre -> izquierdo = nullptr;
        } else {
            padre -> derecho == nullptr;
        }
    //Caso 2: Si tiene un hijo
    /*Como funciona/como es la sintaxis de  *?*: (condicion booleana) ? accion1 si es true: accion 2 si es false;  */
    } else if (actual -> izquierdo == nullptr || actual -> derecho == nullptr){
        pNodo hijo = (actual -> izquierdo != nullptr) ? actual -> izquierdo : actual -> derecho;

        if (padre == nullptr){
            //Si es la raiz
            *a = hijo;
        } else if (padre -> izquierdo == actual){
            padre -> izquierdo = hijo;
        } else {
            padre -> derecho = hijo;
        }
        //actualizar el padre del hijo
        hijo -> padre = padre;
    //Caso 3: Si tiene dos hijos
    } else {
        //Encontrar el predecesor inOrden (el nodo mas a la derecha del sub-arbol izquierdo)
        pNodo predecesorPadre = actual;
        pNodo predecesor = actual -> izquierdo;

        while (predecesor -> derecho != nullptr) {
          predecesorPadre = predecesor;
          predecesor = predecesor -> derecho;
        }
         //Reemplazar datos
        actual -> dato = predecesor -> dato;

        //Eliminar el predecesor
        if (predecesorPadre != actual){
            predecesorPadre -> derecho = predecesor -> izquierdo;
            if (predecesor -> izquierdo != nullptr){
                predecesor -> izquierdo -> padre = predecesorPadre;
            }
        } else {
            predecesorPadre -> izquierdo = predecesor -> izquierdo;
            if (predecesor -> izquierdo != nullptr){
                predecesor -> izquierdo -> padre = predecesorPadre;
            }
        }

        //ahora actual posee el nodo que vamos a eliminar
        actual = predecesor;
    }

    //Liberar la memoria del nodo
    delete actual;

    //Equilibrar desde el padre del nodo eliminado
    Equilibrar(a, padre, (padre != nullptr && padre -> izquierdo == actual) ? IZQUIERDO : DERECHO, FALSE);
}


// Función para validar que la entrada del usuario sea un entero
int obtenerNumeroValido(const string& mensaje) {
    string ingreso_usuario;
    bool valid = false;
    int numero = 0;

    while (!valid) {
        cout << mensaje;
        cin >> ingreso_usuario;

        try {
            numero = stoi(ingreso_usuario);  // Intenta convertir la entrada a un entero
            valid = true;  // Si la conversión es exitosa, salimos del bucle
        }
        catch (const invalid_argument& e) {
            cout << "Entrada inválida, por favor ingresa un número entero válido.\n";
        }
        catch (const out_of_range& e) {
            cout << "Número fuera de rango, intenta de nuevo.\n";
        }
    }

    return numero;  // Devuelve el número entero validado
}


void Modificar(pNodo* a, int numero){
    int numero_agregar;
    pNodo actual = *a;

    //Buscar el nodo correspondiente al numero ingresado
    while (actual != nullptr && numero != actual -> dato){
        if (numero < actual -> dato){
            actual = actual -> izquierdo;
        } else {
            actual = actual -> derecho;
        }
    }

    //si no se encuentra el dato se cierra el procedimiento
    if (actual == nullptr){
        return;
    }

    cout << "Dame el numero que quieres agregar: ";
    while(!(cin >> numero_agregar)) {  // Mientras la entrada no sea válida
        cout << "Error: No es un número válido.\nIntenta de nuevo: ";
        cin.clear();  // Limpia el estado de error
        cin.ignore(10000, '\n');
    }

    // Guardar el viejo dato
    int viejoDato = actual->dato;

    // Modificar el dato
    actual->dato = numero_agregar;

    // Verificar si se mantiene la propiedad del arbol binario
    if ((actual->izquierdo != nullptr && numero_agregar < actual->izquierdo->dato) ||
        (actual->derecho != nullptr && numero_agregar > actual->derecho->dato)) {
        cout << "El nuevo número no cumple con las propiedades del árbol." << endl;
        // Restaurar el viejo dato si es necesario
        actual->dato = viejoDato;
        return;
    }

    actual -> dato = numero_agregar;

}


int Buscar(pNodo root, int numero) {

    if (root == nullptr) {
        cout << "\nNO SE ENCONTRO EL NUMERO" << endl;
        return false;
    } else if (root -> dato == numero) {
        cout << "\nSE ENCONTRO EL NUMERO" << endl;
        return true;
    } else if (numero < root -> dato) {
        return Buscar(root -> izquierdo, numero);
    } else {
        return Buscar(root -> derecho, numero);
    }

}


void MenuPrincipal() {
    cout << "\n";
    cout << "<1> Ingresar numero\n";
    cout << "<2> Busqueda numero\n";
    cout << "<3> Eliminar numero\n";
    cout << "<4> Modificar elemento ingresado\n";
    cout << "<5> Generar Grafo\n";
    cout << "<6> Salir\n";
    cout << "\n";
}

int main() {
    Arbol ArbolInt = nullptr;
    int opcion = 0;
    int valor;

    while (opcion != 6) {
        MenuPrincipal();
        cout << "Ingrese su opcion: ";
        while(!(cin >> opcion)) {  // Mientras la entrada no sea válida
            cout << "Error: No es un número válido.\nIntenta de nuevo: ";
            cin.clear();  // Limpia el estado de error
            cin.ignore(10000, '\n');
        }

        switch (opcion) {
            case 1:
                cout << "Ingrese un numero para añadir: ";
                while(!(cin >> valor)) {  // Mientras la entrada no sea válida
                    cout << "Error: No es un número válido.\nIntenta de nuevo: ";
                    cin.clear();  // Limpia el estado de error
                    cin.ignore(10000, '\n');
                }
                Insertar(&ArbolInt, valor);
                break;
            case 2:
                cout << "Ingrese un numero para buscar: ";
                while(!(cin >> valor)) {  // Mientras la entrada no sea válida
                    cout << "Error: No es un número válido.\nIntenta de nuevo: ";
                    cin.clear();  // Limpia el estado de error
                    cin.ignore(10000, '\n');
                }
                Buscar(ArbolInt, valor);
                break;
            case 3:
                cout << "Ingrese un numero para eliminar: ";
                while(!(cin >> valor)) {  // Mientras la entrada no sea válida
                    cout << "Error: No es un número válido.\nIntenta de nuevo: ";
                    cin.clear();  // Limpia el estado de error
                    cin.ignore(10000, '\n');
                }
                Eliminar(&ArbolInt, valor);
                break;
            case 4:
                cout << "Ingresa un numero para eliminar: ";
                while(!(cin >> valor)) {  // Mientras la entrada no sea válida
                    cout << "Error: No es un número válido.\nIntenta de nuevo: ";
                    cin.clear();  // Limpia el estado de error
                    cin.ignore(10000, '\n');
                }
                Modificar(&ArbolInt, valor);
                break;
            case 5:
                GenerarGrafo(ArbolInt);
                break;
        }
    }

    /* Liberar memoria asociada al arbol. */
    Podar(&ArbolInt);
    return 0;
}
