#include <stdio.h>
#include <string.h>

#define wlen 26

char A[256][wlen+1];
int idx = 0;

void push(char *w) {
    strncpy(A[idx++], w, wlen+1);
}

int close_to_same(char *a, char *b) {
    int diff = 0;
    for(int i = 0; i < wlen; i++) {
        if(a[i] != b[i]) {
            diff++;
        }
    }
    if(diff > 1) return 0;
    return 1;
}

int main(int argc, char **argv) {
    FILE *f = fopen(argv[1], "r");
    char *line = NULL;
    size_t n = 0;
    ssize_t nread;
    while((nread = getline(&line, &n, f)) > 0) {
        line[wlen] = 0;
        push(line);
    }
    
    char *a1, *a2;
    for(int i = 0; i < idx; i++ ){
        for(int j = 0; j < idx; j++) {
            if(i == j) continue;
            if(close_to_same(A[i], A[j])) {
                a1 = A[i];
                a2 = A[j];
                goto found;
            }
        }
    }
    return 1;

found:
    printf("%s %s\n", a1, a2);
    char newstr[wlen+1];
    int ptr = 0;
    for(int i = 0; i < wlen; i++) {
        if(a1[i] == a2[i]) {
            newstr[ptr++] = a1[i];
        }
    }
    newstr[ptr] = 0;
    printf("%s\n", newstr);
}
