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
    adj.resize(225);
    dist.resize(225,1e9);
    road.resize(225,-1);

  //  std::vector<std::vector<bool>> vis(15,std::vector<bool>(15,0));

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
    row1 = initialRow;
    column1 = initialColumn;
    QPixmap tom("Tom.png");
    tom = tom.scaledToWidth(50);
    tom = tom.scaledToHeight(50);
    setPixmap(tom);
    setPos(25+50*column1, 25+50*row1);
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

void Tom::keyPressEvent(QKeyEvent * event)
{

    if(event->key() == Qt::Key_Up)
        move('u');
    else if(event->key() == Qt::Key_Down)
        move('d');
    else if(event->key() == Qt::Key_Right)
       move('r');
    else if(event->key() == Qt::Key_Left)
       move('l');

    /*QList<QGraphicsItem*> items = collidingItems();

    for(int i = 0; i<items.size(); i++)
    {
        if(typeid(*items[i]) == typeid(jerry)){

        }

    }*/
}
void Tom::move(char d)
{
    if(d == 'u' && data1[row1-1][column1] != -1){
       row1--;
       lastMove=d;
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
        move(lastMove);
        // and here
    }

    setPos(25+50*column1, 25+50*row1);
}

void Tom::randomlyMove(){
    char tmp[] = {'u', 'd', 'r', 'l'};

    int idx = rand()%4;

    move(tmp[idx]);

    lastRand=idx;
}
void Tom::dij(int s){
    dist.resize(225,1e9);
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
    int a=-5;
    int c = 0;

    while(jerPosition!=tompos){
        if(c>=225) {
            a=jerpos;
            break;

        }
        c++;
        a =jerPosition;
        jerPosition=road[jerPosition];
    }

    //if(ch) return;
    std::pair<int,int> f = getPos(a); // next step position
    if(f.first==-1) f=getPos(jerpos);
    if(f.first==-1)  return;
    if(f.first>row1){
        move('d');
    } else if(f.first<row1){
        move('u');
    } else if(f.second<column1)
            move('l');
    else if(f.second>column1)
            move('r');
    else {
        // to be handled here
       move(lastMove);
    }

}
