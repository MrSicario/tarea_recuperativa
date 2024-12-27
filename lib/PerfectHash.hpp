#pragma once
#include <vector>
#include <random>
#include <iostream>
#include <cstdint>

namespace lib 
{   
    class PerfectHash
    {
    private:
        std::uint64_t k, c, n, m, a=1, b=0, base_prime, size_;
        std::vector<std::tuple<std::uint64_t, std::uint64_t, std::uint64_t>> hashTable;
        std::vector<std::vector<std::uint64_t>> B;
        std::random_device rd;
        std::mt19937 rng{rd()};
        std::uint64_t rand_(std::uint64_t min, std::uint64_t max);
        std::uint64_t rand_a(std::uint64_t prime = 0);
        std::uint64_t rand_b(std::uint64_t prime = 0);
        std::uint64_t h(std::uint64_t x);
        std::uint64_t h_i(std::uint64_t x, std::uint64_t i);
    public:
        void build(const std::vector<std::uint64_t> &nums, std::uint64_t k, std::uint64_t c);
        std::uint64_t size();
    };
    template <typename T>
    T isPrime(T const &n);
    template <typename T>
    T nextPrime(T const &n);
}