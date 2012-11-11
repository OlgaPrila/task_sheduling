#ifndef ABSTRACTPARSER_H
#define ABSTRACTPARSER_H

//#include <QFile>
#include <fstream>
#include "graph.h"

class AbstractParser
{
public:
    AbstractParser();

    virtual bool parseFile(Graph& output) = 0 ;
    virtual const std::vector<std::string> & errors();
    virtual ~AbstractParser();
};

#endif // ABSTRACTPARSER_H
