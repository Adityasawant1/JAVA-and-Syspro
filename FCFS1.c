#include<stdio.h>

struct pro{
    int p, BT, AT, ST, FT, WT, TAT;
} pro[100];

int main() {
    int i, j, n;
    struct pro temp;

    printf("Enter the number of processes:\n");
    scanf("%d", &n);

    // Arrival time input
    printf("\nEnter the arrival time:\n");
    for(i = 1; i <= n; i++) {
        pro[i].p = i;
        printf("p%d AT: ", i);
        scanf("%d", &pro[i].AT);
    }

    // Burst time input
    printf("\nEnter the burst time:\n");
    for(i = 1; i <= n; i++) {
        printf("p%d BT: ", i);
        scanf("%d", &pro[i].BT);
    }

    // Sort processes by arrival time
    for(i = 1; i <= n; i++) {
        for(j = i + 1; j <= n; j++) {
            if(pro[i].AT > pro[j].AT) {
                temp = pro[i];
                pro[i] = pro[j];
                pro[j] = temp;
            }
        }
    }

    // Start time calculation
    pro[1].ST = pro[1].AT;
    for(i = 2; i <= n; i++) {
        if(pro[i].AT > pro[i-1].FT) {
            pro[i].ST = pro[i].AT;
        } else {
            pro[i].ST = pro[i-1].FT;
        }
    }

    // Finish time calculation
    for(i = 1; i <= n; i++) {
        pro[i].FT = pro[i].ST + pro[i].BT;
    }

    // Wait time calculation
    for(i = 1; i <= n; i++) {
        pro[i].WT = pro[i].ST - pro[i].AT;
    }

    // Turnaround time calculation
    for(i = 1; i <= n; i++) {
        pro[i].TAT = pro[i].FT - pro[i].AT;
    }

    // Gantt Chart
    printf("\n\n************* Gantt Chart ***************\n");
    for(i = 1; i <= n; i++) {
        printf("| p%d ", pro[i].p);
    }
    printf("|\n");

    printf("%d", pro[1].ST);
    for(i = 1; i <= n; i++) {
        printf(" %d", pro[i].FT);
    }
    printf("\n");

    // Sort by process ID for final output
    for(i = 1; i <= n; i++) {
        for(j = i + 1; j <= n; j++) {
            if(pro[i].p > pro[j].p) {
                temp = pro[i];
                pro[i] = pro[j];
                pro[j] = temp;
            }
        }
    }

    // Display final results
    printf("\n\n********* FCFS ***********\n");
    printf("______________________________________________________\n");
    printf("\nPro\tAT\tBT\tST\tFT\tWT\tTAT\n");
    for(i = 1; i <= n; i++) {
        printf("p%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
            pro[i].p, pro[i].AT, pro[i].BT, pro[i].ST, pro[i].FT, pro[i].WT, pro[i].TAT);
    }
    printf("______________________________________________________\n\n");

    return 0;
}