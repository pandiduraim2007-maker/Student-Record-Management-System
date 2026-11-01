
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student {
    int regNo;
    char name[50];
    char department[30];
    int year;
    float mark;
    struct Student *next;
};

struct Student *head = NULL;

struct Student* searchStudent(int regNo) {
    struct Student *temp = head;

    while (temp != NULL) {
        if (temp->regNo == regNo)
            return temp;
        temp = temp->next;
    }
    return NULL;
}

void addStudent() {
    struct Student *newNode, *temp;

    newNode = (struct Student*)malloc(sizeof(struct Student));

    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }

    printf("Enter Register Number: ");
    scanf("%d", &newNode->regNo);

    if (searchStudent(newNode->regNo) != NULL) {
        printf("Student already exists!\n");
        free(newNode);
        return;
    }

    getchar();

    printf("Enter Student Name: ");
    fgets(newNode->name, sizeof(newNode->name), stdin);
    newNode->name[strcspn(newNode->name, "\n")] = '\0';

    printf("Enter Department: ");
    fgets(newNode->department, sizeof(newNode->department), stdin);
    newNode->department[strcspn(newNode->department, "\n")] = '\0';

    printf("Enter Year: ");
    scanf("%d", &newNode->year);

    printf("Enter Mark: ");
    scanf("%f", &newNode->mark);

    newNode->next = NULL;

    if (head == NULL) {
        head = newNode;
    } else {
        temp = head;
        while (temp->next != NULL)
            temp = temp->next;

        temp->next = newNode;
    }

    printf("Student added successfully!\n");
}

void displayStudents() {
    struct Student *temp = head;

    if (temp == NULL) {
        printf("No student records found!\n");
        return;
    }

    printf("\n--- Student Records ---\n");

    while (temp != NULL) {
        printf("\nRegister Number: %d\n", temp->regNo);
        printf("Name: %s\n", temp->name);
        printf("Department: %s\n", temp->department);
        printf("Year: %d\n", temp->year);
        printf("Mark: %.2f\n", temp->mark);

        temp = temp->next;
    }
}

void searchRecord() {
    int regNo;
    struct Student *temp;

    printf("Enter Register Number to Search: ");
    scanf("%d", &regNo);

    temp = searchStudent(regNo);

    if (temp == NULL) {
        printf("Student not found!\n");
    } else {
        printf("\nStudent Found!\n");
        printf("Register Number: %d\n", temp->regNo);
        printf("Name: %s\n", temp->name);
        printf("Department: %s\n", temp->department);
        printf("Year: %d\n", temp->year);
        printf("Mark: %.2f\n", temp->mark);
    }
}

void updateStudent() {
    int regNo;
    struct Student *temp;

    printf("Enter Register Number to Update: ");
    scanf("%d", &regNo);

    temp = searchStudent(regNo);

    if (temp == NULL) {
        printf("Student not found!\n");
    } else {
        printf("Enter New Mark: ");
        scanf("%f", &temp->mark);

        printf("Student record updated successfully!\n");
    }
}

void deleteStudent() {
    int regNo;
    struct Student *temp, *prev = NULL;

    printf("Enter Register Number to Delete: ");
    scanf("%d", &regNo);

    temp = head;

    while (temp != NULL && temp->regNo != regNo) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Student not found!\n");
        return;
    }

    if (prev == NULL) {
        head = temp->next;
    } else {
        prev->next = temp->next;
    }

    free(temp);
    printf("Student deleted successfully!\n");
}

void freeList() {
    struct Student *temp;

    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    int choice;

    do {
        printf("\n===== STUDENT RECORD MANAGEMENT SYSTEM =====\n");
        printf("1. Add Student\n");
        printf("2. Display Students\n");
        printf("3. Search Student\n");
        printf("4. Update Student\n");
        printf("5. Delete Student\n");
        printf("0. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addStudent();
                break;

            case 2:
                displayStudents();
                break;

            case 3:
                searchRecord();
                break;

            case 4:
                updateStudent();
                break;

            case 5:
                deleteStudent();
                break;

            case 0:
                printf("Exiting Program...\n");
                break;

            default:
                printf("Invalid choice! Try again.\n");
        }

    } while (choice != 0);

    freeList();
    return 0;
}
