#include <iostream>
#include <vector>
#include <cstring>
#include <fstream>
#include <climits>
#include <algorithm>

#define TRUE 0
#define FALSE 1

using namespace std;

//funcion para leer nodos y darles letras del alfabeto
void leer_nodos(string *vector, int n){
    int inicio = 97;
    for (int i = 0; i < n; i++) {
        vector[i] = inicio + i;
    }
};

// inicializa un vector de caracteres con espacios vacios
void inicializar_vector_caracter (string *vector, int n) {
    int col;

    // recorre el vector.
    for (col=0; col<n; col++) {
        vector[col] = " ";
    }
}

//incializa un vector D con los valores de la primera fila de la matriz
void inicializar_vector_D(int *D, int **matriz, int n){
    int col;

    for (col = 0; col < n; col++) {
        D[col] = matriz[0][col];
    }
}

// imprime los elementos del vector de caracteres
void imprimir_vector_caracter(string *vector, int n) {
    cout << endl;
    for (int i=0; i<n; i++) {
        cout << "vector[" << i << "]: " << vector[i] << " ";
    }
    cout << endl;
}

//busca un caracter en el vector y devuelve TRUE si lo encuentra
int busca_caracter(string c, string *vector, int n) {
    for (int j = 0; j < n; j++) {
        if (c == vector[j]) {
            return TRUE;
        }
    }
    return FALSE;
};

//actualiza el vector VS con los nodos que no estan en S
void actualizar_VS(string *V, string *S, string *VS, int n){
    int k = 0;
    inicializar_vector_caracter(VS, n);

    for (int j = 0; j < n; j++) {
        if (busca_caracter(V[j], S, n) != TRUE) {
            VS[k] = V[j];
            k++;
        }
    }
};

//busca el indice de un caracter en el vector V
int buscar_indice_caracter(string *V, string caracter, int n){
    int i = 0;
    for (i = 0; i < n; i++) {
        if (V[i] == caracter)
            return i;
    }
    return i;
};

//agrega un vertice a S cuando hay espacio vacio
void agrega_vertice_a_S(string *S, string vertice, int n){
    for (int i = 0; i < n; i++) {
        if (S[i] == " " ) {
            S[i] = vertice;
            return;
        }
    }
};

//Elige el vertice con el menor peso de VS y lo retorna
string elegir_vertice(string *VS, int *D, string *V, int n){
    int menor = -1;
    int peso;
    bool es_primero = true;
    string vertice;

    for (int i = 0; VS[i] != " "; i++) {
        peso = D[buscar_indice_caracter(V, VS[i], n)];
        if (peso != -1 && peso != 0) {
            if (es_primero || peso < menor) {
                menor = peso;
                vertice = VS[i];
                es_primero = false;
            }
        }
    }

    cout << "\nvertice: " << vertice << "\n\n";
    return vertice;
};

//calcula el minimo entre tres valores y retorna el mas bajo
int calcular_minimo(int dw, int dv, int mvw){
    int min;

    if (dw == -1) {
        if (dv != -1 && mvw != -1)
            min = dv + mvw;
        else
            min = -1;
    } else {
        if (dv != -1 && mvw != -1) {
            if (dw <= (dv + mvw))
                min = dw;
            else
                min = (dv + mvw);
        } else {
            min = dw;
        }
    }

    cout << "dw: " << dw << " dv: " << dv << " mvw: " << mvw << " min: " << min << endl;

    return min;
};

//actualiza los pesos en D segun los vertices visitados y la matriz de adyacencia
void actualizar_pesos(int *D, string *VS, int **matriz, string *V, string v, int n){
    int indice_w, indice_v;
    cout << "\n> actualiza pesos en D[]\n";

    indice_v = buscar_indice_caracter(V, v,n);
    for (int i = 0; VS[i] != " "; i++) {
        if (VS[i] != v) {
            indice_w = buscar_indice_caracter(V, VS[i], n);
            D[indice_w] = calcular_minimo(D[indice_w], D[indice_v], matriz[indice_v][indice_w]);
        }
    }
};

//imprime los elementos del vector D que contiene distancias minimas
void imprimir_vector_entero(int *vector, int n){
    for (int i = 0; i < n; i++) {
        cout << "D[" << i << "]: " << vector[i] << " ";
    }
    cout << endl;
};

//imprime la matriz de adyacencia completa con sus pesos respectivos
void imprimir_matriz(int **matriz, int n){
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << "matriz[" << i << "," << j << "]: " << matriz[i][j] << " ";
        }
        cout << endl;
    }
};

//modifica los pesos de la matriz segun las entradas del usuario
void modificar_pesos_matriz(int **matriz, int n){
    string respuesta;
    int numero;
    // Recorremos la matriz para pedir al usuario los pesos de las aristas
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j) {
                cout << "Peso de la arista de " << char('A' + i) << " a " << char('A' + j) << ": ";
                cin >> respuesta;
                if (respuesta == "0"){
                    numero = -1;
                } else{
                    numero = stoi(respuesta);
                }
                matriz[i][j] = numero;
            } else {
                matriz[i][j] = 0;  // Puede establecerse en 0 para indicar que no hay auto-bucles.
            }
        }
    }
}

//implementa el algoritmo de dijkstra para encontrar los caminos mas cortos del grafo
void aplicar_dijkstra(string *V, string *S, string *VS, int *D, int **matriz, int n){
    int i;
    string v;


    inicializar_vector_D(D, matriz, n );

    cout << "---------Estados iniciales ---------------------------------------\n";
    imprimir_matriz(matriz, n);
    cout << endl;
    imprimir_vector_caracter(S, n);
    imprimir_vector_caracter(VS, n);
    imprimir_vector_entero(D, n);
    cout << "------------------------------------------------------------------\n\n";

    cout << "> agrega primer valor V[0] a S[] y actualiza VS[]\n\n";
    agrega_vertice_a_S(S, V[0], n);
    imprimir_vector_caracter(S, n);

    actualizar_VS(V, S, VS, n);

    imprimir_vector_caracter(VS, n);
    imprimir_vector_entero(D, n);

    for (i = 1; i < n; i++) {
        cout << "\n> elige vertice menor en VS[] según valores en D[]\n";
        cout << "> lo agrega a S[] y actualiza VS[]\n";
        v = elegir_vertice(VS, D, V, n);

        agrega_vertice_a_S(S, v, n);
        imprimir_vector_caracter(S, n);

        actualizar_VS(V, S, VS, n);
        imprimir_vector_caracter(VS, n);

        actualizar_pesos(D, VS, matriz, V, v, n);
        imprimir_vector_entero(D, n);

    }
};

//imprime un grafo en formato DOT para generar la visualizacion
void imprimir_grafo(int **matriz, string *vector, int n){
    ofstream fp("matriz.txt");

    fp << "digraph G {\n";
    fp << "graph [rankdir=LR];\n";
    fp << "node [style=filled fillcolor=yellow];\n";

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j && matriz[i][j] > 0) {
                fp << vector[i] << "->" << vector[j] << " [label=" << matriz[i][j] << "];\n";
            }
        }
    }

    fp << "}\n";
    fp.close();

    system("dot -Tpng -o grafo.png matriz.txt");
    system("eog grafo.png &");
}

//inicializa la matriz nxn con -1 para indicar que no tiene conexiones
void inicializar_matriz_enteros (int **matriz, int n) {
    for (int fila=0; fila<n; fila++) {
        for (int col=0; col<n; col++) {
            matriz[fila][col] = -1;
        }
    }
}

//imprime el contenido del vector D que representa distancias minimas
void imprimir_camino(int *D, int n){

    cout << "El vector D es: ";
    for(int i = 0; i < n; i++){
        cout << " " << D[i];
    }
}

int main(int argc, char **argv) {
    // número de elementos.
    int n;

    // verificar que se pasaron suficientes argumentos
    if (argc < 2) {
        cout << "Por consola ingresa un numero mayor que dos!!\n vuelve a usar " << argv[0] << " <numero de elementos>" << endl;
        return -1;
    }


    // convierte string a entero.
    n = atoi(argv[1]);
    // valida cantidad de parámetros mínimos.
    if (n < 3) {
        cout << "Valor no valido, vuelve a intentarlo." << endl;
        return -1;
    }

    //inicializar_vector_caracter con las tres char
    string V[n], S[n], VS[n];
    int D[n];

    // inicializa e imprime vectores.
    inicializar_vector_caracter(V, n);
    inicializar_vector_caracter(S, n);
    inicializar_vector_caracter(VS, n);
    imprimir_vector_caracter(V, n);

    //Leer nodos
    leer_nodos(V,n);


    // crea matriz nxn de enteros.
    int **matriz;
    matriz = new int*[n];
    for(int i=0; i<n; i++)
        matriz[i] = new int[n];

    //añadir incializacion de creacion de matriz de adyacencia
    inicializar_matriz_enteros(matriz, n);

    //modificar los pesos de la matriz de adyacencia
    modificar_pesos_matriz(matriz, n);
    imprimir_vector_caracter(V, n);
    imprimir_matriz(matriz, n);

    aplicar_dijkstra(V, S, VS, D, matriz, n);

    imprimir_matriz(matriz, n);

    imprimir_camino(D,n);

    imprimir_grafo(matriz, V, n);

    return 0;
}



