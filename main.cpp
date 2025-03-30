#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QGraphicsView>
#include <QApplication>
#include <QFile>
#include <QString>
#include <QVector>

QVector<QVector<int>> graphsScan(QString path)
{
    QVector<QVector<int>> res;
    QFile file = path;
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qWarning("File is not open!");
        return res;
    }
    QTextStream in(&file);
    while(!in.atEnd())
    {
        QString line = in.readLine();
        QStringList strokes = line.split(',', Qt::SkipEmptyParts);
        QVector<int> rowInt;
        for(QString &numStr : strokes)
        {
            int numInt = numStr.trimmed().toInt();
            rowInt.append(numInt);
        }
        res.append(rowInt);
    }
    file.close();
    return res;
}


class Graphs
{
private:
    int radius = 200;
    int centerX = 200;
    int centerY = 200;
    int graphRadius = 50;

    QVector<QPointF> pos;
public:
    int graphsCounter(QString path)
    {
        QFile file = path;
        if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            qWarning("File is not open!");
            return 0;
        }

        int counter = 0;
        QTextStream in(&file);
        while(!in.atEnd())
        {
            QString line = in.readLine();
            qDebug() << line;
            counter++;
        }
        return counter;
    }

    void graphsDraw(int counter, QGraphicsScene &scene)
    {
        pos.clear();
        scene.clear();

        int c = 1;
        for(int i = 0; i < counter; i++)
        {
            double angle = 2 * M_PI * i / counter;

            int x = centerX + radius * cos(angle) - graphRadius;
            int y = centerY + radius * sin(angle) - graphRadius;

            pos.append(QPointF(x + graphRadius, y + graphRadius));

            QGraphicsTextItem *textItem = scene.addText(QString::number(c++));
            textItem->setScale(3);
            textItem->setPos(x + graphRadius/2, y + graphRadius/5);

            scene.addEllipse(x, y, graphRadius * 2, graphRadius * 2);
        }
    }
    void connectionsDraw(QVector<QVector<int>> connections, QGraphicsScene &scene)
    {
        QPen pen(Qt::black);
        pen.setWidth(2);

        for(int i = 0; i < connections.size(); i++)
        {
            for(int j = 0; j < connections[i].size(); j++)
            {
                int target = connections[i][j] - 1;
                if(target >= 0 && target < pos.size())
                    scene.addLine(QLineF(pos[i], pos[target]), pen);
            }
        }
    }
};

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QString filePath = "/home/rizuniar/Документы/Graphs/cords";

    QGraphicsScene scene;

    Graphs JustGraph;
    QVector<QVector<int>> arr = graphsScan(filePath);

    int GraphsCount = JustGraph.graphsCounter(filePath);

    if(GraphsCount == 0)
    {
        qWarning() << "Zero graphs in file!";
        return 0;
    }

    JustGraph.graphsDraw(GraphsCount, scene);
    JustGraph.connectionsDraw(arr, scene);

    QGraphicsView view(&scene);
    view.setWindowTitle("Graphs");
    view.setRenderHint(QPainter::Antialiasing);
    view.show();
    return app.exec();
}
