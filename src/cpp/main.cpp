#include <chrono>
#include <random>     // mt19937 and uniform_int_distribution
#include <algorithm>  // generate
#include <vector>     // vector
#include <iterator>   // begin, end, and ostream_iterator
#include <functional> // bind
#include <iostream>
#include "lib/PerfectHash.hpp"

using std::cout,
    std::endl,
    std::size_t,
    std::vector;

vector<size_t> create_random_data(int n) {
    std::random_device r;
    std::seed_seq      seed{r(), r(), r(), r(), r(), r(), r(), r()};
    std::mt19937       eng(seed); // a source of random data    
    std::uniform_int_distribution<size_t> dist;
    vector<size_t> v;   
    generate(begin(v), end(v), bind(dist, eng));
    return v;
}

// Experiment 1
void exp1() {}

// Experiment 2
void exp2() {}

// Experiment 3
void exp3() {}

int main() {
    
    int base = 10*10*10*10*10*10;

    int N = base;

    vector<size_t> A;
    A = create_random_data(N);

    hashlib::PerfectHash hashTable;
    hashTable.build(A, 4, 1);
    cout<<"finished"<<endl;
}