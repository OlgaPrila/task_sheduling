#include <iostream>
#include <string>
#include <vector>

#include "abstractalgorithm.h"
#include "abstractparser.h"
#include "configurator.h"

using namespace std;

void perrors(const string & message, const vector<string> & errors){
    cerr << message << endl;
    for (vector<string>::const_iterator i=errors.begin(); i!=errors.end();i++){
        cerr << *i << endl;
    }
}

int main(int argc, char** argv)
{
    Configurator & conf = Configurator::instance();
    conf.init(argc,argv);

    Graph task;
    if (! conf.getParser()->parseFile(task)){
        perrors("Troubles parsing task",conf.getParser()->errors());
        return -1;
    }
    Graph grid;
    if (! conf.getScanner()->scan(grid)){
        perrors("Troubles parsing grid scheme",conf.getScanner()->errors());
        return -1;
    }
    Result result;
    if(! conf.getAlgorithm()->process(task,grid,result)){
        perrors("Troubles while mapping", conf.getAlgorithm()->errors());
        return -1;
    }
    if(! conf.getPrinter()->printResult(result)){
        perrors("Troubles writing result",conf.getPrinter()->errors());
        return -1;
    }



    return 0;
}
