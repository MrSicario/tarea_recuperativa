#include <vector>
#include <random>
#include <print>
#include "PerfectHash.hpp"

namespace hashlib 
{   
    void PerfectHash::build(std::vector<std::size_t> nums, std::size_t k, std::size_t c)
    {
        std::size_t n = nums.size();
        this->n = n;
        this->k = k;
        this->c = c;
        this->m = k*n;
        this->p = ((unsigned long long)(1<<31) - 1);
        std::vector<std::pair<std::size_t, std::size_t>> new_hash_table(m);
        this->hashTable = new_hash_table;
        bool finished_table = false;
        int attempts_h = 0;
        while (!finished_table)
        {
            attempts_h++;
            this->a = rand_a();
            this->b = rand_b();
            std::vector<std::vector<std::size_t>> B_tmp(m);
            for (int i=0; i<n; i++)
                B_tmp[h(nums[i])].push_back(nums[i]);
            std::size_t total_size = 0;
            for (int i=0; i<m; i++)
            {
                auto B_i = B_tmp.at(i);
                if (B_i.empty())
                {
                    this->hashTable[i] = {0, 0};
                    std::vector<std::size_t> empty_vector;
                    this->B.push_back(empty_vector);
                    continue;
                }
                int B_i_size = B_i.size() * B_i.size() * c;
                total_size += B_i_size;
                std::vector<std::size_t> tmp(B_i_size);
                std::vector<bool> hashed(B_i_size, false);
                this->B.push_back(tmp);
                bool finished_B = false;
                int attempts_bi = 0;
                while (!finished_B) 
                {
                    attempts_bi++;
                    std:size_t a_i = rand_a(), b_i = rand_b();
                    this->hashTable[i] = {a_i, b_i};
                    for (int j=0; j<B_i.size(); j++)
                    {
                        auto hash = h_i(B_i[j], i);
                        if (hashed.at(hash))
                            break;
                        else
                        {   
                            hashed.at(hash) = true;
                            this->B.back().at(hash) = B_i[j];
                        }
                    }
                    finished_B = true;
                }
            }
            if (total_size <= m) {
                finished_table = true;
                std::print("Found good hash function in {0} attempts\n", attempts_h);
                double ratio = (double)total_size/(double)n;
                std::print("total size / n = {0}\n", ratio);
            }
        }
    }

    std::size_t PerfectHash::h(std::size_t x)
    {
        std::size_t i = ((this->a * x + this->b) % this->p) % this->m;
        return i;
    }

    std::size_t PerfectHash::h_i(std::size_t x, std::size_t i)
    {
        auto [a, b] = this->hashTable[i];
        auto m = this->B[i].capacity();
        std::size_t i_ = ((a * x + b) % this->p) % m;
        return i_;
    }

    std::size_t PerfectHash::size()
    {
        std::size_t total_size = 0;
        for (auto it = this->B.begin(); it != this->B.end(); it++)
        {
            auto B_i = *it;
            total_size += B_i.capacity();
        }
        return total_size;
    }

    std::size_t PerfectHash::rand_a()
    {
        std::uniform_int_distribution<> dist(1,this->p-1);
        return dist(this->rng);
    }

    std::size_t PerfectHash::rand_b()
    {
        std::uniform_int_distribution<> dist(0,this->p-1);
        return dist(this->rng);
    }
}