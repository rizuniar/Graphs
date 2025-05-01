#ifndef GRAPHSELEMENT_H
#define GRAPHSELEMENT_H
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QGraphicsView>
#include <QApplication>
#include <QFile>
#include <QString>
#include <QVector>


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
    void Dejkstra(int Start, int End, QVector<QVector<int>> Graphs);
    void GraphsDraw(int Counter, QGraphicsScene &Scene);
    void ConnectionsDraw(QVector<QVector<int>> Connections, QGraphicsScene &Scene);
};


#endif // GRAPHSELEMENT_H
