#include <stdio.h>
#include <stdlib.h>

int main() {
    char filename[100];
    FILE *fp;
    int ch, lines = 0, words = 0, spaces = 0, characters = 0,tab=0;
    int in_word = 0;

    fp = fopen("abc.txt", "r");
    if (fp == NULL) {
        perror("Error opening file");
        return 1;
    }

    while ((ch = getc(fp)) != EOF) {
        characters++;

        if (ch == '\n') {
            lines++;
        }

        if (ch == ' ') {
            spaces++;
        }

        if(ch=='\t'){
            tab++;
        }

        if (ch == ' ' || ch == '\n' || ch == '\t' || ch == '\r' || ch == '\f' || ch == '\v') {
            in_word = 0;
        } else if (!in_word) {
            in_word = 1;
            words++;
        }
    }

    if (ch == '\n') {
        lines++;
    }

    fclose(fp);

    printf("Lines: %d\n", lines);
    printf("Tabs: %d\n", tab);
    printf("Words: %d\n", words);
    printf("Spaces: %d\n", spaces);
    printf("Characters: %d\n", characters);

    return 0;
}
