#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    FILE *f = fopen(argv[1], "r");
    int i = 0;
    int final = 0;
    while(sscanf("%d\n", &i)) {
        final += i;
    }
    printf("%d\n", final);
}
