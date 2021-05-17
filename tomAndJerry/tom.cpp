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



    QVector<QVector<int>> adj(107);

        int k = 0;
        for(int i=0; i<15; i++)
         {
             for(int j = 0; j<15; j++)
             {
                 if(data1[i][j]!=-1)
                 {

                if(validLimits(i-1,j,15,15))
                    if(data1[i-1][j]!=-1)
                       adj[k].push_back(data1[i-1][j]);

                if(validLimits(i+1,j,15,15))
                    if(data1[i+1][j]!=-1)
                       adj[k].push_back(data1[i+1][j]);

                if(validLimits(i,j-1,15,15))
                    if(data1[i][j-1]!=-1)
                       adj[k].push_back(data1[i][j-1]);

                if(validLimits(i,j+1,15,15))
                    if(data1[i][j+1]!=-1)
                       adj[k].push_back(data1[i][j+1]);
                k++;
                 }
            }
         }

         for(int i = 0; i<107; i++)
            for(int k = 0; k<adj[i].size(); k++)
                adjacencyMatrix[i][adj[i][k]] = 1;


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
    int temp[COUNT][COUNT], costs[COUNT], previous[COUNT];
        bool visited[COUNT];
        // temp
        for (int i = 0; i < COUNT; i++)
            for (int j = 0; j < COUNT; j++)
                if (adjacencyMatrix[i][j] == 0)
                    temp[i][j] = INFINITE;
                else
                    temp[i][j] = adjacencyMatrix[i][j];
        // costs, previous, and visited
        for (int i = 0; i < COUNT; i++)
        {
            costs[i] = temp[startVertex][i];
            previous[i] = startVertex;
            visited[i] = false;
        }
        // startNode
        costs[startVertex] = 0;
        visited[startVertex] = true;

        int count = 1, nextNode, minimumCost;
        while (count < COUNT)
        {
            // Find the minimum cost in order to visit a node.
            minimumCost = INFINITE;
            for (int i = 0; i < COUNT; i++)
                if ((costs[i] < minimumCost) && (visited[i] == false))
                {
                    minimumCost = costs[i];
                    nextNode = i;
                }
            // Visit the node.
            visited[nextNode] = true;
            // Update the costs of the children of the visited node.
            for (int i = 0; i < COUNT; i++)
                if ((minimumCost + temp[nextNode][i] < costs[i]) && (visited[i] == false))
                {
                    costs[i] = minimumCost + temp[nextNode][i];
                    previous[i] = nextNode;
                }
            count++;
        }
        // Fill the paths.
        int j;
        QVector<QVector<int>> paths;
        paths.resize(COUNT);
        for (int i = 0; i < COUNT; i++)
        {
            paths[i].push_back(i);
            if (i != startVertex)
            {
                j = i;
                do
                {
                    j = previous[j];
                    paths[i].push_back(j);
                } while (j != startVertex);
            }
        }
        return paths[jerry::getVertex()];
}

void Tom::move()
{
   startVertex = data1[getRow1()][getColumn1()];
   path = dijkestra(adjacencyMatrix, startVertex);


if(data1[row1][column1+1] == path.size()- 2 )
{
    column1++;
    setPos(25 + 50 * column1, 25 + 50 * row1);

}
//else if((m==0 || m== 1|| m==2 || m==4) && data[row++][column]> -1 && row <16)
else if(data1[row1+1][column1]== path.size()- 2)
{
    row1++;
    setPos(25 + 50 * column1, 25 + 50 * row1);

}
//else if((m==0 || m== 1|| m==2 || m==4) &&data[row][column--]>-1 && column > 0)
else if(data1[row1][column1-1]== path.size()- 2)
{column1--;

     setPos(25 + 50 * column1, 25 + 50 * row1);

}
//else if((m==0 || m== 1|| m==2 || m==4) && data[row--][column]> -1 && row > 0)
else if (data1[row1-1][column1]== path.size()- 2)
{
    row1--;
    setPos(25 + 50 * column1, 25 + 50 * row1);
}
}
// function for dijkstra


