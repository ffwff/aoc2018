/*
 * there is no 2.cpp because I couldn't solve it :(
 * i had to look at a sample
 * 
 * i need to improve my algorithmic skills
 */

#include <cstdio>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
#include <stack>

const int length = 'Z'-'A'+1;
std::vector<int> chars[length];
bool chars_available[length] = { 0 };

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
}
