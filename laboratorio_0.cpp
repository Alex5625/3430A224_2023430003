#include <iostream>

/* Una funcion para revisar si el valor ingresado es par o no y hacer lo mismo con los numeros del 1 al 10 (hacer un ciclo)

 */
void par_o_no(int respuesta_num){
    if (respuesta_num % 2 == 0){
        std::cout << "El respuesta_num " << respuesta_num << " es par\n";

    } else {

        std::cout << "El respuesta_num " << respuesta_num << " no es par\n";

    }
    int contador = 1;
    while (contador <= 10){


        if (contador % 2 == 0){

            std::cout << "El respuesta_num " << contador << " es par\n";

        } else {

            std::cout << "El respuesta_num " << contador << " no es par\n";

        }
        ++contador;


    }
}

/* Debo medir la longitud de una string ingresada por el usuario y otro string ya puesto en la funcion
 */


int main(){
    int respuesta_num = 0;
    std::cout << "Ingresa un valor para poder ver si es par o no: ";
    std::cin >> respuesta_num;
    par_o_no(respuesta_num);
}
