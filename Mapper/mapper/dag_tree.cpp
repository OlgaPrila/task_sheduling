#include "dag_tree.h"

#include <iostream>

using namespace std;
namespace mapper{


DAG_tree::result_type DAG_tree::dag_map(const DAG_tree &clusters,
                                        weight_function node_weight,
                                        weight_function line_weight) {
    count_levels();
    return result_type(1,pair<int,int> (1,1));
}

//result_type DAG_tree::dag_map(const DAG_tree &clusters,
//                              weight_function node_weight,
//                              weight_function line_weight) const{

//}

void DAG_tree::count_levels(){
    cout << "Start counting levels" << endl;
    for (DAG_map::iterator i = _nodes.begin(); i != _nodes.end(); i++){
        // initiating levels;
        i->second.setLevel(0);

    }
    for (DAG_map::const_iterator i = _nodes.begin(); i != _nodes.end(); i++){
        int level = i->second.level() +1;
        cout << "node " << i->second.name() <<  "; level+1 " << level << endl;

        for ( map<int,DAG_line>::const_iterator j = i->second.lines().begin();
             j != i->second.lines().end(); j++){
            //inc levels only if current level is lower
            DAG_node & node = _nodes.at(j->second.to());
            if( node.level() < level){
                node.setLevel(level);
            }

        }

    }
    for (DAG_map::const_iterator i = _nodes.begin(); i != _nodes.end(); i++){
        // initiating levels;
        cout<< i->second.name() << "  " << i->second.level() << endl;
    }

}

}

