#include <vector>
#include <random>
#include <print>
#include <cstdint>
#include <algorithm>
#include "PerfectHash.hpp"

namespace lib 
{   
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

    void PerfectHash::build(const std::vector<std::uint64_t> &nums, std::uint64_t k, std::uint64_t c)
    {
        std::uint64_t n = nums.size();
        this->n = n;
        this->k = k;
        this->c = c;
        this->m = k*n;
        this->base_prime = nextPrime(n);
        std::vector<std::tuple<std::uint64_t, std::uint64_t, std::uint64_t>> new_hash_table(this->m);
        std::vector<std::vector<std::uint64_t>> new_B(this->m);
        this->hashTable = new_hash_table;
        this->B = new_B;
        bool finished_table = false;
        int attempts_h = 0;
        while (!finished_table)
        {
            attempts_h++;
            this->a = rand_a();
            this->b = rand_b();
            std::vector<std::vector<std::uint64_t>> B_tmp(this->m);
            for (int i=0; i<n; i++)
                B_tmp[h(nums[i])].push_back(nums[i]);
            std::uint64_t total_size = 0;
            for (int i=0; i<m; i++)
            {
                auto bucket = B_tmp.at(i);
                if (bucket.empty())
                    continue;
                int B_i_size = bucket.size() * bucket.size() * c;
                total_size += B_i_size;
                std::vector<std::uint64_t> B_i(B_i_size);
                std::uint64_t max = *std::max_element(bucket.begin(), bucket.end());
                std::uint64_t prime = nextPrime(max);
                this->B[i].resize(B_i_size);
                bool finished_B = false;
                int attempts_bi = 0;
                while (!finished_B) 
                {
                    attempts_bi++;
                    finished_B = true;
                    std:uint64_t a_i = rand_a(), b_i = rand_b();
                    std::vector<bool> hashed(B_i_size, false);
                    this->hashTable[i] = {a_i, b_i, prime};
                    for (int j=0; j<bucket.size(); j++)
                    {
                        std::uint64_t hash = h_i(bucket[j], i);
                        if (hashed.at(hash))
                        {
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
                this->B[i] = B_i;
                std::print("finished B[{0}] in {1} attempts.\n", i, attempts_bi);
            }
            if (total_size <= this->m) {
                finished_table = true;
                this->size_ = total_size;
                std::print("found good hash function in {0} attempts.\n", attempts_h);
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

    std::uint64_t PerfectHash::rand_a()
    {
        std::uniform_int_distribution<> dist(1, this->base_prime-1);
        return dist(this->rng);
    }

    std::uint64_t PerfectHash::rand_b()
    {
        std::uniform_int_distribution<> dist(0, this->base_prime-1);
        return dist(this->rng);
    }
}