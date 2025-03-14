#include "baby_giant_step.h"
#include <unordered_map>

namespace std {
    template<>
    struct hash<Point> {
        std::size_t operator() (const Point& point) const noexcept {
            return std::hash<long long>()(point.x) ^
                            (std::hash<long long>()(point.y) << 1);
        }
    };
}

std::tuple<long long, long long> Babystep_Giantstep(
                                EllipticCurve& curve, Point& P, Point& Q) {
    if (curve.is_on_curve(P) == false || curve.is_on_curve(Q) == false) {
        throw std::invalid_argument("P or Q are not on curve");
    }

    ModularArithmetic mod(curve.n);
    long long m = std::ceil(std::sqrt(static_cast<double>(curve.n)));

    std::unordered_map<Point, long long> hashed_baby;
    for (long long b = 0; b <= m; b++) {
        Point baby = curve.scalar_multi(b, P);
        hashed_baby[baby] = b;
    }
    
    for (long long a = 0; a <= m; a++) {
        long long am = mod.multi(a, m);
        Point negetive_amP = curve.inverse_of_point(curve.scalar_multi(am, P));
        Point giant = curve.add(Q, negetive_amP);
        
        auto it = hashed_baby.find(giant);
        if (it != hashed_baby.end()) {
            long long b = it->second;
            long long logarithm = mod.add(am, b);
            return std::make_tuple(logarithm, a);
        }
    }
    throw std::invalid_argument("logarithm not found");
}