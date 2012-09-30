#include <QtCore/QString>
#include <QtTest/QtTest>

#include "../dag_tree.h"



using namespace std;
using namespace mapper;


struct weight : public DAG_tree::weight_function {
    bool operator() (vector<float> a, vector<float> b) {return (a[0] / b[0]);}
};

class test_DAG_node : public QObject
{
    Q_OBJECT
    DAG_node init_node(int n, float f);

public:
    test_DAG_node(){};
    
private Q_SLOTS:

    void testCase();

};

DAG_node test_DAG_node::init_node(int n, float f){
    vector<float> vector;
    vector.push_back(f);

    string block_name = "block ";
    QString s = QString::number(n);
    block_name.append(s.toStdString());
    return DAG_node(n, block_name , vector);
}

void test_DAG_node::testCase()
{
    DAG_tree tree;

    DAG_node node1 = init_node(1,0.0f);
    DAG_node node2 = init_node(2,10.0f);
    DAG_node node3 = init_node(3,100.0f);
    DAG_node node4 = init_node(4,250.0f);
    DAG_node node5 = init_node(5,70.0f);
    DAG_node node6 = init_node(6,80.0f);
    DAG_node node7 = init_node(7,0.0f);

    DAG_line line12(1, 2, vector<float>(1,10.0f));
    DAG_line line13(1, 3, vector<float>(1,100.0f));
    DAG_line line24(2, 4, vector<float>(1,20.0f));
    DAG_line line34(3, 4, vector<float>(1,200.0f));
    DAG_line line45(4, 5, vector<float>(1,20.0f));
    DAG_line line46(4, 6, vector<float>(1,200.0f));
    DAG_line line57(5, 7, vector<float>(1,20.0f));
    DAG_line line67(6, 7, vector<float>(1,100.0f));

    qDebug() << node1.lines().size();

    node1.add_DAG_line(line12);

    qDebug() << node1.lines().size();
    node1.add_DAG_line(line13);

    qDebug() << node1.lines().size();

    node2.add_DAG_line(line24);
    node3.add_DAG_line(line34);

    qDebug() << node4.lines().size();
    node4.add_DAG_line(line45);
    qDebug() << node4.lines().size();
    node4.add_DAG_line(line46);
    qDebug() << node4.lines().size();
    node5.add_DAG_line(line57);
    node6.add_DAG_line(line67);

    tree.add_node(node1);
    tree.add_node(node2);
    tree.add_node(node3);
    tree.add_node(node4);
    tree.add_node(node5);
    tree.add_node(node6);
    tree.add_node(node7);

    QVERIFY(node1.number() == 1);
    QVERIFY(node1.name() == "block 1");
    QVERIFY(node1.parameter(0) == 0.0f);

    QVERIFY(line12.from() == 1);
    QVERIFY(line12.to() == 2);
    QVERIFY(line12.parameter(0) == 10.0f);

    QVERIFY(line46.from() == 4);
    QVERIFY(line46.to() == 6);

    qDebug() << node4.lines().size();
    QVERIFY(node4.lines().size() == 2);

    DAG_tree::weight_function fu = weight();
    tree.dag_map(tree, fu, fu);
    QVERIFY(1==1);

}


QTEST_APPLESS_MAIN(test_DAG_node)
#include "tst_dag_node.moc"
