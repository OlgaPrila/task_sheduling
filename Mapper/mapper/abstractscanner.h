#ifndef ABSTRACTSCANNER_H
#define ABSTRACTSCANNER_H

#include "graph.h"

class AbstractScanner
{
public:
    AbstractScanner(){}
    virtual ~AbstractScanner(){}
//    анализирует сеть
//    может это как делать сам так и читать из файла
    virtual bool scan(PGraph & result) =0;
};

#endif // ABSTRACTSCANNER_H
