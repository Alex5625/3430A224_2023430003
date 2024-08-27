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

    Paciente comunidad[3];

    comunidad[0].nombre = "ola";
    comunidad[0].edad = 23;
    comunidad[0].altura = 167;
    comunidad[0].peso = 45.8;

    comunidad[1].nombre = "Amarlo";
    comunidad[1].edad = 54;
    comunidad[1].altura = 154;
    comunidad[1].peso = 39.1;

    comunidad[2].nombre = "Erlo";
    comunidad[2].edad = 12;
    comunidad[2].altura = 121;
    comunidad[2].peso = 32.1;


    for (int i = 0; i < 3; i++){

        cout << "Nombre: " << comunidad[i].nombre << "\n";
        cout << "edad: " << comunidad[i].edad<< "\n";
        cout << "altura: " << comunidad[i].altura << "\n";
        cout << "peso: " << comunidad[i].peso << "\n\n";


    }

    return 0;
}
