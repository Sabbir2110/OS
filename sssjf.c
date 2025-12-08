#include <stdio.h>

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    float bt[n], wt[n], tat[n];
    int i, j;
    int process[n];

    printf("Enter burst times:\n");
    for (i = 0; i < n; i++) {
        printf("P%d: ", i + 1);
        scanf("%f", &bt[i]);
        process[i] = i + 1;
    }

    // Sort by burst time
    for (i = 0; i < n-1; i++) {
        for (j = 0; j < n-i-1; j++) {
            if (bt[j] > bt[j+1]) {
                float temp = bt[j]; bt[j] = bt[j+1]; bt[j+1] = temp;
                int tempP = process[j]; process[j] = process[j+1]; process[j+1] = tempP;
            }
        }
    }

    wt[0] = 0;
    for (i = 1; i < n; i++) wt[i] = wt[i-1] + bt[i-1];
    for (i = 0; i < n; i++) tat[i] = wt[i] + bt[i];

    printf("\nProcess\tBT\tWT\tTAT\n");
    float totalWT=0, totalTAT=0;
    for (i = 0; i < n; i++) {
        printf("P%d\t%.1f\t%.1f\t%.1f\n", process[i], bt[i], wt[i], tat[i]);
        totalWT += wt[i]; totalTAT += tat[i];
    }
    printf("\nAverage WT=%.2f, Average TAT=%.2f\n", totalWT/n, totalTAT/n);

    // Gantt Chart
    printf("\nGantt Chart:\n ");
    for(i=0;i<n;i++){for(j=0;j<bt[i];j++)printf("--"); printf(" ");} printf("\n|");
    for(i=0;i<n;i++){for(j=0;j<bt[i]-1;j++)printf(" "); printf("P%d", process[i]); for(j=0;j<bt[i]-1;j++)printf(" "); printf("|");}
    printf("\n ");
    for(i=0;i<n;i++){for(j=0;j<bt[i];j++)printf("--"); printf(" ");}
    printf("\n0"); float time=0; for(i=0;i<n;i++){time+=bt[i]; printf("   %.0f", time);} printf("\n");
    return 0;
}
