#pragma once
#include <vector>
#include <chrono>
#include <random>
#include <cstdint>

namespace lib 
{   
    class PerfectHash
    {
    private:
        std::uint64_t k, c, n, size_;
        std::vector<std::pair<std::uint64_t, std::uint64_t>> primes_;
        std::vector<std::uint64_t> table;
        std::vector<std::vector<std::uint64_t>> B;
        std::random_device rd;
        std::mt19937 rng{rd()};
        float time_;

        std::uint64_t h(std::uint64_t x);
        std::uint64_t h_i(std::uint64_t val, std::uint64_t i, std::uint64_t l, std::uint64_t size);
        template <typename T>
        T isPrime(T const &n);
        template <typename T>
        T nextPrime(T const &n);
        template <typename T>
        T mod_pow(T base, T exp, T mod);
        template <typename T>
        bool miller_rabin(T n, T d, T s);
        float timer(std::chrono::_V2::system_clock::time_point start, std::chrono::_V2::system_clock::time_point stop);
    public:
        int build(const std::vector<std::uint64_t> &nums, std::uint64_t k, std::uint64_t c, int time_limit = 1);
        std::uint64_t size();
        float time();
    };
}