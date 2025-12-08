#include <stdio.h>

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    float bt[n], rt[n], wt[n], tat[n];
    int i, j, completed=0, t=0, min_index;
    float min;
    int is_completed;

    printf("Enter burst times:\n");
    for (i = 0; i < n; i++) {
        printf("P%d: ", i+1);
        scanf("%f", &bt[i]);
        rt[i] = bt[i];
        wt[i] = 0;
        tat[i] = 0;
    }

    printf("\nGantt Chart (time unit marks process execution):\n");
    while (completed != n) {
        min = 1e9;
        min_index = -1;
        for (i = 0; i < n; i++) {
            if (rt[i] > 0 && rt[i] < min) {
                min = rt[i]; min_index = i;
            }
        }

        if (min_index != -1) {
            printf("|P%d", min_index+1);
            rt[min_index] -= 1;
            t += 1;

            if (rt[min_index] == 0) {
                completed++;
                tat[min_index] = t;
                wt[min_index] = tat[min_index] - bt[min_index];
            }
        }
    }

    // Print table
    printf("\n\nProcess\tBT\tWT\tTAT\n");
    float totalWT=0, totalTAT=0;
    for(i=0;i<n;i++){
        printf("P%d\t%.1f\t%.1f\t%.1f\n", i+1, bt[i], wt[i], tat[i]);
        totalWT += wt[i]; totalTAT += tat[i];
    }
    printf("\nAverage WT=%.2f, Average TAT=%.2f\n", totalWT/n, totalTAT/n);

    return 0;
}
