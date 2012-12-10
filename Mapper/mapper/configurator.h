#ifndef CONFIGURATOR_H
#define CONFIGURATOR_H

#include "abstractalgorithm.h"
#include "abstractparser.h"
#include "abstractscanner.h"
#include "abstractresultprinter.h"
#include "graphprinter.h"


//#define TWO_CLUSTERS
#define SECOND_EXAMPLE
#define TIME_BASED

class Configurator
{
public:
    static Configurator & instance(){
        static Configurator instance;
        return instance;
    }
//парсим коммандную строку, а также читаем конфигурацию из файла, if needed
    bool parseCLI(int argc, char ** argv);


    AbstractAlgorithm *   getAlgorithm() const{
        return algorithm;
    }
    AbstractParser *    getParser() const{
        return parser;
    }
    AbstractScanner *   getScanner() const{
        return scanner;
    }
    AbstractResultPrinter * getPrinter() const{
        return printer;
    }

    std::vector<std::string> & errors(){
        return _errors;
    }
    const std::string & getTaskFilename(){
        return _taskFilename;
    }
    int getTaskNodePropertiesCount(){
        return taskNodePropertiesCount;
    }

    int getGridNodePropertiesCount(){
        return gridNodePropertiesCount;
    }
    int getTaskLinePropertiesCount(){
        return taskLinePropertiesCount;
    }

    int getGridlinePropertiesCount(){
        return gridLinePropertiesCount;
    }
    void setTaskNodePropertiesCount(int i){
        taskNodePropertiesCount = i;
    }
    void setTaskLinePropertiesCount(int i){
        taskLinePropertiesCount = i;
    }
    void setGridNodePropertiesCount(int i){
        gridNodePropertiesCount = i;
    }
    void setGridLinePropertiesCount(int i){
        gridLinePropertiesCount = i;
    }

private:
    Configurator(): _errors(),algorithm(NULL), parser(NULL),
        scanner(NULL), printer(NULL), _taskFilename("test")
    {
    }
    ~Configurator();

    std::vector<std::string>  _errors;
    AbstractAlgorithm * algorithm;
    AbstractParser * parser;
    AbstractScanner * scanner;
    AbstractResultPrinter * printer;

    std::string _taskFilename;
    int taskNodePropertiesCount;
    int gridNodePropertiesCount;

    int taskLinePropertiesCount;
    int gridLinePropertiesCount;

    void readSettings();

};

#endif // CONFIGURATOR_H
