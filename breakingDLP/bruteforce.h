#ifndef BREAKING_DLP_BRUTE_FORCE_H_H
#define BREAKING_DLP_BRUTE_FORCE_H_H

#include <tuple>
#include <cstdlib>
#include "../elliptic_curve.h"

std::tuple<long long, long long> BruteForce(
                            EllipticCurve& curve, Point& P, Point& Q);

#endif /* BREAKING_DLP_BRUTE_FORCE_H_H */