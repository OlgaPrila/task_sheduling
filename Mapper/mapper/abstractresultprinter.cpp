#include "abstractresultprinter.h"


#include <iostream>

#include "configurator.h"

using namespace std;

bool AbstractResultPrinter::printResult(const Result &result){
//    std::cout <<
     //Configurator::instance().errors().push_back("Not implemeted printing yet");
    cout << "Result for filename: " <<
            Configurator::instance().getTaskFilename() << endl;
    for (Result::const_iterator i = result.begin(); i!= result.end(); ++i){
        cout << (*i).first << "\t" << (*i).second << endl;
    }
    cout << endl;
    return true;
 }
