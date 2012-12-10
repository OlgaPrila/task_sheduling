#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "configurator.h"

#include <map>
#include <set>

#include <QString>

class Algorithm : public AbstractAlgorithm
{
    // result -array of pairs
    // solution  - pair of result and weight
public:
    Algorithm(){}
    virtual ~Algorithm(){}
    virtual bool process( Graph * _task,
                          Graph * _grid, Result & _result);
protected:
    typedef std::pair<Result,float>   Solution;

    typedef std::vector<Graph::vertex_descriptor> Nodes;
    typedef std::vector<Graph::edge_descriptor> Edges;

    typedef std::pair<Graph::vertex_descriptor, Graph::vertex_descriptor> NodeClusterPair;
    typedef std::vector<NodeClusterPair> NodeClusterCombination;
    typedef std::vector<NodeClusterCombination > ManyCombinations;

    typedef std::pair<NodeClusterCombination, Solution> WeightedCombination;
    typedef std::vector<WeightedCombination> ManyWeightedCombinations;

    typedef std::vector<Graph::vertex_descriptor> Subset;
    typedef std::vector<Subset> ManySubsets;


    virtual float LineWeight(const NodeClusterPair & src, const NodeClusterPair & dst);
    virtual float weight(std::vector <float> a, std::vector<float> b);


    Graph* task;
    Graph* grid;

    int taskSize;
    int gridSize;
    std::vector<unsigned int> levels;
    int maxLevel;
private:
    void FillSelectionWithLevel(Nodes & select, int level);
    void CreateCombinations (ManyCombinations & comb, const Nodes & curr);
    void GetAllSubsets(ManySubsets &comb, const Nodes &s);
    void CalculateWeights(ManyWeightedCombinations &cur, const ManyWeightedCombinations &prev);
//    void printWeights(const NodesAndWeights& weights);
    void printWeightedCombinations( const ManyWeightedCombinations &s);
    QString CombinationToQString(const NodeClusterCombination &c);
//    void CalculateOnlyNodesWeights(const ManyCombinations &comb, NodesAndWeights &weights);
    void InitWeights (const ManyCombinations &selection, ManyWeightedCombinations & weights);
    void GetAllKSubsetsGrid(ManySubsets &comb, int K);
    void GetAllInEdgesTask(Edges &e, Graph::vertex_descriptor v);


};



#endif // ALGORITHM_H
