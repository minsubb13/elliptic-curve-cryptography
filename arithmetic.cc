#include "arithmetic.h"

ModularArithmetic::ModularArithmetic(long long _p) : modulus(_p) {
    if (modulus <= 0) {
        throw std::invalid_argument("Modulus must be postive");
    }
}

// find a (mod n)
long long ModularArithmetic::normalize(long long a) const {
    return ((a) % modulus + modulus) % modulus;
}

// find x such that a + x = 0 (mod n)
long long ModularArithmetic::additive_inverse(long long a) const {
    return ((-a) % modulus + modulus) % modulus;
}

long long ModularArithmetic::add(long long a, long long b) const {
    long long result = ((a % modulus) + (b % modulus)) % modulus;
    if (result < 0) {
        result = normalize(result);
    }
    return result;
}

long long ModularArithmetic::subtract(long long a, long long b) const {
    long long result = ((a % modulus) - (b % modulus)) % modulus;
    if (result < 0) {
        result = normalize(result);
    }
    return result;
}

long long ModularArithmetic::multi(long long a, long long b) const {
    long long result = ((a % modulus) * (b % modulus)) % modulus;
    if (result < 0) {
        result = normalize(result);
    }
    return result;
}

long long ModularArithmetic::multi_inverse(long long a) const {
    if (a == 0) {
        throw std::invalid_argument(
            "Multiplicative inverse of 0 doesn't exist");
    }
    
    if (a < 0) {
        return modulus - multi_inverse(-a);
    }
    
    auto [gcd, x, y] = extended_euclidean_algorithm(a, modulus);
    
    if (gcd != 1) {
        throw std::invalid_argument(
            "Multiplicative inverse doesn't exist because GCD is not 1");
    }

    return (x % modulus + modulus) % modulus;
}

long long ModularArithmetic::power(long long base, long long exponent) const {
    base = base % modulus;
    long long result = 1;
    while (exponent > 0) {
        if (exponent % 2 == 1) {
            result = (result * base) % modulus;
        }
        exponent = exponent >> 1;
        base = (base * base) % modulus;
    }
    return result;
}