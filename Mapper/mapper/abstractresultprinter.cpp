#include "abstractresultprinter.h"


#include <iostream>

#include "configurator.h"

#include <QDebug>
using namespace std;

bool AbstractResultPrinter::printResult(const Result &result){
//    std::cout <<
     //Configurator::instance().errors().push_back("Not implemeted printing yet");
//    cout << "Result for filename: " <<
//            Configurator::instance().getTaskFilename() << endl;
//    for (unsigned int i=0; i< result.size(); ++i){
//        unsigned int tmp = -1;
//        if (result.at(i) == Graph::null_vertex()){
//            tmp = result.at(i);
//        }
//        cout << i << ":" << tmp << endl;
//    }
    qDebug("Result for filename: %s", Configurator::instance().getTaskFilename().c_str());
    QString str2  ;

//    str.append(" = ");
    for (unsigned int k =0; k< result.size(); k++){
        str2.append("(");
        str2.append(QString::number(k));
        str2.append(",");
        if (result.at(k) > (unsigned int) result.size()){
            str2.append("-1");
        }else {
            str2.append( QString::number(result.at(k)));
        }
        //                str2.append("; ");
        str2.append(")");
    }
    str2.append("); ");
//    str.append(str2);
    qDebug() << str2;
    return true;
 }
