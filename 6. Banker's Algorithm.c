#include <stdio.h>

int main() {
    int n, m, i, j, k;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter number of resource types: ");
    scanf("%d", &m);

    int alloc[n][m], max[n][m], avail[m];
    int need[n][m], finish[n], safe[n];

    printf("\nEnter Allocation Matrix:\n");
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            scanf("%d", &alloc[i][j]);

    printf("\nEnter Max Matrix:\n");
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            scanf("%d", &max[i][j]);

    printf("\nEnter Available Resources:\n");
    for (i = 0; i < m; i++)
        scanf("%d", &avail[i]);

    // Calculate Need matrix
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            need[i][j] = max[i][j] - alloc[i][j];

    for (i = 0; i < n; i++)
        finish[i] = 0;

    int count = 0;
    int index = 0;

    while (count < n) {
        int found = 0;

        for (i = 0; i < n; i++) {
            if (finish[i] == 0) {
                int flag = 0;

                for (j = 0; j < m; j++) {
                    if (need[i][j] > avail[j]) {
                        flag = 1;
                        break;
                    }
                }

                if (flag == 0) {
                    for (k = 0; k < m; k++)
                        avail[k] += alloc[i][k];

                    safe[index++] = i;
                    finish[i] = 1;
                    found = 1;
                    count++;
                }
            }
        }

        if (found == 0) {
            printf("\nSystem is in DEADLOCK! No safe sequence.\n");
            return 0;
        }
    }

    printf("\nSystem is in SAFE STATE.\nSafe Sequence: ");
    for (i = 0; i < n; i++)
        printf("P%d ", safe[i]);

    printf("\n");
    return 0;
}


