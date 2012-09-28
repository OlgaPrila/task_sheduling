#ifndef DAG_NODE_H
#define DAG_NODE_H

#include <vector>
#include <string>

#include "dag_line.h"

namespace mapper {

class DAG_node
{
public:
    DAG_node(int number,const std::string & name,  const std::vector<float> & parameters):
        _number(number), _name(name), _parameters(parameters){}
    DAG_node(const DAG_node & node):
        _number(node._number),
        _name(node._name),
        _parameters(node._parameters),
        _lines(node._lines)
    {}


    inline void add_DAG_line(const DAG_line & new_line){
        _lines.push_back(new_line);
    }

    inline int get_number() const{
        return _number;
    }
    const std::string & get_name() const{
        return _name;
    }
    const std::vector<float> & get_parameters() const{
        return _parameters;
    }
    const float get_n_parameter(int n) const {
        return _parameters.at(n);
    }
    const std::vector<DAG_line> & get_lines() const{
        return _lines;
    }
    const DAG_line & get_n_line(int n){
        return _lines.at(n);
    }


private:
    DAG_node();
    int _number;
    std::string _name;
    std::vector<float> _parameters;
    std::vector<DAG_line> _lines;
    /*
  * another params
  * name of executable ? if needed
  */
};
} //namespace mapper
#endif // DAG_NODE_H
