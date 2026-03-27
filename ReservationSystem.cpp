#include "ReservationSystem.hpp"

// Constructor
ReservationSystem::ReservationSystem(int room_count, int* room_capacities){
    this->room_count = room_count;
    int* room_capacities_copy = new int[room_count];
    for (int i = 0; i < room_count; i++){
	room_capacities_copy[i] = room_capacities[i];
    }
    this->room_capacities = room_capacities_copy //criar um novo room_capacities pra nao alterar o orig.
    //INICIALIZAR ROOMS

};


// Destructor
ReservationSystem::~ReservationSystem(){
    // not implemented error
}

