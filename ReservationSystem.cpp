#include "ReservationSystem.hpp"

// Constructor
ReservationSystem::ReservationSystem(int room_count, int* room_capacities){
    this->room_count = room_count;
    this->room_capacities = room_capacities;
}

// Destructor
ReservationSystem::~ReservationSystem(){
    // not implemented error
}

