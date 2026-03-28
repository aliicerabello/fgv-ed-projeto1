#include "ReservationSystem.hpp"
using namespace std;

// Constructor
ReservationSystem::ReservationSystem(int room_count, int* room_capacities){
    this->room_count = room_count;
    int* room_capacities_copy = new int[room_count];
    for (int i = 0; i < room_count; i++){
	room_capacities_copy[i] = room_capacities[i];
    }
    this->room_capacities = room_capacities_copy; //criar um novo room_capacities pra nao alterar o orig.
    rooms = new Room[room_count];
    for (int i = 0; i < room_count; i++){ 
        //criando uma lista de salas correspondentes à room_capacities
        rooms[i].room_capacity = room_capacities[i];
        rooms[i].head = nullptr;

    };

};


// Destructor
ReservationSystem::~ReservationSystem(){
    for (int i = 0; i < room_count; i++){ 
        Reservation* atual = rooms[i].head;
        while (atual != nullptr){ // apaga a lista encadeada de reserva de cada sala
            Reservation* proximo = atual->next;
            delete atual;
            atual = proximo;
        }

    }

    delete[] rooms; //apagar a lista de salas
    delete[] room_capacities; //apagar a copia que fiz de room_capacities
}

bool ReservationSystem::reserve(ReservationRequest request){
    string course_name = request.getCourseName();
    int end_hour = request.getEndHour();
    int start_hour = request.getStartHour();
    int student_count = request.getStudentCount();
    string weekday = request.getWeekday();

    for (int i = 0; i < room_count; i++){
    if (rooms[i].room_capacity < student_count){
        continue; //sai do if quando existe a sala i que tem capacidade suficiente
    };
    //agora verificamos conflito de horario

    Reservation* atual = rooms[i].head;
    bool sala_disponivel = true;

while (atual != nullptr){
    if (weekday == atual->weekday){  // so verifica conflito se for o mesmo dia
        bool sem_conflito = (end_hour <= atual->start_hour) || (start_hour >= atual->end_hour);
        if (!sem_conflito){          // se tem conflito
            sala_disponivel = false;
            break;                 
        }
    }
    atual = atual->next;
}

    if (sala_disponivel == true){
        Reservation* nova = new Reservation();
        nova->course_name = course_name;
        nova->end_hour = end_hour;
        nova->start_hour = start_hour;
        nova->student_count = student_count;
        nova->weekday = weekday;
        nova->next = rooms[i].head; //aponta pro primeiro elemento das reservas de rooom
        rooms[i].head = nova; // se torna no 1o elemento de room

        return true;
    }

    return false;
}


