#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// guard
struct guard {
    int id;
    int minsleep[60];
    struct guard *next;
};

struct guard *gstart = NULL, *gend = NULL;

struct guard *guard_create(int id) {
    struct guard *guard = malloc(sizeof(struct guard));
    guard->id = id;
    memset(guard->minsleep, 0, sizeof(guard->minsleep));
    guard->next = NULL;
    
    if(gstart == NULL) {
        gstart = guard;
        gend = guard;
    } else {
        gend->next = guard;
        gend = guard;
    }
    
    return guard;
}

struct guard *get_guard(int id, int create) {
    if(gstart == NULL)
        return guard_create(id);
    for(struct guard *guard = gstart; guard != NULL; guard = guard->next)
        if(guard->id == id)
            return guard;
    if(create)
        return guard_create(id);
    return NULL;
}

int guard_sum_sleep(struct guard *g) {
    int sum = 0;
    for(int i = 0; i < 59; i++) {
        sum += g->minsleep[i];
    }
    return sum;
}

void guard_print(struct guard *g) {
    printf("%04d [", g->id);
    for(int i = 0; i < 59; i++) {
        printf("%d ", g->minsleep[i]);
    }
    printf("] %d\n", guard_sum_sleep(g));
    //printf("%04d [%02d-%02d %02d:%02d] %s\n", ts->id, ts->month, ts->day, ts->hour, ts->minute, ts->desc);
}

// ts array
struct timeslot *ts_array[2048];
int pos = 0;
void push(struct timeslot *ts) {
    ts_array[pos++] = ts;
}

// timeslot thingies
struct timeslot {
    int id;
    char *desc;
    int month, day, hour, minute;
    struct timeslot *prev, *next;
};

struct timeslot *timeslot_create(char *line) {
    struct timeslot *ts = malloc(sizeof(struct timeslot));
    // [1518-06-15 00:15] falls asleep
    char s[512];
    sscanf(line, "[1518-%02d-%02d %02d:%02d] %512[^\n]", &(ts->month), &(ts->day), &(ts->hour), &(ts->minute), s);
    ts->desc = malloc(strlen(s)+1);
    strcpy(ts->desc, s);
    push(ts);
    return ts;
}

void timeslot_print(struct timeslot *ts) {
    printf("%04d [%02d-%02d %02d:%02d] %s\n", ts->id, ts->month, ts->day, ts->hour, ts->minute, ts->desc);
}

int timeslot_cmp(const void *a, const void *b) {
    struct timeslot *ta = *(struct timeslot **)a, *tb = *(struct timeslot **)b;
#define cmp(a,b) if((a) > (b)) return 1; else if((a) < (b)) return -1;
    cmp(ta->month, tb->month);
    cmp(ta->day, tb->day);
    cmp(ta->hour, tb->hour);
    cmp(ta->minute, tb->minute);
    return 0;
}

void update() {
    int cguard = 0, last_sleep = 0;
    for(int i = 0; i < pos; i++) {
        ts_array[i]->id = i;
        if(strcmp(ts_array[i]->desc, "falls asleep") == 0) {
            struct guard *guard = get_guard(cguard, 0);
            guard->minsleep[ts_array[i]->minute]++;
            last_sleep = ts_array[i]->minute+1;
        } else if(strcmp(ts_array[i]->desc, "wakes up") == 0) {
            //printf("%d %d\n",last_sleep,ts_array[i]->minute);
            struct guard *guard = get_guard(cguard, 0);
            for(int j = last_sleep; j < ts_array[i]->minute; j++) {
                guard->minsleep[j]++;
            }
        } else {
            //continue;
            int id = 0;
            if(sscanf(ts_array[i]->desc, "Guard #%d begins shift", &id) > 0) {
                get_guard(id, 1);
                cguard = id;
            }
        }
    }
}

// main
int main(int argc, char **argv) {
    FILE *f = fopen(argv[1], "r");
    char *line = NULL;
    size_t n = 0;
    ssize_t nread = 0;
    while((nread = getline(&line, &n, f))>0) {
        //printf("%s\n", line);
        timeslot_create(line);
    }
    qsort(ts_array, pos, sizeof(struct timeslot*), timeslot_cmp);
    update();
    
    struct guard *gmostslept = gstart;
    for(struct guard *g = gstart; g!=NULL;g=g->next) {
        if(guard_sum_sleep(g) > guard_sum_sleep(gmostslept)) {
            gmostslept = g;
        }
    }
    guard_print(gmostslept);
    
    int mostsleptmin=0;
    for(int i = 0; i < 59; i++) {
        if(gmostslept->minsleep[i] > gmostslept->minsleep[mostsleptmin])
            mostsleptmin = i;
    }
    printf("%d\n",mostsleptmin);
    
    printf("%d\n",gmostslept->id*mostsleptmin);
}
