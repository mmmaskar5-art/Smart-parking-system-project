#ifndef HEADER_H
#define HEADER_H

#include <time.h>

struct Vehicle {
    int id;
    char ownerName[50];
    char plateNumber[20];
    time_t entryTime;
    int isOccupied;
};

extern struct Vehicle parking[50];

void add_vehicle();
void print_vehicle_data();
void remove_vehicle();

#endif
