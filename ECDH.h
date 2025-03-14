#ifndef ECDH_H_
#define ECDH_H_

#include "elliptic_curve.h"

extern std::tuple<long long, Point> make_keypair(const EllipticCurve& curve);

#endif /* ECDH_H_ */