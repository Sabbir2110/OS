#include <stdio.h>

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    float bt[n], wt[n], tat[n];

    printf("Enter burst times:\n");
    for (int i = 0; i < n; i++) {
        printf("P%d: ", i + 1);
        scanf("%f", &bt[i]);
    }

    // FCFS calculations
    wt[0] = 0;
    for (int i = 1; i < n; i++) {
        wt[i] = wt[i - 1] + bt[i - 1];
    }

    for (int i = 0; i < n; i++) {
        tat[i] = wt[i] + bt[i];
    }

    // Print Table
    printf("\nProcess\tBT\tWT\tTAT\n");
    float totalWT = 0, totalTAT = 0;
    for (int i = 0; i < n; i++) {
        printf("P%d\t%.1f\t%.1f\t%.1f\n", i + 1, bt[i], wt[i], tat[i]);
        totalWT += wt[i];
        totalTAT += tat[i];
    }

    // Print Averages
    printf("\nAverage Waiting Time = %.2f", totalWT / n);
    printf("\nAverage Turnaround Time = %.2f\n", totalTAT / n);

    // Gantt Chart
    printf("\nGantt Chart:\n");

    // Top bar
    printf(" ");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < bt[i]; j++) printf("--");
        printf(" ");
    }
    printf("\n|");

    // Process IDs inside boxes
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < bt[i] - 1; j++) printf(" ");
        printf("P%d", i + 1);
        for (int j = 0; j < bt[i] - 1; j++) printf(" ");
        printf("|");
    }
    printf("\n ");

    // Bottom bar
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < bt[i]; j++) printf("--");
        printf(" ");
    }

    // Timeline
    printf("\n0");
    float time = 0;
    for (int i = 0; i < n; i++) {
        time += bt[i];
        printf("   %.0f", time);
    }

    printf("\n");
    return 0;
}
