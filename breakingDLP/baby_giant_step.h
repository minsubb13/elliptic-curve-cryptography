#ifndef BREAKING_DLP_THE_BABY_STEP_GIANT_STEP_H_
#define BREAKING_DLP_THE_BABY_STEP_GIANT_STEP_H_

#include "../elliptic_curve.h"

std::tuple<long long, long long> Babystep_Giantstep(
                        EllipticCurve& curve, Point& P, Point& Q);

#endif /* BREAKING_DLP_THE_BABY_STEP_GIANT_STEP_H_ */