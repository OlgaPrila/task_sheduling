#ifndef ABSTRACTSCANNER_H
#define ABSTRACTSCANNER_H

class AbstractScanner
{
public:
    virtual bool scan(Graph & result);
    virtual const std::vector<std::string> & errors();
    virtual ~AbstractScanner();
};

#endif // ABSTRACTSCANNER_H
