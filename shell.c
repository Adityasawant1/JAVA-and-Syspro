#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
char *buff,*t1,*t2,*t3,ch;
FILE *fp;
int pid;
void count(char *t2,char *t3)
{
	int charcnt=0,wordcnt=0,linecnt=0;
	if((fp=fopen(t3,"r"))==NULL)
		printf("file not found");
	else
	{
		while((ch=fgetc(fp))!=EOF)
		{
			if(ch==' ')
				wordcnt++;
			else if(ch=='\n')
			{
				linecnt++;
			}
			else
				charcnt++;
		}

		fclose(fp);

		if(strcmp(t2,"c")==0)
			printf("the total no. of character : %d\n",charcnt);
		else if(strcmp(t2,"w")==0)
			printf("the total no. of word : %d\n",wordcnt);
		else if(strcmp(t2,"l")==0)
			printf("the total no. of lines : %d\n",linecnt);
		else
			printf("command not found\n");
	}
}

main()
{
	while(1)
	{
		printf("myshell$");
		fflush(stdin);
		t1=(char *)malloc(80);
		t2=(char *)malloc(80);
		t3=(char *)malloc(80);

		buff=(char *)malloc(80);
		fgets(buff,80,stdin);
		sscanf(buff,"%s %s %s",t1,t2,t3);
	
		if(strcmp(t1,"pause")==0)
			exit(0);
		else if(strcmp(t1,"count")==0)
			count(t2,t3);
		else
		{
			pid=fork();
			if(pid<0)
			{
				printf("child process is not created\n");
			}
			else if(pid==0)
			{
				execlp("/bin",NULL);
				if((strcmp(t1,"exit")==0))
				exit(0);
				system(buff);
			}
			else
			{
				wait(NULL);
				exit(0);
			}

		}
	}
}