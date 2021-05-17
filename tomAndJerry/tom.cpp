#include "tom.h"

bool validLimits(int x, int y, int nx, int ny) {
    if(
            x<0 ||
            x>=nx ||
            y<0 ||
            y>=ny
        ) return false;
    return true;

}
Tom::Tom(int initialRow, int initialColumn, int d[15][15])
{
    for(int i = 0; i<15; i++)
        for(int j = 0; j<15; j++)
            data1[i][j] = d[i][j];
    row1 = initialRow;
    column1 = initialColumn;
    QPixmap tom("Tom.png");
    tom = tom.scaledToWidth(50);
    tom = tom.scaledToHeight(50);
    setPixmap(tom);
    setPos(25+50*column1, 25+50*row1);


    for(int i = 0; i<107; i++)
        for(int j = 0; j<107; j++)
            adjacencyMatrix[i][j] = 0;


    int k;

    for(int i=0; i<15; i++)
    {
        for(int j = 0; j<15; j++)
        {
            if(data1[i][j]!=-1)
            {
                k = data1[i][j];
                if(validLimits(i-1,j,15,15))
                    if(data1[i-1][j]!=-1)
                       adjacencyMatrix[k][data1[i-1][j]] = 1;

                if(validLimits(i+1,j,15,15))
                    if(data1[i+1][j]!=-1)
                       adjacencyMatrix[k][data1[i+1][j]] = 1;

                if(validLimits(i,j-1,15,15))
                    if(data1[i][j-1]!=-1)
                       adjacencyMatrix[k][data1[i][j-1]] = 1;

                if(validLimits(i,j+1,15,15))
                    if(data1[i][j+1]!=-1)
                        adjacencyMatrix[k][data1[i][j+1]] = 1;

                 }
            }
         }

    lastRand=0;
}
void Tom::setRow1(int newRow1)
{
    row1 = newRow1;
}
int Tom::getRow1()
{
    return row1;
}
void Tom::setColumn1(int newColumn1)
{
    column1 = newColumn1;
}
int Tom::getColumn1()
{
    return column1;
}

QVector<int> Tom::dijkestra(int adjacencyMatrix[107][107], int startVertex)
{
    int temp[COUNT][COUNT];
    for (int i = 0; i < COUNT; i++)
    {
        for (int j = 0; j < COUNT; j++)
        {
            if (adjacencyMatrix[i][j] == 0)
                temp[i][j] = INFINITE;
            else
                temp[i][j] = adjacencyMatrix[i][j];
        }
    }
    bool visited[COUNT];
    int previous[COUNT];
    float cost[COUNT];
    // 1st Row:
    for (int i = 0; i < COUNT; i++)
    {
        if (i == startVertex)
        {
            previous[i] = -1;
            cost[i] = 0;
            visited[i] = true;
        }
        else
        {
            previous[i] = startVertex;
            cost[i] = temp[startVertex][i];
            visited[i] = false;
        }
    }
    // All Rows:
    int count = 1;
    while (count < COUNT)
    {
        // Determine which vertex to visit.
        int minimum = INFINITE, visitedVertex;
        for (int i = 0; i < COUNT; i++)
        {
            if (visited[i] == false && cost[i] < minimum)
            {
                minimum = cost[i];
                visitedVertex = i;
            }
        }
        // Visit the vertex.
        visited[visitedVertex] = true;

        // Check whether there are shorter paths.
        for (int i = 0; i < COUNT; i++)
        {
            if (visited[i] == false)
            {
                if ((cost[visitedVertex] + temp[visitedVertex][i]) < cost[i])
                {
                    previous[i] = visitedVertex;
                    cost[i] = (cost[visitedVertex] + temp[visitedVertex][i]);
                }
            }
        }
        count++;
    }
    // Extract the paths.
    QVector<QVector<int>> paths;
    paths.resize(COUNT);
    int j;
    for (int i = 0; i < COUNT; i++)
    {
        paths[i].push_back(i);
        if (i != startVertex)
        {
            j = i;
            do
            {
                j = previous[j];
                paths[i].insert(paths[i].begin(), j);
            } while (j != startVertex);
        }
    }
    return paths[jerry::getVertex()];
}

void Tom::move()
{
   startVertex = data1[getRow1()][getColumn1()];
   column1++;
   setPos(25+50*column1, 25+50*row1);
}

