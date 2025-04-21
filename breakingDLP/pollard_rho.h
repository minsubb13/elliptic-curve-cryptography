#ifndef BREAKING_DLP_POLLARD_RHO_H_
#define BREAKING_DLP_POLLARD_RHO_H_

#include "../elliptic_curve.h"

std::tuple<long long, long long> pseudo_random_func(EllipticCurve& curve,
                                                    Point& X,
                                                    long long a,
                                                    long long b);
std::tuple<long long, long long> pollard_rho(EllipticCurve& curve,
                                             Point& P,
                                             Point& Q);

#endif /* BREAKING_DLP_POLLARD_RHO_H_ */