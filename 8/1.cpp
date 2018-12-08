#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int pop_front(std::vector<int> &vi) {
    int i = *(vi.begin());
    vi.erase(vi.begin());
    return i;
}

int sum = 0;
void parse(std::vector<int> &vi) {
    int nchild = pop_front(vi);
    int nmeta = pop_front(vi);
    while(nchild--)
        parse(vi);
    while(nmeta--)
        sum += pop_front(vi);
}

int main(int argc, char **argv) {
    std::ifstream f(argv[1]);
    std::vector<int> vi;
    for(int i; f >> i;)
        vi.push_back(i);
    parse(vi);
    std::cout << sum << "\n";
}
