#pragma once
#include <vector>
#include <random>
#include <iostream>

namespace hashlib 
{
    class PerfectHash
    {
    private:
        std::size_t k, c, n, m, a=1, b=0, p;
        std::vector<std::pair<std::size_t, std::size_t>> hashTable;
        std::vector<std::vector<std::size_t>> B;
        std::random_device rd;
        std::mt19937 rng{rd()};
    public:
        void build(std::vector<std::size_t> nums, std::size_t k, std::size_t c);
        std::size_t h(std::size_t x);
        std::size_t h_i(std::size_t x, std::size_t i);
        std::size_t size();
        std::size_t rand_a();
        std::size_t rand_b();
    };
}