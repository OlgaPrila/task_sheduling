#ifndef NULLPARSER_H
#define NULLPARSER_H

#include "configurator.h"

class NullParser : public AbstractParser
{
public:
    NullParser(){}
    virtual ~NullParser(){}
    virtual bool parse(PGraph &result);

};

#endif // NULLPARSER_H
