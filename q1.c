#include <stdio.h>
#include <stdbool.h>


#define FILENAME "records.dat"


struct student {
    int roll;
    char name[101];
    int marks[5];
    bool isDeleted;
};


bool found(int roll) {
    FILE *fp = fopen(FILENAME, "rb");
    if (fp == NULL) {
        return 0;
    }

    struct student s;
    while (fread(&s, sizeof(struct student), 1, fp)) {
        if (s.roll == roll && !s.isDeleted) {
            fclose(fp);
            return true;
        }
    }

    fclose(fp);
    return false;
}


void addStudent() {
    struct student s;
    printf("Enter roll number: ");
    scanf("%d", &(s.roll));

    if (found(s.roll)) {
        printf("Roll number all ready exists!\n");
        return;
    }

    FILE *fp = fopen(FILENAME, "ab");
    if (fp == NULL) {
        printf("Error opening file.\n");
        return;
    }

    printf("Enter name: ");
    scanf("%s", s.name);

    for (int i = 0; i < 5; i++) {
        printf("Enter marks in subject %d: ", i + 1);
        scanf("%d", &((s.marks)[i]));
    }

    s.isDeleted = false;

    fwrite(&s, sizeof(struct student), 1, fp);
    fclose(fp);
}


void displayAll() {
    FILE *fp = fopen(FILENAME, "rb");
    if (fp == NULL) {
        printf("Error opening file.\n");
        return;
    }

    struct student s;
    int totalScore = 0;
    while (fread(&s, sizeof(struct student), 1, fp)) {
        for (int i = 0; i < 5; i++) {
            totalScore += (s.marks)[i];
        }

        if (!s.isDeleted) {
            printf("Roll: %d, Name: %s, Total Score: %d\n",
                   s.roll, s.name, totalScore);
        }
    }

    fclose(fp);
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
        printf("Any other number to exit\n");
        
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