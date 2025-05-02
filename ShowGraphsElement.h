#ifndef SHOWGRAPHSELEMENT_H
#define SHOWGRAPHSELEMENT_H
#include<QGraphicsView>
#include <QString>

class ShowGraphsEl : public QGraphicsView
{
    public:
        ShowGraphsEl(QGraphicsScene *scene, const QString &title = "Graphs", QWidget *parent = nullptr) : QGraphicsView(scene, parent)
        {
            setRenderHint(QPainter::Antialiasing, true);
            setWindowTitle(title);
        }
};

#endif // SHOWGRAPHSELEMENT_H
