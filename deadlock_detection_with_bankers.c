#include <stdio.h>
#include <stdbool.h>
int main() {
    int P, R;
    // Input number of processes and resources
    printf("Enter number of processes: ");
    scanf("%d", &P);
    printf("Enter number of resource types: ");
    scanf("%d", &R);
    int alloc[P][R];   // Allocation Matrix
    int request[P][R]; // Request Matrix (similar to Need in Banker's Algorithm)
    int avail[R];      // Available Resources
    bool finish[P];    // Track which processes can finish
    // Initialize finish array to false
    for (int i = 0; i < P; i++)
        finish[i] = false;
    // Input Allocation Matrix
    printf("\nEnter Allocation Matrix (%d x %d):\n", P, R);
    for (int i = 0; i < P; i++) {
        printf("Process P%d: ", i);
        for (int j = 0; j < R; j++) {
            scanf("%d", &alloc[i][j]);
        }
    }
    // Input Request Matrix
    printf("\nEnter Request Matrix (%d x %d):\n", P, R);
    for (int i = 0; i < P; i++) {
        printf("Process P%d: ", i);
        for (int j = 0; j < R; j++) {
            scanf("%d", &request[i][j]);
        }
    }
    // Input Available Resources
    printf("\nEnter Available Resources (size %d): ", R);
    for (int j = 0; j < R; j++) { 

        scanf("%d", &avail[j]);
    }
    // Begin Deadlock Detection
    int count = 0;
    while (count < P)  {
        bool found = false;
        for (int i = 0; i < P; i++) {
            // If the process has not finished yet
            if (!finish[i]) {
                int j;
                // Check if the process's request can be satisfied with available resources
                for (j = 0; j < R; j++) {
                    if (request[i][j] > avail[j])
                        break;
                }
                // If all resources needed by the process are available
                if (j == R) {
                    // Assume process finishes; release its allocated resources
                    for (int k = 0; k < R; k++) {
                        avail[k] += alloc[i][k];
                    }
                    finish[i] = true;
                    found = true;
                    count++;
                }
            }
        }
        // If no unfinished process could proceed, break the loop (potential deadlock)
        if (!found)
            break;
    }
    // Final check for deadlock
    bool deadlock = false;
    printf("\nDeadlock Detection Result:\n");
    for (int i = 0; i < P; i++) {
        if (!finish[i]) {
            deadlock = true;
            printf("Process P%d is deadlocked.\n", i);
        }
    }
    if (!deadlock)
        printf("No deadlock detected. All processes can finish.\n");

    return 0;
}
