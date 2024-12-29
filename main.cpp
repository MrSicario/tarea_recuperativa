#include <chrono>
#include <random>     // mt19937 and uniform_int_distribution
#include <algorithm>  // generate
#include <vector>     // vector
#include <map>
#include <string>
#include <format>
#include <iterator>   // begin, end, and ostream_iterator
#include <functional> // bind
#include <cstdint>
#include <iostream>
#include <print>
#include "lib/PerfectHash.hpp"
#include "lib/Logger.hpp"

using 
    lib::PerfectHash,
    lib::Logger,
    lib::INFO,
    lib::ERROR,
    std::print,
    std::println,
    std::format,
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
    std::sort(v.begin(), v.end());
    return v;
}

map<int, string> ten_pow_dict = {
    {10, "10¹"},
    {100, "10²"},
    {1'000, "10³"},
    {10'000, "10⁴"},
    {100'000, "10⁵"},
    {1'000'000, "10⁶"},
    {10'000'000, "10⁷"}
};

// Experiment 1
void exp1(Logger &logger) 
{
    logger.log(INFO, "Experiment 1");
    println("==============");
    println("Experimento 1: n in [10, 10⁷], k=4, c=1;");
    println("--");
    for (int n=10; n<100'000'000; n*=10)
    {
        println("Generating {0} nums...", ten_pow_dict[n]);
        vector<u64> S = create_random_data(n);
        PerfectHash hash_table;
        println("Building hashtable...");
        auto start = high_resolution_clock::now();
        hash_table.build(S, 4, 1, 15);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<milliseconds>(stop-start);
        string msg = format("n= {0} => time= {1}s, space= {2}", ten_pow_dict[n], duration.count()/(float)1'000, hash_table.size());
        println("{0}", msg);
        logger.log(INFO, msg);
        println("--");
    }
    println("==============");
}

// Experiment 2
void exp2(Logger &logger) 
{
    logger.log(INFO, "Experiment 2");
    println("==============");
    println("Experimento 2: n=10⁶, k in [2, 8], c=1;");
    println("--");
    for (double k=2; k<9; k++)
    {
        u64 n = 1'000'000;
        println("Generating {0} nums...", ten_pow_dict[n]);
        vector<u64> S = create_random_data(n);
        PerfectHash hash_table;
        println("Building hashtable...");
        auto start = high_resolution_clock::now();
        int error_code = hash_table.build(S, k, 1);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<milliseconds>(stop-start);
        if (error_code)
        {
            string msg = format("k= {0} => Exceeded time limit: {1}s", k, duration.count()/(float)1'000);
            println("{0}", msg);
            logger.log(ERROR, msg);
        }
        else
        {
            string msg = format("k= {0} => time= {1}s, size= {2}", k, duration.count()/(float)1'000, hash_table.size());
            println("{0}", msg);
            logger.log(INFO, msg);
        }
        println("--");
    }
}

// Experiment 3
void exp3(Logger &logger) 
{
    logger.log(INFO, "Experiment 3");
    println("==============");
    println("Experimento 3: n=10⁶, k=4, c in [1, 4];");
    println("--");
    for (int c=1; c<5; c++)
    {
        u64 n = 1'000'000;
        println("Generating {0} nums...", ten_pow_dict[n]);
        vector<u64> S = create_random_data(n);
        PerfectHash hash_table;
        println("Building hashtable...");
        auto start = high_resolution_clock::now();
        int error_code = hash_table.build(S, 4, c);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<milliseconds>(stop-start);
        if (error_code)
        {
            string msg = format("c= {0} => Exceeded time limit: {1}s", c, duration.count()/(float)1'000);
            println("{0}", msg);
            logger.log(ERROR, msg);
        }
        else
        {
            string msg = format("c= {0} => time= {1}s, size= {2}", c, duration.count()/(float)1'000, hash_table.size());
            println("{0}", msg);
            logger.log(INFO, msg);
        }
        println("--");
    }
}

// Experiment 4
void exp4(Logger &logger)
{
    logger.log(INFO, "Experiment 4");
    println("==============");
    println("Experimento 4: n=10⁶, k in [2, 8], c in [1, k];");
    println("--");
    for (int k=2; k<9; k++)
    {
        for (int c=1; c<=k; c++)
        {
            u64 n = 1'000'000;
            println("Generating {0} nums...", ten_pow_dict[n]);
            vector<u64> S = create_random_data(n);
            PerfectHash hash_table;
            println("Building hashtable...");
            auto start = high_resolution_clock::now();
            int error_code = hash_table.build(S, k, c);
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<milliseconds>(stop-start);
            if (error_code)
            {
                string msg = format("k= {2} & c= {0} => Exceeded time limit: {1}s", c, duration.count()/(float)1'000, k);
                println("{0}", msg);
                logger.log(ERROR, msg);
            }
            else
            {
                string msg = format("k= {3} & c= {0} => time= {1}s, size= {2}", c, duration.count()/(float)1'000, hash_table.size(), k);
                println("{0}", msg);
                logger.log(INFO, msg);
            }
            println("--");
        }
    }
}

int main() {

    Logger logger("log.txt");

    exp1(logger);
    exp2(logger);
    exp3(logger);
    exp4(logger);

    return 0;
}