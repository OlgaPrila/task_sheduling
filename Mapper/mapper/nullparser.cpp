#include "nullparser.h"
#include <QDebug>

using namespace boost;


bool NullParser::parse(PGraph &result){

//    BOOST_CONCEPT_ASSERT(( IncidenceGraphConcept<Graph> ));
//    Configurator::instance().errors().push_back("Not implemeted parsing yet");

   result = new Graph(4);
    // vertex setup
    //node 0
    Graph::vertex_descriptor node = result->m_vertex_set[0];
    (*result)[node].setNumber(0);
    (*result)[node].setLevel(0);
    (*result)[node].parameters().push_back(500.0f);
    //node1
    node = result->m_vertex_set[1];
    (*result)[node].setNumber(1);
    (*result)[node].setLevel(1);
    (*result)[node].parameters().push_back(2000.0f);
    //node2
    node = result->m_vertex_set[2];
    (*result)[node].setNumber(2);
    (*result)[node].setLevel(1);
    (*result)[node].parameters().push_back(100.0f);
    //node3
    node = result->m_vertex_set[3];
    (*result)[node].setNumber(3);
    (*result)[node].setLevel(2);
    (*result)[node].parameters().push_back(100.0f);


    //line initialization

    Graph::edge_descriptor line =  add_edge(0,1,*result).first;
    (*result)[line].push_back(100.0f);
    line = add_edge(0,result->m_vertex_set[2],*result).first;
    (*result)[line].push_back(10.0f);
    line = add_edge(1,3,*result).first;
    (*result)[line].push_back(200.0f);
    line = add_edge(result->m_vertex_set[2],result->m_vertex_set[3],*result).first;
    (*result)[line].push_back(50.0f);

    std::pair<Graph::in_edge_iterator, Graph::in_edge_iterator> p;
    in_edges(result->m_vertex_set[3],*result);
   int i=0;
    while( p.first != p.second){
        i++;
        p.first++;
    }
    qDebug("%d",i);
    return true;
}
