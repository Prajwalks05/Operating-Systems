#include <stdio.h>
#include <stdlib.h>
struct process_fcfs
{
    char process_id[5];
    int arrival_time;
    int burst_time;
    int completion_time;
    int turn_around_time;
    int waiting_time;
    int response_time;
    int queue_type; // 0 for high priority, 1 for low priority
};
void input_process_details(struct process_fcfs *p)
{
    printf("Enter Process ID: ");
    scanf("%s", p->process_id);

    printf("Enter Arrival Time: ");
    scanf("%d", &p->arrival_time);

    printf("Enter Burst Time: ");
    scanf("%d", &p->burst_time);

    printf("Enter Queue Type (0 for High Priority, 1 for Low Priority): ");
    scanf("%d", &p->queue_type); // 0 for High Priority, 1 for Low Priority
}
void calculate_times(struct process_fcfs *p, int n)
{
    int current_time = 0;
    for (int i = 0; i < n; i++)
    {
        if (current_time < p[i].arrival_time)
        {
            current_time = p[i].arrival_time;
        }
        p[i].completion_time = current_time + p[i].burst_time;
        p[i].turn_around_time = p[i].completion_time - p[i].arrival_time;
        p[i].waiting_time = p[i].turn_around_time - p[i].burst_time;
        p[i].response_time = p[i].waiting_time;
        current_time = p[i].completion_time;
    }
}
void calculate_averages(struct process_fcfs p[], int n)
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
void display_process_details(struct process_fcfs p[], int n)
{
    printf("\n%-15s%-15s%-15s%-15s%-15s%-15s%-15s%-15s\n", "Process ID", "Arrival Time", "Burst Time", "Completion Time", "Turn Around Time", "Waiting Time", "Response Time", "Queue Type");
    for (int i = 0; i < n; i++)
    {
        printf("%-15s%-15d%-15d%-15d%-15d%-15d%-15d%-15d\n", p[i].process_id, p[i].arrival_time, p[i].burst_time, p[i].completion_time, p[i].turn_around_time, p[i].waiting_time, p[i].response_time, p[i].queue_type);
    }
    calculate_averages(p, n);
}
void schedule_multilevel_queue(struct process_fcfs p[], int n)
{
    struct process_fcfs high_priority_queue[n], low_priority_queue[n];
    int high_priority_count = 0, low_priority_count = 0;

    // Separate processes into high priority and low priority queues
    for (int i = 0; i < n; i++)
    {
        if (p[i].queue_type == 0)
        {
            high_priority_queue[high_priority_count++] = p[i];
        }
        else
        {
            low_priority_queue[low_priority_count++] = p[i];
        }
    }
    // First, calculate times for the high priority queue
    calculate_times(high_priority_queue, high_priority_count);
    // Then calculate times for the low priority queue
    calculate_times(low_priority_queue, low_priority_count);
    // Merge the queues back into the original array for display
    int index = 0;
    for (int i = 0; i < high_priority_count; i++)
    {
        p[index++] = high_priority_queue[i];
    }
    for (int i = 0; i < low_priority_count; i++)
    {
        p[index++] = low_priority_queue[i];
    }
}
int main()
{
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct process_fcfs processes[n];
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
            for (int i = 0; i < n; i++)
            {
                printf("\nEnter details for Process %d:\n", i + 1);
                input_process_details(&processes[i]);
            }
            break;

        case 2:
            schedule_multilevel_queue(processes, n);
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
