#ifndef ABSTRACTPARSER_H
#define ABSTRACTPARSER_H

#include "graph.h"

class AbstractParser
{
public:
    AbstractParser(){}
    virtual ~AbstractParser(){}
//    считываем структуру задачи из файла, который укажет конфигуратор
    virtual bool parse(PGraph  & output) = 0 ;

};

#endif // ABSTRACTPARSER_H
