#include <stdio.h>

int main() {
    FILE *fp;
    int mem[1000] = {0}, opcode, reg, opnd, pc = 0;
    float reg1[4] = {0.0}; 
    fp = fopen("div.txt", "r");

    if (fp == NULL) {
        printf("File not found\n");
        return 1;
    }

    while (fscanf(fp, "%d", &mem[pc]) != EOF) {
        pc++;
    }
    fclose(fp); 

    pc = 0;

    while (1) {
        opcode = mem[pc] / 10000;
        reg = (mem[pc] % 10000) / 1000;
        opnd = mem[pc] % 1000;

       
        printf("PC: %d, Instruction: %d, Opcode: %d, Reg: %d, Operand: %d\n", pc, mem[pc], opcode, reg, opnd);

        switch (opcode) {
            case 0:
                printf("Termination\n");
                return 0;
            case 8:
                if (mem[opnd] == 0) { 
                    printf("Error: Division by zero\n");
                } else {
                    printf("Before division: reg1[%d] = %.2f, mem[%d] = %d\n", reg, reg1[reg], opnd, mem[opnd]);
                    reg1[reg] = reg1[reg] / (float)mem[opnd];
                    printf("After division: reg1[%d] = %.2f\n", reg, reg1[reg]);
                }
                break;
            case 9:
                printf("\nEnter the number:\n");
                scanf("%d", &mem[opnd]);
                break;
            case 4:
                printf("Loading mem[%d] = %d into reg1[%d]\n", opnd, mem[opnd], reg);
                reg1[reg] = (float)mem[opnd];
                break;
            case 5:
                printf("Storing reg1[%d] = %.2f into mem[%d]\n", reg, reg1[reg], opnd);
                mem[opnd] = reg1[reg]; 
                break;
            case 10:
                printf("\nThe result is: %.2f\n", reg1[reg]);
                break;
            default:
                printf("Invalid opcode: %d\n", opcode);
                break;
        }
        pc++;
    }

    return 0;
}
