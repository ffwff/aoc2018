#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

char *buf;

int combine(char *str) {
    int ncombines = 0;
    int len = strlen(str);
    int pos = 0;
    for(int i = 0; i < len; i++) {
        char a = str[i], b = str[i+1];
        if( (isupper(a) && islower(b) && (a-'A' == b-'a')) ||
            (islower(a) && isupper(b) && (a-'a' == b-'A')) ) {
            i++;
            ncombines++;
            continue;
        }
        buf[pos++] = a;
    }
    buf[pos] = 0;
    return ncombines;
}

void full_reaction(char *line) {
    buf = malloc(strlen(line));
    int ncombines = combine(line);
    while(ncombines) {
        char *new = strdup(buf);
        ncombines = combine(new);
        free(new);
    }
}

char *filtered_unit(char *line, char ch) {
    char *filtered = malloc(strlen(line));
    int size = strlen(line);
    int pos = 0;
    for(int i = 0; i < size; i++) {
        if(tolower(line[i]) == ch)
            continue;
        filtered[pos++] = line[i];
    }
    filtered[pos] = 0;
    return filtered;
}

int main(int argc, char **argv) {
    FILE *f = fopen(argv[1], "r");
    char line[50000];
    fscanf(f, "%50000[^\n]", line);
    
    for(char c = 'a'; c <= 'z'; c++) {
        char *filtered = filtered_unit(line, c);
        full_reaction(filtered);
        printf("%c: %d\n", c, strlen(buf));
        free(filtered);
        free(buf);
    }
    
    //full_reaction(line);
    //printf("%s\n", buf);
}
