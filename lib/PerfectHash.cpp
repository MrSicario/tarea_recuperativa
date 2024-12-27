#include <vector>
#include <random>
#include <print>
#include <cstdint>
#include "PerfectHash.hpp"

namespace hashlib 
{   
    void PerfectHash::build(const std::vector<std::uint64_t> &nums, std::uint64_t k, std::uint64_t c)
    {
        std::uint64_t n = nums.size();
        this->n = n;
        this->k = k;
        this->c = c;
        this->m = k*n;
        this->base_prime = ((unsigned long long)(1<<31) - 1);
        std::vector<std::pair<std::uint64_t, std::uint64_t>> new_hash_table(this->m);
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
                auto B_i = B_tmp.at(i);
                if (B_i.empty())
                    continue;
                int B_i_size = B_i.size() * B_i.size() * c;
                total_size += B_i_size;
                std::vector<std::uint64_t> tmp(B_i_size);
                this->B[i] = tmp;
                bool finished_B = false;
                int attempts_bi = 0;
                while (!finished_B) 
                {
                    attempts_bi++;
                    finished_B = true;
                    std:uint64_t a_i = rand_a(), b_i = rand_b();
                    std::vector<bool> hashed(B_i_size, false);
                    this->hashTable[i] = {a_i, b_i};
                    for (int j=0; j<B_i.size(); j++)
                    {
                        auto hash = h_i(B_i[j], i);
                        if (hashed.at(hash))
                        {
                            finished_B = false;
                            this->B[i].clear();
                            break;
                        }
                        else
                        {   
                            hashed.at(hash) = true;
                            this->B[i][hash] = B_i[j];
                        }
                    }
                }
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
        auto [a, b] = this->hashTable[i];
        std::uint64_t m = this->B[i].capacity();
        std::uint64_t i_ = ((a * x + b) % this->base_prime) % m;
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