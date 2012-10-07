#ifndef DAG_TREE_H
#define DAG_TREE_H

#include "dag_node.h"

namespace mapper{



class DAG_tree
{
public:
    typedef std::map<int, DAG_node > DAG_map;
    typedef std::pair<int, DAG_node > DAG_pair;
    enum tree_type {line, simple, combined, hard};
    //typedef std::multimap<int, DAG_line > DAG_multimap;


    typedef std::binary_function <std::vector<float>,
    std::vector<float>, float > weight_function;
    typedef std::vector<std::pair<int,int> > result_type;

    DAG_tree(){

    }

    const DAG_map & nodes() const{
        return _nodes;
    }

    void add_node( const DAG_node & node){
        _nodes.insert(DAG_pair(node.number(),node));
    }

    float dag_map(const DAG_tree &clusters,
                        weight_function node_weight,
                        weight_function line_weight,
                        result_type & results
                  ) ;

private:
    DAG_map _nodes;

    int max_level();
    void count_levels();
    tree_type check_type();


};
} // namespace mapper
#endif // DAG_TREE_H
