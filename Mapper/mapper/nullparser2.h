#ifndef NULLPARSER2_H
#define NULLPARSER2_H

#include "configurator.h"

class NullParser2 : public AbstractParser
{
public:
    NullParser2(){}
    virtual ~NullParser2(){}
    virtual bool parse(PGraph &result);

};

#endif // NULLPARSER2_H
