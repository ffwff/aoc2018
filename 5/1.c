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

int main(int argc, char **argv) {
    FILE *f = fopen(argv[1], "r");
    char line[50000];
    while(fscanf(f, "%50000[^\n]", &line)>0) {
        //printf(">%s\n", line);
        
        buf = malloc(strlen(line));
        int ncombines = combine(line);
        while(ncombines) {
            char *new = strdup(buf);
            ncombines = combine(new);
            free(new);
        }
        
        printf("%s\n", buf);
    }
}
