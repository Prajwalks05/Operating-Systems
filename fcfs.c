#include <stdio.h>
#include <stdlib.h>

typedef struct fcfs {
    int pid;
    int arrivaltime;
    int bursttime;
    int completiontime;
    int turnaroundtime;
    int waitingtime;
    int responsetime;
} fcfs;

void input_process_details(struct fcfs *f) {
    printf("Enter Process ID: ");
    scanf("%d", &f->pid);

    printf("Enter Arrival Time: ");
    scanf("%d", &f->arrivaltime);

    printf("Enter Burst Time: ");
    scanf("%d", &f->bursttime);
}

int compare_arrival_time(const void *a, const void *b) {
    return ((fcfs*)a)->arrivaltime - ((fcfs*)b)->arrivaltime;
}

void calculate_time(fcfs *processes, int n) {
    int current_time = 0;

    qsort(processes, n, sizeof(fcfs), compare_arrival_time);

    for (int i = 0; i < n; i++) {
        if (current_time < processes[i].arrivaltime) {                                                                                                                                             
            current_time = processes[i].arrivaltime;
        }

        processes[i].completiontime = current_time + processes[i].bursttime;
        processes[i].turnaroundtime = processes[i].completiontime - processes[i].arrivaltime;
        processes[i].waitingtime = processes[i].turnaroundtime - processes[i].bursttime;
        processes[i].responsetime = processes[i].waitingtime;

        current_time = processes[i].completiontime;
    }
}

float calculate_avg_turnaround_time(fcfs *processes, int n) {
    int total_turnaround_time = 0;
    for (int i = 0; i < n; i++) {
        total_turnaround_time += processes[i].turnaroundtime;
    }
    return (float)total_turnaround_time / n;
}

float calculate_avg_waiting_time(fcfs *processes, int n) {
    int total_waiting_time = 0;
    for (int i = 0; i < n; i++) {
        total_waiting_time += processes[i].waitingtime;
    }
    return (float)total_waiting_time / n;
}

void display_process_details(fcfs *processes, int n) {
    printf("\nProcess ID\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\tResponse Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", 
                processes[i].pid, processes[i].arrivaltime, processes[i].bursttime, 
                processes[i].completiontime, processes[i].turnaroundtime, 
                processes[i].waitingtime, processes[i].responsetime);
    }

    float avg_turnaround_time = calculate_avg_turnaround_time(processes, n);
    float avg_waiting_time = calculate_avg_waiting_time(processes, n);

    printf("\nAverage Turnaround Time: %.2f", avg_turnaround_time);
    printf("\nAverage Waiting Time: %.2f\n", avg_waiting_time);
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    
    struct fcfs processes[n];
    int choice;

    do {
        printf("\nMenu:\n");
        printf("1. Input Process Details\n");1s 
        printf("2. Display All Process Details\n");
        printf("3. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            for (int i = 0; i < n; i++) {
                printf("\nEnter details for Process %d:\n", i + 1);
                input_process_details(&processes[i]);
            }
            calculate_time(processes, n);
            break;
        case 2:
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
