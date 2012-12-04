#ifndef ABSTRACTRESULTPRINTER_H
#define ABSTRACTRESULTPRINTER_H


#include "result.h"


class AbstractResultPrinter
{
public:
    AbstractResultPrinter(){}
    virtual ~AbstractResultPrinter(){}
//    сохраняем результат работы алгоритма
//    куда сохранять, знает конфигуратор
    virtual bool printResult (const Result & result);
};

#endif // ABSTRACTRESULTPRINTER_H
