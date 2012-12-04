#include "configurator.h"

#include "algorithm.h"
#include "nullparser.h"
#include "nullscanner.h"

 Configurator::~Configurator(){
     // освобождаем все что тольуо можем
     delete algorithm;
     delete parser;
     delete scanner;
     delete printer;
 }


bool Configurator::parseCLI(int argc, char **argv){
//    на данном этапе все тестовое

//     если кто либо не создан - заменяем его дефолтным,
//     на данный момент дефолтное - тестовое
     if (! algorithm){
         algorithm = new Algorithm();
     }
     if (! parser){
         parser = new NullParser();
     }
     if (! scanner){
         scanner = new NullScanner();
     }
     if (! printer){
         printer = new AbstractResultPrinter();
     }
    return true;
}

