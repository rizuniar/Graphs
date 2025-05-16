#ifndef GRAPHSELEMENT_H
#define GRAPHSELEMENT_H
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QGraphicsView>
#include <QApplication>
#include <QFile>
#include <QString>
#include <QVector>
#include <boost/graph/astar_search.hpp>
#include <boost/graph/adjacency_list.hpp>

using namespace boost;

using GraphObj = adjacency_list<
    vecS,
    vecS,
    directedS,
    no_property,
    property<edge_weight_t, double>
    >;

class GraphsEl
{
private:
    int Radius;
    int CenterX;
    int CenterY;
    int GraphRadius;
    QVector<QPointF> Pos;
    int FindMinVer(QVector<int> Dist, QVector<bool> Visited);
public:
    GraphsEl();
    QVector<QVector<int>> GraphsScan(QString Path);
    int GraphsCounter(QString Path);
    void DejkstraAlgorithm(int Start, int End, QVector<QVector<int>> Graphs);
    void GraphsDraw(int Counter, QGraphicsScene &Scene);
    void ConnectionsDraw(QVector<QVector<int>> Connections, QGraphicsScene &Scene);
    GraphObj FromQVectorToBoostGraph(QVector<QVector<int>> &Graphs);
    void AStarAlgorithm(int Start, int End, QVector<QVector<int>> &Graphs);
};


#endif // GRAPHSELEMENT_H
