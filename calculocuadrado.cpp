#include <iostream>

double square(double x){
    return x*x;
}

void print_square(double x){

    std::cout << "El Cuadrado de " << x << " es " << square(x) << "\n";

}


int main(){

    print_square(1.21321);

    print_square(4.2321);
}
