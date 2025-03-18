#include <stdio.h>
#include <stdlib.h>

struct process_sjf {
    char process_id[5];
    int arrival_time;
    int burst_time;
    int completion_time;
    int turn_around_time;
    int waiting_time;
    int response_time;
    int start_time;
};

// Function to input process details
void input_process_details(struct process_sjf *p) {
    printf("Enter Process ID: ");
    scanf("%s", p->process_id);

    printf("Enter Arrival Time: ");
    scanf("%d", &p->arrival_time);

    printf("Enter Burst Time: ");
    scanf("%d", &p->burst_time);

    // Initializing remaining burst time for SJF
    p->start_time = -1;
}

// Function to compare processes by arrival time (used for sorting)
int compare_arrival_time(const void *a, const void *b) {
    struct process_sjf *p1 = (struct process_sjf *)a;
    struct process_sjf *p2 = (struct process_sjf *)b;
    return p1->arrival_time - p2->arrival_time;
}

// Function to compare processes by burst time (used for SJF Non-Preemptive scheduling)
int compare_burst_time(const void *a, const void *b) {
    struct process_sjf *p1 = (struct process_sjf *)a;
    struct process_sjf *p2 = (struct process_sjf *)b;
    return p1->burst_time - p2->burst_time;
}

// Function to calculate times (Completion, Turnaround, Waiting, Response times)
void calculate_times(struct process_sjf *p, int n) {
    int current_time = 0;
    int completed = 0;
    int process_completed[n];
    for (int i = 0; i < n; i++) {
        process_completed[i] = 0;  // Mark all processes as not completed
    }

    // Process the CPU based on shortest burst time
    while (completed < n) {
        int shortest_process_index = -1;
        int min_burst_time = 10000;  // Arbitrarily large number

        // Find the process that is ready to execute and has the shortest burst time
        for (int i = 0; i < n; i++) {
            if (!process_completed[i] && p[i].arrival_time <= current_time && p[i].burst_time < min_burst_time) {
                min_burst_time = p[i].burst_time;
                shortest_process_index = i;
            }
        }

        if (shortest_process_index != -1) {
            // Set start time if it's the first time it's starting
            if (p[shortest_process_index].start_time == -1) {
                p[shortest_process_index].start_time = current_time;
            }

            // Execute the process to completion
            current_time += p[shortest_process_index].burst_time;
            p[shortest_process_index].completion_time = current_time;

            // Calculate turnaround time (Completion Time - Arrival Time)
            p[shortest_process_index].turn_around_time = p[shortest_process_index].completion_time - p[shortest_process_index].arrival_time;

            // Calculate waiting time (Turnaround Time - Burst Time)
            p[shortest_process_index].waiting_time = p[shortest_process_index].turn_around_time - p[shortest_process_index].burst_time;

            // Set response time (waiting time for non-preemptive SJF)
            p[shortest_process_index].response_time = p[shortest_process_index].waiting_time;

            // Mark this process as completed
            process_completed[shortest_process_index] = 1;
            completed++;
        } else {
            // If no process is ready to execute, increment time
            current_time++;
        }
    }
}

// Function to display process details
void display_process_details(struct process_sjf p[], int n) {
    // Print header row
    printf("\n%-15s%-15s%-15s%-15s%-15s%-15s%-15s\n", "Process ID", "Arrival Time", "Burst Time", "Completion Time", "Turn Around Time", "Waiting Time", "Response Time");

    // Print process details for each process
    for (int i = 0; i < n; i++) {
        printf("%-15s%-15d%-15d%-15d%-15d%-15d%-15d\n", p[i].process_id, p[i].arrival_time, p[i].burst_time, p[i].completion_time, p[i].turn_around_time, p[i].waiting_time, p[i].response_time);
    }
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct process_sjf processes[n];  // Declare an array of structures

    int choice;
    do {
        printf("\nMenu:\n");
        printf("1. Input Process Details\n");
        printf("2. Display All Process Details\n");
        printf("3. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                // Input details for each process
                for (int i = 0; i < n; i++) {
                    printf("\nEnter details for Process %d:\n", i + 1);
                    input_process_details(&processes[i]);
                }
                break;

            case 2:
                // Sort processes by arrival time
                qsort(processes, n, sizeof(struct process_sjf), compare_arrival_time);

                // Calculate and display details for all processes
                calculate_times(processes, n);
                display_process_details(processes, n);
                break;

            case 3:
                printf("Exiting...\n");
                break;

            default:
                printf("Invalid choice, please try again.\n");
        }
    } while (choice != 3);

    return 0;
}
