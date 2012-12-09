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


    taskSize = task->m_vertex_set.size();
    gridSize = grid->m_vertex_set.size();

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

    //    Selection previousSelection;
    //    NodesAndWeights previousSelectionWeights;
    //    ManyCombinations previousCombinations;

    ManyWeightedCombinations previousResults;
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
        //        NodesAndWeights currentWeights;
        ManyWeightedCombinations results;
        InitWeights(currentCombs,results);
        CalculateWeights(results,previousResults);

//        printWeights(currentWeights);
        printWeightedCombinations(results);
        //        previousSelection = currentSelection;
        //        previousSelectionWeights = currentWeights;
        //        previousCombinations = currentCombs;
        previousResults = results;
    }

            Solution ret;
            ret.second = numeric_limits<float>::max();
    //    float max = -1;
    // как то определить найлучший результат
         foreach (WeightedCombination i, previousResults){
             if(i.second.second < ret.second){
                 ret = i.second;
             }
         }
        _result = ret.first;
    return true;
}



//does not work
void Algorithm::CalculateWeights(ManyWeightedCombinations &cur, const ManyWeightedCombinations &prev){
    if (prev.empty()){
        return;
    }

    Result nullResult( taskSize,Graph::null_vertex());
    Solution nullSolution(nullResult, numeric_limits<float>::max());

    for (ManyWeightedCombinations::iterator weightedPair = cur.begin(); weightedPair != cur.end(); ++weightedPair)
    {
        // if not empty - try to calc weights for links
        NodeClusterCombination & comb = (*weightedPair).first;
//        Solution & main = (*weightedPair).second;
            vector<Solution>  solutions;
            // now we have one combination and lets try to get the best prev combination
            for (ManyWeightedCombinations::const_iterator prevIter = prev.begin(); prevIter != prev.end(); ++prevIter)
            {
                WeightedCombination prevPair = *prevIter;
                Solution thisTry = prevPair.second;
                foreach (const NodeClusterPair &p, comb){
                    Edges edges;
                    GetAllInEdgesTask(edges,p.first);
                    foreach (Graph::edge_descriptor e, edges)
                    {
                        Graph::vertex_descriptor srcTask = source(e,*task);
                        Graph::vertex_descriptor srcGrid = thisTry.first.at(srcTask);
                        Graph::vertex_descriptor dstTask = p.first;
                        Graph::vertex_descriptor dstGrid = p.second;
                        Graph::edge_descriptor taskLine = e;
                        if (srcGrid == dstGrid){
                            // the cost of moving data from here to here is nothing
                            thisTry.second += 0;
                            continue;
                        }
                        std::pair<Graph::edge_descriptor, bool> gridLine = edge(srcGrid,dstGrid,*grid);
                        if (gridLine.second)
                        {
                            float w = weight((*task)[taskLine],(*grid)[gridLine.first]);
                            thisTry.second+=w;
                        }
                                //                        qDebug("Line from %ld on %ld to %ld on %ld", srcTask, srcGrid,dstTask,dstGrid);

                    }
                    // put the pair in the result
                    thisTry.first.at(p.first)=p.second;
                    thisTry.second += weight((*task)[p.first].parameters(),(*grid)[p.second].parameters());
                }
                qDebug("%2.3f", thisTry.second);
                solutions.push_back(thisTry);

            } // previous combinations loop
            float max = numeric_limits<float>::max();
            foreach (Solution s, solutions)
            {
                if (s.second < max){
                    (*weightedPair).second = s;
//                    main.second = s.second;
//                    main.first = s.first;
                    max = s.second;
                }
            }
            qDebug("%2.3f",(*weightedPair).second.second);
            qDebug(" ");
    } // current loop
}

void Algorithm::GetAllInEdgesTask(Edges & e, Graph::vertex_descriptor v){
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
//    qDebug("in-edge size for v%ld =%ld ",v,e.size());
}

void Algorithm::InitWeights(const ManyCombinations & combinations ,ManyWeightedCombinations &weights){
    weights.clear();
    Result nullResult( taskSize,Graph::null_vertex());
    Solution nullSolution(nullResult, 0.0f);
//    ClusterWeights nullCluster( grid->m_vertex_set.size(),nullSolution);

    for (ManyCombinations::const_iterator i = combinations.begin(); i!= combinations.end(); ++i){
//        NodesAndWeights w(task->m_vertex_set.size(), nullCluster);
        NodeClusterCombination const & c = *i;
        Solution s(nullSolution);
        s.second = 0;
        for (NodeClusterCombination::const_iterator j = (*i).begin(); j!=(*i).end(); ++j ){
            NodeClusterPair const p = *j;
            Result & r = s.first;
            r.at(p.first) = p.second;

            s.second += weight( (*task)[p.first].parameters(),
                               (*grid)[p.second].parameters() );
        }
        weights.push_back(WeightedCombination(c,s));
    }
//    weights.resize( task->m_vertex_set.size(), nullCluster );
//    for (Selection::const_iterator i = selection.begin(); i!= selection.end(); ++i){
//        Graph::vertex_descriptor node= *i;
//        ClusterWeights cluster(grid->m_vertex_set.size(),nullSolution) ;
//        for ( Graph::vertex_iterator g = grid->m_vertex_set.begin();
//              g != grid->m_vertex_set.end(); ++g ){

//            float we = weight( (*task)[node].parameters(),
//                               (*grid)[*g].parameters() );
//            cluster[*g].first.at(node) =  (*g);
//            cluster[*g].second = we;


//        }
//        weights.at(node)=cluster;
//    }
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
    if (curr.size() > (unsigned int) gridSize ){
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


void Algorithm::printWeightedCombinations(const ManyWeightedCombinations & s){
    for (ManyWeightedCombinations::const_iterator i = s.begin(); i!= s.end(); ++i){
        const WeightedCombination & c = *i;
        QString str = CombinationToQString(c.first);
        const Solution & s = c.second;
        str.append(" = ");
        QString str2 = "" ;
        str2.append(QString::number(s.second));
        str2.append("; ");
        for (unsigned int k =0; k< s.first.size(); k++){
            str2.append("(");
            str2.append(QString::number(k));
            str2.append(",");
            if (s.first.at(k) > (unsigned int) gridSize){
                str2.append("-1");
            }else {
                str2.append( QString::number(s.first.at(k)));
            }
            //                str2.append("; ");
            str2.append(")");
        }
        str2.append("); ");
        str.append(str2);
        qDebug() << str;
    }
}


QString  Algorithm::CombinationToQString(const NodeClusterCombination &c){
    QString s;

    foreach (NodeClusterPair p, c){
        s+="(";
        s+= QString::number(p.first);
        s+= ":";
        s+= QString::number(p.second);
        s+=")";

    }
    return s;
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
