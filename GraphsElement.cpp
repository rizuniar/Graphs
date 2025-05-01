#include <GraphsElement.h>

GraphsEl::GraphsEl()
{
    Radius = 200;
    CenterX = 200;
    CenterY = 200;
    GraphRadius = 50;
    Pos;
}

QVector<QVector<int>> GraphsEl::GraphsScan(QString Path)
{
    QVector<QVector<int>> Res;
    QFile File = (QFile)Path;
    if(!File.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qWarning("File is not open!");
        return Res;
    }
    QTextStream In(&File);
    while(!In.atEnd())
    {
        QString Line = In.readLine();
        QStringList Strokes = Line.split(',', Qt::SkipEmptyParts);
        QVector<int> RowInt;
        for(QString &NumStr : Strokes)
        {
            int NumInt = NumStr.trimmed().toInt();
            RowInt.append(NumInt);
        }
        Res.append(RowInt);
    }
    File.close();
    return Res;
}

int GraphsEl::FindMinVer(QVector<int> Dist, QVector<bool> Visited)
{
    int MinVal = INT_MAX;
    int MinIndex = -1;

    for(int i = 0; i < Dist.size(); i++)
    {
        if(!Visited[i] && Dist[i] < MinVal)
        {
            MinVal = Dist[i];
            MinIndex = i;
        }
    }
    return MinIndex;
}

int GraphsEl::GraphsCounter(QString Path)
{
    QFile File = (QFile)Path;
    if(!File.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qWarning("File is not open!");
        return 0;
    }

    int Counter = 0;
    QTextStream In(&File);
    while(!In.atEnd())
    {
        QString Line = In.readLine();
        qDebug() << Line;
        Counter++;
    }
    return Counter;
}

void GraphsEl::Dejkstra(int Start, int End, QVector<QVector<int>> Graphs)
{
    int n = Graphs.size();
    QVector<int> Dist(n, INT_MAX);
    QVector<int> Prev(n, -1);
    QVector<bool> Visited(n, false);

    Dist[Start] = 0;

    for(int i = 0; i < n; i++)
    {
        int u = FindMinVer(Dist, Visited);
        if(u == -1) break;

        Visited[u] = true;

        for(int Way : Graphs[u])
        {
            int v = Way - 1;
            if(v < 0 || v >= n) continue;
            int Weight = 1;
            if(!Visited[v] && Dist[u] != INT_MAX && Dist[v] > Dist[u] + Weight)
            {
                Dist[v] = Dist[u] + Weight;
                Prev[v] = u;
            }
        }
    }

    if(Dist[End] == INT_MAX)
    {
        qWarning() << "No way's from: " << Start + 1 << " -> " << End + 1;
        return;
    }

    int Current = End;
    QVector<int> GraphPath;
    while(Current != -1)
    {
        GraphPath.prepend(Current);
        Current = Prev[Current];
    }

    qDebug() << "Shortest way:";
    for(int a : GraphPath)
    {
        qDebug() << a + 1;
    }
}

void GraphsEl::GraphsDraw(int Counter, QGraphicsScene &Scene)
{
    Pos.clear();
    Scene.clear();

    int c = 1;
    for(int i = 0; i < Counter; i++)
    {
        double angle = 2 * M_PI * i / Counter;

        int x = CenterX + Radius * cos(angle) - GraphRadius;
        int y = CenterY + Radius * sin(angle) - GraphRadius;

        Pos.append(QPointF(x + GraphRadius, y + GraphRadius));

        QGraphicsTextItem *TextItem = Scene.addText(QString::number(c++));
        TextItem->setScale(3);
        TextItem->setPos(x + GraphRadius/2, y + GraphRadius/5);

        Scene.addEllipse(x, y, GraphRadius * 2, GraphRadius * 2);
    }
}

void GraphsEl::ConnectionsDraw(QVector<QVector<int>> Connections, QGraphicsScene &Scene)
{
    QPen Pen(Qt::black);
    Pen.setWidth(2);

    for(int i = 0; i < Connections.size(); i++)
    {
        for(int j = 0; j < Connections[i].size(); j++)
        {
            int Target = Connections[i][j] - 1;
            if(Target >= 0 && Target < Pos.size())
                Scene.addLine(QLineF(Pos[i], Pos[Target]), Pen);
        }
    }
}
