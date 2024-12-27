#include <vector>
#include <random>
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
        bool finished_table = false;
        while (!finished_table)
        {
            this->a = rand_a();
            this->b = rand_b();
            std::vector<std::vector<std::size_t>> B_tmp(n);
            for (int i=0; i<n; i++)
                B_tmp[h(nums[i])].push_back(nums[i]);
            std::size_t total_size = 0;
            for (int i=0; i<n; i++)
            {
                auto B_i = B_tmp.at(i);
                if (B_i.empty()) 
                    continue;
                int B_i_size = B_i.size() * B_i.size() * c;
                total_size += total_size + B_i_size;
                std::vector<std::size_t> tmp(B_i_size);
                std::vector<bool> hashed(B_i_size, false);
                this->B.push_back(tmp);
                bool finished_B = false;
                while (!finished_B) 
                {
                    this->hashTable[i] = {rand_a(), rand_b()};
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
                        finished_B = true;
                    }
                }
            }
            if (total_size <= m)
                finished_table = true;
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
        auto m = this->B[i].size();
        std::size_t i_ = ((a * x + b) % this->p) % m;
        return i_;
    }

    std::size_t PerfectHash::size()
    {
        std::size_t total_size = 0;
        for (auto it = this->B.begin(); it != this->B.end(); it++)
        {
            auto B_i = *it;
            total_size += B_i.size();
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