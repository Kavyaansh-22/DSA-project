#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_RECORDS 100

// Structure for Patient (Used for the permanent Array database)
typedef struct {
    char name[50];
    char illness[100];
    int priority;
} PatientRecord;

// Node for the Live Triage Queue (Used for the Linked List)
typedef struct Node {
    PatientRecord data;
    struct Node* next;
} Node;

// Global Array for Database (Experiment 4 style - Static Storage)
PatientRecord hospitalDB[MAX_RECORDS];
int totalPatients = 0;

// Function to calculate priority based on illness keywords
int calculatePriority(char illness[]) {
    char temp[100];
    strcpy(temp, illness);
    // Convert to lowercase to ensure matching works regardless of case
    for(int i = 0; temp[i]; i++) temp[i] = tolower(temp[i]);

    // Priority 1: Critical / Life-threatening
    if (strstr(temp, "heart") || strstr(temp, "chest") || strstr(temp, "breath") || 
        strstr(temp, "unconscious") || strstr(temp, "stroke") || strstr(temp, "cancer")) 
        return 1; 
    
    // Priority 2: Urgent / Serious but stable
    if (strstr(temp, "fracture") || strstr(temp, "blood") || strstr(temp, "pain") || 
        strstr(temp, "burn") || strstr(temp, "injury")) 
        return 2; 
    
    // Priority 3: Non-urgent
    return 3;     
}

// Function to insert into Priority Linked List (Experiment 6 & 10 Logic)
void enqueueTriage(Node** head, PatientRecord p) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = p;
    newNode->next = NULL;

    // Insert at head if list is empty or new patient has higher priority (lower number)
    if (*head == NULL || p.priority < (*head)->data.priority) {
        newNode->next = *head;
        *head = newNode;
    } else {
        // Traverse to find the correct sorted position
        Node* curr = *head;
        while (curr->next != NULL && curr->next->data.priority <= p.priority) {
            curr = curr->next;
        }
        newNode->next = curr->next;
        curr->next = newNode;
    }
}

// Function to remove and treat the top priority patient
void treatNextPatient(Node** head) {
    if (*head == NULL) {
        printf("\nNo patients waiting in the triage queue.\n");
        return;
    }
    Node* temp = *head;
    printf("\n>>> NOW TREATING: %s for %s (Priority %d)\n", 
           temp->data.name, temp->data.illness, temp->data.priority);
    *head = (*head)->next;
    free(temp);
}

// Function to display the permanent array database
void displayHistory() {
    if (totalPatients == 0) {
        printf("\nNo history found in database.\n");
        return;
    }
    printf("\n--- HOSPITAL PERMANENT RECORDS (ARRAY DATABASE) ---\n");
    printf("%-20s %-30s %-10s\n", "Name", "Illness", "Priority");
    printf("------------------------------------------------------------\n");
    for (int i = 0; i < totalPatients; i++) {
        printf("%-20s %-30s %-10d\n", hospitalDB[i].name, hospitalDB[i].illness, hospitalDB[i].priority);
    }
}

// Function to display the live waiting list
void displayLiveQueue(Node* head) {
    printf("\n--- LIVE TRIAGE QUEUE (PRIORITY LINKED LIST) ---\n");
    if (head == NULL) {
        printf("Queue is empty. No patients waiting.\n");
        return;
    }
    while (head != NULL) {
        printf("[%s | P:%d] -> ", head->data.name, head->data.priority);
        head = head->next;
    }
    printf("NULL\n");
}

int main() {
    Node* liveQueue = NULL;
    int choice;

    while (1) {
        printf("\n=================================");
        printf("\n HOSPITAL TRIAGE MANAGEMENT SYSTEM");
        printf("\n=================================");
        printf("\n1. Admit New Patient");
        printf("\n2. Treat Next Patient (Dequeue)");
        printf("\n3. View Permanent Records (Array)");
        printf("\n4. View Live Triage Queue (List)");
        printf("\n5. Exit");
        printf("\nEnter Choice: ");
        
        if (scanf("%d", &choice) != 1) {
            while(getchar() != '\n'); // Clear invalid input
            continue;
        }
        getchar(); // Clear the newline from buffer after scanf

        if (choice == 1) {
            if (totalPatients >= MAX_RECORDS) {
                printf("\nError: Hospital database is full!\n");
                continue;
            }

            PatientRecord p;
            printf("Enter Patient Name: ");
            fgets(p.name, sizeof(p.name), stdin);
            p.name[strcspn(p.name, "\n")] = 0; // Remove trailing newline

            printf("Enter Illness/Symptoms: ");
            fgets(p.illness, sizeof(p.illness), stdin);
            p.illness[strcspn(p.illness, "\n")] = 0; // Remove trailing newline
            
            p.priority = calculatePriority(p.illness);
            printf("\n>>> System Analyzed Condition. Priority Assigned: %d\n", p.priority);

            // Save to the Array (Historical Record)
            hospitalDB[totalPatients++] = p;
            
            // Add to the Linked List (Live Triage)
            enqueueTriage(&liveQueue, p);
            printf("Patient admitted successfully.\n");

        } else if (choice == 2) {
            treatNextPatient(&liveQueue);
        } else if (choice == 3) {
            displayHistory();
        } else if (choice == 4) {
            displayLiveQueue(liveQueue);
        } else if (choice == 5) {
            printf("Exiting system...\n");
            break;
        } else {
            printf("Invalid choice. Please try again.\n");
        }
    }

    // Clean up memory before exiting
    while (liveQueue != NULL) {
        Node* temp = liveQueue;
        liveQueue = liveQueue->next;
        free(temp);
    }

    return 0;
}