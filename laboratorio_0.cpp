#include <iostream>
#include <string>

/* Una funcion para revisar si el valor ingresado es par o no y hacer lo mismo con los numeros del 1 al 10 (hacer un ciclo)

 */
using namespace std;
void par_o_no(int respuesta_num){
    if (respuesta_num % 2 == 0){
        cout << "El respuesta_num " << respuesta_num << " es par\n";

    } else {

        cout << "El respuesta_num " << respuesta_num << " no es par\n";

    }
    int contador = 1;
    while (contador <= 10){


        if (contador % 2 == 0){

            cout << "El respuesta_num " << contador << " es par\n";

        } else {

            cout << "El respuesta_num " << contador << " no es par\n";

        }
        ++contador;


    }
}

//Funcion para contar el largo de una cadena de texto, incluyendo los espacios
void largo_string(string respuesta){


    int i = 0;
    while (i < respuesta.length()){
        ++i;
    }
    cout << "El largo de la palabra " << respuesta << " es: " << i << "\n";


/*
    int longitud = 0;

    for (int i = 0; respuesta[i] != 0; ++i){

        ++longitud;
    }

    cout << "El string tiene como longitud un numero de " << longitud << " caracteres\n\n";
*/

    string palabra = "Alexis";
    int f = 0;
    while (f < palabra.length()){
        ++f;
    }

    cout << "El largo de la palabra " << palabra << " es: " << f << "\n";

}
/* Debo medir la longitud de una string ingresada por el usuario y otro string ya puesto en la funcion
 */


int main(){
    int respuesta_num = 0;
    string respuesta_char;

    cout << "Ingresa un valor para poder ver si es par o no: ";
    cin >> respuesta_num;
    //Cada vez que haya un ingreso de texto a traves de std::cin, ese comando almacena un salto de linea (\n)
    //entonces debes utilizar cin.get() para limpiar la memoria de ese comando.
    //respuesta: https://stackoverflow.com/questions/2525352/problem-of-using-cin-twice
    cin.get();
    par_o_no(respuesta_num);




    cout << "Ingresa una palabra para poder saber su largo: ";

    getline(cin, respuesta_char);
    cout << "La palabra es: " << respuesta_char << "\n";
    largo_string(respuesta_char);
}
