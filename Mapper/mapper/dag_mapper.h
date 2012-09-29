#ifndef DAG_MAPPER_H
#define DAG_MAPPER_H

#include "dag_node.h"

namespace mapper{

    typedef std::binary_function <std::vector<float>,
        std::vector<float>, float > weight_function;
    DAG_node map(const DAG_node & dag, const DAG_node & clusters,
                        weight_function node, weight_function line );

} //namespace mapper
#endif // DAG_MAPPER_H
