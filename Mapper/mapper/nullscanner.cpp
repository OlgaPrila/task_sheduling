#include "nullscanner.h"

bool NullScanner::scan(PGraph &result){
     result = new Graph(2);
     // vertex setup
     //node 0
     Graph::vertex_descriptor node = result->m_vertex_set[0];
     (*result)[node].setNumber(0);
     (*result)[node].parameters().push_back(1.0f);
     //node1
     node = result->m_vertex_set[1];
     (*result)[node].setNumber(1);
     (*result)[node].parameters().push_back(0.5f);

     //node2
#define TWO
#ifndef TWO
     node = result->m_vertex_set[2];
     (*result)[node].setNumber(2);
     (*result)[node].parameters().push_back(0.5f);
#endif

     //line initialization

     Graph::edge_descriptor line ;
     line =  add_edge(0,1,*result).first;
     (*result)[line].push_back(0.1f);
     line = add_edge(1,0,*result).first;
     (*result)[line].push_back(0.1f);

     #ifndef TWO
     line = add_edge(1,2,*result).first;
     (*result)[line].push_back(0.05f);
     line = add_edge(0,2,*result).first;
     (*result)[line].push_back(0.1f);
     line = add_edge(2,0,*result).first;
     (*result)[line].push_back(0.1f);
     line = add_edge(2,1,*result).first;
     (*result)[line].push_back(0.05f);
#endif
     return true;
}
