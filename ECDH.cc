#include "ECDH.h"

std::tuple<long long, Point> make_keypair(const EllipticCurve& curve) {
    long long private_key = rand() % curve.n;
    Point public_key = curve.scalar_multi(private_key, curve.g);

    return std::make_tuple(private_key, public_key);
}