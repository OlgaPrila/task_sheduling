#ifndef DAG_LINE_H
#define DAG_LINE_H


#include <vector>



namespace mapper {
class DAG_node;
class DAG_line
{

public:
    DAG_line(const DAG_line &);
    DAG_line(const DAG_node & from, const  DAG_node & to,
             const std::vector<float> & parameters):
            _from(from),_to(to),_parameters(parameters)
    {}
    DAG_line& operator = (const mapper::DAG_line& line);
    inline const DAG_node & get_from() const{
        return _from;
    }

    inline const DAG_node & get_to() const{
        return _to;
    }

    inline const std::vector<float> & get_parameters() const{
        return _parameters;
    }

    inline const float & get_n_parameter(int n) const{
        return _parameters.at(n);
    }

private:
    DAG_line();
    const DAG_node & _from;
    const DAG_node & _to;
    std::vector<float> _parameters;



};
} //namespace mapper
#endif // DAG_LINE_H
