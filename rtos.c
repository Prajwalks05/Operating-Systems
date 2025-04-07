#include <stdio.h>
#include <string.h>

#define MAX 10

typedef struct {
    char name[4];         // Process name (max 3 chars + null terminator)
    int burst_time;       // Execution time
    int deadline;         // Max completion time (deadline)
    int start_time;       // When it starts
    int end_time;         // When it ends
    int status;           // 1 = Success, 0 = Failed
} Process;

void sortByDeadline(Process p[], int n) {
    Process temp;
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (p[j].deadline > p[j+1].deadline) {
                temp = p[j];
                p[j] = p[j+1];
                p[j+1] = temp;
            }
        }
    }
}

int main() {
    Process p[MAX];
    int n, current_time = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("\nProcess %d:\n", i + 1);
        printf("Enter process name (max 3 characters): ");
        scanf("%s", p[i].name);
        printf("Enter burst time (ms): ");
        scanf("%d", &p[i].burst_time);
        printf("Enter deadline (max completion time in ms): ");
        scanf("%d", &p[i].deadline);
    }

    // Sort processes based on deadline (Earliest Deadline First)
    sortByDeadline(p, n);

    printf("\nScheduling Order and Status:\n");
    printf("--------------------------------------------------\n");
    printf("| Name | Start | End  | Deadline | Status        |\n");
    printf("--------------------------------------------------\n");

    for (int i = 0; i < n; i++) {
        p[i].start_time = current_time;
        p[i].end_time = current_time + p[i].burst_time;
        p[i].status = (p[i].end_time <= p[i].deadline) ? 1 : 0;
        current_time = p[i].end_time;

        printf("| %-4s | %-5d | %-4d | %-8d | %-13s |\n",
               p[i].name,
               p[i].start_time,
               p[i].end_time,
               p[i].deadline,
               p[i].status ? "Success" : "Failed");
    }

    printf("--------------------------------------------------\n");
    return 0;
}
