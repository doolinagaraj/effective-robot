struct Job:
         This structure defines the attributes of a job, including the job title, department, and salary
struct JobNode:
        This structure represents a node in the linked list. It contains a struct Job to store job details, an isVacant flag to indicate whether the job is vacant (1 for vacant, 0 for filled), and a pointer to the next node in the list.
void addJob(struct JobNode** head, struct Job job, int isVacant):
        This function adds a new job to the linked list in a sorted manner based on salary. It dynamically allocates memory for a new node, assigns job details and vacancy status, and inserts the node into the linked list.
void displayJobs(struct JobNode* head):
        This function displays information about each job in the linked list, including the title, department, salary, and vacancy status.
void applyForJob(struct JobNode** head):
        This function allows the user to apply for a vacant job by selecting a job number. The linked list is updated to mark the chosen job as filled.This function displays the available jobs, allows the user to choose a job to apply for, and updates the linked list by marking the selected job as filled. The user is prompted to enter the number of the desired job, and the function handles validation to ensure a valid choice. If the chosen job is vacant, its details are displayed, and it is marked as filled in the linked list. Otherwise, an error message is displayed.
void readJobsFromFile(struct JobNode** head, const char* filename):
        The readJobsFromFile function opens a file specified by the given filename, reads job information (title, department, salary) from the file, and adds each job to a linked list pointed to by the head parameter. If there is an error opening the file or reading its content, an appropriate error message is printed, and the program exits.
int main():
        The main function initializes the linked list with sample job data, displays the available jobs, allows the user to apply for a job, and then displays the updated list.
