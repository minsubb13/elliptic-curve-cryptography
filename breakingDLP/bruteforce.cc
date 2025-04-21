#include "bruteforce.h"
#include <random>

std::tuple<long long, long long> BruteForce(EllipticCurve& curve,
                                            Point& P,
                                            Point& Q)
{
    long long order = curve.get_order();
    if (curve.is_on_curve(P) == false  || curve.is_on_curve(Q) == false) {
        throw std::invalid_argument("P or Q are not on curve");
    }
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<long long> dis(0, order);

    long long start = dis(gen);
    Point r = curve.scalar_multi(start, P);
    long long steps = 0;
    for (long long i = 0; i < order; i++) {
        steps++;
        if (r == Q) {
            long long logarithm = (start + i) % order;
            return std::make_tuple(logarithm, steps);        
        }
        r = curve.add(r, P);
    }
    throw std::invalid_argument("logarithm not found");
}