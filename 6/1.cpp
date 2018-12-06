#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

struct pt {
    int x, y, i;
    int area;
    bool unbounded;
};
int dist(int x1, int y1, int x2, int y2) {
    return abs(x2-x1)+abs(y2-y1);
}

std::vector<struct pt> pts;

int main(int argc, char **argv) {
    FILE *f = fopen(argv[1], "r");
    int x, y, i = 0;
    const int tx = 10, ty = 10;
    while(fscanf(f, "%d, %d\n", &x, &y) > 0) {
        struct pt pt;
        pt.i = i++;
        pt.x = x+tx;
        pt.y = y+ty;
        pt.area = 0;
        pt.unbounded = false;
        pts.push_back(pt);
    }
    
    const int width = 1000, height = 1000;
    int map[width][height];
    memset(map, 0, sizeof(map));
    
    do {
        std::vector<struct pt> sorted(pts);
        for(int x = 0; x < width; x++) {
            for(int y = 0; y < height; y++) {
                std::sort(sorted.begin(), sorted.end(), [x,y](struct pt pt1, struct pt pt2) {
                    float d1 = dist(pt1.x, pt1.y, x, y);
                    float d2 = dist(pt2.x, pt2.y, x, y);
                    return d1 < d2;
                });
                struct pt *pt = &sorted[0];
                if(pt->x == x && pt->y == y) {
                    map[x][y] = pt->i+1;
                    pts.at(pt->i).area++;
                } else if(dist(sorted[0].x,sorted[0].y,x,y) == dist(sorted[1].x,sorted[1].y,x,y)) {
                    map[x][y] = 0; // occupied by 2 or more
                } else {
                    map[x][y] = -(pt->i+1);
                    pts.at(pt->i).area++;
                }
            }
        }
    } while(0);
    
#define DEBOUND(pos) { \
    if(pos < 0) { \
        int idx = -(pos)-1; \
        pts.at(idx).unbounded = true; \
    } \
}
    // horizontal edge
    for(int x = 0; x < width; x++) {
        DEBOUND(map[x][0]); 
        DEBOUND(map[x][height-1]);
    }
    // vertical edge
    for(int y = 0; y < height; y++) {
        DEBOUND(map[0][y]); 
        DEBOUND(map[width-1][y]);
    }
   
    /*
    for(int y = 0; y < height; y++) {
        for(int x = 0; x < width; x++) {
            printf("%02d ", map[x][y]);
        }
        printf("\n");
    } */
   
    for(auto pt : pts) {
        printf("[%d] %d %d %d %d\n", pt.i, pt.x, pt.y, pt.area, pt.unbounded);
    }

    pts.erase(std::remove_if(pts.begin(), pts.end(), [](struct pt pt) {
        return pt.unbounded;
    }), pts.end());
    struct pt pt = *std::max_element(pts.begin(), pts.end(), [](struct pt pt1, struct pt pt2) {
        return pt1.area < pt2.area;
    });
    printf("%d\n", pt.area);
}
