#include "configurator.h"

#include "algorithm.h"
#include "nullparser.h"
#include "nullscanner.h"
#include "nullparser2.h"
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
#define TWO
#ifdef TWO
     if (! parser){
         parser = new NullParser2();
     }

#else
     if (! parser){
         parser = new NullParser();
     }
 #endif
     if (! scanner){
         scanner = new NullScanner();
     }
     if (! printer){
         printer = new AbstractResultPrinter();
     }
    return true;
}

