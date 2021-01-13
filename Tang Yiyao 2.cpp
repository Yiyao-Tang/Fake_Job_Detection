#include <iostream>
#include <algorithm>
#define MAX 100
using namespace std;

bool visit[MAX] = {0};
int sequence[MAX] = {0};
int component[MAX][MAX] = {0};
int tree_edges[MAX][MAX] = {0};
int graph[MAX][MAX]={{0,1,1,0,0,0,0,0,0},{1,0,1,0,0,0,0,0,0,},{1,1,0,1,0,0,0,0,0,}
,{0,0,1,0,0,0,0,0,0,},{0,0,0,0,0,1,1,0,0,},{0,0,0,0,1,0,1,0,0,},{0,0,0,0,1,1,0,0,0,},{0,0,0,0,0,0,0,0,1},{0,0,0,0,0,0,0,1,0}};
int component_count = 0;
int parent[MAX] = {0};
bool has_cycle[MAX] = {0};
int parent_node = -1;
int N = 0;
int counter = 0;

void inputgraph(int);
void customize_graph(void);
void outputgraph(void);
void show_info(void);
void check(void);
void dfs(int);


int main()
{
    int start = 0;
    bool use_default_graph = false;
    cout << "Enter 1 to use the default graph provided in the lab manual, enter 0 to customize the graph:"<<endl;
    cin >> use_default_graph;
    if(use_default_graph == false)
        customize_graph();
    else
        N = 9;
    outputgraph();
    cout <<"Enter your starting vertex:"<<endl;
    cin >> start;
    dfs(start-1);
    check();
    show_info();
}

void customize_graph(void)
{
    cout <<"How many nodes are there? "<<endl;
        cin  >> N;
        while(N > MAX || N < 1)
        {
            cout << "Invalid number of vertices"<<endl;
            cout << "Please re-enter the value:"<<endl;
            cin  >> N;
        }
        inputgraph(N);
}

void inputgraph(int N)
{
    int x,y,edge;
    for(x=0;x<N;x++)
    {
        for(y=0;y<N;y++)
            graph[x][y] = 0;
    }
    for (x=0;x<N;x++)
    {
        for (y=x+1;y<N;y++)
        {
            printf("graph[%d][%d]=",x+1,y+1);
            cin >> edge;
            graph[x][y]=edge;
            graph[y][x]=edge;
        }
    }
}

void outputgraph(void)
{
    int x, y;
    cout <<"Adjacency Matrix of Graph:"<<endl;
    for(x=0;x<N;x++)
    {
        printf("\n |  ");
        for(y=0;y<N;y++)
            cout <<graph[x][y]<<"   ";
        cout<<"| "<<endl;
    }
}


void dfs(int vertex)
{

    if (parent_node != -1)
    {
        parent[vertex] = parent_node;
    }
    parent_node = vertex;
    visit[vertex] = 1;
    sequence[counter] = vertex+1;
    component[component_count][counter] = (vertex+1);
    counter++;
    for (int i = N-1;i>=0;i--)
    {
        if (graph[vertex][i] == 1 && visit[i]==0)
        {
            tree_edges[vertex][i] = 1;
            dfs(i);
        }
    }
}

void check()
{
    for (int i = N-1;i>= 0;i--)
    {
        if (visit[i] == 0)
        {
            component_count++;
            parent_node = -1;
            dfs(i);
        }
    }
}

void show_info()
{
    cout << "visiting sequence is ";
    for (int i=0;i<=N-1;i++)
        cout<<sequence[i]<<"  ";
    cout<<endl;
    cout<<"There exist "<<(component_count+1)<<" disconnected components"<<endl;
    for(int j=0;j<=component_count;j++)
    {
        cout << "component "<<j+1<< " (vertices): ";
        for (int k=0;k<=N;k++)
        {
            if(component[j][k]!=0) {
                cout << component[j][k] << " " ;
            } else {
                continue;
            }
        }
        cout << endl << endl;

    }
    for (int i = 0; i < N; i++)
    {
        if (parent[i] != 0 )
            cout << "Vertex " << i+1 << "'s parent is " << parent[i]+1<<","<<endl;
        else
            cout << "Vertex " << i+1 << " has no parent."<<endl;
    }

    cout <<"tree edges:"<<endl;
    for (int i=0;i<=N-1;i++)
    {
        for (int j=0;j<=N-1;j++)
        {
            if (graph[i][j] ==1 && tree_edges[i][j] == 1)
                cout<< i+1<<"-->"<<j+1 <<" is a tree edge "<<endl;
        }
    }
    cout << "back edges: "<<endl;
    for (int i=0;i<=N-1;i++)
        {
            for (int j=i;j<=N-1;j++)
            {
                if (graph[i][j] ==1 && tree_edges[i][j] != 1 && tree_edges[j][i]!=1)
                    {cout<< i+1<<"-->"<<j+1 <<" is a back edge "<<endl;
                        for(int k=0;k<=component_count;k++)
                        {
                            bool exist = (std::find(begin(component[k]), std::end(component[k]), i+1) != std::end(component[k]))&&((std::find(begin(component[k]), std::end(component[k]), j+1) != std::end(component[k])));
                            if(exist==true)
                            {
                                has_cycle[k]=true;
                            }

                        }
                    }
            }
        }
    for(int i=0;i<=component_count;i++)
        {
            if(has_cycle[i]==1)
                cout<<"component "<<i+1<<" has a cycle"<<endl;
            else
                cout<<"component "<<i+1<<" has no cycle"<<endl;
        }
}
