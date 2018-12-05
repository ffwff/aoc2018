#include <stdio.h>

#define wlen 26
#define nalpha 'z'-'a'

int main(int argc, char **argv) {
    FILE *f = fopen(argv[1], "r");
    char *line = NULL;
    size_t n = 0;
    ssize_t nread;
    int twos = 0, threes = 0;
    while((nread = getline(&line, &n, f)) > 0) {
        line[wlen] = 0;
        
        int L[nalpha] = { 0 };
        for(int i = 0; i < wlen; i++) {
            char c = line[i];
            L[c-'a']++;
        }
        
        // no letters that appear exactly 2 or 3
        int has_2 = 0, has_3 = 0;
        for(int i = 0; i < nalpha; i++)
            if(L[i] == 2) has_2++;
            else if(L[i] == 3) has_3++;
        if(!has_2 && !has_3) continue;
        if(has_2) twos++;
        if(has_3) threes++;
        
        printf("[%s]\n", line);
    }
    
    printf("checksum = %d\n", twos*threes);
}
