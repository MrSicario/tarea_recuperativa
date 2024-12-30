#include <random>     // mt19937 and uniform_int_distribution
#include <algorithm>  // generate
#include <vector>     // vector
#include <iterator>   // begin, end, and ostream_iterator
#include <functional> // bind
#include <cstdint>    // uint64_t
#include <map>
#include <string>
#include <format>
#include "lib/PerfectHash.hpp"
#include "lib/Logger.hpp"

using 
    lib::PerfectHash,
    lib::Logger,
    lib::INFO,
    lib::ERROR,
    std::format,
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
    {10, "1e1"},
    {100, "1e2"},
    {1'000, "1e3"},
    {10'000, "1e4"},
    {100'000, "1e5"},
    {1'000'000, "1e6"},
    {10'000'000, "1e7"}
};

// Experiment 1
void exp1(Logger &logger) 
{
    logger.log(INFO, "Experiment 1");
    for (int n=10; n<100'000'000; n*=10)
    {
        vector<u64> S = create_random_data(n);
        PerfectHash ht;
        ht.build(S, 4, 1, 15);
        string msg = format("n= {0} => time= {1}s, size= {2}", ten_pow_dict[n], ht.time(), ht.size());
        logger.log(INFO, msg);
    }
}

// Experiment 2
void exp2(Logger &logger) 
{
    logger.log(INFO, "Experiment 2");
    for (double k=1; k<9; k++)
    {
        u64 n = 1'000'000;
        vector<u64> S = create_random_data(n);
        PerfectHash ht;
        int error_code = ht.build(S, k, 1);
        if (error_code)
        {
            string msg = format("k= {0} => Exceeded time limit: {1}s", k, ht.time());
            logger.log(ERROR, msg);
        }
        else
        {
            string msg = format("k= {0} => time= {1}s, size= {2}", k, ht.time(), ht.size());
            logger.log(INFO, msg);
        }
    }
}

// Experiment 3
void exp3(Logger &logger) 
{
    logger.log(INFO, "Experiment 3");
    for (int c=1; c<5; c++)
    {
        u64 n = 1'000'000;
        vector<u64> S = create_random_data(n);
        PerfectHash ht;
        int error_code = ht.build(S, 4, c);
        if (error_code)
        {
            string msg = format("c= {0} => Exceeded time limit: {1}s", c, ht.time());
            logger.log(ERROR, msg);
        }
        else
        {
            string msg = format("c= {0} => time= {1}s, size= {2}", c, ht.time(), ht.size());
            logger.log(INFO, msg);
        }
    }
}

// Experiment 4
void exp4(Logger &logger)
{
    logger.log(INFO, "Experiment 4");
    for (int k=1; k<9; k++)
    {
        for (int c=1; c<=k; c++)
        {
            u64 n = 1'000'000;
            vector<u64> S = create_random_data(n);
            PerfectHash ht;
            int error_code = ht.build(S, k, c);
            if (error_code)
            {
                string msg = format("k= {2} & c= {0} => Exceeded time limit: {1}s", c, ht.time(), k);
                logger.log(ERROR, msg);
            }
            else
            {
                string msg = format("k= {3} & c= {0} => time= {1}s, size= {2}", c, ht.time(), ht.size(), k);
                logger.log(INFO, msg);
            }
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