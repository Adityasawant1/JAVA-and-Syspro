#include <stdio.h>


int main() {
    int n, m, i, j, k;
    
    int count = 0, choice;

    printf("Enter the number of processes: ");
    scanf("%d", &n);
    printf("Enter the number of resources: ");
    scanf("%d", &m);
    
    int alloc[n][m], max[n][m];
    int total[m], avail[m], need[n][TMP_MAX];
    int finish[n], safeSequence[n];

    printf("Enter the allocation matrix:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            scanf("%d", &alloc[i][j]);
        }
    }

    printf("Enter the max matrix:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    printf("Select an option:\n");
    printf("1. Input available resources directly.\n");
    printf("2. Input total resources and calculate available resources.\n");
    scanf("%d", &choice);

    if (choice == 1) {
        printf("Enter the available resources:\n");
        for (i = 0; i < m; i++) {
            scanf("%d", &avail[i]);
        }
    } else if (choice == 2) {
        printf("Enter the total resources:\n");
        for (i = 0; i < m; i++) {
            scanf("%d", &total[i]);
        }
        for (j = 0; j < m; j++) {
            avail[j] = total[j];
            for (i = 0; i < n; i++) {
                avail[j] -= alloc[i][j];
            }
        }
    } else {
        printf("Invalid choice! Exiting...\n");
        return 1;
    }
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }

    printf("\nThe Need Matrix is:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            printf("%d ", need[i][j]);
        }
        printf("\n");
    }

    for (i = 0; i < n; i++) {
        finish[i] = 0;
    }

    int processCompleted;
    while (count < n) {
        processCompleted = 0;

        for (i = 0; i < n; i++) {
            if (finish[i] == 0) {
                int flag = 1;
                for (j = 0; j < m; j++) {
                    if (need[i][j] > avail[j]) {
                        flag = 0;
                        break;
                    }
                }

                if (flag == 1) {                    
                    for (j = 0; j < m; j++) {
                        avail[j] += alloc[i][j];  
                    }
                    safeSequence[count++] = i;
                    finish[i] = 1;
                    processCompleted = 1;
                }
            }
        }
        if (!processCompleted) {
            printf("The system is not in a safe state.\n");
            return 0;
        }
    }
    printf("The system is in a safe state.\nSafe sequence is: ");
    for (i = 0; i < n; i++) {
        printf("%d ", safeSequence[i]);
    }
    printf("\n");
    return 0;
}