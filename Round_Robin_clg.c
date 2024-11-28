#include<stdio.h>
#include<string.h>
struct input
{
	char pname[10];
	int bt,at,ct,tbt;
}tab[5];
struct Sequence
{
	int start,end;
	char pname[10];
}seq[100],seq1[20];
int finish,time,n,k,prev,q;
void getinput()
{
	int i;
	printf("\n Enter No. of Processes :");
	scanf("%d",&n);
	printf(" Enter Time Slice :");
	scanf("%d",&q);
	for(i=0;i<n;i++)
	{  
		printf("Process Name:");
		scanf("%s",tab[i].pname);
		printf("Burst Time:");
		scanf("%d",&tab[i].bt);
		printf("Arrival Time:");
		scanf("%d",&tab[i].at);
		tab[i].tbt = tab[i].bt;
	}
		
}
void printinput()
{
	int i;
	printf("\nProcess\tBT\tAT");
	for(i=0;i<n;i++)
		printf("\n%s\t%d\t%d",tab[i].pname,tab[i].bt,tab[i].at);
}
void sort()
{
	struct input t;
	int i,j;
	for(i=0;i<n;i++)
	{
		for(j=0;n-1-i;j++)
		{
			if(tab[j+1].at<tab[j].at)
			{
				t = tab[i];
				tab[i] = tab[j];
				tab[j] = t;				
			}
		}
	}
		
}
void printoutput()
{
	int i;
	float avgtat=0,avgwt=0;
	printf("\nProcess\tAT\tBT\tCT\tTAT\tWT");
	for(i=0;i<n;i++)
	{
		printf("\n%s\t%d\t%d\t%d\t%d\t%d",tab[i].pname,tab[i].at,tab[i].bt,tab[i].ct,tab[i].ct-tab[i].at,tab[i].ct-tab[i].at-tab[i].bt);
	avgtat += tab[i].ct-tab[i].at;
	avgwt += tab[i].ct-tab[i].at-tab[i].bt;
	}
	avgtat/=n;
	avgwt/=n;
	printf("\nAverage TAT = %f",avgtat);
	printf("\nAverage WT = %f",avgwt);
}
int arrived(int t)
{
	int i;
	for(i=0;i<n;i++)
		if(tab[i].at<=t && tab[i].tbt!=0)
			return 1;
	return 0;
}
void processinput()
{
	int i=0,j;
	finish = k = 0;
	while(finish!=n)
	{
		if(arrived(time))
		{
			if(tab[i].tbt!=0)
			{
				for(j=0;j<q;j++)
				{
					time++;
					tab[i].tbt--;
					//printinput();
					seq[k].start = prev;
					seq[k].end = time;
					strcpy(seq[k++].pname,tab[i].pname);
					prev = time;
					tab[i].ct = time;
					if(tab[i].tbt==0)
					{
						finish++;
						break;
					}
				}
			}
		}
		else
		{
			time++;
			seq[k].start = prev;
			seq[k].end = time;
			strcpy(seq[k++].pname,"*");
			prev = time;
		}
		if(time<tab[(i+1)%n].at)
		{
			i=0;
			while(tab[i].tbt!=0 && finish!=n)
				i++;
		}
		else
			i = (i+1)%n;
	}
}
void ganttchart()
{
	int i,j=1;
	seq1[0] = seq[0];
	for(i=1;i<k;i++)
	{
		if(strcmp(seq1[j-1].pname,seq[i].pname)==0)
			seq1[j-1].end = seq[i].end;
		else
			seq1[j++] = seq[i];
	}
	for(i=0;i<j;i++)
		printf("\n%d\t%s\t%d",seq1[i].start,seq1[i].pname,seq1[i].end);		
}
int main()
{
	int i;
	getinput();
	processinput();
	printoutput(); 
	ganttchart();	
	for(i=0;i<n;i++)
	{
		tab[i].tbt = tab[i].bt = rand()%10+1;
		tab[i].at=tab[i].ct+2;
		//tab[i].at=rand() % 10;
	}
	/*processinput();
	printoutput();
	ganttchart();*/
	
}