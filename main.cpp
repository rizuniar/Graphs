#include <QApplication>
#include <GraphsElement.h>


int main(int argc, char *argv[])
{
    QApplication App(argc, argv);
    QString FilePath = "/home/rizuniar/Документы/Graphs/cords";

    QGraphicsScene Scene;

    GraphsEl JustGraph;
    QVector<QVector<int>> Arr = JustGraph.GraphsScan(FilePath);

    int GraphsCount = JustGraph.GraphsCounter(FilePath);

    if(GraphsCount == 0)
    {
        qWarning() << "Zero graphs in file!";
        return 0;
    }

    JustGraph.GraphsDraw(GraphsCount, Scene);
    JustGraph.ConnectionsDraw(Arr, Scene);
    JustGraph.Dejkstra(0, 2, Arr);

    QGraphicsView View(&Scene);
    View.setWindowTitle("Graphs");
    View.setRenderHint(QPainter::Antialiasing);
    View.show();
    return App.exec();
}
