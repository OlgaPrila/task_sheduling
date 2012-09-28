#include "dag_line.h"
#include "dag_node.h"

namespace mapper{

// DAG_line& DAG_line::operator = (const mapper::DAG_line& line) const{
//    _from = line._from;
//    _to = line._to;
//    _parameters = line._parameters;
//    return *this;
//}

DAG_line::DAG_line(const DAG_line & line):
    _from(line._from), _to(line._to),_parameters(line._parameters){}
//{
//        _from = line._from;
//        _to = line._to;
//        _parameters = line._parameters;
//}


} // namespace mapper
