#include <stdio.h>
int main() {
    FILE *fp;
    int mem[1000] = {0}, opcode, reg, opnd, pc = 0;
    int reg1[100] = {0};
    fp = fopen("sub.txt", "r");

    if (fp == NULL) {
        printf("File not found\n");
        return 1;
    } 

    while (fscanf(fp, "%d", &mem[pc]) != EOF) {
        pc++;
    }
    pc = 0;

    while (1) {
        opcode = mem[pc] / 10000;
        reg = (mem[pc] /1000)% 10;
        opnd = mem[pc] % 1000;

        switch (opcode) {
            case 0:
                printf("Termination ");
                return 0;
            case 2:
                reg1[reg] -= mem[opnd];
                break;

            case 9:
                printf("\nEnter the number to be Substract:\n");
                scanf("%d", &mem[opnd]);
                break;

            case 4:
                reg1[reg] = mem[opnd];
                break;

            case 5:
                mem[opnd] = reg1[reg];
                break;

            case 10:
                printf("\nThe result is: %d\n", mem[opnd]);
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