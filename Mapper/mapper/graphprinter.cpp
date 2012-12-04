#include "graphprinter.h"

//#include <QDebug>

#include "configurator.h"

#include <iostream>

GraphPrinter::GraphPrinter()
{
}

void GraphPrinter::print(const Graph *graph){
    if (! graph) {
        Configurator::instance().errors().push_back("No graph to print");
        return;
        //abort();
    }
    for (Graph::vertex_iterator vertexIterator=graph->m_vertex_set.begin();
         vertexIterator != graph->m_vertex_set.end();
         ++ vertexIterator){
        Graph::vertex_descriptor node = *vertexIterator;
        const  Vertex &  v= (*graph)[node];
        std::cout << v.number() << " level= " << v.level() << " with params =";
        for (std::vector<float>::const_iterator i = v.parameters().begin();
             i!= v.parameters().end(); ++i){
            std::cout << " "<< *i << ";" ;
        }
        std::cout << std::endl;
    }
//    for (Graph::edge_iterator edgeIterator=graph->m_num_edges.begin();
//         edgeIterator != graph->m_num_edges.end();
//         ++ edgeIterator){
//        Graph::edge_descriptor node = *edgeIterator;
//        //const  Vertex &  v= (*graph)[node];
//        qDebug("|%d with level %d and parameter 1=%2.2f",,v.parameter(0));
//        //for (Graph::edge_iterator graph->m_num_edges,)


//    }

}
