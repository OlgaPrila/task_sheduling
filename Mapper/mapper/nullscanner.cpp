#include "nullscanner.h"

bool NullScanner::scan(PGraph &result){
     result = new Graph(3);
     // vertex setup
     //node 0
     Graph::vertex_descriptor node = result->m_vertex_set[0];
     (*result)[node].setNumber(0);
     (*result)[node].parameters().push_back(100.0f);
     //node1
     node = result->m_vertex_set[1];
     (*result)[node].setNumber(1);
     (*result)[node].parameters().push_back(50.0f);
     //node2
     node = result->m_vertex_set[2];
     (*result)[node].setNumber(2);
     (*result)[node].parameters().push_back(50.0f);


     //line initialization

     Graph::edge_descriptor line ;
     line =  add_edge(0,1,*result).first;
     (*result)[line].push_back(10.0f);
     line = add_edge(0,2,*result).first;
     (*result)[line].push_back(10.0f);
     line = add_edge(1,0,*result).first;
     (*result)[line].push_back(10.0f);
     line = add_edge(1,2,*result).first;
     (*result)[line].push_back(5.0f);
     line = add_edge(2,0,*result).first;
     (*result)[line].push_back(10.0f);
     line = add_edge(2,1,*result).first;
     (*result)[line].push_back(5.0f);
     return true;
}
