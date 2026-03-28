#include "ReservationRequest.cpp"
#include "ReservationSystem.cpp"
#include <iostream>

int main(){

    // inicializacao do sistema
    int capacities[5] = {20,30,30,40,50};
    
    ReservationSystem sistema1(5, capacities);
    Reservation r1;
    r1.course_name = "Álgebra Linear";
    r1.weekday = "segunda";
    r1.start_hour = 9;
    r1.end_hour = 11;
    r1.student_count = 35; //Achamos que não é necessário

    ReservationRequest rr1(r1.course_name, r1.weekday, r1.start_hour,
    r1.end_hour, r1.student_count);

    bool x = sistema1.reserve(rr1);
    cout << x;
}