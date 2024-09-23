#include <fstream>
#include <iostream>
using namespace std;

struct Node {
    int info;
    Node* left;
    Node* right;
};

// Crear un nuevo nodo
Node* createNode(int data) {
    Node* newNode = new Node;
    newNode->info = data;
    newNode->left = nullptr;
    newNode->right = nullptr;
    return newNode;
}

class Arbol {
private:
    Node* root = nullptr;

    // Insertar un nodo
    Node* insertNode(Node* node, int data) {

        if (node == nullptr) {
            // Crear un nuevo nodo si se encuentra una posicion vacia
            return createNode(data);
        }

        if (data < node->info) {
            node->left = insertNode(node->left, data);
        } else if (data > node->info) {
            node->right = insertNode(node->right, data);
        } else {
            cout << "El nodo ya se encuentra en el árbol: " << data << endl;
        }

        return node;
    }

    // Buscar el nodo
    bool buscar_2(Node* root, int buscar) {

        if (root == nullptr) {
            return false;
        } else if (root->info == buscar) {
            return true;
        } else if (buscar < root->info) {
            return buscar_2(root->left, buscar);
        } else {
            return buscar_2(root->right, buscar);
        }
    }

    // Eliminar un nodo
    Node* deleteNode(Node* root, int key) {

        if (root == nullptr) {
            return root;
        }

        if (key < root->info) {
            root->left = deleteNode (root->left, key);
        } else if (key > root->info) {
            root->right = deleteNode(root->right, key);
        } else {
            if (root->left == nullptr) {
                Node* temp = root->right;
                delete root;
                return temp;
            } else if (root->right == nullptr) {
                Node* temp = root->left;
                delete root;
                return temp;
            }

            Node* temp = root->right;
            while (temp->left != nullptr) {
                temp = temp->left;
            }

            root->info = temp->info;
            root->right = deleteNode(root->right, temp->info);
        }

        return root;
    }

    // Impresion PreOrden
    void printPreOrden(Node* node) const {
        if (node == nullptr) {
            return;
        }
        cout << node->info << " ";
        printPreOrden(node->left);
        printPreOrden(node->right);
    }

    // Impresion InOrden
    void printInOrden(Node* node) const {
        if (node == nullptr) {
            return;
        }
        printInOrden(node->left);
        cout << node->info << " ";
        printInOrden(node->right);
    }

    // Impresion PostOrden
    void printPostOrden(Node* node) const {
        if (node == nullptr) {
            return;
        }
        printPostOrden(node->left);
        printPostOrden(node->right);
        cout << node->info << " ";
    }

    // Recorrer el arbol
    void recorrer(Node* node, ofstream& fp) {
        if (node != nullptr) {
            if (node->left != nullptr) {
                fp << node->info << "->" << node->left->info << ";" << endl;
            } else {
                string cadena = to_string(node->info) + "i";
                fp << "\"" << cadena << "\" [shape=point];" << endl;
                fp << node->info << "->\"" << cadena << "\";" << endl;
            }

            if (node->right != nullptr) {
                fp << node->info << "->" << node->right->info << ";" << endl;
            } else {
                string cadena = to_string(node->info) + "d";
                fp << "\"" << cadena << "\" [shape=point];" << endl;
                fp << node->info << "->\"" << cadena << "\";" << endl;
            }

            recorrer(node->left, fp);
            recorrer(node->right, fp);
        }
    }

public:
    Arbol() : root(nullptr) {}

    void insert(int data) {

        root = insertNode(root, data);
    }

    void buscar_1(int numero_buscar) {

        if (buscar_2(root, numero_buscar)) {
            cout << "\nSe encontró el numero ~ " << numero_buscar << "\n";
        } else {
            cout << "\nNo se ha encontrado el numero ~ " << numero_buscar << "\n";
        }
    }

    void eliminar_elemento(int numero_eliminar) {
        if (buscar_2(root, numero_eliminar)) {
            cout << "\nEliminando elemento\n";
            root = deleteNode(root, numero_eliminar);
            cout << "\nElemento eliminado\n";
        } else {
            cout << "\nNo se ha encontrado el elemento\n";
        }
    }

    void printPreOrden() const {
        printPreOrden(root);
        cout << endl;
    }

    void printInOrden() const {
        printInOrden(root);
        cout << endl;
    }

    void printPostOrden() const {
        printPostOrden(root);
        cout << endl;
    }

    void visualize() {
        ofstream fp("grafo.txt");

        if (!fp.is_open()) {
            cerr << "Error al abrir el archivo grafo.txt" << endl;
            return;
        }

        fp << "digraph G {" << endl;
        fp << "node [style=filled fillcolor=yellow];" << endl;

        recorrer(root, fp);

        fp << "}" << endl;
        fp.close();

        system("dot -Tpng -o arbol.png grafo.txt");
        system("eog arbol.png");
    }
};

int main() {
    Arbol arbol;

    char opcion;
    int numero;
    while(opcion != 8){
        cout << "\nOpciones:\n";
        cout << "1. Inertar un valor\n";
        cout << "2. Buscar un numero\n";
        cout << "3. Recorrer en preOrden\n";
        cout << "4. Recorrer en inOrden\n";
        cout << "5. Recorrer en postOrden\n";
        cout << "6. Visualizar el arbol\n";
        cout << "7. Eliminar un numero\n";
        cout << "8. Salir\n";
        cout << "Ingrese su opción: ";
        while(!(cin >> numero)) {  // Mientras la entrada no sea válida
            cout << "Error: No es un número válido. Intenta de nuevo: ";
            cin.clear();  // Limpia el estado de error
            cin.ignore(10000, '\n');
        }

        //AÑADIR VALIDACIONES
        switch(opcion){
            case '1':
                cout << "Dame el numero que deseas insertar: ";
                while(!(cin >> numero)) {  // Mientras la entrada no sea válida
                    cout << "Error: No es un número válido. Intenta de nuevo: ";
                    cin.clear();  // Limpia el estado de error
                    cin.ignore(10000, '\n');
                }
                arbol.insert(numero);
                break;
            case '2':
                cout << "Dame el numero que deseas buscar: ";
                while(!(cin >> numero)) {  // Mientras la entrada no sea válida
                    cout << "Error: No es un número válido. Intenta de nuevo: ";
                    cin.clear();  // Limpia el estado de error
                    cin.ignore(10000, '\n');
                }
                arbol.buscar_1(numero);
                break;

            case '3':
                cout << "Recorrido en preorden: ";
                arbol.printPreOrden();
                break;
            case '4':
                cout << "Recorrido en InOrden: ";
                arbol.printInOrden();
                break;
            case '5':
                cout << "Recorrido en PostOrden: ";
                arbol.printPostOrden();
                break;
            case '6':
                cout << "Se va a visualizar el arbol" << endl;
                 arbol.visualize();
                break;
            case '7':
                cout << "Dame el numero que deseas eliminar: ";
                while(!(cin >> numero)) {  // Mientras la entrada no sea válida
                    cout << "Error: No es un número válido. Intenta de nuevo: ";
                    cin.clear();  // Limpia el estado de error
                    cin.ignore(10000, '\n');
                }
                arbol.eliminar_elemento(numero);
                break;
            case '8':
                cout << "Salir" << endl;
                return 0;
                break;
            default:
                cout << "Opcion no valida. Intente de nuevo." << endl;
                break;
        }

    }
}
