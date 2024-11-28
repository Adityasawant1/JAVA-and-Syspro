#include <stdio.h>

int main() {
    FILE *fp;
    int mem[1000], opcode, reg, opnd, pc = 0, flag;
    int reg1[4];
    fp = fopen("factorial.txt", "r");

    if (fp == NULL) {
        printf("File not found\n");
        return 1;
    } 

    while (fscanf(fp, "%d", &mem[pc]) != EOF) {
        pc++;
    }
    pc = 0;
    mem[103] = 1;
    while (1) {
        opcode = mem[pc] / 10000;
        reg = (mem[pc] % 10000) / 1000;
        opnd = mem[pc] % 1000;
        switch (opcode) {
            case 0:
                printf("Termination\n");
                return 0;
            case 1:
                reg1[reg] += mem[opnd];
                break;
                
            case 3: 
                reg1[reg] *= mem[opnd];
                break;

            case 4: 
                reg1[reg] = mem[opnd];
                break;

            case 5: 
                mem[opnd] = reg1[reg];
                break;

            case 6:
                flag = (reg1[reg] <= mem[opnd]) ? 0 : 1;
                break;

            case 7: 
                if (flag == 0) {
                    pc = 2;
                }                
                break;

            case 9: 
                printf("\nEnter the number: \n");
                scanf("%d", &mem[opnd]);
                break;

            case 10:                
                printf("\nThe result is: %d\n",mem[opnd]);
                return 0;
            default:
                printf("Invalid opcode: %d\n", opcode);
                break;
        }
        pc++;
    }
    fclose(fp);
    return 0;
}
