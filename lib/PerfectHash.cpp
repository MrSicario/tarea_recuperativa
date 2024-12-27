#include <vector>
#include <random>
#include <print>
#include <cstdint>
#include <algorithm>
#include "PerfectHash.hpp"

namespace lib 
{   
    void PerfectHash::build(const std::vector<std::uint64_t> &nums, std::uint64_t k, std::uint64_t c)
    {
        std::uint64_t n = nums.size();
        this->n = n;
        this->k = k;
        this->c = c;
        this->m = k*n;
        this->base_prime = nextPrime(nums.back());
        this->hashTable.resize(this->m);
        this->B.resize(this->m);
        bool finished_table = false;
        while (!finished_table)
        {
            std::uint64_t total_size = 0;
            this->a = rand_a();
            this->b = rand_b();
            std::vector<std::vector<std::uint64_t>> B_tmp(this->m);
            for (int i=0; i<n; i++)
                B_tmp[h(nums[i])].push_back(nums[i]);
            for (int i=0; i<m; i++)
            {
                auto bucket = B_tmp.at(i);
                if (bucket.empty())
                    continue;
                int B_i_size = bucket.size() * bucket.size() * c;
                std::vector<std::uint64_t> B_i(B_i_size);
                this->B[i].resize(B_i_size);
                total_size += B_i_size;
                if (bucket.size() == 1)
                {
                    std::uint64_t a_i = rand_a(), b_i = rand_b();
                    this->hashTable[i] = {a_i, b_i, this->base_prime};
                    B_i[h_i(bucket.back(), i)] = bucket.back();
                }
                else
                {
                    std::uint64_t prime = nextPrime(bucket.back());
                    bool finished_B = false;
                    while (!finished_B) 
                    {
                        finished_B = true;
                        std::uint64_t a_i = rand_a(prime), b_i = rand_b(prime);
                        this->hashTable[i] = {a_i, b_i, prime};
                        std::vector<bool> hashed(B_i_size, false);
                        for (int j=0; j<bucket.size(); j++)
                        {
                            std::uint64_t hash = h_i(bucket[j], i);
                            if (hashed.at(hash))
                            {
                                /*
                                Como los datos son generados al azar,
                                existe la chance de que haya una cantidad de
                                elementos repetidos que romperian el esquema
                                del algoritmo.
                                */
                                if (B_i[hash]==bucket[j])
                                    continue;
                                finished_B = false;
                                B_i.clear();
                                break;
                            }
                            else
                            {   
                                hashed.at(hash) = true;
                                B_i[hash] = bucket[j];
                            }
                        }
                    }
                }
                this->B[i] = B_i;
            }
            if (total_size <= this->m) {
                finished_table = true;
                this->size_ = total_size;
            }
        }
    }

    std::uint64_t PerfectHash::h(std::uint64_t x)
    {
        std::uint64_t i = ((this->a * x + this->b) % this->base_prime) % this->m;
        return i;
    }

    std::uint64_t PerfectHash::h_i(std::uint64_t x, std::uint64_t i)
    {
        auto [a, b, p] = this->hashTable[i];
        std::uint64_t m = this->B[i].capacity();
        std::uint64_t i_ = ((a * x + b) % p) % m;
        return i_;
    }

    std::uint64_t PerfectHash::size()
    {
        return this->size_;
    }

    std::uint64_t PerfectHash::rand_(std::uint64_t min, std::uint64_t max)
    {
        std::uniform_int_distribution<std::uint64_t> dist(min, max);
        return dist(this->rng);
    }

    std::uint64_t PerfectHash::rand_a(std::uint64_t prime)
    {
        std::uint64_t prime_ = prime == 0 ? this->base_prime : prime;
        return rand_(1, prime_-1);
    }

    std::uint64_t PerfectHash::rand_b(std::uint64_t prime)
    {
        std::uint64_t prime_ = prime == 0 ? this->base_prime : prime;
        return rand_(0, prime_-1);
    }

    template <typename T>
    T isPrime(T const & n)
    {
        if (n % 2 == 0)
            return false;
        for (std::int64_t d = 3; d * d <= n; d += 2)
            if (n % d == 0)
                return false;
        return true;
    }

    template <typename T>
    T nextPrime(T const & i)
    {
        if (i <= 2) return 2;
        for (T j = i | 1;; j += 2)
            if (isPrime(j))
                return j;
    }
}