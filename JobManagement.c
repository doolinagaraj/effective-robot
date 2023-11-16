#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Job {
    char title[50];
    char department[50];
    int salary;
};

struct JobNode {
    struct Job job;
    int isVacant;
    struct JobNode* next;
};

void addJob(struct JobNode** head, struct Job job, int isVacant) {
    struct JobNode* newNode = (struct JobNode*)malloc(sizeof(struct JobNode));
    newNode->job = job;
    newNode->isVacant = isVacant;

    struct JobNode* current = *head;
    struct JobNode* prev = NULL;
    while (current != NULL && current->job.salary > job.salary) {
        prev = current;
        current = current->next;
    }

    if (prev == NULL) {
        newNode->next = *head;
        *head = newNode;
    } else {
        prev->next = newNode;
        newNode->next = current;
    }
}

void displayJobs(struct JobNode* head) {
    struct JobNode* current = head;
    while (current != NULL) {
        printf("Title: %s\nDepartment: %s\nSalary: %d\nStatus: %s\n\n",
               current->job.title, current->job.department, current->job.salary,
               current->isVacant ? "Vacant" : "applied");
        current = current->next;
    }
}

void readJobsFromFile(struct JobNode** head, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    struct Job job;
    int readCount;
    while ((readCount = fscanf(file, " %49[^,],%49[^,],%d%*c", job.title, job.department, &job.salary)) == 3) {
        addJob(head, job, 1);
    }

    if (readCount != EOF) {
        if (readCount != 3) {
            fprintf(stderr, "Error reading file. Check the file format.\n");
        } else {
            fprintf(stderr, "Error reading file. Maximum jobs limit reached.\n");
        }
        exit(EXIT_FAILURE);
    }

    fclose(file);
}

void applyForJob(struct JobNode** head) {
    int choice;
    while (1) {
        printf("Available Jobs:\n");
        int count = 1;
        struct JobNode* current = *head;
        while (current != NULL) {
            if (current->isVacant) {
                printf("%d. Title: %s\nDepartment: %s\nSalary: %d\n\n", count, current->job.title, current->job.department, current->job.salary);
                count++;
            }
            current = current->next;
        }

        printf("Enter the number of the job you want to apply for (or 0 to cancel): ");
        scanf("%d", &choice);

        if (choice >= 1 && choice < count) {
            current = *head;
            int vacantCount = 0;
            while (current != NULL) {
                if (current->isVacant) {
                    vacantCount++;
                }
                if (vacantCount == choice) {
                    break;
                }
                current = current->next;
            }

            if (current != NULL && current->isVacant) {
                printf("You have applied for the following job:\n");
                printf("Title: %s\nDepartment: %s\nSalary: %d\n\n",
                    current->job.title, current->job.department, current->job.salary);
                current->isVacant = 0;
                break;
            } else {
                printf("Invalid choice or job is already filled. Please select a valid job number.\n");
            }
        } else if (choice == 0) {
            printf("Application canceled.\n");
            break;  // exit the loop if the user cancels the application
        } else {
            printf("Invalid choice. Please select a valid job number.\n");
        }
    }
}

int main() {
    struct JobNode* jobs = NULL;
    const char* filename = "jobs.txt";

    readJobsFromFile(&jobs, filename);

    displayJobs(jobs);

    applyForJob(&jobs);

    displayJobs(jobs);

    return 0;
}
