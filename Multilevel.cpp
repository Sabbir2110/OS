#include <stdio.h>

struct process {
    int pid;
    int burst_time;
};

int main() {
    struct process q0[10], q1[10], q2[10];
    int n0, n1, n2;
    int i;

    printf("Enter number of processes in Queue 0 (Highest Priority): ");
    scanf("%d", &n0);
    for (i = 0; i < n0; i++) {
        q0[i].pid = i + 1;
        printf("Burst time for P%d: ", q0[i].pid);
        scanf("%d", &q0[i].burst_time);
    }

    printf("\nEnter number of processes in Queue 1: ");
    scanf("%d", &n1);
    for (i = 0; i < n1; i++) {
        q1[i].pid = i + 1;
        printf("Burst time for P%d: ", q1[i].pid);
        scanf("%d", &q1[i].burst_time);
    }

    printf("\nEnter number of processes in Queue 2 (Lowest Priority): ");
    scanf("%d", &n2);
    for (i = 0; i < n2; i++) {
        q2[i].pid = i + 1;
        printf("Burst time for P%d: ", q2[i].pid);
        scanf("%d", &q2[i].burst_time);
    }

    printf("\nExecution Order:\n");

    printf("\nQueue 0:\n");
    for (i = 0; i < n0; i++) {
        printf("P%d executed for %d units\n", q0[i].pid, q0[i].burst_time);
    }

    printf("\nQueue 1:\n");
    for (i = 0; i < n1; i++) {
        printf("P%d executed for %d units\n", q1[i].pid, q1[i].burst_time);
    }

    printf("\nQueue 2:\n");
    for (i = 0; i < n2; i++) {
        printf("P%d executed for %d units\n", q2[i].pid, q2[i].burst_time);
    }

    return 0;
}
