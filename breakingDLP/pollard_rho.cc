#include "pollard_rho.h"

std::tuple<long long, long long> pseudo_random_func(
            EllipticCurve& curve, Point& X, long long a, long long b) {
    ModularArithmetic mod(curve.n);
    long long set = X.x % 3;
    long long newA;
    long long newB;
    
    switch (set) {
        case 0:
            newA = mod.add(a, 1);
            newB = b;
            break;
        
        case 1:
            newA = mod.multi(2, a);
            newB = mod.multi(2, b);
            break;

        case 2:
            newA = a;
            newB = mod.add(b, 1);
            break;
    }
    return std::make_tuple(newA, newB);
}

std::tuple<long long, long long> pollard_rho(
                        EllipticCurve& curve, Point& P, Point& Q) {
    ModularArithmetic mod(curve.n);
    long long steps = 0;
    Point X_tortoise = P;
    long long a_tortoise = 0;
    long long b_tortoise = 0;

    Point X_hare = X_tortoise;
    long long a_hare = a_tortoise;
    long long b_hare = b_tortoise;

    while(true) {
        steps++;

        std::tuple<long long, long long> new_tortoise = pseudo_random_func(
                            curve, X_tortoise, a_tortoise, b_tortoise);
        a_tortoise = std::get<0>(new_tortoise);
        b_tortoise = std::get<1>(new_tortoise);
        X_tortoise = curve.add(curve.scalar_multi(a_tortoise, P),
                               curve.scalar_multi(b_tortoise, Q));

        std::tuple<long long, long long> new_hare = pseudo_random_func(
            curve, X_hare, a_hare, b_hare);
        a_hare = std::get<0>(new_hare);
        b_hare = std::get<1>(new_hare);
        X_hare = curve.add(curve.scalar_multi(a_hare, P),
                           curve.scalar_multi(b_hare, Q));
        new_hare = pseudo_random_func(curve, X_hare, a_hare, b_hare);
        a_hare = std::get<0>(new_hare);
        b_hare = std::get<1>(new_hare);
        X_hare = curve.add(curve.scalar_multi(a_hare, P),
                           curve.scalar_multi(b_hare, Q));

        if (X_tortoise == X_hare) {
            long long dx = mod.subtract(a_tortoise, a_hare);
            long long dy = mod.subtract(b_hare, b_tortoise);
            if (dy == 0) {
                continue;
            }
            long long dy_inv = mod.multi_inverse(dy);

            long long logarithm = mod.multi(dx, dy_inv);
            return std::make_tuple(logarithm, steps);
        }
    }
}