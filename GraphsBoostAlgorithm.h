#ifndef GRAPHSBOOSTALGORITHM_H
#define GRAPHSBOOSTALGORITHM_H
#include <boost/graph/astar_search.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <QVector>

using namespace boost;

using GraphObj = adjacency_list<
    vecS,
    vecS,
    directedS,
    no_property,
    no_property
>;

class GraphsBoost
{
    public:
        GraphObj CreateGraphFromQVector(QVector<QVector<int>> Graph);
        QVector<int>


#endif // GRAPHSBOOSTALGORITHM_H
