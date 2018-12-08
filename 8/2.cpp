#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int pop_front(std::vector<int> &vi) {
    int i = *(vi.begin());
    vi.erase(vi.begin());
    return i;
}

int parse(std::vector<int> &vi) { // returns value
    int nchild = pop_front(vi);
    int nmeta = pop_front(vi);
    if(nchild == 0) {
        // If a node has no child nodes, its value is the sum of its metadata entries.
        int i = 0;
        while(nmeta--)
            i += pop_front(vi);
        return i;
    } else {
        // However, if a node does have child nodes, the metadata entries become
        // indexes which refer to those child nodes.
        std::vector<int> my_childn;
        while(nchild--)
            my_childn.push_back(parse(vi));
        int value = 0;
        while(nmeta--) {
            int i = pop_front(vi);
            if(i == 0) continue;
            if(i > (int)my_childn.size()) continue;
            value += my_childn.at(i-1);
        }
        return value;
    }
}

int main(int argc, char **argv) {
    std::ifstream f(argv[1]);
    std::vector<int> vi;
    for(int i; f >> i;)
        vi.push_back(i);
    std::cout << parse(vi) << "\n";
}
