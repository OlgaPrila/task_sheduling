#include "algorithm.h"
#include "configurator.h"

#include "math.h"

#include <iostream>
#include <limits>
#include <vector>
#include <set>
#include <map>

using namespace std;
using namespace boost;

#define DEBUG
#ifdef DEBUG
#include <QDebug>
#endif




bool Algorithm::process( Graph * _task, Graph * _grid, Result & _result){
    if (! _task || !_grid ){
        Configurator::instance().errors().push_back("No task or grid provided");
        return 0;
    }

    this->grid = _grid;
    this->task = _task;


    int taskSize = task->m_vertex_set.size();
    int gridSize = grid->m_vertex_set.size();
    levels.resize(taskSize);
    int maxLevel =-1;
    for (Graph::vertex_iterator vertexIterator=task->m_vertex_set.begin();
         vertexIterator != task->m_vertex_set.end();
         ++ vertexIterator){
        int lev = (*task)[*vertexIterator].level();
        levels[lev]++;
        if(lev > maxLevel) {
            maxLevel = lev;
        }
    }
    levels.resize(maxLevel+1);
    for (int i= 0;i<levels.size(); ++i){
        qDebug("levels[%d]=%d",i,levels.at(i));
    }

    Selection previousSelection;
    NodesAndWeights previousSelectionWeights;
    for (int level= 0; level < maxLevel; ++level ){
        Selection currentSelection;
        FillSelectionWithLevel(currentSelection,level);
        if (currentSelection.size()!=levels[level]){
            qDebug("какая то лажа ");
            abort();
        }
        ManyCombinations currentCombs;
        CreateCombinations(currentCombs,currentSelection);
        NodesAndWeights currentWeights;
        CalculateWeights(currentCombs,currentWeights,previousSelectionWeights);

        printWeights(currentWeights);

        previousSelection = currentSelection;
        previousSelectionWeights = currentWeights;

    }

    Result ret;
    float max = -1;
    //     for (Selection::const_iterator i = previousSelection.begin();
    //          i!=previousSelectionWeights.end(); ++i){

    //     }

    //    result = solutions.front().first;
    return true;
}


void Algorithm::FillSelectionWithLevel(Selection &select, int level){
    for (Graph::vertex_iterator vertexIterator=this->task->m_vertex_set.begin();
         vertexIterator != this->task->m_vertex_set.end();
         ++ vertexIterator){
        int lev = (*task)[*vertexIterator].level();
        if (lev == level){
            select.push_back(*vertexIterator);
        }
    }
}

void  Algorithm::CreateCombinations(ManyCombinations &comb, Selection &curr){
    if (curr.size() > grid->m_vertex_set.size()){
        qDebug("какая то лажа ");
        abort();
    }
    ManySubsets subsets;
    GetAllKSubsetsGrid(subsets,curr.size());
    for (ManySubsets::iterator j = subsets.begin(); j!= subsets.end(); ++j){
        qDebug( "Begin combo");
        NodeClusterCombination combination;
        Subset ss = *j;
        if (curr.size() != ss.size()){
            qDebug("какая то лажа ");
            abort();
        }
        Selection::iterator selectionIter = curr.begin();
        Subset::iterator subsetIter = ss.begin();
        for (int i = 0; i< curr.size();i++){
            NodeClusterPair pair(*selectionIter,*subsetIter);
            ++selectionIter;
            ++subsetIter;
            qDebug("Pair %d , %d", pair.first, pair.second );
            combination.push_back(pair);
        }
        qDebug( "End combo");
        comb.push_back(combination);
    }
    qDebug("Combinations count %d", comb.size());
}



void Algorithm::CalculateWeights(ManyCombinations &comb, NodesAndWeights &weights, const NodesAndWeights &prevSet){

}

void Algorithm::printWeights(NodesAndWeights &weights){
    qDebug("printWeights");
    for (NodesAndWeights::iterator i=weights.begin(); i!= weights.end(); ++i ){
        QString str = "Node "+ QString::number((*i).first) + ":";
        for(ClusterWeights::const_iterator j = (*i).second.begin(); j!=(*i).second.end();++j){
            QString str2 = "(for " +QString::number((*j).first) + "weight=" ;
            Solution s = (*j).second;
            str2.append(QString::number(s.second));
            str2.append("); ");
        }
        qDebug() << str;
    }
}

void Algorithm::GetAllSubsets(ManySubsets &comb,const Selection & s){
    for (int i = 0; i < pow(2,s.size()) +1; ++i){
        Subset ss;
        for (int j=1; j < s.size(); ++j){
            int k = 1 << j;
            if (i & k != 0){
                ss.push_back(s[j]);
            }
        }
        comb.push_back(ss);
    }
}


// только до К =5 , при условии что в гриде не больше 5 вершин.
void Algorithm::GetAllKSubsetsGrid(ManySubsets &subsets, int K){
    //    только до 2 в  5
    const int magic[][11] = {
        { 0,  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},   // 0 единиц в числе - 0 чисел
        { 5,  0x01,0x02,0x04,0x08,0x10,0x00,0x00,0x00,0x00,0x00},   // 1 единица в числе - 5 чисел
        { 10, 0x03,0x05,0x06,0x09,0x0A,0x0C,0x11,0x12,0x14,0x18},   // 2   - 10
        { 10, 0x07,0x0B,0x0D,0x0E,0x13,0x15,0x16,0x19,0x1A,0x1C},    // 3   - 10
        { 5,  0x0F,0x17,0x1B,0x1D,0x1E,0x00,0x00,0x00,0x00,0x00},
        { 1,  0x1F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}
    };
    if (K > 5 || grid->m_vertex_set.size() > 5 || K > grid->m_vertex_set.size()){
        qDebug("какая то лажа ");
        abort();
    }
    for (int j=0; j < grid->m_vertex_set.size(); ++j){
        Subset ss;
        for (int i = 0; i < magic[K][0]; ++i){
            int k = 1 << j;
            int z = magic[K][i +1];
            if (z & k != 0){
                ss.push_back(grid->m_vertex_set[j]);
            }

        }
        subsets.push_back(ss);
        qDebug ("K = %d, i = %d, size = %d ",K,j,ss.size());
    }
    qDebug("K = %d, size = %d",K,subsets.size());
}

float Algorithm::weight(vector<float> a, vector<float> b){
    return a[0]/b[0];
}
