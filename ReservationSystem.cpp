#include "ReservationSystem.hpp"
#include <iostream>
#include <stdlib.h>
using namespace std;

// Constructor: ReservationSystem possui int room_count, int *room_capacities e Room rooms
ReservationSystem::ReservationSystem(int room_count, int *room_capacities){
    // self para o room_count
    this->room_count = room_count; 
    
    // inicializo o ponteiro pro array de tamanho room_count e
    // associo cada capacidade copiada ao que foi passado
    int *room_capacities_copy = new int[room_count];
    for (int i = 0; i < room_count; i++)
	    room_capacities_copy[i] = room_capacities[i];
    
    // self da capacidade 
    this->room_capacities = room_capacities_copy; //criar um novo room_capacities pra nao alterar o orig.
    
    // 
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
        Reservation *atual = rooms[i].head;
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

    if (request.getStartHour() >= request.getEndHour()){ 
        cout << "Horario inicial deve ser menor que o final ";
        return false;
    }
    
    if (request.getStartHour() < 7 || request.getEndHour() > 21){ 
        cout << "Horario fora do funcionamento ";
        return false;
    }
    
    // finds a room with capacity
    for (int i = 0; i < room_count; i++){
        if (rooms[i].room_capacity < student_count)
            continue; 
    
        //agora verificamos conflito de horario
        Reservation *atual = rooms[i].head;
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

        if (sala_disponivel) {
            Reservation *nova = new Reservation();
            nova->course_name = course_name;
            nova->end_hour = end_hour;
            nova->start_hour = start_hour;
            nova->student_count = student_count;
            nova->weekday = weekday;
            nova->next = rooms[i].head; //aponta pro primeiro elemento das reservas de rooom
            rooms[i].head = nova; // se torna no 1o elemento de room
            cout << "[DEBUG] " << course_name << " alocada na sala " << i+1 << endl;
            return true;
        }
    }
    return false;
}

bool ReservationSystem::cancel(std::string course_name){
    for(int i = 0; i < room_count; i++){
        
        Reservation *atual = rooms[i].head; 
        Reservation *anterior = nullptr;

        while(atual != nullptr) {
            
            if(atual->course_name == course_name){
                if(anterior == nullptr){
                    rooms[i].head = atual->next; //first node
                }
                else
                    anterior->next = atual->next;
                delete atual;
                return true;
            }
            anterior = atual;
            atual = atual->next;
        }
    }
    return false;
}

void ReservationSystem::printSchedule(){

    // ordem dos dias para comparacao
    string days[5] = {"segunda", "terca", "quarta", "quinta", "sexta"};

    // funcao auxiliar: retorna o indice do dia (0=segunda, ..., 4=sexta)
    auto dayIndex = [&](string day) -> int {
        for(int i = 0; i < 5; i++)
            if(days[i] == day) return i;
        return -1;
    };

    for(int i = 0; i < room_count; i++){
        cout << "Room " << i+1 << endl;

        if(rooms[i].head == nullptr){
            cout << "  (sem reservas)" << endl;
            continue;
        }

        // bubble sort: troca os dados dos nos (nao os ponteiros)
        bool trocou = true;
        while(trocou){
            trocou = false;
            Reservation *atual = rooms[i].head;
            while(atual != nullptr && atual->next != nullptr){
                Reservation *prox = atual->next;

                // compara dia; se mesmo dia, compara horario
                bool fora_de_ordem;
                int diaAtual = dayIndex(atual->weekday);
                int diaProx  = dayIndex(prox->weekday);

                if(diaAtual != diaProx)
                    fora_de_ordem = diaAtual > diaProx;
                else
                    fora_de_ordem = atual->start_hour > prox->start_hour;

                if(fora_de_ordem){
                    // troca os dados entre os dois nos
                    swap(atual->course_name, prox->course_name);
                    swap(atual->weekday,     prox->weekday);
                    swap(atual->start_hour,  prox->start_hour);
                    swap(atual->end_hour,    prox->end_hour);
                    swap(atual->student_count, prox->student_count);
                    trocou = true;
                }
                atual = atual->next;
            }
        }

        // impressao apos ordenacao
        string dia_atual = "";
        Reservation *atual = rooms[i].head;
        while(atual != nullptr){
            if(atual->weekday != dia_atual){
                dia_atual = atual->weekday;
                cout << dia_atual << ":" << endl;
            }
            cout << "  " << atual->start_hour << "h~" 
                 << atual->end_hour << "h: " 
                 << atual->course_name << endl;
            atual = atual->next;
        }
    }
}


