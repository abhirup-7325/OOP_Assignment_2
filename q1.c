#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>


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
    struct student s;

    int rollNo;
    printf("Enter roll: ");
    scanf("%d", &rollNo);

    FILE *fp;

    if ((fp = fopen(FILENAME, "rb")) == NULL) {
        printf("Error Opening File\n");
        return;
    }

    bool hasFound = false;

    while (fread(&s, sizeof(struct student), 1, fp)) {
        if (s.roll == rollNo) {
            if (s.isDeleted) {
                printf("Roll no is deleted.\n");
            } else {
                printf("Roll: %d, Name: %s\n", s.roll, s.name);
                for (int i = 0; i < 5; i++) {
                    printf("Marks in subject %d: %d\n", i + 1, (s.marks)[i]);
                }
            }

            fclose(fp);
            return;
        }
    }

    printf("Cannot find record.\n");
    fclose(fp);
    return;
}


void editStudent() {
    FILE *fp;

    if ((fp = fopen(FILENAME, "rb+")) == NULL) {
        printf("Cannot open file!\n");
        return;
    }

    int rollNo;
    printf("Enter roll number: ");
    scanf("%d", &rollNo);


    int pos;
    struct student s;
    while (!feof(fp)) {
        pos = ftell(fp);

        fread(&s, sizeof(struct student), 1, fp);

        if (s.roll == rollNo && !s.isDeleted) {
            fseek(fp, pos, SEEK_SET);

            printf("Enter modified name: ");
            scanf("%s", s.name);

            for (int i = 0; i < 5; i++) {
                printf("Enter marks in subject %d: ", i + 1);
                scanf("%d", &((s.marks)[i]));
            }

            fwrite(&s, sizeof(struct student), 1, fp);
            fclose(fp);
            return;
        }
    }

    fclose(fp);
    printf("Could not found roll no.\n");
}


void deleteLogical() {
    FILE *fp;

    if ((fp = fopen(FILENAME, "rb+")) == NULL) {
        printf("Cannot open file!\n");
        return;
    }

    int rollNo;
    printf("Enter roll number: ");
    scanf("%d", &rollNo);


    int pos;
    struct student s;
    while (!feof(fp)) {
        pos = ftell(fp);

        fread(&s, sizeof(struct student), 1, fp);

        if (s.roll == rollNo && !s.isDeleted) {
            fseek(fp, pos, SEEK_SET);
            s.isDeleted = true;

            fwrite(&s, sizeof(struct student), 1, fp);
            fclose(fp);
            return;
        }
    }

    fclose(fp);
    printf("Could not found roll no.\n");
}


void deletePhysical() {
    FILE *fp = fopen(FILENAME, "rb");
    if (fp == NULL) {
        printf("Error opening file.\n");
        return;
    }

    fseek(fp, 0, SEEK_END);
    int fileSize = ftell(fp);
    int recordCount = fileSize / sizeof(struct student);

    if (recordCount == 0) {
        printf("No records found.\n");
        fclose(fp);
        return;
    }

    struct student *students = (struct student *)malloc(recordCount * sizeof(struct student));
    if (students == NULL) {
        printf("Memory allocation failed.\n");
        fclose(fp);
        return;
    }

    fseek(fp, 0, SEEK_SET);
    fread(students, sizeof(struct student), recordCount, fp);
    fclose(fp);

    int roll;
    printf("Enter roll number to delete (physical): ");
    scanf("%d", &roll);

    bool hasFound = false;
    int indexToDelete = -1;

    for (int i = 0; i < recordCount; i++) {
        if (students[i].roll == roll) {
            hasFound = true;
            indexToDelete = i;
            break;
        }
    }

    if (!hasFound) {
        printf("Record not available, logically or physically!\n");
        free(students);
        return;
    }

    for (int i = indexToDelete; i < recordCount - 1; i++) {
        students[i] = students[i + 1];
    }

    recordCount--;

    fp = fopen(FILENAME, "wb");
    if (fp == NULL) {
        printf("Error reopening file.\n");
        free(students);
        return;
    }

    fwrite(students, sizeof(struct student), recordCount, fp);
    fclose(fp);

    free(students);
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