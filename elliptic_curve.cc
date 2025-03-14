#include "elliptic_curve.h"

EllipticCurve::EllipticCurve(const ModularArithmetic& _Fp, long long _a,
                             long long _b, const Point& _g, long long _n)
    : Fp(_Fp), a(_a), b(_b), g(_g), n(_n) {

    long long p = Fp.getModulus();
    if (Fp.power(2, p - 1) != 1) {
        throw std::invalid_argument(
            "It's not satisfied with Fermat's Little Theorem");
    }
    if (Fp.add(Fp.multi(4, Fp.power(a, 3)),
               Fp.multi(27, Fp.power(b, 2))) % p == 0) {
        throw std::invalid_argument(
            "It's not satisfied with non-singular condition");
    }
    if (is_on_curve(g) == false) {
        throw std::invalid_argument("g is not on curve");
    }
    if (EllipticCurve::scalar_multi(n, g).infinity != true) {
        throw std::invalid_argument("nP should be a infinity");
    }
}

bool EllipticCurve::is_on_curve(const Point& point) const {
    if (point.infinity) {
        return true;
    }
    long long left_term = Fp.power(point.y, 2);
    long long right_term = Fp.add(
        Fp.add(Fp.power(point.x, 3), Fp.multi(a, point.x)), b
    );
    return left_term == right_term;
}

Point EllipticCurve::inverse_of_point(const Point& point) const {
    if (is_on_curve(point) == false) {
        throw std::invalid_argument("point is not on curve");
    }

    if (point.infinity) {
        return point;
    }
    return Point(point.x, Fp.normalize(-point.y));
}

Point EllipticCurve::add(const Point& P, const Point& Q) const {
    if (is_on_curve(P) == false || is_on_curve(Q) == false) {
        throw std::invalid_argument("P or Q are not on curve");
    }

    if (P.infinity == true) {
        return Q;
    }
    else if (Q.infinity == true) {
        return P;
    }

    if (P.x == Q.x && P.y == Fp.normalize(-Q.y)) {
        return Point();
    }

    long long m;
    if (P.x == Q.x && P.y == Q.y) {
        m = Fp.multi(Fp.add(Fp.multi(3, Fp.power(P.x, 2)), a),
                     Fp.multi_inverse(Fp.multi(2, P.y)));
    }
    else {
        m = Fp.multi(Fp.subtract(Q.y, P.y),
                     Fp.multi_inverse(Fp.subtract(Q.x, P.x)));
    }
    long long x_R = Fp.subtract(Fp.subtract(Fp.power(m, 2), P.x), Q.x);
    long long y_R = Fp.add(P.y, Fp.multi(m, Fp.subtract(x_R, P.x)));
    return Point(x_R, Fp.normalize(-y_R));
}

Point EllipticCurve::doublePoint(const Point& point) const {
    return add(point, point);
}

Point EllipticCurve::scalar_multi(long long scalar, const Point& point) const {
    if (is_on_curve(point) == false) {
        throw std::invalid_argument("P or Q are not on curve");
    }

    scalar = ((scalar % n) + n) % n;
    if (scalar == 0 || point.infinity == true) {
        return Point();
    }

    Point result;
    long long num_bits = std::floor(std::log2(scalar)) + 1;
    for (long long i = num_bits - 1; i >= 0; --i) {
        result = EllipticCurve::doublePoint(result);
        if ((scalar >> i) & 1) {
            result = EllipticCurve::add(result, point);
        }
    }
    return result;
}