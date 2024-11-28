#include <stdio.h>
#include <string.h>

int main() {
    char t1[100], t2[100], t3[100];
    char mem[100];
    int code;
    FILE *fp;
    fp = fopen("chk_mnemonic.txt", "r");
    if (fp == NULL) {
        printf("File not found\n");
        return 1;
    }

    while (!feof(fp)) {
        code = -1;
        fgets(mem,100,fp);
        sscanf(mem, "%s %s %s", t1, t2, t3);

        if ((strcmp(t1, "READ") == 0)||(strcmp(t1, "PRINT") == 0)||(strcmp(t1,"START")==0)) 
        {
            code = 1;
        }
        else if ((strcmp(t1, "ADD") == 0) || (strcmp(t1, "MOVER") == 0) || 
            (strcmp(t1, "MOVEM") == 0) || (strcmp(t1, "SUB") == 0) || 
            (strcmp(t1, "MULT") == 0) || (strcmp(t1, "DIV") == 0) || 
            (strcmp(t1, "COMP") == 0)) 
        {
            code = 2;
        } 
        else if(strcmp(t1, "BC") == 0) 
        {
            code = 3;
        } 
        else if (strcmp(t1, "STOP") == 0) 
        {
            code = 6;
        }
        else
        {
            code = 7;
        }
        if((strcmp(t2,"DS")==0)||(strcmp(t2,"DC")==0))
        {
            code = 4;
        }
        switch (code) {
            case 1:
                if(t2>0||strcmp(t3," ")==0)
                {

                }
                else
                    printf("%s\t Invalid statement\n",t1);
                break;
            case 2:
                if (((strcmp(t2, "AREG") == 0) || (strcmp(t2, "BREG") == 0) || 
                     (strcmp(t2, "CREG") == 0) || (strcmp(t2, "DREG") == 0)) && 
                     (strlen(t3) > 0))
                {
                    
                } 
                else {
                    printf("%s\t Invalid statement\n",t2);
                }
                break;
            case 3:
                if (((strcmp(t2, "LT") == 0) || (strcmp(t2, "LE") == 0) || 
                     (strcmp(t2, "EQ") == 0) || (strcmp(t2, "GT") == 0) || 
                     (strcmp(t2, "GE") == 0) || (strcmp(t2, "ANY") == 0)) && 
                     (strlen(t3) > 0)) 
                {

                } 
                else {
                   printf("%s\t Invalid statement\n",t2);
                }
                break;
            case 4:
                if(t3>0)
                {

                }
                else
                    printf("%s\t Invalid statement\n",t1);
                break;     
            case 7:
                printf("%s\t Invalid Mnemonics\n",t1);
                break;
            case 8:
                printf("%s\t Invalid Mnemonics\n",t2);
                break;
        }
    }
    fclose(fp);
    return 0;
}
