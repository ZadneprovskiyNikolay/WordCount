#include <stdio.h>
#include <errno.h>
#include <string.h>

// Count the number of lines, words and bytes for a given text file.
int main(int argc, char **argv) {
    if (argc < 2) {
        printf("You didn't specify file name.");
    }         

    char *file_name, *option = "";
    if (argc == 2)
        file_name = argv[1];
    else
        option = argv[1];
        file_name = argv[2];

    FILE *fp = fopen(file_name, "r");
    if (fp == NULL) {         
        printf("Could not open the file %s: %s", file_name, strerror(errno));
        return 0;
    }

    size_t words_num = 0, lines_num = 0, bytes_num = 0;

    // Count bytes
    fseek(fp, 0L, SEEK_END);
    bytes_num = ftell(fp);

    // Count words
    fseek(fp, 0L, SEEK_SET);    
    char word[1023];    
    while (fscanf(fp, "%1023s", word) == 1) { 
        words_num++;
    }

    // Count lines
    fseek(fp, 0L, SEEK_SET);    
    if (bytes_num != 0) { 
        lines_num = 1;
        for (char c = getc(fp); c != EOF; c = getc(fp))
            if (c == '\n')
                lines_num++;
    }
    
    if (strcmp(option, "") == 0)
        printf("lines: %i, words: %i, bytes: %i", lines_num, words_num, bytes_num);
    else if (strcmp(option, "--lines") == 0 || strcmp(option, "-l") == 0)
        printf("lines: %i", lines_num);
    else if (strcmp(option, "--words") == 0 || strcmp(option, "-w") == 0) 
        printf("words: %i", words_num);
    else if (strcmp(option, "--bytes") == 0 || strcmp(option, "-b") == 0)
        printf("bytes: %i", bytes_num);
    else
        printf("Incorrect option specified: '%s'.", option); 

    return 0;
}