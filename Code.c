#include <stdio.h>
#include "header.h"

int main() {
    for (int i = 0; i < 50; i++) {
        parking[i].isOccupied = 0;
    }
    
    int choice;
    while (1) {
        printf("\n--- Smart Parking System ---\n");
        printf("1. Add Vehicle\n");
        printf("2. View Vehicle Info\n");
        printf("3. Remove Vehicle\n");
        printf("4. Exit\n");
        printf("Choice: ");
        scanf("%d", &choice);
        
        if (choice == 1) add_vehicle();
        else if (choice == 2) print_vehicle_data();
        else if (choice == 3) remove_vehicle();
        else if (choice == 4) break;
    }
    return 0;
}
