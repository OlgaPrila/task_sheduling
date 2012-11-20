#ifndef GRAPH_H
#define GRAPH_H

#include <string>

#include <boost/graph/adjacency_list.hpp>

typedef boost::adjacency_list
<
  boost::vecS,
  boost::vecS,
  boost::directedS,
  boost::property<boost::vertex_name_t,std::string>,
  boost::property<boost::edge_weight_t,float>,
  boost::property<boost::graph_name_t,std::string>
> Graph;

#endif // GRAPH_H
