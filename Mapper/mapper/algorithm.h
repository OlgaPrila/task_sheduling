#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "configurator.h"

#include <map>
#include <set>

class Algorithm : public AbstractAlgorithm
{
    // result -array of pairs
    // solution  - pair of result and weight
    typedef std::pair<Result,float>   Solution;
    // array of weights of node - cluster pairs
    // one node -all clusters
    typedef std::vector<Solution>  ClusterWeights;
    //weights of all
    typedef std::vector<ClusterWeights> NodesAndWeights;

    typedef std::vector<Graph::vertex_descriptor> Selection;

    typedef std::vector<float> Weights;

    typedef std::pair<Graph::vertex_descriptor, Graph::vertex_descriptor> NodeClusterPair;
    typedef std::vector<NodeClusterPair> NodeClusterCombination;
    typedef std::vector<NodeClusterCombination > ManyCombinations;
    typedef std::vector<Graph::vertex_descriptor> Subset;
    typedef std::vector<Subset> ManySubsets;


public:
    Algorithm(){}
    virtual ~Algorithm(){}
    virtual bool process( Graph * _task,
                          Graph * _grid, Result & _result);
private:
    void FillSelectionWithLevel(Selection & select, int level);
    void CreateCombinations (ManyCombinations & comb, const Selection & curr);
    void GetAllSubsets(ManySubsets &comb, const Selection &s);
    void CalculateWeights (ManyCombinations & comb, NodesAndWeights & weights, const NodesAndWeights & prevSet);
    void printWeights(const NodesAndWeights& weights);
    void CalculateOnlyNodesWeights(const ManyCombinations &comb, NodesAndWeights &weights);
    void InitNodesAndWeights (const Selection & selection, NodesAndWeights & weights);
    void GetAllKSubsetsGrid(ManySubsets &comb, int K);
    float weight(std::vector <float> a, std::vector<float> b);
    Graph* task;
    Graph* grid;
    std::vector<unsigned int> levels;
    int maxLevel;
};



#endif // ALGORITHM_H
