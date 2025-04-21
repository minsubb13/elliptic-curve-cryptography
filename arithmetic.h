#ifndef ARITHMETIC_H_
#define ARITHMETIC_H_

#include <iostream>
#include <cassert>
#include <sstream>
#include <stdexcept>
#include <cmath>
#include <cstdlib>
#include <tuple>

inline std::tuple<long long, long long, long long> extended_euclidean_algorithm
                                                    (long long a, long long b) {
    long long old_r = a, r = b;
    long long old_s = 1, s = 0;
    long long old_t = 0, t = 1;
    while (r != 0) {
        long long quotient = old_r / r;
        long long temp = r;
        r = old_r - quotient * r;
        old_r = temp;

        temp = s;
        s = old_s - quotient * s;
        old_s = temp;

        temp = t;
        t = old_t - quotient * t;
        old_t = temp;
    }
    return std::make_tuple(old_r, old_s, old_t);
}

class ModularArithmetic {
  private:
    long long modulus;

  public:
    ModularArithmetic(long long modulus);

    long long normalize(long long a) const;
    long long additive_inverse(long long a) const;
    long long add(long long a, long long b) const;
    long long subtract(long long a, long long b) const;
    long long multi(long long a, long long b) const;
    long long multi_inverse(long long a) const;
    long long power(long long a, long long b) const;
    long long getModulus() const { return modulus; }
};

#endif /* ARITHMETIC_H_ */