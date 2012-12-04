#ifndef NULLSCANNER_H
#define NULLSCANNER_H

#include "configurator.h"

class NullScanner : public AbstractScanner
{
public:
    NullScanner(){}
    virtual ~NullScanner(){}
    virtual bool scan(PGraph &result);
};

#endif // NULLSCANNER_H
