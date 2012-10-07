#include "dag_tree.h"

#include <iostream>

using namespace std;
namespace mapper{




float DAG_tree::dag_map(const DAG_tree &clusters,
                                        weight_function node_weight,
                                        weight_function line_weight,
                                        result_type & result) {
    //tree_type type = check_type();
    return 0;//result_type(1,pair<int,int> (1,1));
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

        for ( map<int,DAG_line>::const_iterator j = i->second.outlines().begin();
              j != i->second.outlines().end(); j++){
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

int DAG_tree::max_level(){
    int max = 0;
    for (DAG_map::const_iterator i = _nodes.begin(); i != _nodes.end(); i++){
//        cout<< i->second.name() << "  " << i->second.level() << endl;
        if( i->second.level() > max) {
            max = i->second.level();
        }
    }
    return max;
}

DAG_tree::tree_type DAG_tree::check_type(){
    count_levels();
    cout << "max level:"<< max_level() << endl;
    cout << "node count" <<_nodes.size() << endl;
    vector<int> count(7,0);
    for (DAG_map::const_iterator i = _nodes.begin(); i != _nodes.end(); i++){
        count[i->second.level()]++;
    }
    int j = 0;
    bool flag_line = true;
    for (vector<int>::const_iterator i = count.begin(); i != count.end(); i++){
        cout << j++ <<": "<< *i << endl ;
        if (*i >1 ) {
            flag_line = flag_line && false;
            break;
        }
    }
    if (flag_line == true) {
        return line;
    }


    return simple;

}

}// namespace

