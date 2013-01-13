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
    //инициализация свойств класса
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
    // результат размещения предыдущего набора
    ManyWeightedCombinations previousResults;
    // main loop
    //    выполняем размещение для каждого набора
    for (int level= 0; level < maxLevel +1; ++level ){
        Nodes currentSelection;
        //        выделяем набор
        FillSelectionWithLevel(currentSelection,level);
        if (currentSelection.size() != levels[level]){
            qDebug("какая то лажа ");
            abort();
        }
        ManyCombinations currentCombs;
        //        создаем все возможные размещения
        CreateCombinations(currentCombs,currentSelection);

        //        подготавливаем веса размещений
//      вычисляем вес размещения блока на кластере без учета предыдущих блоков
        ManyWeightedCombinations results;
        InitWeights(currentCombs,results);
//     пересчитываем веса размещений  принимая во внимание размещение предыдущих блоков
        CalculateWeights(results,previousResults);
// выводим результат
        printWeightedCombinations(results);
//    резульатт текущего размещеняи становится результатом предыдущего размещения на следующем шаге алгоритма
        previousResults = results;
    }

    Solution ret;
    ret.second = numeric_limits<float>::max();
    // выбираем лучшее размещение
    foreach (WeightedCombination i, previousResults){
        if(i.second.second < ret.second){
            ret = i.second;
        }
    }
//    помещаем его в результат
    _result = ret.first;
    return true;
}

// виртуальный метод для нахождения "веса" линии
// переопределение его позволяет "играться" с алгоритмом в классах-наследниках
float Algorithm::LineWeight(const NodeClusterPair & src,const NodeClusterPair& dst){
    float ret = 0;
    if (src.second == dst.second){
        // the cost of moving data from here to here is nothing
        ret = 0;
    }
    std::pair<Graph::edge_descriptor, bool> taskLine = edge(src.first,dst.first,*task);
    std::pair<Graph::edge_descriptor, bool> gridLine = edge(src.second,dst.second,*grid);
    if (gridLine.second && taskLine.second)
    {
        ret = weight((*task)[taskLine.first],(*grid)[gridLine.first]);
    }
    return ret;
}



// подсчет "веса" размещения с учетом предыдущих
void Algorithm::CalculateWeights(ManyWeightedCombinations &cur, const ManyWeightedCombinations &prev){
    if (prev.empty()){
        return;
    }
//  для каждого текущего размещения
    for (ManyWeightedCombinations::iterator weightedPair = cur.begin(); weightedPair != cur.end(); ++weightedPair)
    {
        // if not empty - try to calc weights for links
        NodeClusterCombination & comb = (*weightedPair).first;
        //        Solution & main = (*weightedPair).second;
        vector<Solution>  solutions;
        // now we have one combination and lets try to get the best prev combination

//        перебираем все предыдущие размещения
        for (ManyWeightedCombinations::const_iterator prevIter = prev.begin(); prevIter != prev.end(); ++prevIter)
        {
            WeightedCombination prevPair = *prevIter;
            Solution thisTry = prevPair.second;
//вычисляем суммарный вес всех линий
            foreach (const NodeClusterPair &dst, comb){
                Edges edges;
                GetAllInEdgesTask(edges,dst.first);
                foreach (Graph::edge_descriptor e, edges)
                {
                    Graph::vertex_descriptor srcTask = source(e,*task);
                    Graph::vertex_descriptor srcGrid = thisTry.first.at(srcTask);
                    NodeClusterPair src(srcTask,srcGrid);
                    float w = LineWeight(src,dst);
                    thisTry.second += w;
                    //                        qDebug("Line from %ld on %ld to %ld on %ld", srcTask, srcGrid,dstTask,dstGrid);

                }
                // put the pair in the result
                thisTry.first.at(dst.first)=dst.second;
                thisTry.second += weight((*task)[dst.first].parameters(),(*grid)[dst.second].parameters());
            }
            QDebug(Configurator::instance().getLogDevice()) << QString("%1").arg(thisTry.second,5,'f',3) << "\n" ;
            solutions.push_back(thisTry);

        } // previous combinations loop
        float max = numeric_limits<float>::max();
//        выбираем из всех вариантов - лучший
        foreach (Solution s, solutions)
        {
            if (s.second < max){
                (*weightedPair).second = s;
                max = s.second;
            }
        }
        QDebug(Configurator::instance().getLogDevice()) << QString("Result weight = %1").arg( (*weightedPair).second.second) << "\n";
    } // current loop
}
// находит все входящие в вершину линии
void Algorithm::GetAllInEdgesTask(Edges & e, Graph::vertex_descriptor v){
    for (Graph::vertex_iterator u = task->m_vertex_set.begin(); u!= task->m_vertex_set.end(); ++u){
        std::pair<Graph::edge_descriptor, bool> p = edge(*u,v,*task);
        if(p.second){
            e.push_back(p.first);
        }

    }
    //    qDebug("in-edge size for v%ld =%ld ",v,e.size());
}
// предварительное вычисление весов размещений
void Algorithm::InitWeights(const ManyCombinations & combinations ,ManyWeightedCombinations &weights){
    weights.clear();
    Result nullResult( taskSize,Graph::null_vertex());
    Solution nullSolution(nullResult, 0.0f);

    for (ManyCombinations::const_iterator i = combinations.begin(); i!= combinations.end(); ++i){
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

}

// заполнение текущего набора
void Algorithm::FillSelectionWithLevel(Nodes &select, int level){
    for (Graph::vertex_iterator vertexIterator=this->task->m_vertex_set.begin();
         vertexIterator != this->task->m_vertex_set.end();
         ++ vertexIterator){
        int lev = (*task)[*vertexIterator].level();
        if (lev == level){
            select.push_back(*vertexIterator);
        }
    }
}
// создание всех возможных вариантов размещений
void  Algorithm::CreateCombinations(ManyCombinations &comb, const Nodes &curr){
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
            if (curr.size() != ss.size()){
                qDebug("какая то лажа ");
                abort();
            }

            Nodes::const_iterator selectionIter = curr.begin();
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
    QDebug(Configurator::instance().getLogDevice()) <<  QString("Combinations count %1").arg(comb.size()) << "\n";
}


// отладочный вывод
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
        QDebug(Configurator::instance().getLogDevice())  << str << "\n";
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
void Algorithm::GetAllSubsets(ManySubsets &comb,const Nodes & s){
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


std::vector<int> getAllKBits( int K, int max)
{
    std::vector< int > result;
    int maxSize = pow( 2, max );
    for (int number = 0; number < maxSize; ++number )
    {
        int count = 0;
        for (int j = 0; j < max; ++j)
        {
            int k = 1 << j;
            if ( number & k )
            {
                count ++;
            }
        }
        if (count == K)
        {
            result.push_back(number);
        }
    }
    return result;
}

// работает
//нахождение всех К подмножеств множества основано на переборе
// всех чисел от 0 до 2^К у которых ровно К единичных битов (К-чисел)


// при проходе по множеству элементов элементы добавляются в результирующее подмножество
// только в том случае если бит с таким же смещением равен 1,

// количество подмножеств равно количесву К-чисел
void Algorithm::GetAllKSubsetsGrid(ManySubsets &subsets, int K){

    int size = grid->m_vertex_set.size();
    std::vector <int> kVector(getAllKBits(K, size));
    for (unsigned int index = 0; index < kVector.size(); ++index)
    {
        Subset ss;

        int magicNumber = kVector.at(index);
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
        qDebug ("K = %d, index = %d, magic number = %d, size = %ld",K,index,magicNumber,ss.size());
    }
    qDebug("K = %d, size = %ld",K,subsets.size());
}


// виртуальный метод для определения веса из наборов параметров
float Algorithm::weight(vector<float> a, vector<float> b){
    return a[0]/b[0];
}
