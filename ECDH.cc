#include "ECDH.h"

std::tuple<long long, Point> make_keypair(const EllipticCurve& curve) {
    long long order = curve.get_order();
    Point generator = curve.get_generator();
    long long private_key = rand() % order;
    Point public_key = curve.scalar_multi(private_key, generator);

    return std::make_tuple(private_key, public_key);
}