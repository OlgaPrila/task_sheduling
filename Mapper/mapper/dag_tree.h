#ifndef DAG_TREE_H
#define DAG_TREE_H

#include "dag_node.h"

namespace mapper{



class DAG_tree
{
public:
    typedef std::map<int, DAG_node > DAG_map;
    typedef std::pair<int, DAG_node > DAG_pair;

    //typedef std::multimap<int, DAG_line > DAG_multimap;


    typedef std::binary_function <std::vector<float>,
    std::vector<float>, float > weight_function;
    typedef std::vector<std::pair<int,int> > result_type;

    DAG_tree(){

    }

    const DAG_map & nodes() const;

    void add_node( const DAG_node & node){
        _nodes.insert(DAG_pair(node.number(),node));
    }

    result_type dag_map(const DAG_tree &clusters,
                        weight_function node_weight,
                        weight_function line_weight) ;

private:
    DAG_map _nodes;

    void count_levels();
    //DAG_multimap _lines;

};
} // namespace mapper
#endif // DAG_TREE_H
