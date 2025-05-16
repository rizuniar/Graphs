#include <QApplication>
#include <GraphsElement.h>
#include <ShowGraphsElement.h>

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
    JustGraph.DejkstraAlgorithm(0, 2, Arr);
    JustGraph.AStarAlgorithm(0, 5, Arr);

    ShowGraphsEl View(&Scene, "Graphs");
    View.show();
    return App.exec();
}
