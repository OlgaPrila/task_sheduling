#include "timebasedalgorithm.h"

float TimeBasedAlgorithm::LineWeight(const NodeClusterPair &src,
                                     const NodeClusterPair &dst){
    float ret = 0;
    //some strange circumstances
    int diff = (*task)[dst.first].level() - (*task)[src.first].level();
    if (diff > 1  ) {
        float weightLine = Algorithm::LineWeight(src,dst);
        // somehow calculate weight of another lines.
        float anotherlineWeight = 0;
        if ( weightLine > anotherlineWeight ){
            ret = weightLine - anotherlineWeight;
        }
        std::cerr <<  " Unhandled situation with different levels "  << std::endl;
//        abort();

    }else
    {
       ret = Algorithm::LineWeight(src,dst);
    }
    return ret;
}
