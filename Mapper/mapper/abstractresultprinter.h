#ifndef ABSTRACTRESULTPRINTER_H
#define ABSTRACTRESULTPRINTER_H


#include <fstream>

#include "result.h"


class AbstractResultPrinter
{
public:
    virtual bool printResult (const Result & result);
    virtual const std::vector<std::string> & errors();
    virtual ~AbstractResultPrinter();
};

#endif // ABSTRACTRESULTPRINTER_H
