#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Process
{
    int pid;
    char p_name[50];
    char process_arrival_time[7];
    char process_completion_time[7];
    int executiontime;
} proc;
void addProcesses(proc *process_array, int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("Enter the Process id:\t");
        scanf("%d", &process_array[i].pid);
        printf("Enter the Process name:\t");
        scanf("%s", process_array[i].p_name);
        printf("Enter the Process arrival time (HH:MM:SS):\t");
        scanf("%s", process_array[i].process_arrival_time);
        printf("Enter the Process completion time (HH:MM:SS):\t");
        scanf("%s", process_array[i].process_completion_time);
        printf("Enter the Process execution time (in ms):\t");
        scanf("%d", &process_array[i].executiontime);
    }
}
void displayProcesses(proc *process_array, int n)
{
    printf("\n\nList of Processes:\n");
    for (int i = 0; i < n; i++)
    {
        printf("Process id: %d\n", process_array[i].pid);
        printf("Process name: %s\n", process_array[i].p_name);
        printf("Process arrival time: %s\n", process_array[i].process_arrival_time);
        printf("Process completion time: %s\n", process_array[i].process_completion_time);
        printf("Process execution time: %d ms\n", process_array[i].executiontime);
        printf("--------------------------\n");
    }
}
void searchProcessById(proc *process_array, int n, int search_pid)
{
    int found = 0;
    for (int i = 0; i < n; i++)
    {
        if (process_array[i].pid == search_pid)
        {
            printf("\nProcess Found:\n");
            printf("Process id: %d\n", process_array[i].pid);
            printf("Process name: %s\n", process_array[i].p_name);
            printf("Process arrival time: %s\n", process_array[i].process_arrival_time);
            printf("Process completion time: %s\n", process_array[i].process_completion_time);
            printf("Process execution time: %d ms\n", process_array[i].executiontime);
            found = 1;
            break;
        }
    }
    if (!found)
    {
        printf("\nNo process found with Process id: %d\n", search_pid);
    }
}
int main()
{
    int n;
    printf("Enter the number of processes to add: ");
    scanf("%d", &n);
    proc process_array[n];
    addProcesses(process_array, n);
    displayProcesses(process_array, n);
    int search_pid;
    printf("\nEnter Process ID to search: ");
    scanf("%d", &search_pid);
    searchProcessById(process_array, n, search_pid);
    return 0;
}