#include <stdio.h>

#define d 1000
int map[d][d] = {0}; // x,y

int main(int argc, char **argv) {
    FILE *f = fopen(argv[1], "r");
    // #1 @ 393,863: 11x29
    int id, x, y, w, h;
    while(fscanf(f, "#%d @ %d,%d: %dx%d\n", &id, &x, &y, &w, &h) > 0) {
        for(int x_ = x; x_ < (x+w); x_++) {
            for(int y_ = y; y_ < (y+h); y_++) {
                map[x_][y_]++;
            }
        }
    }
    int i = 0;
    for(int x_ = 0; x_ < d; x_++) {
        for(int y_ = 0; y_ < d; y_++) {
            if(map[x_][y_] >= 2) 
                i++;
        }
    }
    printf("%d\n", i);
}
