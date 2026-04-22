#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_RECORDS 100

// structure to store patient info (array storage)
typedef struct {
    char name[50];
    char illness[100];
    int priority;
} PatientRecord;

// linked list node
typedef struct Node {
    PatientRecord data;
    struct Node* next;
} Node;

// global array (acts like database)
PatientRecord hospitalDB[MAX_RECORDS];
int totalPatients = 0;

// function to assign priority based on illness keywords
int calculatePriority(char illness[]) {
    char temp[100];

    // copy because we convert to lowercase
    strcpy(temp, illness);

    // convert string to lowercase so matching becomes easier
    for(int i = 0; temp[i]; i++)
        temp[i] = tolower(temp[i]);

    // checking for critical conditions
    if (strstr(temp, "heart") || strstr(temp, "chest") || strstr(temp, "breath") ||
        strstr(temp, "unconscious") || strstr(temp, "stroke")) {
        return 1; // highest priority
    }

    // medium level cases
    if (strstr(temp, "fracture") || strstr(temp, "blood") || strstr(temp, "pain")) {
        return 2;
    }

    // default case
    return 3;
}

// function to create node and insert in sorted way
void createNode(Node** head, PatientRecord p) {

    // allocating memory for new node
    Node* newNode = (Node*)malloc(sizeof(Node));

    // copying data into node
    newNode->data = p;
    newNode->next = NULL;

    // if list empty OR new node has higher priority
    if (*head == NULL || p.priority < (*head)->data.priority) {

        // insert at beginning
        newNode->next = *head;
        *head = newNode;

    } else {

        // traverse to find correct position
        Node* temp = *head;

        // move till correct position is found
        while (temp->next != NULL && temp->next->data.priority <= p.priority) {
            temp = temp->next;
        }

        // insert node in between
        newNode->next = temp->next;
        temp->next = newNode;
    }
}

// function to delete highest priority node (first node)
void deleteNode(Node** head) {

    // if list empty
    if (*head == NULL) {
        printf("\nNo patients.\n");
        return;
    }

    // temp pointer to first node
    Node* temp = *head;

    // showing which patient is being treated
    printf("\nTreating: %s (%d)\n", temp->data.name, temp->data.priority);

    // move head to next node
    *head = (*head)->next;

    // free memory
    free(temp);
}

// display array records
void displayHistory() {

    if (totalPatients == 0) {
        printf("\nNo records.\n");
        return;
    }

    printf("\n--- Records ---\n");

    // simple loop to print all records
    for (int i = 0; i < totalPatients; i++) {
        printf("%s | %s | %d\n",
               hospitalDB[i].name,
               hospitalDB[i].illness,
               hospitalDB[i].priority);
    }
}

// display linked list
void displayList(Node* head) {

    if (head == NULL) {
        printf("\nEmpty list\n");
        return;
    }

    printf("\n--- Live Patients ---\n");

    // traverse till end
    while (head != NULL) {
        printf("[%s P:%d] -> ", head->data.name, head->data.priority);
        head = head->next;
    }

    printf("NULL\n");
}

int main() {

    Node* head = NULL; // initially empty list
    int choice;

    while (1) {

        // menu
        printf("\n1.Add Patient\n2.Treat Patient\n3.View Records\n4.View List\n5.Exit\n");
        printf("Enter: ");

        scanf("%d", &choice);
        getchar(); // clear newline

        if (choice == 1) {

            // check if array full
            if (totalPatients >= MAX_RECORDS) {
                printf("Database full\n");
                continue;
            }

            PatientRecord p;

            // input name
            printf("Name: ");
            fgets(p.name, sizeof(p.name), stdin);
            p.name[strcspn(p.name, "\n")] = 0;

            // input illness
            printf("Illness: ");
            fgets(p.illness, sizeof(p.illness), stdin);
            p.illness[strcspn(p.illness, "\n")] = 0;

            // assign priority
            p.priority = calculatePriority(p.illness);

            // store in array (history)
            hospitalDB[totalPatients++] = p;

            // insert into linked list
            createNode(&head, p);

            printf("Added with priority %d\n", p.priority);
        }

        else if (choice == 2) {
            deleteNode(&head);
        }

        else if (choice == 3) {
            displayHistory();
        }

        else if (choice == 4) {
            displayList(head);
        }

        else if (choice == 5) {
            break;
        }
    }

    return 0;
}
