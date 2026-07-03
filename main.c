/**
 * main.c
 * ------
 * Entry point for the Smart Parking Management System.
 * Contains the main menu loop and handles all user interaction.
 *
 * IEEE-RAS Zagazig Student Chapter - "Code Speaks Louder Than Words"
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "functions.h"

/* === Input Helper Section === */

/**
 * read_line
 * ---------
 * Safely reads a line of text from stdin using fgets (replacing gets()),
 * strips the trailing newline, and stores it in buffer.
 */
static void read_line(char *buffer, int size) {
    if (fgets(buffer, size, stdin) != NULL) {
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
        }
    } else {
        buffer[0] = '\0';
    }
}

/**
 * read_int
 * --------
 * Safely reads an integer from stdin, re-prompting on invalid input.
 */
static int read_int(const char *prompt) {
    char buf[64];
    int value;
    while (1) {
        printf("%s", prompt);
        read_line(buf, sizeof(buf));
        if (sscanf(buf, "%d", &value) == 1) {
            return value;
        }
        printf("Invalid input. Please enter a valid number.\n");
    }
}

/* === Menu Section === */

static void print_menu(void) {
    printf("\n==================================================\n");
    printf("          SMART PARKING MANAGEMENT SYSTEM\n");
    printf("==================================================\n");
    printf(" 1. Add Vehicle\n");
    printf(" 2. Assign Parking Slot\n");
    printf(" 3. View Vehicle Information\n");
    printf(" 4. Remove Vehicle (Exit Parking)\n");
    printf(" 5. Calculate Parking Fee\n");
    printf(" 6. Display Parking Overview\n");
    printf(" 7. Search Vehicle (by ID or Plate)\n");
    printf(" 8. Edit Vehicle Information\n");
    printf(" 9. Save Data to File\n");
    printf(" 0. Exit\n");
    printf("==================================================\n");
}

/* === Menu Action Handlers Section === */

static void handle_add_vehicle(void) {
    char owner[NAME_LEN], plate[PLATE_LEN], type[TYPE_LEN];

    int id = read_int("Enter Vehicle ID: ");

    printf("Enter Owner Name: ");
    read_line(owner, sizeof(owner));

    printf("Enter Plate Number: ");
    read_line(plate, sizeof(plate));

    printf("Enter Vehicle Type: ");
    read_line(type, sizeof(type));

    add_vehicle(id, owner, plate, type);
}

static void handle_assign_slot(void) {
    int id = read_int("Enter Vehicle ID to assign a slot: ");
    assign_slot(id);
}

static void handle_view_vehicle(void) {
    int id = read_int("Enter Vehicle ID: ");
    print_vehicle_data(id);
}

static void handle_remove_vehicle(void) {
    int id = read_int("Enter Vehicle ID to remove: ");
    remove_vehicle(id);
}

static void handle_calculate_fee(void) {
    int id = read_int("Enter Vehicle ID: ");
    double fee = calculate_fees(id);
    if (fee >= 0) {
        printf("Parking fee for vehicle %d: $%.2f\n", id, fee);
    }
}

static void handle_search_vehicle(void) {
    printf("Search by:\n 1. Vehicle ID\n 2. Plate Number\n");
    int choice = read_int("Choose an option: ");
    char plate[PLATE_LEN] = "";
    int id = 0;

    if (choice == 1) {
        id = read_int("Enter Vehicle ID: ");
    } else if (choice == 2) {
        printf("Enter Plate Number: ");
        read_line(plate, sizeof(plate));
    } else {
        printf("Invalid option.\n");
        return;
    }

    search_vehicle(id, plate);
}

static void handle_edit_vehicle(void) {
    int id = read_int("Enter Vehicle ID to edit: ");

    if (find_vehicle_index_by_id(id) == -1) {
        printf("Error: Vehicle ID %d not found.\n", id);
        return;
    }

    char owner[NAME_LEN], plate[PLATE_LEN], type[TYPE_LEN];

    printf("Enter new Owner Name (leave blank to keep current): ");
    read_line(owner, sizeof(owner));

    printf("Enter new Plate Number (leave blank to keep current): ");
    read_line(plate, sizeof(plate));

    printf("Enter new Vehicle Type (leave blank to keep current): ");
    read_line(type, sizeof(type));

    edit_vehicle(id, owner, plate, type);
}

/* === Main Program === */

int main(void) {
    /* Load any previously saved parking data on startup */
    load_from_file(DATA_FILE);

    int running = 1;
    while (running) {
        print_menu();
        int choice = read_int("Enter your choice: ");

        switch (choice) {
            case 1: handle_add_vehicle(); break;
            case 2: handle_assign_slot(); break;
            case 3: handle_view_vehicle(); break;
            case 4: handle_remove_vehicle(); break;
            case 5: handle_calculate_fee(); break;
            case 6: display_parking_overview(); break;
            case 7: handle_search_vehicle(); break;
            case 8: handle_edit_vehicle(); break;
            case 9: save_to_file(DATA_FILE); break;
            case 0:
                save_to_file(DATA_FILE);
                printf("Data saved. Exiting Smart Parking Management System. Goodbye!\n");
                running = 0;
                break;
            default:
                printf("Invalid choice. Please select an option from the menu.\n");
        }
    }

    return 0;
}
