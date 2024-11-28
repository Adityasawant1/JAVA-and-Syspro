#include <stdio.h>
#include <string.h>
int main() {
    char t1[10], t2[10], t3[10];
    char line[50];
    int code;
    FILE *fp;
    fp = fopen("chk_mnemonic.txt", "r");
    if (fp == NULL) {
        printf("File not found\n");
        return 1;
    }
    while (fgets(line, sizeof(line), fp) != NULL) {
        code = -1;
        int numItems = sscanf(line, "%s %s %s", t1, t2, t3);
        if (numItems == 3) {
            printf("%s %s %s\n", t1, t2, t3);
            if ((strcmp(t1, "ADD") == 0) || (strcmp(t1, "MOVER") == 0) || 
                (strcmp(t1, "MOVEM") == 0) || (strcmp(t1, "SUB") == 0) || 
                (strcmp(t1, "MULT") == 0) || (strcmp(t1, "DIV") == 0) || 
                (strcmp(t1, "COMP") == 0)) {
                code = 0;
            } else if (strcmp(t1, "BC") == 0) {
                code = 3;
            }
            printf("Code: %d\n", code);
        } 
        else if (numItems == 2) {
            printf("%s %s\n", t1, t2);
            if ((strcmp(t1, "READ") == 0) || (strcmp(t1, "PRINT") == 0)) {
                code = 1;
            }
            printf("Code: %d\n", code);
        } 
        else if (numItems == 1) {
            printf("%s\n", t1);
            if (strcmp(t1, "STOP") == 0) {
                code = 2;
            }
            printf("Code: %d\n", code);
        } 
        else {
            printf("Invalid Mnemonics: %s", line);
        }
        switch (code) {
            case 0:
                if (((strcmp(t2, "AREG") == 0) || (strcmp(t2, "BREG") == 0) || 
                     (strcmp(t2, "CREG") == 0) || (strcmp(t2, "DREG") == 0)) && 
                     (t3 > 0)) {
                    printf("Valid mnemonic\n");
                } else {
                    printf("Invalid mnemonic Statement\n");
                }
                break;
            case 1:
                if (t2 > 0) {
                    printf("Valid mnemonic\n");
                } else {
                    printf("Invalid mnemonic Statement\n");
                }
                break;
            case 2:
                printf("Valid mnemonic\n");
                break;
            case 3:
                if (((strcmp(t2, "LT") == 0) || (strcmp(t2, "LE") == 0) || 
                     (strcmp(t2, "EQ") == 0) || (strcmp(t2, "GT") == 0) || 
                     (strcmp(t2, "GE") == 0) || (strcmp(t2, "ANY") == 0)) && 
                     (t3 > 0)) {
                    printf("Valid mnemonic\n");
                } else {
                    printf("Invalid mnemonic Statement\n");
                }
                break;
            default:
                printf("Invalid mnemonic\n");
                break;
        }
    }
    fclose(fp);
    return 0;
}