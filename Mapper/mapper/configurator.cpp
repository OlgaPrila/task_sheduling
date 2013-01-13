#include "configurator.h"

#include <QBuffer>

#include "algorithm.h"
#include "nullparser.h"
#include "nullscanner.h"
#include "nullparser2.h"
#include "timebasedalgorithm.h"
Configurator::~Configurator(){
    // освобождаем все что тольуо можем
    delete algorithm;
    delete parser;
    delete scanner;
    delete printer;
    delete log;
}


bool Configurator::parseCLI(int argc, char **argv){
    //    на данном этапе все тестовое

    //     если кто либо не создан - заменяем его дефолтным,
    //     на данный момент дефолтное - тестовое
    if ( algorithm){
        delete algorithm;
    }
#ifdef TIME_BASED
    algorithm = new TimeBasedAlgorithm();
#else
    algorithm = new Algorithm();
#endif


    if ( parser)
    {
        delete parser;
    }
#ifdef SECOND_EXAMPLE
    parser = new NullParser2();
#else
    parser = new NullParser();
#endif


    if ( scanner)
    {
        delete scanner;
    }
    scanner = new NullScanner();

    if (printer){
        delete printer;
    }
    printer = new AbstractResultPrinter();

    if (log){
        delete log;
    }
    log = new QBuffer();
    log->open(QIODevice::Append);


    return true;
}

