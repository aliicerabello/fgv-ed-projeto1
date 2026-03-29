#include "ReservationRequest.hpp"
using namespace std;

// constructor
ReservationRequest::ReservationRequest(std::string course_name_, 
                                       std::string weekday_, 
                                       int start_hour_, 
                                       int end_hour_, 
                                       int student_count_) {                              
        this->course_name = course_name_;
        this->weekday = weekday_;
        this->start_hour = start_hour_;
        this->end_hour = end_hour_;
        this->student_count = student_count_;
}

// destructor
ReservationRequest::~ReservationRequest(){
}

// getters
int ReservationRequest::getStartHour(){
    return start_hour;
}

int ReservationRequest::getEndHour(){
    return end_hour;
}

string ReservationRequest::getCourseName(){
    return course_name;
}

string ReservationRequest::getWeekday(){
    return weekday;
}

int ReservationRequest::getStudentCount(){
    return student_count;
}


