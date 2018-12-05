#include <stdio.h>
#include <stdlib.h>

long array[1024];
int idx = 0;
void array_push(long n) {
    if(idx > sizeof(array)) {
        printf("overflow!\n");
        exit(1);
    }
    array[idx] = n;
    idx++;
}

int main(int argc, char **argv) {
    FILE *f = fopen(argv[1], "r");
    long i = 0, cur_freq = 0;
    array_push(0);
    while(fscanf(f, "%li\n", &i) > 0) {
        cur_freq += i;
        array_push(cur_freq);
        printf("%li\n", cur_freq);
    }
    printf("%li\n", cur_freq);
    while(1) {
        rewind(f);
        while(fscanf(f, "%li\n", &i) > 0) {
            cur_freq += i;
            printf("CR %li\n", cur_freq);
            for(int j = 0; j < idx; j++) {
                if(array[j] == cur_freq) {
                    printf("FOUND: %li\n", cur_freq);
                    return 0;
                }
            }
        }
    }
    fclose(f);
}
