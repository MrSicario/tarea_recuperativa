#include <vector>
#include <random>
#include <cstdint>
#include <chrono>
#include "PerfectHash.hpp"

namespace lib 
{   
    int PerfectHash::build(const std::vector<std::uint64_t> &nums, std::uint64_t k, std::uint64_t c, int time_limit)
    {
        std::uint64_t n = nums.size();
        this->n = n;
        this->k = k;
        this->c = c;
        this->B.resize(this->n);
        this->table.resize(this->n);
        auto start = std::chrono::high_resolution_clock::now();
        auto now_ = std::chrono::high_resolution_clock::now();
        while (timer(start, now_) <= time_limit)
        {
            this->primes_.push_back({this->rng(), nextPrime(this->n)});
            std::uint64_t total_size = 0;
            std::vector<std::vector<std::uint64_t>> B_tmp(this->n);
            std::vector<std::uint64_t> K;
            for (int i=0; i<n; i++)
                B_tmp[h(nums[i])].push_back(nums[i]);
            for (int i=0; i<n; i++)
            {
                auto bucket = B_tmp.at(i);
                if (bucket.empty())
                    continue;
                int B_i_size = bucket.size() * bucket.size() * c;
                std::vector<std::uint64_t> B_i(B_i_size);
                total_size += B_i_size;
                std::uint64_t l = 0;
                for (l=1; l<10'000; l++)
                {
                    bool exists = false;
                    K.clear();
                    B_i.clear();
                    for (int j=0; j<bucket.size(); j++)
                    {
                        auto const val = bucket[j];
                        auto const hash = h_i(val, i, l, B_i_size);
                        for (auto k : K) {
                            if (k == hash)
                            {
                                exists = true;
                                break;
                            }
                        }
                        if (exists)
                            break;
                        K.push_back(hash);
                        B_i[hash] = val;
                    }
                    if (!exists)
                        break;
                }
                this->table[i] = l;
                this->B[i] = B_i;
            }
            now_ = std::chrono::high_resolution_clock::now();
            if (total_size <= k*n) {
                this->size_ = total_size;
                break;
            }
            else
            {
                this->primes_.clear();
                this->B.clear();
                this->table.clear();
            }
        }
        this->time_ = std::chrono::duration_cast<std::chrono::milliseconds>(now_-start).count() / 1e3;
        if (timer(start, now_) <= time_limit)
            return 0;
        else
            return 1;
    }

    std::uint64_t PerfectHash::h(std::uint64_t x)
    {
        return h_i(x, 0, 0, 0);
    }

    std::uint64_t PerfectHash::h_i(std::uint64_t x, std::uint64_t i, std::uint64_t l, std::uint64_t size)
    {
        while (i >= this->primes_.size())
            this->primes_.push_back({this->rng(), nextPrime(this->primes_.back().second + 1)});
        auto const [k, p] = this->primes_[i];
        std::uint64_t mod = l == 0 ? this->n : size;
        return ((k * x) % p) % mod;
    }

    std::uint64_t PerfectHash::size()
    {
        return this->size_;
    }

    float PerfectHash::time()
    {
        return this->time_;
    }

    template <typename T>
    T PerfectHash::mod_pow(T base, T exp, T mod)
    {
        if (mod == 1)
            return 1;
        T res = 1;
        base = base % mod;
        while (exp > 0)
        {
            if (exp&1)
                res = (res * base) % mod;
            exp = exp >> 1;
            base = (base * base) % mod;
        }
        return res;
    }

    template <typename T>
    bool PerfectHash::miller_rabin(T n, T d, T s)
    {
        std::uniform_int_distribution<T> dist(1, n-1);
        T a = dist(this->rng);
        T x = mod_pow(a, d, n);
        if (x==1 || x==n-1)
            return true;
        for (int i=0; i<s; i++)
        {
            x = (x * x) % n;
            if (x==n-1)
                return true;
        }
        return false;
    }

    template <typename T>
    T PerfectHash::isPrime(T const & n)
    {
        if (n <= 1 || n == 4) return false;
        if (n <= 3) return true;
        T s = 0, d = n-1;
        while (!(d&1))
        {
            s++;
            d = d>>1;
        }
        for (int i=0; i<4; i++)
            if (!miller_rabin(n, d, s))
                return false;
        return true;
    }

    template <typename T>
    T PerfectHash::nextPrime(T const & i)
    {
        if (i <= 2) return 2;
        for (T j = i | 1;; j += 2)
            if (isPrime(j))
                return j;
    }

    float PerfectHash::timer(std::chrono::_V2::system_clock::time_point start, std::chrono::_V2::system_clock::time_point stop)
    {
        return std::chrono::duration_cast<std::chrono::milliseconds>(stop-start).count() / 6e4;
    }
}