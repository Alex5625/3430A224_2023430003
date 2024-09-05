//Forma de crear la lista de espera a nuestro gusto -> comentar pq lo hicimos
#include <cmath>
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
    double imc;
    double a1c;
    double puntaje_prioridad;
    Paciente* next;
};

double puntaje_prioridad(double imc, double a1c){
    int factor_riesgo;
    //Se calcula a traves del parametro a1c principalmente y luego se multiplica el imc para que sea el factor de comparacion.
    //Esta lista de espera es para pacientes diabeticos dentro de un hospital de emergencia.

    //Persona sin diabetes
    if(a1c < 5.7){
        factor_riesgo = 0;
    }

    //Persona con prediabetes
    if(a1c >= 5.7 && a1c <= 6.5){
        factor_riesgo = 1;
    }

    //Persona con diabetes
    if(a1c > 6.5){
        factor_riesgo = 2;
    }

    return factor_riesgo*imc;
}

//Funcion para añadir pacientes
//esta lista funciona como cola
void anadirPacienteAuto(Paciente*& head, const string& nombre, int edad, double altura, double peso, double a1c) {

    double nuevo_imc = (double)peso / pow(altura, 2);

    Paciente* nuevoPaciente = new Paciente();
    nuevoPaciente-> nombre = nombre;
    nuevoPaciente -> edad = edad;
    nuevoPaciente -> altura = altura;
    nuevoPaciente -> peso = peso;
    nuevoPaciente -> imc = nuevo_imc;
    nuevoPaciente -> a1c = a1c;
    nuevoPaciente -> puntaje_prioridad = puntaje_prioridad(nuevo_imc, a1c);
    nuevoPaciente -> next = head;
    head = nuevoPaciente;

    cout << "Paciente añadido correcamente\n\n";
}

//-----------------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------------

//Funcion para imprimir pacientes
void imprimirPacientes(const Paciente* head){
    int contador;
    const Paciente* actual = head;
    while (actual != nullptr){

        cout << "Nombre: " << actual->nombre << "\n";
        cout << "edad: " << actual->edad<< "\n";
        cout << "altura: " << actual->altura << "\n";
        cout << "peso: " << actual->peso << "\n";
        cout << "imc: " << actual -> imc << "\n";
        cout << "puntaje_prioridad: " << actual -> puntaje_prioridad << endl;
        cout << "a1c: " << actual -> a1c << "\n\n";
        actual = actual -> next;
        contador = contador + 1;
    }
    cout << "El largo de la lista es: " << contador << endl;
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


    ifstream archivo(nombreArchivo);

    // Verificar si el archivo se abrió correctamente
    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo: " << nombreArchivo << endl;
        return;
    }

    string linea;
    int contador = 1;

    // Leer cada línea del archivo
    getline(archivo, linea); // Leer y ignorar la línea de encabezado

    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string nombre, edad_str, altura_str, peso_str, ac1_str;

        // Leer cada campo separado por ','
        getline(ss, nombre, ',');
        getline(ss, edad_str, ',');
        getline(ss, altura_str, ',');
        getline(ss, peso_str, ',');
        getline(ss, ac1_str, '\n');

        // Convertir los campos a los tipos correctos
        int edad = stoi(edad_str);
        double altura = stod(altura_str);
        int peso = stoi(peso_str);
        double ac1 = stod(ac1_str);

        anadirPacienteAuto(head, nombre, edad, altura, peso, ac1);

        contador++;
    }

    archivo.close();

    cout << "\n\n";
}

// Función para encolar un paciente en una lista ya definida según su puntaje de prioridad
void enqueuePrioridad(Paciente*& head, Paciente* nuevoPaciente) {
    // Caso 1: La lista está vacía
    if (head == nullptr) {
        head = nuevoPaciente; // Si la cola está vacía, el nuevo nodo es la cabeza
        return;
    }

    // Caso 2: Insertar al principio (mayor prioridad que el primer nodo)
    if (nuevoPaciente->puntaje_prioridad > head->puntaje_prioridad) {
        nuevoPaciente->next = head;
        head = nuevoPaciente;
        return;
    }

    // Caso 3: Buscar la posición correcta para insertar
    Paciente* actual = head;
    while (actual->next != nullptr && actual->next->puntaje_prioridad >= nuevoPaciente->puntaje_prioridad) {
        actual = actual->next;
    }

    // Insertar el nuevo nodo en la posición correcta
    nuevoPaciente->next = actual->next;
    actual->next = nuevoPaciente;
}


void generar_lista_espera(Paciente* head, Paciente*& listaPrioridad){
    Paciente* actual = head;
    while (actual != nullptr) {
        // Crear un nuevo nodo para la lista de prioridad
        Paciente* nuevoPaciente = new Paciente();
        nuevoPaciente->nombre = actual->nombre;
        nuevoPaciente->edad = actual->edad;
        nuevoPaciente->altura = actual->altura;
        nuevoPaciente->peso = actual->peso;
        nuevoPaciente->imc = actual->imc;
        nuevoPaciente->a1c = actual->a1c;
        nuevoPaciente->puntaje_prioridad = actual->puntaje_prioridad;
        nuevoPaciente->next = nullptr;

        // Encolar en la lista de prioridad
        enqueuePrioridad(listaPrioridad, nuevoPaciente);

        // Avanzar al siguiente paciente en la lista original
        actual = actual->next;
    }
}

void dequeuePrioridad(Paciente** listaPrioridad) {
    if (*listaPrioridad == nullptr) {
        return;
    }

    Paciente* temp = *listaPrioridad;
    *listaPrioridad = (*listaPrioridad)->next;
    delete temp;
}
//Funcion para vaciar la lista
void vaciarListaPrioridad(Paciente** listaPrioridad) {
    while (*listaPrioridad != nullptr) {
        dequeuePrioridad(listaPrioridad);
    }
}


int main(){

    Paciente* head = nullptr;
    Paciente* listaPrioridad = nullptr;
    cout << "Bienvenido al simulador de agenda hospitalaria" << "\n";


    string nombre;
    while(true){
        int edad = 0;
        int altura = 0;
        double peso = 0.0;
        double a1c = 0.0;
        int numero_funcion = 0;
        string archivo = "./patient_list.csv";

        cout << "Por favor digite: \n1. si quiere ingresar los datos de un paciente \n2. si quiere eliminar un paciente\n3. si quiere ver la lista de pacientes que posee\n4. si desea determinar el promedio de peso y altura de los pacientes\n5. Calcular el IMC de cada paciente\n6. desea agregar pacientes desde un archivo .txt o .csv\n7. Generar lista de espera.\n8. Imprimir lista de espera.\n9. Atender a un paciente\n10.Vaciar la lista de Espera\n11. Salir.\n\n";
        cin >> numero_funcion;
        cout << "\n";
        switch (numero_funcion) {

            case 1:


                cout << "Dame el nombre del paciente\n";
                cin >> nombre;
                cin.get();
                cout << "Dame la edad del paciente\n";
                cin >> edad;
                cout << "Dame la altura en centimetros del paciente\n";
                cin >> altura;
                cout << "Dame el peso en kilogramos del paciente, de la forma (00.0)\n";
                cin >> peso;
                cout << "Dame el a1c del paciente:\n";
                cin >> a1c;
                anadirPacienteAuto(head, nombre, edad, altura, peso, a1c);
                break;

            case 2:
                cout << "Ingrese el nombre del paciente que desea eliminar: ";
                cin >> nombre;
                eliminarPaciente(head, nombre);
                break;

            case 3:
                imprimirPacientes(head);
                break;
            case 4:
                promediosPacientes(head);
                break;

            case 5:
                imcPacientes(head);
                break;

            case 6:
                cout << "Entra al lector de archivos";
                leerCSV(head, archivo);
                break;

            case 7:

                generar_lista_espera(head, listaPrioridad);
            break;

            case 8:
                imprimirPacientes(listaPrioridad);
                break;

            case 9:
                dequeuePrioridad(&listaPrioridad);
                cout << "ATENDIDO AL PACIENTE\n\n";
                break;
            case 10:
                vaciarListaPrioridad(&listaPrioridad);
                break;
            case 11:
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



