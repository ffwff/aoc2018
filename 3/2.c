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
    
    rewind(f);
    while(fscanf(f, "#%d @ %d,%d: %dx%d\n", &id, &x, &y, &w, &h) > 0) {
        for(int x_ = x; x_ < (x+w); x_++) {
            for(int y_ = y; y_ < (y+h); y_++) {
                if(map[x_][y_] > 1) goto skip;
            }
        }
        printf("%d\n", id);
    skip:
        continue;
    }
}
