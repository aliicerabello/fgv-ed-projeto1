#include "ReservationRequest.cpp"
#include "ReservationSystem.cpp"
#include <iostream>

int main(){

    // inicializacao do sistema
    int capacities[5] = {20,30,30,40,50};
    
    ReservationSystem sistema1(5, capacities);
    
    ReservationRequest r1("Álgebra Linear", "segunda", 9, 11, 35);
    ReservationRequest r2("Cálculo I", "terça", 9, 11, 50);
    ReservationRequest r3("Computação", "terça", 11, 12, 50);

    bool x = sistema1.reserve(r1);
    bool y = sistema1.reserve(r2);
    bool z = sistema1.reserve(r3);
    cout << x << "\n";
    cout << y << "\n";
    cout << z << "\n";

    bool a = sistema1.cancel("Cálculo I");
    bool b = sistema1.cancel("Modelagem");
    cout << a << "\n";
    cout << b << "\n";
}