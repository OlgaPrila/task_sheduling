#ifndef CONFIGURATOR_H
#define CONFIGURATOR_H

#include "abstractalgorithm.h"
#include "abstractparser.h"
#include "abstractscanner.h"
#include "abstractresultprinter.h"

class Configurator
{
public:
    static Configurator & instance(){
        static Configurator instance;
        return instance;
    }

    bool init(int argc, char ** argv);


    AbstractAlgorithm *   getAlgorithm();
    AbstractParser *    getParser();
    AbstractScanner *   getScanner();
    AbstractResultPrinter * getPrinter();



private:
    Configurator();
    ~Configurator();


    AbstractAlgorithm * algorithm;
    AbstractParser * parser;
    AbstractScanner * scanner;
    AbstractResultPrinter * printer;
    void readSettings();



};

#endif // CONFIGURATOR_H
