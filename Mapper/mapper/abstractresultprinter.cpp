#include "abstractresultprinter.h"


#include <iostream>

#include "configurator.h"

using namespace std;

bool AbstractResultPrinter::printResult(const Result &result){
//    std::cout <<
     //Configurator::instance().errors().push_back("Not implemeted printing yet");
    cout << "Result for filename: " <<
            Configurator::instance().getTaskFilename() << endl;
    for (unsigned int i=0; i< result.size(); ++i){
        cout << i << ":" << result.at(i);
    }
    cout << endl;
    return true;
 }
