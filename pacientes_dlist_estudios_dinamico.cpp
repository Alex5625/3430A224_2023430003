#include <cmath>
//Biblioteca que te facilita el uso de archivos csv para su apertura, lectura y editaje
//Estara incluido en el repositorio
#include "csv.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

// Define estructura de paciente, el peso es en kg, altura en metros
struct Paciente {
    string nombre;
    int edad;
    double altura;
    double peso;

    Paciente* next;
};


    //Funcion para añadir pacientes
    void añadirPacienteAuto(Paciente*& head, const string& nombre, int edad, int altura, double peso) {
        Paciente* nuevoPaciente = new Paciente();
        nuevoPaciente-> nombre = nombre;
        nuevoPaciente -> edad = edad;
        nuevoPaciente -> altura = altura;
        nuevoPaciente -> peso = peso;
        nuevoPaciente -> next = head;
        head = nuevoPaciente;

        cout << "Paciente añadido correcamente\n\n";
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
        cout << "Se ha eliminado correctamente\n\n";

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
         *        cout << "El total de la edad es: " << totalEdad << "\n\n";
         *        cout << "El total del peso es: " << totalPeso << "\n";
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

void leerCSV(Paciente*& head, const string& nombreArchivo){


    //TipoObjeto: CSVReader <cantidad de columnas>
    //abrir el archivo
    io::CSVReader<4> csvReader(nombreArchivo);
    //leer el archivo excluyendo la primera fila que son la cabecera
    csvReader.read_header(io::ignore_extra_column, "Nombre", "Edad", "Altura", "Peso");

    string nombre;
    int edad;
    int altura;
    double peso;

    //leer la columna con el respectivo orden y ser agregados a la lista
    while (csvReader.read_row(nombre, edad, altura, peso)) {
        añadirPacienteAuto(head, nombre, edad, altura, peso);
    }
}

int main(){

    Paciente* head = nullptr;


    añadirPacienteAuto(head, "ola", 23, 167, 45.8);
    añadirPacienteAuto(head, "Amarlo", 54, 154, 39.1);
    añadirPacienteAuto(head, "Erlo", 12, 121, 32.1);

    cout << "Bienvenido al simulador de agenda hospitalaria" << "\n";


    string nombre;
    while(true){
        int edad = 0;
        int altura = 0;
        double peso = 0.0;
        char numero_funcion;
        string archivo = "./nombres.csv";

        cout << "Por favor digite: \n1. si quiere ingresar los datos de un paciente \n2. si quiere eliminar un paciente\n3. si quiere ver la lista de pacientes que posee\n4. si desea determinar el promedio de peso y altura de los pacientes\n5. Calcular el IMC de cada paciente\n6. desea agregar pacientes desde un archivo .txt o .csv\n7. Salir.\n\n";
        cin >> numero_funcion;
        cout << "\n";
        switch (numero_funcion) {

            case '1':


                cout << "Dame el nombre del paciente\n";
                cin >> nombre;
                cin.get();
                cout << "Dame la edad del paciente\n";
                cin >> edad;
                cout << "Dame la altura en centimetros del paciente\n";
                cin >> altura;
                cout << "Dame el peso en kilogramos del paciente, de la forma (00.0)\n";
                cin >> peso;

                añadirPacienteAuto(head, nombre, edad, altura, peso);
                break;

            case '2':
                cout << "Ingrese el nombre del paciente que desea eliminar: ";
                cin >> nombre;
                eliminarPaciente(head, nombre);
                break;

            case '3':
                imprimirPacientes(head);
                break;
            case '4':
                promediosPacientes(head);
                break;

            case '5':
                imcPacientes(head);
                break;

            case '6':
                cout << "Entra al lector de archivos";
                leerCSV(head, archivo);
                break;

            case '7':
                //Vaciar memoria
                while (head != nullptr) {
                    Paciente* temporal = head;
                    head = head->next;
                    delete temporal;
                }
                return 0;

            default:
                break;
        }
    }

    return 0;
}

