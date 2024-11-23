#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct Student {
    char rollNumber[50];
    char name[50];
    char department[50];
    char course[10];
    struct Student* left;
    struct Student* right;
} Student;

Student* createStudent(const char rollNumber[], const char name[], const char department[], const char course[]) {
    Student* newNode = (Student*)malloc(sizeof(Student));
    strcpy(newNode->rollNumber, rollNumber);
    strcpy(newNode->name, name);
    strcpy(newNode->department, department);
    strcpy(newNode->course, course);
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

Student* insert(Student* root, const char rollNumber[], const char name[], const char department[], const char course[]) {
    if (root == NULL) {
        return createStudent(rollNumber, name, department, course);
    }
    int cmp = strcmp(rollNumber, root->rollNumber);
    if (cmp < 0) {
        root->left = insert(root->left, rollNumber, name, department, course);
    } else if (cmp > 0) {
        root->right = insert(root->right, rollNumber, name, department, course);
    }

    return root;
}

Student* search(Student* root, const char rollNumber[]) {
    if (root == NULL || strcmp(rollNumber, root->rollNumber) == 0) {
        return root;
    }
    int cmp = strcmp(rollNumber, root->rollNumber);
    if (cmp < 0) {
        return search(root->left, rollNumber);
    } else {
        return search(root->right, rollNumber);
    }
}

void displayByDepartment(Student* root, const char department[]) {
    if (root == NULL) {
        return;
    }
    displayByDepartment(root->left, department);
    if (strcmp(root->department, department) == 0) {
        printf("Roll Number: %s, Name: %s, Course: %s\n", root->rollNumber, root->name, root->course);
    }
    displayByDepartment(root->right, department);
}

void displayByCourse(Student* root, const char course[]) {
    if (root == NULL) {
        return;
    }
    displayByCourse(root->left, course);
    if (strcmp(root->course, course) == 0) {
        printf("Roll Number: %s, Name: %s, Department: %s\n", root->rollNumber, root->name, root->department);
    }
    displayByCourse(root->right, course);
}

int main() {
    Student* root = NULL;
    int choice;
    char rollNumber[50];
    char name[50];
    char department[50];
    char course[10];
    Student* result = NULL;

    while (1) {
        printf("\nStudent Management System Menu:\n");
        printf("1. Add Student\n");
        printf("2. Search Student\n");
        printf("3. Display Students by Department\n");
        printf("4. Display Students by Course\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter Roll Number: ");
                scanf("%s", rollNumber);
                printf("Enter Name: ");
                scanf(" %49[^\n]", name);
                printf("Enter Department: ");
                scanf(" %49[^\n]", department);
                printf("Enter Course: ");
                scanf("%s", course);
                root = insert(root, rollNumber, name, department, course);
                break;
            case 2:
                printf("Enter Roll Number to search: ");
                scanf("%s", rollNumber);
                result = search(root, rollNumber);
                if (result != NULL) {
                    printf("Student Found: Roll Number: %s, Name: %s, Department: %s, Course: %s\n",
                           result->rollNumber, result->name, result->department, result->course);
                } else {
                    printf("Student with Roll Number %s not found.\n", rollNumber);
                }
                break;
            case 3:
                printf("Enter Department to display students: ");
                scanf(" %49[^\n]", department);
                printf("\nStudents in %s Department:\n", department);
                displayByDepartment(root, department);
                break;
            case 4:
                printf("Enter Course to display students: ");
                scanf("%s", course);
                printf("\nStudents in %s Course:\n", course);
                displayByCourse(root, course);
                break;
            case 5:
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}

