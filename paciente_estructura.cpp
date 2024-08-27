#include <iostream>


using namespace std;

// Define estructura de paciente, el peso es en kg, altura en metros
struct Paciente {
    string nombre;
    int edad;
    double altura;
    double peso;
};




int main(){

    Paciente paciente1;
    paciente1.nombre = "ola";
    paciente1.edad = 23;
    paciente1.altura = 1.67;
    paciente1.peso = 45.8;

    Paciente paciente2;
    paciente2.nombre = "Amarlo";
    paciente2.edad = 54;
    paciente2.altura = 1.54;
    paciente2.peso = 39.1;

    Paciente paciente3;
    paciente3.nombre = "Erlo";
    paciente3.edad = 12;
    paciente3.altura = 1.21;
    paciente3.peso = 32.1;


    cout << paciente1.nombre << "\n";
    cout << paciente1.edad << "\n" ;
    cout << paciente1.altura << "\n";
    cout << paciente1.peso << "\n\n" ;

    cout << paciente2.nombre << "\n";
    cout << paciente2.edad << "\n" ;
    cout << paciente3.altura << "\n";
    cout << paciente2.peso << "\n\n" ;

    cout << paciente3.nombre << "\n" ;
    cout << paciente3.altura << "\n";
    cout << paciente3.edad << "\n" ;
    cout << paciente3.peso << "\n\n";



}
