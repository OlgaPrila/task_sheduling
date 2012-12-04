#ifndef GRAPH_H
#define GRAPH_H

#include <string>

#include <boost/graph/adjacency_matrix.hpp>

class Vertex{
public :
    Vertex():_level(0){}
    Vertex(int number, const std::vector<float> & parameters ):
        _number(number),
        _parameters(parameters),
        _level(0)
    {}
    Vertex(const Vertex & node):
        _number(node._number),
        _parameters(node._parameters),
        _level(node._level)
    {}

    bool operator=(const Vertex &v){
        _number = v._number;
        _parameters = v._parameters;
        _level = v._level;
        return true;
    }

    int number() const{
        return _number;
    }
    void setNumber(int i){
        _number = i;
    }

    std::vector<float> & parameters() {
        return _parameters;
    }
    const std::vector<float> & parameters() const{
        return _parameters;
    }
    float parameter(int n) const {
        return _parameters.at(n);
    }
    int level() const{
        return _level;
    }

    void setLevel(int l){
        _level = l;
    }

private:

    int _number;
    std::vector<float> _parameters;
    int _level;
};
/*
class Line{
public:
    Line();
    Line( const Line & line):
         _parameters(line._parameters){}

     Line(const std::vector<float> & parameters):
         _parameters(parameters)
     {}

     const std::vector<float> & parameters() const{
         return _parameters;
     }

     float parameter(int n) const{
         return _parameters.at(n);
     }

 private:
     std::vector<float> _parameters;
};
*/
typedef boost::adjacency_matrix
<
boost::directedS,   // направленный граф
Vertex,             // property блоков
std::vector<float>,               // property потоков
std::string         // property графа - имя
> Graph, * PGraph;



#endif // GRAPH_H
