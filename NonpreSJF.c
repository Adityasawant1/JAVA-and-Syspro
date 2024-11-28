#include <stdio.h>

struct Process {
    int p, bt, at, st, ft, wt, tat;
};

int main() {
    int n, i, j, currentTime = 0, completed = 0, minIndex;
    float totalwt = 0, totaltat = 0;    
    printf("Enter the number of processes: ");
    scanf("%d", &n);    
    struct Process P[n];
    int isCompleted[n];

    for(i = 0; i < n; i++) {
        P[i].p = i + 1;
        printf("Enter Burst Time for Process %d: ", P[i].p);
        scanf("%d", &P[i].bt);
        printf("Enter Arrival Time for Process %d: ", P[i].p);
        scanf("%d", &P[i].at);
        isCompleted[i] = 0;
    }
    
    while(completed != n) {
        
        minIndex = -1;
        int minBurstTime = 99;
        
        for(i = 0; i < n; i++) {
            if(P[i].at <= currentTime && !isCompleted[i]) {
                if(P[i].bt < minBurstTime) {
                    minBurstTime = P[i].bt;
                    minIndex = i;
                }
                if(P[i].bt == minBurstTime) {
                    if(P[i].at < P[minIndex].at) {
                        minIndex = i;
                    }
                }
            }
        }
        
        if(minIndex != -1) {
            P[minIndex].st = currentTime;
            P[minIndex].ft = P[minIndex].st + P[minIndex].bt;
            currentTime = P[minIndex].ft;
            
            P[minIndex].tat = P[minIndex].ft - P[minIndex].at;
            P[minIndex].wt = P[minIndex].st - P[minIndex].at;
            
            totaltat += P[minIndex].tat;
            totalwt += P[minIndex].wt;
            
            isCompleted[minIndex] = 1;
            completed++;
        } else {
            currentTime++;
        }
    }
     printf("\n************* Gantt Chart ***************\n");
    printf(" ");
    for(i = 0; i < n; i++) {
        printf("  P%d   ", P[i].p);
    }
    printf("\n");

    printf(" ");
    for(i = 0; i < n; i++) {
        printf("|------");
    }
    printf("|\n");

    printf("%d", P[0].st);
    for(i = 0; i < n; i++) {
        printf("     %d", P[i].ft);
    }
    printf("\n");
    
    // Display the table
    printf("\nProcess\t\tBT\t\tAT\t\tST\t\tFT\t\tWT\t\tTAT\n");
    for(i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", 
               P[i].p, 
               P[i].bt, 
               P[i].at, 
               P[i].st, 
               P[i].ft, 
               P[i].wt, 
               P[i].tat);
    }    
    float avgtat = totaltat / n;
    float avgwt = totalwt / n;
    
    printf("\nAverage Waiting Time: %.2f", avgwt);
    printf("\nAverage Turnaround Time: %.2f\n", avgtat);    
    return 0;
}
