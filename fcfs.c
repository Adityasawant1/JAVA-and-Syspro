#include<stdio.h>

struct Process
{
    int p, bt, at, st, ft, wt, tat;
};

int main()
{
    int n,i,j;

    printf("Enter the number of processes:\n");
    scanf("%d", &n);
    struct Process P[n];
    struct Process temp;  // Temporary variable for swapping

    // Arrival time and Burst time input
    for(i = 0; i < n; i++)
    {
        P[i].p = i+1;
        printf("Enter Burst Time for Process %d: ", P[i].p);
        scanf("%d", &P[i].bt);
        printf("Enter Arrival Time for Process %d: ", P[i].p);
        scanf("%d", &P[i].at);
    }

    // Sort processes by arrival time
    for(i = 0; i < n; i++)
    {
        for(j = i+1; j < n; j++)
        {
            if(P[i].at > P[j].at)
            {
                temp = P[i];
                P[i] = P[j];
                P[j] = temp;
            }
        }
    }


    // First process starts at its arrival time
    P[0].st = P[0].at;
    P[0].ft = P[0].st + P[0].bt;
    P[0].wt = P[0].st - P[0].at;
    P[0].tat = P[0].ft - P[0].at;

    // Calculate times for remaining processes
    for(i = 1; i < n; i++)
    {
        P[i].st = P[i-1].ft; // Start time is the finish time of the previous process
        if (P[i].st < P[i].at) {
            P[i].st = P[i].at;  // Process cannot start before its arrival time
        }
        P[i].ft = P[i].st + P[i].bt;
        P[i].wt = P[i].st - P[i].at;
        P[i].tat = P[i].ft - P[i].at;
    }

    // Gantt chart
    printf("Gantt chart:\n");
    printf("|   P%d", P[0].p);
    for(i = 1; i < n; i++)
    {
        printf("  |  P%d", P[i].p);
    }
    printf("  |\n");

    printf("%d   ", P[0].st);
    for(i = 0; i < n; i++)
    {
        printf("%d   ", P[i].ft);
    }
    printf("\n\n");

    // Sort by process number for final table
    for(i = 0; i < n; i++)
    {
        for(j = i+1; j < n; j++)
        {
            if(P[i].p > P[j].p)
            {
                temp = P[i];
                P[i] = P[j];
                P[j] = temp;
            }
        }
    }

    // Table
    printf("Table:\n");
    printf("Process\tAT\tBT\tST\tFT\tWT\tTAT\n");
    for(i = 0; i < n; i++)
    {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n", P[i].p, P[i].at, P[i].bt, P[i].st, P[i].ft, P[i].wt, P[i].tat);
    }

    return 0;
}
