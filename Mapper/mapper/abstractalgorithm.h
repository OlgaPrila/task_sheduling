#ifndef ABSTRACTALGORITHM_H
#define ABSTRACTALGORITHM_H

#include <string>

#include "graph.h"
#include "result.h"



class AbstractAlgorithm
{
public:
    AbstractAlgorithm(){}
    virtual ~AbstractAlgorithm(){}
    //
    virtual bool process( Graph * task,
                          Graph * grid,
                          Result & result) = 0;

};

#endif // ABSTRACTALGORITHM_H
