#ifndef RESERVATION_SYSTEM_HPP
#define RESERVATION_SYSTEM_HPP
#include "ReservationRequest.hpp"

struct Reservation{
        int start_hour;
        int end_hour;
        std::string weekday;
        std::string course_name;
        int student_count;
        Reservation *next;
};

struct Room {
    Reservation *head;
    int room_capacity;
};       

class ReservationSystem {

private:
    int room_count;
    int *room_capacities;
    Room *rooms;

public:
    ReservationSystem(int room_count, int* room_capacities);
    ~ReservationSystem();

    bool reserve(ReservationRequest request);
    bool cancel(std::string course_name);

    void printSchedule();
};

#endif