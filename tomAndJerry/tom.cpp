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
    // adjacency list representation
    /*
     * adj.resize(225);

    for(int i=0; i<15; i++)
         for(int j = 0; j<15; j++){
             if(data1[i][j]==-1) continue;

            if(validLimits(i-1,j,15,15))
                if(data1[i-1][j]!=-1){
                   adj[data1[i][j]].push_back(data1[i-1][j]);
                   adj[data1[i-1][j]].push_back(data1[i][j]);
                }
            if(validLimits(i+1,j,15,15))
                if(data1[i+1][j]!=-1){
                   adj[data1[i][j]].push_back(data1[i+1][j]);
                   adj[data1[i+1][j]].push_back(data1[i][j]);
                }

            if(validLimits(i,j-1,15,15))
                if(data1[i][j-1]!=-1){
                   adj[data1[i][j]].push_back(data1[i][j-1]);
                   adj[data1[i][j-1]].push_back(data1[i][j]);
                }
            if(validLimits(i,j+1,15,15))
                if(data1[i][j+1]!=-1){
                   adj[data1[i][j]].push_back(data1[i][j+1]);
                   adj[data1[i][j+1]].push_back(data1[i][j]);
                }
        }
    for(auto vec : adj){
        sort( vec.begin(), vec.end() );
        vec.erase( unique( vec.begin(), vec.end() ), vec.end() );
    }
    */
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
            if(!validLimits(i,j,107,107)) continue;
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
                if(!validLimits(i,j,107,107)) continue;
                j = previous[j];
                paths[i].insert(paths[i].begin(), j);
            } while (j != startVertex);
        }
    }
    return paths[jerry::getVertex()];
}
std::pair<int,int> Tom::getPos(int x){
    for(int i=0; i<15; i++){
        for(int j=0; j<15; j++)
            if(data1[i][j]==x)
                return {i,j};
    }
    return{-1,-1};
}

void Tom::move(char d, int recursionTracker)
{
    if(d == 'u' && data1[row1-1][column1] != -1){
       row1--;
    }

    else if(d == 'd' && data1[row1+1][column1] != -1){
        row1++;
        lastMove=d;
    }

    else if(d == 'r' && data1[row1][column1+1] != -1){
        column1++;
        QPixmap tom("TomRight.png");
        tom = tom.scaledToWidth(50);
        tom = tom.scaledToHeight(50);
        setPixmap(tom);
        lastMove=d;
    }

    else if(d == 'l' && data1[row1][column1-1] != -1){
        column1--;
        QPixmap tom("Tom.png");
        tom = tom.scaledToWidth(50);
        tom = tom.scaledToHeight(50);
        setPixmap(tom);
        lastMove=d;
    } else {
        if(recursionTracker>225) {
            return;
        }
        move(lastMove, recursionTracker+1);
        // and here
    }

    setPos(25+50*column1, 25+50*row1);
}
void Tom::move()
{
   startVertex = data1[getRow1()][getColumn1()];
   path = dijkestra(adjacencyMatrix, startVertex);
   if(path.size()<=1) return;
   std::pair<int,int> f = getPos(   path[1]); // next step position
   if(f.first==-1) f=getPos(jerpos);
   if(f.first==-1)  return;
   if(f.first>row1){
       move('d',0);
   } else if(f.first<row1){
       move('u',0);
   } else if(f.second<column1)
           move('l',0);
   else if(f.second>column1)
           move('r',0);
}

// Adjacency Level Dijkstra
/*
 * void Tom::dij(int s){
    dist.resize(225,1e9);
    road.resize(225,-1);
    dist[s]=0;
    road[s]=s;
    std::priority_queue<std::pair<int,int>, std::vector<std::pair<int,int>>, std::greater<std::pair<int,int>> > p;
    p.push({0,s});
    while(!p.empty()){
        int u = p.top().second;
        p.pop();
        for(auto i=adj[u].begin(); i!=adj[u].end(); i++){
            int v = *i;
            if(dist[v]>dist[u]+1){
                dist[v]=dist[u]+1;
                p.push({dist[v], v});
                road[v]=u;
            }
        }
    }
}
std::pair<int,int> Tom::getPos(int x){
    for(int i=0; i<15; i++){
        for(int j=0; j<15; j++)
            if(data1[i][j]==x)
                return {i,j};
    }
    return{-1,-1};
}
void Tom::toJerry(){
    // you should make this as input from the connect in main
    int tompos=data1[row1][column1];
    if(tompos==jerpos) return;

    dij(tompos);
    int jerPosition=jerpos;

    int a=jerPosition;
    int c = 0;

    while(jerPosition!=tompos){
        if(c>=225) {break; }
        c++;
        a =jerPosition;
        jerPosition=road[jerPosition];
    }

    //if(ch) return;
    std::pair<int,int> f = getPos(a); // next step position
    if(f.first==-1) f=getPos(jerpos);
    if(f.first==-1)  return;
    if(f.first>row1){
        move('d',0);
    } else if(f.first<row1){
        move('u',0);
    } else if(f.second<column1)
            move('l',0);
    else if(f.second>column1)
            move('r',0);

}
*/
