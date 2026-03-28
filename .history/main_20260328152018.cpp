#include "ReservationRequest.cpp"
#include "ReservationSystem.cpp"
#include <iostream>

int main(){

    // inicializacao do sistema
    int capacities[5] = {20,30,30,40,50};
    
    ReservationSystem sistema1(5, capacities);
    
    ReservationRequest r1("Álgebra Linear", "segunda", 9,
    11, 35);

    bool x = sistema1.reserve(r1);
    cout << x << "\n";
}