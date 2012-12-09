#include "nullparser2.h"
#include <QDebug>

using namespace boost;


bool NullParser2::parse(PGraph &result){

//    BOOST_CONCEPT_ASSERT(( IncidenceGraphConcept<Graph> ));
//    Configurator::instance().errors().push_back("Not implemeted parsing yet");

   result = new Graph(4);
    // vertex setup
    //node 0
    Graph::vertex_descriptor node = result->m_vertex_set[0];
    (*result)[node].setNumber(0);
    (*result)[node].setLevel(0);
    (*result)[node].parameters().push_back(1.0f);
    //node1
    node = result->m_vertex_set[1];
    (*result)[node].setNumber(1);
    (*result)[node].setLevel(0);
    (*result)[node].parameters().push_back(5.0f);
    //node2
    node = result->m_vertex_set[2];
    (*result)[node].setNumber(2);
    (*result)[node].setLevel(1);
    (*result)[node].parameters().push_back(2.0f);
    //node3
    node = result->m_vertex_set[3];
    (*result)[node].setNumber(3);
    (*result)[node].setLevel(2);
    (*result)[node].parameters().push_back(2.0f);


    //line initialization

    Graph::edge_descriptor line =  add_edge(0,2,*result).first;
    (*result)[line].push_back(1.0f);
    line = add_edge(0,3,*result).first;
    (*result)[line].push_back(1.0f);
    line = add_edge(1,2,*result).first;
    (*result)[line].push_back(0.1f);
    line = add_edge(2,3,*result).first;
    (*result)[line].push_back(0.2f);

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
