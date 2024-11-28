#include <stdio.h>
#include <ctype.h>

int main() {
    FILE *file;
    char  ch;
    int vowel_count = 0;
    
    file = fopen("abc.txt", "r");

    // Check if the file was opened successfully
    if (file == NULL) {
        printf("Could not open file\n");
        return 1;
    }

    
    while ((ch = fgetc(file)) != EOF) {
        ch = tolower(ch); 
        if (ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u') {
            vowel_count++;
        }
    }

    
    fclose(file);

    printf("The file contains %d vowels.\n",vowel_count);

    return 0;
}
