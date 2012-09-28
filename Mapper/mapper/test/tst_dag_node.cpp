#include <QtCore/QString>
#include <QtTest/QtTest>

#include "../dag_node.h"

class test_DAG_node : public QObject
{
    Q_OBJECT
    
public:
    test_DAG_node(){};
    
private Q_SLOTS:

    void testCase();

};



void test_DAG_node::testCase()
{
    std::vector<float> vector;
    vector.push_back(1);
    vector.push_back(2);

    mapper::DAG_node node(1,"block 1",vector);

    QVERIFY(node.get_number() == 1);

}


QTEST_APPLESS_MAIN(test_DAG_node)
#include "tst_dag_node.moc"
