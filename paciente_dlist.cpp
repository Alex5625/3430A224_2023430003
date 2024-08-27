#include <iostream>


using namespace std;

// Define estructura de paciente, el peso es en kg, altura en metros
struct Paciente {
    string nombre;
    int edad;
    double altura;
    double peso;
    Paciente* next;
};


//Funcion para añadir pacientes a la lista
void añadirPaciente(Paciente*& head, const string& nombre, int edad, int altura, double peso) {
    Paciente* nuevoPaciente = new Paciente();
    nuevoPaciente-> nombre = nombre;
    nuevoPaciente -> edad = edad;
    nuevoPaciente -> altura = altura;
    nuevoPaciente -> peso = peso;
    nuevoPaciente -> next = head;
    head = nuevoPaciente;
}

void imprimirPacientes(const Paciente* head){

    const Paciente* actual = head;
    while (actual != nullptr){

        cout << "Nombre: " << actual->nombre << "\n";
        cout << "edad: " << actual->edad<< "\n";
        cout << "altura: " << actual->altura << "\n";
        cout << "peso: " << actual->peso << "\n\n";
        actual = actual -> next;
    }
}


/*void printPeople(const Person* head) {
    const Person* current = head;
    while (current != nullptr) {
        std::cout << current->name << " is " << current->age << " years old." << std::endl;
        current = current->next;
    }
}
*/
int main(){
    Paciente* head = nullptr;


    añadirPaciente(head, "ola", 23, 167, 45.8);
    añadirPaciente(head, "Amarlo", 54, 154, 39.1);
    añadirPaciente(head, "Erlo", 12, 121, 32.1);


    imprimirPacientes(head);
}

