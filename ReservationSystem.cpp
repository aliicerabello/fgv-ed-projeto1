#include "ReservationSystem.hpp"
#include <iostream>
#include <stdlib.h>
using namespace std;

// constructor
ReservationSystem::ReservationSystem(int room_count_, int *room_capacities_){
    this->room_count = room_count_; 
    
    // coppying capacities
    int *room_capacities_copy = new int[room_count];
    for (int i = 0; i < room_count; i++)
	    room_capacities_copy[i] = room_capacities_[i];
    
    this->room_capacities = room_capacities_copy;
    
    rooms = new Room[room_count];
    for (int i = 0; i < room_count; i++){ 
        rooms[i].room_capacity = room_capacities[i];
        rooms[i].head = nullptr;

    };
};

// destructor
ReservationSystem::~ReservationSystem(){
    for (int i = 0; i < room_count; i++){ 
        Reservation *atual = rooms[i].head;
        while (atual != nullptr){
            Reservation* proximo = atual->next;
            delete atual;
            atual = proximo;
        }
    }
    delete[] rooms;
    delete[] room_capacities;
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
    
        // checks the hour schedule
        Reservation *atual = rooms[i].head;
        bool sala_disponivel = true;

        while (atual != nullptr){
            if (weekday == atual->weekday){
                bool sem_conflito = (end_hour <= atual->start_hour) 
                                    || (start_hour >= atual->end_hour);
                if (!sem_conflito){          
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
            nova->next = rooms[i].head;
            rooms[i].head = nova;
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
                if(anterior == nullptr)
                    rooms[i].head = atual->next; //first node
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

// aux functions for bubble sort
void swapInt(int &a, int &b){
    int temp = a;
    a = b;
    b = temp;
}

void swapString(string &a, string &b){
    string temp = a;
    a = b;
    b = temp;
}

// aux function to compare weekdays
int dayIndex(string day){
    string days[5] = {"segunda", "terca", "quarta", "quinta", "sexta"};
    
    for(int i = 0; i < 5; i++){
        if(days[i] == day)
            return i;
    }
    return -1;
}

void ReservationSystem::printSchedule(){

    for(int i = 0; i < room_count; i++){
        cout << "Room " << i+1 << endl;

        if(rooms[i].head == nullptr){
            cout << "(sem reservas)" << endl;
            continue;
        }

        // bubble sort
        bool trocou = true;
        while(trocou){
            trocou = false;
            Reservation *atual = rooms[i].head;
            
            while(atual != nullptr && atual->next != nullptr){
                Reservation *prox = atual->next;

                bool fora_de_ordem;
                int diaAtual = dayIndex(atual->weekday);
                int diaProx  = dayIndex(prox->weekday);

                if(diaAtual != diaProx)
                    fora_de_ordem = diaAtual > diaProx;
                else
                    fora_de_ordem = atual->start_hour > prox->start_hour;

                if(fora_de_ordem){
                    swapString(atual->course_name, prox->course_name);
                    swapString(atual->weekday,     prox->weekday);
                    swapInt(atual->start_hour,  prox->start_hour);
                    swapInt(atual->end_hour,    prox->end_hour);
                    swapInt(atual->student_count, prox->student_count);
                    trocou = true;
                }
                atual = atual->next;
            }
        }

        string dia_atual = "";
        Reservation *atual = rooms[i].head;
        
        while(atual != nullptr){
            if(atual->weekday != dia_atual){
                dia_atual = atual->weekday;
                cout << dia_atual << ":" << endl;
            }
            cout << atual->start_hour << "h~" 
                 << atual->end_hour << "h: " 
                 << atual->course_name << endl;
            atual = atual->next;
        
        }
        if(i != room_count - 1)
            cout << endl;
    }
}
