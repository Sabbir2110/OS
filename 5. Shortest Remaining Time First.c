#include <stdio.h>
#include <stdbool.h>

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int i, completed = 0, t = 0, min_index;
    float bt[n], rt[n], wt[n], tat[n];

    // Input burst times
    printf("Enter burst times:\n");
    for (i = 0; i < n; i++) {
        printf("P%d: ", i + 1);
        scanf("%f", &bt[i]);
        rt[i] = bt[i];  // remaining time
        wt[i] = 0;
        tat[i] = 0;
    }

    printf("\nGantt Chart (time progression showing process execution):\n");

    while (completed != n) {
        float min = 1e9;
        min_index = -1;

        // Find process with shortest remaining time at this time unit
        for (i = 0; i < n; i++) {
            if (rt[i] > 0 && rt[i] < min) {
                min = rt[i];
                min_index = i;
            }
        }

        if (min_index != -1) {
            printf("|P%d", min_index + 1); // mark process execution
            rt[min_index] -= 1;           // execute 1 unit
            t += 1;                       // increment time

            if (rt[min_index] == 0) {     // process completed
                completed++;
                tat[min_index] = t;       // turnaround time
                wt[min_index] = tat[min_index] - bt[min_index]; // waiting time
            }
        }
    }
    printf("|\n");

    // Print table
    printf("\nProcess\tBT\tWT\tTAT\n");
    float totalWT = 0, totalTAT = 0;
    for (i = 0; i < n; i++) {
        printf("P%d\t%.1f\t%.1f\t%.1f\n", i + 1, bt[i], wt[i], tat[i]);
        totalWT += wt[i];
        totalTAT += tat[i];
    }

    printf("\nAverage Waiting Time = %.2f", totalWT / n);
    printf("\nAverage Turnaround Time = %.2f\n", totalTAT / n);

    return 0;
}

