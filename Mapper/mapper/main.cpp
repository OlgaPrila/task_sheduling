#include <iostream>
#include <string>
#include <vector>

#include "configurator.h"

using namespace std;

int perrors(const std::vector<std::string> & errors){
    if (errors.size() == 0){
        return 0;
    }
    for (vector<string>::const_iterator i=errors.begin();
         i!=errors.end();i++){
        cerr << *i << endl;
    }
    return 1;
}

int main(int argc, char** argv){
    Configurator & conf = Configurator::instance();
    if ( conf.parseCLI(argc,argv)){
        Graph * task = NULL;
//        task = new Graph(4);
        if ( conf.getParser()->parse(task)){
            GraphPrinter printer;
            printer.print(task);
            Graph * grid = NULL;
            if ( conf.getScanner()->scan(grid)){
                printer.print(grid);
                Result result;
                if( conf.getAlgorithm()->process(task,grid,result)){
                }
                conf.getPrinter()->printResult(result);
            }
            delete grid;
        }
        delete task;
    }
    return perrors(conf.errors());
}
