#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define M 20
struct ST
{
	char Symb[10];
	int Addr,def,Used,Val,Len;
}S[M];

char OPTAB[][10]={"STOP","ADD","SUB","MULT","MOVER","MOVEM","COMP","BC","DIV","READ","PRINT"};

char ADTAB[][10]={"START","END","ORIGIN","EQU","LTORG"};

int SymbCnt,TokCnt,PC,i,j,k,m;

char Tok1[M],Tok2[M],Tok3[M],Tok4[M],Buffer[80];

FILE *fp;

int SearchSymb(char *s)
{
	for(m=0;m<SymbCnt;m++)
	if(strcmp(S[m].Symb,s)==0)
	return(m);
	return(-1);
}
int SearchOp(char *s)
{
	for(m=0;m<11;m++)
	if(strcmp(OPTAB[m],s)==0)
	return(m);
	return(-1);
}
int SearchDirective(char *s)
{
	for(m=0;m<5;m++)
	if(strcmp(ADTAB[m],s)==0)
	return(m);
	return(-1);
}
void DispSymbTab()
{
	printf("\nSymbol\tAddress\tDeclared\tUsed\tValue\tLength\n");
	for(m=0;m<SymbCnt;m++)
	{
		printf("%s\t%d\t\t%d\t%d\t%d\t%d\n",S[m].Symb,S[m].Addr,S[m].def,S[m].Used,S[m].Val,S[m].Len);
	}
	for(m=0;m<SymbCnt;m++)
	if(S[m].Used==1 && S[m].def == 0)
	printf("\n Symbol %s used but not defined",S[m].Symb);
	else if(S[m].Used==0 && S[m].def==1)
	printf("\n Symbol %s defined but not used",S[m].Symb);
}
void PassOne()
{
	fp=fopen("chk_mnemonic.txt","r");
	if(fp==NULL)
	{
		printf("\n Error in opening file ");
		return;
	}
	while(fgets(Buffer,80,fp))
	{
		TokCnt=sscanf(Buffer,"%s%s%s%s",Tok1,Tok2,Tok3,Tok4);
		switch(TokCnt)
		{
			case 2:
			i=SearchOp(Tok1);
			if(i==9 || i==10)
			{
			j=SearchSymb(Tok2);
			if(j==-1)
			{
			strcpy(S[SymbCnt].Symb,Tok2);
			S[SymbCnt++].Used=1;
			}
			else
			S[j].Used=1;
			break;
			}
			i=SearchDirective(Tok1);
			if(i==0 ||i==2)
			{
			PC=atoi(Tok2)-1;
			}
			else
			{
			i=SearchOp(Tok2);
			if(i==0)
			{
			j=SearchSymb(Tok1);
			if(j==-1)
			{
			strcpy(S[SymbCnt].Symb,Tok1);
			S[SymbCnt].Addr=PC;
			S[SymbCnt].def=1;
			S[SymbCnt].Val=0;
			S[SymbCnt++].Len=0;
			}
			else
			{
			if(S[j].def==1)
			printf("\n Redeclartion of symbol %s",Tok1);
			else
			{
			S[j].Addr=PC;
			S[j].def=1;
			S[j].Val=S[j].Len=0;
			}
			}
			}
			}

			break;
			case 3:
			i=SearchOp(Tok1);
			if(i>=1 && i<=8)
			{
			Tok2[strlen(Tok2)-1]='\0';
			j=SearchSymb(Tok3);
			if(j==-1)
			{
			strcpy(S[SymbCnt].Symb,Tok3);
			S[SymbCnt++].Used=1;
			}
			else
			S[j].Used=1;
			}
			else if(strcmp(Tok2,"DC")==0)
			{
			j=SearchSymb(Tok1);

			if(j==-1)
			{
			strcpy(S[SymbCnt].Symb,Tok1);
			S[SymbCnt].Addr=PC;
			S[SymbCnt].def=1;
			S[SymbCnt].Val=atoi(Tok3);
			S[SymbCnt++].Len=1;
			}
			else
			{
			if(S[j].def==1)
			printf("\n Redeclartion of symbol %s",Tok1);
			else
			{
			S[j].Addr=PC;
			S[j].def=1;
			S[j].Val=atoi(Tok3);
			S[j].Len=1;
			}
			}
			}
			else if(strcmp(Tok2,"DS")==0)
			{
			j=SearchSymb(Tok1);

			if(j==-1)
			{
			strcpy(S[SymbCnt].Symb,Tok1);
			S[SymbCnt].Addr=PC;
			S[SymbCnt].def=1;
			S[SymbCnt].Val=0;
			S[SymbCnt++].Len=atoi(Tok3);
			}
			else
			{
			if(S[j].def==1)
			printf("\n Redeclartion of symbol %s",Tok1);
			else
			{
			S[j].Addr=PC;
			S[j].def=1;
			S[j].Val=0;
			S[j].Len=atoi(Tok3);
			}
			}
			PC+=atoi(Tok3)-1;
			}
			else
			{
			j=SearchSymb(Tok1);
			if(j==-1)
			{
			strcpy(S[SymbCnt].Symb,Tok1);
			S[SymbCnt].Addr=PC;
			S[SymbCnt].def=1;
			S[SymbCnt].Val=0;
			S[SymbCnt++].Len=0;
			}
			else
			{
			if(S[j].def==1)
			printf("\n Redeclartion of symbol %s",Tok1);
			else
			{
			S[j].Addr=PC;
			S[j].def=1;
			S[j].Val=S[j].Len=0;
			}
			}
			i=SearchOp(Tok2);
			if(i==9 || i==10)
			{
			j=SearchSymb(Tok3);
			if(j==-1)
			{
			strcpy(S[SymbCnt].Symb,Tok3);
			S[SymbCnt++].Used=1;
			}
			else
			S[j].Used=1;
			}
			}

			break;
			case 4:
			j=SearchSymb(Tok1);
			if(j==-1)
			{
			strcpy(S[SymbCnt].Symb,Tok1);
			S[SymbCnt].Addr=PC;
			S[SymbCnt].def=1;
			S[SymbCnt].Val=0;
			S[SymbCnt++].Len=0;
			}
			else
			{
			if(S[j].def==1)
			printf("\n Redeclartion of symbol %s",Tok1);
			else
			{
			S[j].Addr=PC;
			S[j].def=1;
			S[j].Val=0;
			S[j].Len=0;
			}
			}
			i=SearchOp(Tok2);
			if(i>=1 && i<=8)
			{
			Tok3[strlen(Tok3)-1]='\0';
			j=SearchSymb(Tok4);
			if(j==-1)
			{
			strcpy(S[SymbCnt].Symb,Tok4);
			S[SymbCnt++].Used=1;
			}
			else
			S[j].Used=1;
			}
		}
		PC++;
	}
	fclose(fp);

}

int main()
{
	PassOne();
	DispSymbTab();
	return 0;
}