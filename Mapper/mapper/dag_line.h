#ifndef DAG_LINE_H
#define DAG_LINE_H


#include <vector>



namespace mapper {
class DAG_line
{

public:
    DAG_line( const DAG_line & line):
        _from(line._from), _to(line._to),_parameters(line._parameters){}

    DAG_line(const int & from, const  int & to,
             const std::vector<float> & parameters):
        _from(from),_to(to),_parameters(parameters)
    {}

    const int from() const{
        return _from;
    }

    const int to() const{
        return _to;
    }

    const std::vector<float> & parameters() const{
        return _parameters;
    }

    const float parameter(int n) const{
        return _parameters.at(n);
    }

private:
    DAG_line();
    int  _from;
    int  _to;
    std::vector<float> _parameters;



};
} //namespace mapper
#endif // DAG_LINE_H
