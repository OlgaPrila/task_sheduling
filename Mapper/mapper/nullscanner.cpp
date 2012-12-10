#include "nullscanner.h"

bool NullScanner::scan(PGraph &result){

#ifdef TWO_CLUSTERS
const int SIZE  = (2);
#else
const int SIZE = (3);
#endif

     result = new Graph(SIZE);
     // vertex setup
     //node 0
     (*result)[0].setNumber(0);
     (*result)[0].parameters().push_back(1.0f);
     //node1
//     node = result->m_vertex_set[1];
     (*result)[1].setNumber(1);
     (*result)[1].parameters().push_back(0.5f);

     //node2
#ifndef TWO_CLUSTERS
//     node = result->m_vertex_set[2];
     (*result)[2].setNumber(2);
     (*result)[2].parameters().push_back(0.5f);
#endif

     //line initialization

     Graph::edge_descriptor line ;
     line =  add_edge(0,1,*result).first;
     (*result)[line].push_back(0.1f);
     line = add_edge(1,0,*result).first;
     (*result)[line].push_back(0.1f);

#ifndef TWO_CLUSTERS
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
