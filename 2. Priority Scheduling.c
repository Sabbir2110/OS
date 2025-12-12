#include <stdio.h>

struct Process {
    int pid;        // Process ID
    int bt;         // Burst Time
    int priority;   // Priority (lower number = higher priority)
    int wt;         // Waiting Time
    int tat;        // Turnaround Time
};

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    // Input
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;

        printf("Enter Burst Time for P%d: ", i + 1);
        scanf("%d", &p[i].bt);

        printf("Enter Priority for P%d: ", i + 1);
        scanf("%d", &p[i].priority);
    }

    // Sorting based on Priority (ascending → highest priority first)
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (p[j].priority < p[i].priority) {
                struct Process temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }

    // Calculate Waiting Time
    p[0].wt = 0;
    for (int i = 1; i < n; i++) {
        p[i].wt = p[i - 1].wt + p[i - 1].bt;
    }

    // Calculate Turnaround Time
    for (int i = 0; i < n; i++) {
        p[i].tat = p[i].bt + p[i].wt;
    }

    // Output
    printf("\nP\tBT\tPri\tWT\tTAT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].bt, p[i].priority, p[i].wt, p[i].tat);
    }

    // Average Times
    float avgWT = 0, avgTAT = 0;
    for (int i = 0; i < n; i++) {
        avgWT += p[i].wt;
        avgTAT += p[i].tat;
    }

    printf("\nAverage Waiting Time = %.2f", avgWT / n);
    printf("\nAverage Turnaround Time = %.2f\n", avgTAT / n);

    return 0;
}
