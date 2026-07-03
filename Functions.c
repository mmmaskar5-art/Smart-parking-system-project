#include <stdio.h>
#include <string.h>
#include <time.h>
#include "header.h"

struct Vehicle parking[50];

void add_vehicle() {
    int slot = -1;
    for (int i = 0; i < 50; i++) {
        if (parking[i].isOccupied == 0) {
            slot = i;
            break;
        }
    }
    
    if (slot == -1) {
        printf("Parking is full!\n");
        return;
    }
    
    printf("ID: ");
    scanf("%d", &parking[slot].id);
    printf("Owner: ");
    scanf("%s", parking[slot].ownerName);
    printf("Plate: ");
    scanf("%s", parking[slot].plateNumber);
    
    parking[slot].entryTime = time(NULL);
    parking[slot].isOccupied = 1;
    printf("Added to slot %d\n", slot + 1);
}

void print_vehicle_data() {
    int search_id;
    printf("Search ID: ");
    scanf("%d", &search_id);
    
    for (int i = 0; i < 50; i++) {
        if (parking[i].isOccupied == 1 && parking[i].id == search_id) {
            printf("\nID: %d | Owner: %s | Plate: %s | Slot: %d\n", 
                parking[i].id, parking[i].ownerName, parking[i].plateNumber, i + 1);
            printf("Entry: %s", ctime(&parking[i].entryTime));
            return;
        }
    }
    printf("Not found!\n");
}

void remove_vehicle() {
    int search_id;
    printf("Remove ID: ");
    scanf("%d", &search_id);
    
    for (int i = 0; i < 50; i++) {
        if (parking[i].isOccupied == 1 && parking[i].id == search_id) {
            double hours = difftime(time(NULL), parking[i].entryTime) / 3600.0;
            if (hours < 1.0) hours = 1.0;
            
            printf("Total fee: $%.2f\n", 10.0 + ((hours > 1.0) ? (hours - 1.0) * 5.0 : 0));
            parking[i].isOccupied = 0;
            printf("Removed!\n");
            return;
        }
    }
    printf("Not found!\n");
}
