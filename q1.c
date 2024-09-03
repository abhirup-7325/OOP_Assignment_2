#include <stdio.h>
#include <stdbool.h>


#define FILENAME "records.dat"


struct student {
    int roll;
    char name[101];
    int score[5];
}


void addStudent() {
    FILE *fp = fopen(FILENAME, "ab");
    if (fp == NULL) {
        printf("Error opening file.\n");
        return;
    }

    
}


void displayAll() {

}


void search() {

}


void editStudent() {

}


void deleteLogical() {

}


void deletePhysical() {

}


int main() {
    int response;
    bool running = true;

    while (running) {
        printf("1. Add Record\n");
        printf("2. Display All Records\n");
        printf("3. Search Record by Roll Number\n");
        printf("4. Edit Record\n");
        printf("5. Delete Record (Logical)\n");
        printf("6. Delete Record (Physical)\n");
        printf("Any other number to exit")
        
        printf("Enter your choice: ");
        scanf("%d", &response);

        switch (response) {
            case 1:
                addStudent();
                break;
            
            case 2:
                displayAll();
                break;

            case 3:
                search();
                break;

            case 4:
                editStudent();
                break;

            case 5: 
                deleteLogical();
                break;

            case 6:
                deletePhysical();
                break;

            default:
                running = false;
                break;
        }
    }

    return 0;
}