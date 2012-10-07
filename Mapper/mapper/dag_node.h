#ifndef DAG_NODE_H
#define DAG_NODE_H


#include <map>
#include <string>
#include <vector>

#include "dag_line.h"

namespace mapper {

class DAG_node
{
public:
    DAG_node(int number,const std::string & name,
             const std::vector<float> & parameters):
        _number(number),
        _name(name),
        _parameters(parameters),
        _level(0)
    {}
    DAG_node(const DAG_node & node):
        _number(node._number),
        _name(node._name),
        _parameters(node._parameters),
        _outlines(node._outlines),
        _inlines(node._inlines),
        _level(node._level)
    {}


    inline void add_DAG_outline(const DAG_line & new_line){
        _outlines.insert(std::pair<int,DAG_line >(new_line.to(), new_line));
    }
    inline void add_DAG_inline(const DAG_line & new_line){
        _inlines.insert(std::pair<int,DAG_line >(new_line.from(), new_line));
    }
    int number() const{
        return _number;
    }
    const std::string & name() const{
        return _name;
    }
    const std::vector<float> & parameters() const{
        return _parameters;
    }
    const float parameter(int n) const {
        return _parameters.at(n);
    }
    const std::map<int,DAG_line> & outlines() const{
        return _outlines;
    }
    const DAG_line & outline(int n) const{
        return _outlines.at(n);
    }
    const std::map<int,DAG_line> & inlines() const{
        return _inlines;
    }
    const DAG_line & in_line(int n) const{
        return _inlines.at(n);
    }
    int level() const{
        return _level;
    }

    void setLevel(int l){
        _level = l;
    }

private:
    DAG_node();
    int _number;

    std::string _name;
    std::vector<float> _parameters;
    std::map<int,DAG_line> _outlines;
    std::map<int,DAG_line> _inlines;
    int _level;
    /*
  * another params
  * name of executable ? if needed
  */
};
} //namespace mapper
#endif // DAG_NODE_H
