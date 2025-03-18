#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct process_sjf
{
    char process_id[5];
    int arrival_time;
    int burst_time;
    int remaining_burst_time;
    int completion_time;
    int turn_around_time;
    int waiting_time;
    int response_time;
    int start_time;
};

// Function to input process details
void input_process_details(struct process_sjf *p)
{
    printf("Enter Process ID: ");
    scanf("%s", p->process_id);

    printf("Enter Arrival Time: ");
    scanf("%d", &p->arrival_time);

    printf("Enter Burst Time: ");
    scanf("%d", &p->burst_time);
    p->remaining_burst_time = p->burst_time; // Initialize remaining burst time
}

// Function to calculate times (Completion, Turnaround, Waiting, Response times)
void calculate_times(struct process_sjf *p, int n)
{
    int current_time = 0;
    int completed = 0;
    bool is_completed[n];
    for (int i = 0; i < n; i++)
    {
        is_completed[i] = false;
    }

    // Process the CPU based on the shortest remaining burst time
    while (completed < n)
    {
        // Find process with the smallest remaining burst time that has arrived
        int idx = -1;
        int min_remaining_burst_time = 10000; // Arbitrarily large number

        for (int i = 0; i < n; i++)
        {
            if (!is_completed[i] && p[i].arrival_time <= current_time && p[i].remaining_burst_time < min_remaining_burst_time)
            {
                min_remaining_burst_time = p[i].remaining_burst_time;
                idx = i;
            }
        }

        if (idx != -1)
        {
            // Start time of process
            if (p[idx].start_time == -1)
            {
                p[idx].start_time = current_time;
            }

            // Execute the process for 1 unit time
            p[idx].remaining_burst_time--;
            current_time++;

            // If process completes
            if (p[idx].remaining_burst_time == 0)
            {
                is_completed[idx] = true;
                completed++;
                p[idx].completion_time = current_time;
                p[idx].turn_around_time = p[idx].completion_time - p[idx].arrival_time;
                p[idx].waiting_time = p[idx].turn_around_time - p[idx].burst_time;
                p[idx].response_time = p[idx].start_time - p[idx].arrival_time;
            }
        }
        else
        {
            current_time++;
        }
    }
}

void calculate_averages(struct process_sjf p[], int n)
{
    int total_turnaround_time = 0;
    int total_waiting_time = 0;
    int total_response_time = 0;

    for (int i = 0; i < n; i++)
    {
        total_turnaround_time += p[i].turn_around_time;
        total_waiting_time += p[i].waiting_time;
        total_response_time += p[i].response_time;
    }

    printf("\nAverages:\n");
    printf("Average Turnaround Time: %.2f\n", (float)total_turnaround_time / n);
    printf("Average Waiting Time: %.2f\n", (float)total_waiting_time / n);
    printf("Average Response Time: %.2f\n", (float)total_response_time / n);
}

void display_process_details(struct process_sjf p[], int n)
{
    // Print header row
    printf("\n%-15s%-15s%-15s%-15s%-15s%-15s%-15s\n", "Process ID", "Arrival Time", "Burst Time", "Completion Time", "Turn Around Time", "Waiting Time", "Response Time");

    // Print process details for each process
    for (int i = 0; i < n; i++)
    {
        printf("%-15s%-15d%-15d%-15d%-15d%-15d%-15d\n", p[i].process_id, p[i].arrival_time, p[i].burst_time, p[i].completion_time, p[i].turn_around_time, p[i].waiting_time, p[i].response_time);
    }

    calculate_averages(p, n);
}

int main()
{
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct process_sjf processes[n]; // Declare an array of structures

    int choice;
    do
    {
        printf("\nMenu:\n");
        printf("1. Input Process Details\n");
        printf("2. Display All Process Details\n");
        printf("3. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            // Input details for each process
            for (int i = 0; i < n; i++)
            {
                printf("\nEnter details for Process %d:\n", i + 1);
                input_process_details(&processes[i]);
                processes[i].start_time = -1; // Initialize start time to -1 (not yet started)
            }
            break;

        case 2:
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
