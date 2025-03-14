#ifndef ELLIPTIC_CURVE_H_
#define ELLIPTIC_CURVE_H_

#include "arithmetic.h"

struct Point {
    long long x;
    long long y;
    bool infinity;

    Point() : x(0), y(0), infinity(true) {}
    Point(long long _x, long long _y) : x(_x), y(_y), infinity(false) {}

    bool operator==(const Point& other) const {
        if (x == other.x && y == other.y && infinity == other.infinity) {
            return true;
        }
        else {
            return false;
        }
    }
};

class EllipticCurve {
public:
    ModularArithmetic Fp;
    long long a;
    long long b;
    Point g;
    long long n;
    // long long h;

    EllipticCurve(const ModularArithmetic& Fp, long long a, long long b,
                  const Point& g, long long n);
    
    bool is_on_curve(const Point& point) const;
    Point inverse_of_point(const Point& point) const;
    Point add(const Point& point1, const Point& point2) const;
    Point doublePoint(const Point& point) const;
    Point scalar_multi(long long scalar, const Point& point) const;

    std::string toString() const {
        std::ostringstream oss;
        char a_sign = (a < 0) ? '-' : '+';
        char b_sign = (b < 0) ? '-' : '+';
        oss << "Y^2 = (x^3 " << a_sign << " " << std::abs(a)
            << "x " << b_sign << " " << std::abs(b)
            << ") mod " << Fp.getModulus();
        return oss.str();
    }
};

#endif /* ELLIPTIC_CURVE_H_ */