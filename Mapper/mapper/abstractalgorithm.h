#ifndef ABSTRACTALGORITHM_H
#define ABSTRACTALGORITHM_H

#include <string>

#include "graph.h"
#include "result.h"



class AbstractAlgorithm
{
public:

    virtual bool process(const Graph & task, const Graph & grid, Result & result) = 0;
    virtual const std::vector<std::string> & errors();
    virtual ~AbstractAlgorithm();
};

#endif // ABSTRACTALGORITHM_H
