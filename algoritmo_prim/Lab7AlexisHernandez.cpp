#include <iostream>
#include <fstream>
#include <climits>

using namespace std;

class Grafo {
private:
    int n; // número de nodos
    int** matriz; // Matriz de adyacencia
    int* padre; // Para almacenar el árbol de expansión mínima
    int* llave; // Llaves utilizadas para seleccionar la arista de menor peso
    bool* nodos_encontrados; // Conjunto de nodos incluidos en el MST

public:
    // Constructor que inicializa la matriz de adyacencia y otros arrays
    Grafo(int n) {
        this->n = n;
        matriz = new int*[n];

        //incializar matriz con -1 para que se muestre que no hay conexiones
        for (int i = 0; i < n; i++) {
            matriz[i] = new int[n];
            for (int j = 0; j < n; j++) {
                matriz[i][j] = -1;
            }
        }

        padre = new int[n];
        llave = new int[n];
        nodos_encontrados = new bool[n];
        for (int i = 0; i < n; i++) {
            llave[i] = INT_MAX;
            nodos_encontrados[i] = false;
        }
    }

    // Destructor para liberar la memoria
    ~Grafo() {
        for (int i = 0; i < n; i++) {
            delete[] matriz[i];
        }
        delete[] matriz;
        delete[] padre;
        delete[] llave;
        delete[] nodos_encontrados;
    }

    // Método para leer la matriz de adyacencia desde la terminal
    void leerMatriz() {
        string respuesta;
        int numero;
        cout << "Ingrese la matriz de adyacencia (" << n << "x" << n << "):\n";
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i != j) {
                    cout << "Peso de la arista de " << char('A' + i) << " a " << char('A' + j) << ": ";
                    cin >> respuesta;
                    if (respuesta == "0"){
                        numero = -1;
                    } else {
                        numero = stoi(respuesta);
                    }
                    matriz[i][j] = numero;
                } else {
                    matriz[i][j] = 0;
                }
            }
        }
    }

    //------------------------------------algoritmo de prim----------------------------------------------

    //Metodo que encuentra el peso minimo de los vertices
    int llaveMinima() {
        int min = INT_MAX;
        int min_index;
        for (int v = 0; v < n; v++) {
            if (!nodos_encontrados[v] && llave[v] < min) {
                min = llave[v];
                //min_index representa al nodo que posee menor peso que tiene el grafo
                min_index = v;
            }
        }
        return min_index;
    }

    // Implementación del algoritmo de Prim
    void aplicarPrim() {
        llave[0] = 0; // Inicializar la primera llave
        padre[0] = -1; // El primer nodo no tiene padre

        for (int count = 0; count < n - 1; count++) {
            int u = llaveMinima();
            nodos_encontrados[u] = true;

            for (int v = 0; v < n; v++) {
                if (matriz[u][v] != -1 && !nodos_encontrados[v] && matriz[u][v] < llave[v]) {
                    padre[v] = u;
                    llave[v] = matriz[u][v];
                }
            }
        }
    }
//------------------------------------algoritmo de prim----------------------------------------------
    // Método para imprimir las conexiones del MST
    void imprimirMatriz() {
        cout << "\nConexiones del Árbol de Expansión Mínima:\n";
        for (int i = 1; i < n; i++) {
            cout << char('A' + padre[i]) << " - " << char('A' + i) << " con peso " << matriz[i][padre[i]] << "\n";
        }
    }

    // Método para generar el archivo .dot para Graphviz
    void generarGraphviz(const string& filename, bool arbol_minimo = false) {
        ofstream archivo(filename);
        if (!archivo.is_open()) {
            cout << "no se pudo abrir el archivo.\n";
            return;
        }

        archivo << "digraph G {\n";
        archivo << "graph [rankdir=LR];\n";
        archivo << "node [shape=circle style=filled fillcolor=yellow];\n";

        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (matriz[i][j] != -1) {
                    if (arbol_minimo && (padre[j] == i || padre[i] == j)) {
                        archivo << "    " << char('A' + i) << " -- " << char('A' + j) << " [label=\"" << matriz[i][j] << "\", color=red];\n";
                    } else if (!arbol_minimo) {
                        archivo << "    " << char('A' + i) << " -- " << char('A' + j) << " [label=\"" << matriz[i][j] << "\", color=blue];\n";
                    }
                }
            }
        }

        archivo << "}\n";
        archivo.close();

        if (!arbol_minimo){
            system("dot -Tpng -o grafo_original.png grafo_original.txt");
            system("eog grafo_original.png &");
        } else {

            system("dot -Tpng -o grafo_minimo.png grafo_costo_minimo.txt");
            system("eog grafo_minimo.png &");
        }
    }
};

int main(int argc, char** argv) {
    if (argc < 2) {
        cout << "Por favor, ingrese el número de nodos como argumento.\n";
        return 1;
    }

    int n = atoi(argv[1]);
    if (n < 3) {
        cout << "El número de nodos debe ser mayor que 2.\n";
        return 1;
    }

    Grafo grafo(n);

    grafo.leerMatriz();
    grafo.aplicarPrim();

    // Generar los dos grafos, el original y el MST
    grafo.generarGraphviz("grafo_original.txt");
    grafo.generarGraphviz("grafo_costo_minimo.txt", true);

    // Imprimir las conexiones del MST
    grafo.imprimirMatriz();

    return 0;
}
