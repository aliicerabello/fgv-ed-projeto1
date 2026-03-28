#ifndef RESERVATION_SYSTEM_HPP
#define RESERVATION_SYSTEM_HPP
#include "ReservationRequest.hpp"

struct Reservation { // registro de uma ReservationRequest que deu crt
                     // na pratica => pegar os dados da reservatiocorrigin request e copiar pra reserva quando reserve() for chamado
        
        int start_hour;
        int end_hour;
        std::string weekday;
        std::string course_name;
        int student_count;
        Reservation *next;  //o tipo da coisa que o next aponta é outra reserva
};


struct Room {
    Reservation *head; // começo da lista de reservas 
    int room_capacity;
};       


class ReservationSystem {

private:
    int room_count;
    int *room_capacities;
    Room *rooms;
    // Estruturas internas escolhidas pelos alunos
    // para armazenar e gerenciar as reservas, os horários, ...

public:

    ReservationSystem(int room_count, int* room_capacities);
    ~ReservationSystem();

    bool reserve(ReservationRequest request);
    bool cancel(std::string course_name);

    void printSchedule();

    // Outros métodos utilitários necessários
    // para auxiliar nas funções requisitadas
};


#endif