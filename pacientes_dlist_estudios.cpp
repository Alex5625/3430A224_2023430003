#include <iostream>
#include <cmath>

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




//Funcion para imprimir pacientes
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

//Funcion elminar pacientes
void eliminarPaciente(Paciente*& head, const string& nombre){

    Paciente* actual = head;
    Paciente* anterior = nullptr;

    while (actual != nullptr && actual -> nombre != nombre){
        anterior = actual;
        actual = actual -> next;
    }

    if(actual != nullptr){
        if(anterior == nullptr){
            head = actual -> next;
        } else {
            anterior -> next = actual -> next;
        }
        delete actual;

    }
}

void promediosPacientes(Paciente*& head){

    int contador;
    double totalPeso;
    int totalEdad;
    const Paciente* actual = head;

    while (actual != nullptr){

        contador = contador + 1;
        totalPeso = totalPeso + actual->peso;
        totalEdad = totalEdad + actual -> edad;

        actual = actual -> next;

        /*
        cout << "El total de la edad es: " << totalEdad << "\n\n";
        cout << "El total del peso es: " << totalPeso << "\n";
        */
    }

    cout << "El promedio de los pesos de los pacientes es de " << totalPeso/contador << " kg.\n";
    cout << "El promedio de las edades de los pacientes es de " << totalEdad/contador << ".\n\n\n”";

}



void imcPacientes(Paciente*& head){

    double imc;
    const Paciente* actual = head;

    while (actual != nullptr){

        imc = actual -> peso / pow((actual -> altura)/100,2);

        cout << actual -> nombre << " posee un IMC de: " << imc << "\n";

        actual = actual -> next;
    }

}
int main(){
    Paciente* head = nullptr;

    //La funcion necesita estos parametros en orden: head, nombre, edad, altura, peso
    añadirPaciente(head, "ola", 23, 167, 45.8);
    añadirPaciente(head, "Amarlo", 54, 154, 39.1);
    añadirPaciente(head, "Erlo", 12, 121, 32.1);


    imprimirPacientes(head);

    promediosPacientes(head);

    imcPacientes(head);
    return 0;
}

