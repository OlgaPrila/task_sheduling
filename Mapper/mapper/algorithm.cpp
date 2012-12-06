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
    //    инициализируем набор уровней
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

    for (unsigned int i= 0;i<levels.size(); ++i){
        qDebug("levels[%d]=%d",i,levels.at(i));
    }

    Selection previousSelection;
    NodesAndWeights previousSelectionWeights;

    // main loop
    for (int level= 0; level < maxLevel +1; ++level ){
        Selection currentSelection;
        FillSelectionWithLevel(currentSelection,level);
        if (currentSelection.size() != levels[level]){
            qDebug("какая то лажа ");
            abort();
        }
        ManyCombinations currentCombs;
        CreateCombinations(currentCombs,currentSelection);
        NodesAndWeights currentWeights;
        InitNodesAndWeights(currentSelection,currentWeights);
        CalculateWeights(currentCombs,currentWeights,previousSelectionWeights);

        printWeights(currentWeights);

        previousSelection = currentSelection;
        previousSelectionWeights = currentWeights;

    }

//    Result ret;
//    float max = -1;
    // как то определить найлучший результат
    //     for (Selection::const_iterator i = previousSelection.begin();
    //          i!=previousSelectionWeights.end(); ++i){

    //     }

    //    result = solutions.front().first;
    return true;
}



//does not work
void Algorithm::CalculateWeights(ManyCombinations &comb, NodesAndWeights &weights, const NodesAndWeights &prevSet){
    if (prevSet.empty()){
        return;
    }
    // создаем вектор весов количеством гридсайз

//    NodesAndWeights

    // if not empty - try to calc weights for links
    for (ManyCombinations::const_iterator allIter = comb.begin(); allIter != comb.end(); ++allIter){

        const NodeClusterCombination & c = *allIter;
        for (NodeClusterCombination::const_iterator one= c.begin(); one!= c.end(); ++one){
            const NodeClusterPair & par =*one;

            Edges edges;
            float lineWeightSum = 0;
           GetAllInEdgesTask(edges,par.first);
           for (Edges::iterator e = edges.begin(); e!= edges.end(); ++e){
               Graph::vertex_descriptor v = source(*e,*task);
               float prevNodeWeight = 0;
               Graph::vertex_descriptor prevNodeCluster = -1;
                // тут надо посчитать ГридСайз вариантов для одного узла

//               float weightConnection = weight((*task)[]
           }
            // need to take every possible pair of this combination and their previous
//            мерджим, и записываем в вектор весов по индексу второго элемента
            // need to calculate every possible pair weight

//            ага

        }// one combination loop

    }// all combinations loop

    // here we must have all combinations, also we must save them all.
//    отсеиваем
}

void Algorithm::GetAllInEdgesTask(Edges e, Graph::vertex_descriptor v){
//   std::pair<Graph::in_edge_iterator, Graph::in_edge_iterator> p;
//   in_edges(v,*task);
//   while( p.first != p.second){
//       e.push_back( *(p.first++) );
//   }
    for (Graph::vertex_iterator u = task->m_vertex_set.begin(); u!= task->m_vertex_set.end(); ++u){
        std::pair<Graph::edge_descriptor, bool> p = edge(*u,v,*task);
        if(p.second){
            e.push_back(p.first);
        }

    }
    qDebug("in-edge size for v%ld =%ld ",v,e.size());
}

void Algorithm::InitNodesAndWeights(const Selection & selection ,NodesAndWeights &weights){
    weights.clear();
    Result nullResult( task->m_vertex_set.size(),Graph::null_vertex());
    Solution nullSolution(nullResult, 0.0f);
    ClusterWeights nullCluster( grid->m_vertex_set.size(),nullSolution);
    weights.resize( task->m_vertex_set.size(), nullCluster );
    for (Selection::const_iterator i = selection.begin(); i!= selection.end(); ++i){
        Graph::vertex_descriptor node= *i;
        ClusterWeights cluster(grid->m_vertex_set.size(),nullSolution) ;
        for ( Graph::vertex_iterator g = grid->m_vertex_set.begin();
              g != grid->m_vertex_set.end(); ++g ){

            float we = weight( (*task)[node].parameters(),
                                   (*grid)[*g].parameters() );
            cluster[*g].first.at(node) =  (*g);
            cluster[*g].second = we;


        }
        weights.at(node)=cluster;
    }
}

//работает
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
//работает
void  Algorithm::CreateCombinations(ManyCombinations &comb, const Selection &curr){
    if (curr.size() > (unsigned int) grid->m_vertex_set.size() ){
        qDebug("какая то лажа ");
        abort();
    }
    ManySubsets subsets;
    // возвращает все к-подмножества
    GetAllKSubsetsGrid(subsets,curr.size());

    for (ManySubsets::iterator j = subsets.begin(); j!= subsets.end(); ++j){
        Subset ss = *j;
        //        для каждой допустимой перестановки к-подмножества создаем комбинацию
        do {
            NodeClusterCombination combination;
//            qDebug( "Begin combo");

            if (curr.size() != ss.size()){
                qDebug("какая то лажа ");
                abort();
            }

            Selection::const_iterator selectionIter = curr.begin();
            Subset::iterator subsetIter = ss.begin();
            for (unsigned int i = 0; i< curr.size();i++){
                NodeClusterPair pair(*selectionIter,*subsetIter);
                ++selectionIter;
                ++subsetIter;
//                qDebug("Pair %ld , %ld", pair.first, pair.second );
                combination.push_back(pair);
            }

//            qDebug( "End combo");
            comb.push_back(combination);
        }   while(next_permutation(ss.begin(), ss.end()));
    }
    qDebug("Combinations count %ld", comb.size());
}

//работает но  выводит только вес
void Algorithm::printWeights(const NodesAndWeights &weights){
    qDebug("printWeights %ld", weights.size());
    for (unsigned int i=0; i!= weights.size(); ++i ){
        QString str = "Node "+ QString::number(i) + ":";
        for(unsigned int j = 0; j != weights.at(i).size(); ++j){
            QString str2 = "(n=" +QString::number(j) + " w=" ;
            Solution s = weights.at(i).at(j);
            str2.append(QString::number(s.second));
                str2.append("; ");
            for (unsigned int k =0; k< s.first.size(); k++){
                str2.append("(");
                str2.append(QString::number(k));
                str2.append(",");
                if (s.first.at(k) > (unsigned int) grid->m_vertex_set.size()){
                    str2.append("-1");
                }else {
                    str2.append( QString::number(s.first.at(k)));
                }
//                str2.append("; ");
                str2.append(")");
            }
            str2.append("); ");
            str.append(str2);
        }
        qDebug() << str;
    }
}
//работает
void Algorithm::GetAllSubsets(ManySubsets &comb,const Selection & s){
    for (int i = 0; i < pow(2,s.size()) +1; ++i){
        Subset ss;
        for (unsigned int j=1; j < s.size(); ++j){
            int k = 1 << j;
            if ( (i & k) != 0){
                ss.push_back(s[j]);
            }
        }
        comb.push_back(ss);
    }
}

// работает
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
    int size = grid->m_vertex_set.size();
    // с единицы потому что первый элемент массива количество
    for (int magicIndex = 1; magicIndex <  magic[K][0]+1; ++magicIndex){
        Subset ss;
        int magicNumber = magic[K][magicIndex];
        int max = pow(2,size) -1; // max allowed
        if (magicNumber > max) {
            continue;
        }
        for (int i =0; i< size; i++ ){
            int k = 1 << i;
            int result = magicNumber & k ;
            if (result != 0){
                ss.push_back(grid->m_vertex_set[i]);
            }
        }
        subsets.push_back(ss);
//     ?   qDebug ("K = %d, index = %d, magic number = %d, size = %ld",K,magicIndex,magic[K][magicIndex],ss.size());
    }
//    qDebug("K = %d, size = %ld",K,subsets.size());
}

float Algorithm::weight(vector<float> a, vector<float> b){
    return a[0]/b[0];
}
