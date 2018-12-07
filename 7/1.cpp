// NOTE code doesnt work for large inputs
// must be something with get_job
// so basically you can't solve aoc with this :(
#include <cstdio>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
#include <stack>

const int length = 'Z'-'A'+1;
std::vector<int> chars[length];
bool chars_available[length] = { 0 };

template<class C, class T>
auto contains(const C& v, const T& x)
-> decltype(end(v), true)
{
    return end(v) != std::find(begin(v), end(v), x);
}

std::string *gen_chain(int idx, std::string *str=new std::string("")) {
    // check
    if(!chars_available[idx])
        return str;
    for(auto idx_ : chars[idx]) {
        if(chars_available[idx_])
            return str;
    }
    
    // do
    chars_available[idx] = false;
    str->append(1, idx+'A');
    
    for(int i = 0; i < length; i++) {
        if(chars_available[i]) {
            gen_chain(i, str);
        }
    }
    
    return str;
}

void print() {
    for(int i = 0; i < length; i++) {
        if(!chars_available[i])
            continue;
        printf("[%c] ", i+'A');
        for(auto &d : chars[i]) {
            printf("%c ", d+'A');
        }
        printf("\n");
    }
}

// #2
std::vector<int> worker_queue;
int get_job() {
    for(int i = 0; i < length; i++) {
        if(!chars_available[i]) continue;
        if(chars[i].empty()) {
            //printf("%d\n", i);
            chars_available[i] = false;
            return i;
        }
    }
    return -1;
    /*
    if(worker_queue.empty()) {
        bool found = false;
        for(int i = 0; i < length; i++) {
            if(!chars_available[i]) continue;
            if(chars[i].empty()) {
                //printf("%d\n", i);
                chars_available[i] = false;
                worker_queue.push_back(i);
                found = true;
            }
        }
        //std::sort(worker_queue.begin(), worker_queue.end());
        if(!found) return -1;
    }
    int i = worker_queue.front();
    worker_queue.erase(worker_queue.begin());
    return i;
    */
}

std::string worker_done("");
int time_spent[length] = {0};
class Elf {
public:
    int i, time_remaining;
    Elf() : i(-1), time_remaining(0) { };
    
    void setup() {
        i = get_job();
        time_remaining = 60+i;
    };
    
    void tick() {
        if(i == -1) {
            setup();
            //time_remaining--;
            return;
        }
        if(time_remaining == 0) {
            // remove dependencies
            int old_i = i;
            setup();
            for(auto &dep : chars) {
                dep.erase(std::remove_if(dep.begin(), dep.end(), [old_i](int c){
                    return c == old_i;
                }), dep.end());
            }
            worker_done.append(1, old_i+'A');
            //
            
            return;
        }
        time_remaining--;
        time_spent[i]++;
    };
};

const int nelves = 5;
Elf elves[nelves];
int seconds = 0;

void log_elves(int sec) {
    printf("%4d\t", sec);
    for(auto &elf : elves)
        printf("%c\t",elf.i==-1?'-':elf.i+'A');
    printf("%s", worker_done.c_str());
    printf("\n");
}

int calculate_seconds() {
    //print();
    int n = 0;
    while(n < 10000) {
        //printf("#%d\n", n);
        int jobs_remaining = 0;
        for(auto &elf : elves) {
            elf.tick();
            //if(elf.i != -1)
            //    jobs_remaining++;
        }
        for(auto &elf : elves) {
            if(elf.i == -1)
                elf.setup();
        }
        log_elves(n);
        //if(jobs_remaining == 0)
        //    break;
        n++;
    }
    return n;
}

int main(int argc, char **argv) {
    FILE *f = fopen(argv[1], "r");
    char prev, next;
    while(fscanf(f, "Step %c must be finished before step %c can begin.\n", &prev, &next) > 0) {
        prev -= 'A';
        next -= 'A';
        chars_available[(int)prev] = true;
        chars_available[(int)next] = true;
        chars[(int)next].push_back((int)prev);
    }
    
    bool chars_available_old[length];
    memcpy(chars_available_old, chars_available, length*sizeof(bool));
    
    // sort
    for(auto &dep : chars) {
        std::sort(dep.begin(), dep.end());
    }
    
    print();
    
    // search for non dependent
    int non_dependent;
    for(int i = 0; i < length; i++) {
        if(!chars_available[i]) continue;
        if(chars[i].empty()) {
            non_dependent = i;
            break;
        }
    }
    printf("%c\n", non_dependent+'A');
    
    // follow chain
    std::string *chain = gen_chain(non_dependent);
    for(int i = 0; i < length; i++) {
        // this took me like an hour
        // i had to take a look at an example solution
        // before realising that length was off by 1!
        if(chars_available[i]) {
            chain->append(1, i+'A');
        }
    }
    printf("%s\n", chain->c_str());
    
    // redo available
    memcpy(chars_available, chars_available_old, length*sizeof(bool));
    //print();
    
    // #2
    printf("---\n");
    int secs = calculate_seconds();
    printf("%d\n", secs);
    
    for(int i = 0; i < length; i++) {
        printf("%d ", time_spent[i]);
    }
    printf("\n");
}
