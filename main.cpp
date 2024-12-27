#include <chrono>
#include <random>     // mt19937 and uniform_int_distribution
#include <algorithm>  // generate
#include <vector>     // vector
#include <map>
#include <string>
#include <iterator>   // begin, end, and ostream_iterator
#include <functional> // bind
#include <cstdint>
#include <iostream>
#include <print>
#include "lib/PerfectHash.hpp"

using 
    lib::PerfectHash,
    std::print,
    std::println,
    std::size_t,
    std::chrono::high_resolution_clock, 
    std::chrono::duration_cast,
    std::chrono::milliseconds,
    std::vector,
    std::map,
    std::string;

typedef std::uint64_t u64;


vector<u64> create_random_data(int n) {
    std::random_device r;
    std::seed_seq      seed{r(), r(), r(), r(), r(), r(), r(), r()};
    std::mt19937       eng(seed); // a source of random data    
    std::uniform_int_distribution<u64> dist;
    vector<u64> v(n);   
    generate(begin(v), end(v), bind(dist, eng));
    return v;
}

// Experiment 1
void exp1() 
{
    map<int, string> ten_pow_dict = {
        {10, "10¹"},
        {100, "10²"},
        {1000, "10³"},
        {10000, "10⁴"},
        {100000, "10⁵"},
        {1000000, "10⁶"},
        {10000000, "10⁷"}
    };
    println("Experimento 1:");
    println("==============");
    println("n in [10, 10⁷], k=4, c=1;");
    for (int n=10; n<100000000; n*=10)
    {
        vector<u64> S = create_random_data(n);
        PerfectHash hash_table;
        auto start = high_resolution_clock::now();
        hash_table.build(S, 4, 1);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<milliseconds>(stop-start);
        println("\tn={0} => {1}s", ten_pow_dict[n], duration.count()/(float)1000);
    }
}

// Experiment 2
void exp2() 
{
    println("Experimento 2:");
    println("==============");
    println("n=10⁶, k in [2, 8], c=1;");
    for (int k=2; k<9; k++)
    {
        u64 n = 1000000;
        vector<u64> S = create_random_data(n);
        PerfectHash hash_table;
        auto start = high_resolution_clock::now();
        hash_table.build(S, k, 1);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<milliseconds>(stop-start);
        println("\tn={0} => {1}s", n, duration.count()/(float)1000);
    }
}

// Experiment 3
void exp3() 
{
    println("Experimento 3:");
    println("==============");
    println("n=10⁶, k=4, c in [1, 4];");
    for (int c=1; c<5; c++)
    {
        u64 n = 1000000;
        vector<u64> S = create_random_data(n);
        PerfectHash hash_table;
        auto start = high_resolution_clock::now();
        hash_table.build(S, 4, 1);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<milliseconds>(stop-start);
        println("\tn={0} => {1}s", n, duration.count()/(float)1000);
    }
}

int main() {
    exp1();
    exp2();
    exp3();
}