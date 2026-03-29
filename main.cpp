#include "ReservationRequest.hpp"
#include "ReservationSystem.hpp"
#include <iostream>
using namespace std;

int main(){

    int capacities[5] = {20, 30, 30, 40, 50};
    ReservationSystem sistema(5, capacities);
    
    // no reserves test
    sistema.printSchedule();
    cout << endl;

    // trivial test
    ReservationRequest r1("Algebra Linear", "segunda", 9, 11, 35);
    ReservationRequest r2("Calculo I", "terca", 9, 11, 50);
    ReservationRequest r3("Computacao", "terca", 11, 13, 10);

    sistema.reserve(r1); sistema.reserve(r2); sistema.reserve(r3);

    // overlapping time test
    ReservationRequest r4("Estatistica", "segunda", 10, 12, 35);
    ReservationRequest r5("Fisica", "segunda", 11, 13, 35);

    sistema.reserve(r4); sistema.reserve(r5);

    // no room avaiable test
    ReservationRequest r6("Filosofia", "quinta", 8, 10, 51);
    
    sistema.reserve(r6);

    // time limit test
    ReservationRequest r7("Historia", "sexta", 7, 9, 10);
    ReservationRequest r8("Geografia", "sexta", 19, 21, 10);
    
    sistema.reserve(r7); sistema.reserve(r8);

    // reserve different rooms in the same day test
    ReservationRequest r9 ("Quimica",    "quarta", 14, 16, 20);
    ReservationRequest r10("Biologia",   "quarta", 14, 16, 30);
    ReservationRequest r11("Portugues",  "quarta", 14, 16, 30);
    ReservationRequest r12("Ingles",     "quarta", 14, 16, 40);
    ReservationRequest r13("Filosofia2", "quarta", 14, 16, 50);
    ReservationRequest r14("Sociologia", "quarta", 14, 16, 10);
    
    sistema.reserve(r9); sistema.reserve(r10); sistema.reserve(r11);
    sistema.reserve(r12); sistema.reserve(r13); sistema.reserve(r14);

    // cancel test
    sistema.cancel("Calculo I"); sistema.cancel("Calculo I"); sistema.cancel("Modelagem");

     // reserve after cancel test
    ReservationRequest r15("Matematica Discreta", "terca", 9, 11, 50);
    sistema.reserve(r15);

    sistema.printSchedule();

    return 0;
}
