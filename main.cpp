#include <chrono>
#include <random>     // mt19937 and uniform_int_distribution
#include <algorithm>  // generate
#include <vector>     // vector
#include <iterator>   // begin, end, and ostream_iterator
#include <functional> // bind
#include <iostream>
#include <print>
#include "lib/PerfectHash.hpp"

using std::print,
    std::size_t,
    std::vector;

vector<size_t> create_random_data(int n) {
    std::random_device r;
    std::seed_seq      seed{r(), r(), r(), r(), r(), r(), r(), r()};
    std::mt19937       eng(seed); // a source of random data    
    std::uniform_int_distribution<size_t> dist;
    vector<size_t> v(n);   
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
    
    int base = 10;

    int N = base;

    vector<size_t> A;
    A = create_random_data(N);
    std::println("|S| = {0}", A.size());

    lib::PerfectHash hashTable;
    hashTable.build(A, 4, 1);
    print("finished with size: {0}\n", hashTable.size());
}