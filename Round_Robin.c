#include<stdio.h>
#include<string.h>

struct input {
	char pname[10];
	int bt, at, ct, tbt;
} tab[5];

struct Sequence {
	int start, end;
	char pname[10];
} seq[100], seq1[20];

int finish, time, n, k, prev, q;

void getinput() {
	int i;
	printf("\nEnter No. of Processes: ");
	scanf("%d", &n);
	printf("Enter Time Slice: ");
	scanf("%d", &q);
	for (i = 0; i < n; i++) {
		printf("Process Name: ");
		scanf("%s", tab[i].pname);
		printf("Burst Time: ");
		scanf("%d", &tab[i].bt);
		printf("Arrival Time: ");
		scanf("%d", &tab[i].at);
		tab[i].tbt = tab[i].bt; // Initialize total burst time
	}
}

void printoutput() {
	int i;
	float avgtat = 0, avgwt = 0;
	printf("\nProcess\tAT\tBT\tCT\tTAT\tWT");
	for (i = 0; i < n; i++) {
		int tat = tab[i].ct - tab[i].at;
		int wt = tat - tab[i].bt;
		printf("\n%s\t%d\t%d\t%d\t%d\t%d", tab[i].pname, tab[i].at, tab[i].bt, tab[i].ct, tat, wt);
		avgtat += tat;
		avgwt += wt;
	}
	avgtat /= n;
	avgwt /= n;
	printf("\nAverage TAT = %f", avgtat);
	printf("\nAverage WT = %f", avgwt);
}

int arrived(int t) {
	int i;
	for (i = 0; i < n; i++) {
		if (tab[i].at <= t && tab[i].tbt != 0)
			return 1;
	}
	return 0;
}

void processinput() {
    int i = 0, j, min_at_index = 0;
    
    // Find the first process with the minimum arrival time
    for (i = 0; i < n; i++) {
        if (tab[i].at < tab[min_at_index].at) {
            min_at_index = i;
        }
    }
    
    i = min_at_index;  // Start with the process having the minimum arrival time
    finish = k = 0;    // Initialize finish and k
    
    while (finish != n) {
        if (arrived(time)) {
            if (tab[i].tbt != 0) {
                // Process in time slice (q time units)
                for (j = 0; j < q && tab[i].tbt > 0; j++) {
                    time++;
                    tab[i].tbt--;
                    seq[k].start = prev;
                    seq[k].end = time;
                    strcpy(seq[k++].pname, tab[i].pname);
                    prev = time;
                    if (tab[i].tbt == 0) {
                        tab[i].ct = time;
                        finish++;  // Mark process as finished
                    }
                }
            }
        } else {  // CPU idle time handling
            time++;
            seq[k].start = prev;
            seq[k].end = time;
            strcpy(seq[k++].pname, "*");
            prev = time;
        }

        // Move to the next process in a circular manner, only if it's ready to run
        i = (i + 1) % n;  // Circular index
        
        // Skip processes that haven't arrived yet or are already finished
        while (tab[i].at > time || tab[i].tbt == 0) {
            i = (i + 1) % n;
        }
    }
}

void ganttchart() {
	int i, j = 1;
	seq1[0] = seq[0]; // Initialize the first entry in the simplified Gantt chart
	for (i = 1; i < k; i++) {
		if (strcmp(seq1[j - 1].pname, seq[i].pname) == 0) {
			seq1[j - 1].end = seq[i].end; // Merge if the same process continues
		} else {
			seq1[j++] = seq[i]; // New process, add a new sequence
		}
	}

	printf("\nGantt Chart:\n");
	for (i = 0; i < j; i++) {
		printf("%d\t%s\t%d\n", seq1[i].start, seq1[i].pname, seq1[i].end);
	}
}

int main() {
	getinput();
	processinput();
	printoutput();
	ganttchart();
	return 0;
}
