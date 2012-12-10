#ifndef TIMEBASEDALGORITHM_H
#define TIMEBASEDALGORITHM_H

#include "algorithm.h"

class TimeBasedAlgorithm : public Algorithm
{
public:
    TimeBasedAlgorithm(){}
    virtual ~TimeBasedAlgorithm(){}

protected:
    virtual float LineWeight(const NodeClusterPair &src, const NodeClusterPair &dst);
};

#endif // TIMEBASEDALGORITHM_H
