#include <iostream>

#include "vector.hpp"

int main (int argc, char *argv[]) {
    Vector<int> vector;

    for(int i{0}; i < 1233; ++i)
        vector.push_back(i);

    for (auto &v : vector)
        std::cout << v << '\t';
    
    return 0;
}
