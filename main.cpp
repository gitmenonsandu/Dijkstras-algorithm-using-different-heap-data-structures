#include <iostream>
#include <ctime>
#include <cstdlib>
#include <Graph.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    char Random;
    int V, start, stop, source, n, edges, rangeStart, rangeEnd;
    float avg_deg;
    do
    {

        cout<<"1. Random Graph"<<endl<<"2. S for specified Graph Input"<<endl;
        cin>>Random;
    }while(Random != '1' and Random != '2');
    cout << "Enter the number of vertices in the graph : ";
    cin >> V;
    cout << "Vertices are labeled from 0 to "<<V<<endl;
    Graph g(V);
    if(Random == '1')
    {
        cout << "Enter the source vertex : ";
        cin >> source;
        cout<< "Enter the average degree: ";
        cin>>avg_deg;
        cout<<"Enter the range of random weights to be assigned to the graph. "<<endl;
        cout<<"Enter starting of range : ";
        cin>>rangeStart;
        cout<<"Enter ending of range : ";
        cin>>rangeEnd;

        edges = (int)(avg_deg * V);
        map<pair<int,int>,int>m;
        cout<<"Edge number "<<edges<<endl;
        cout<<"Edges are: "<<endl;
        for(int i = 0; i < edges; i++)
        {
            srand (time(NULL));
            int random_number = -1;
            while(random_number == -1)
            {
                random_number =rand()%(V*V);
                if(m[make_pair(random_number/V,random_number%V)] || random_number/V == random_number%V)
                    random_number = -1;
                else
                {
                    int weight = rand()%(rangeEnd - rangeStart) + rangeStart;
                    m[make_pair(random_number/V,random_number%V)] = 1;
                    cout<<"("<<random_number/V<<") - ("<<random_number%V<<") : "<<weight<<endl;
                    g.addEdge(random_number/V, random_number%V, weight);
                }
            }
        }
    }
    else
    {
        cout << "Enter the source vertex : ";
        cin >> source;

        for (int i = 0; i < V; i++)
        {
            cout << "Enter the number of neighbours of vertex (" << i << ") :";
            cin >> n;
            assert(n < V);
            cout << "Enter the neighbours of vertex (" << i << ") along with the edge weigths." << endl;
            for (int j = 0; j < n; j++)
            {
                int u, w;
                cin >> u >> w;
                assert(u < V && w >= 0);
                g.addEdge(i, u, w);
            }
        }
    }
    cout << "-----BINARY HEAPS-----" << endl;
    start = clock();
    g.shortestPath(source, BINARY);
	stop = clock();
    cout << "Execution time using Binary Heaps: " << (stop-start)/double(CLOCKS_PER_SEC)*1000 << endl;

    cout << "-----BINOMIAL HEAPS-----" << endl;
    start = clock();
	g.shortestPath(source, BINOMIAL);
	stop = clock();
    cout << "Execution time using Binomial Heaps: " << (stop-start)/double(CLOCKS_PER_SEC)*1000 << endl;

    cout << "-----FIBONACCI HEAPS-----" << endl;
    start = clock();
	g.shortestPath(source, FIBONACCI);
	stop = clock();
    cout << "Execution time using Fibonacci Heaps: " << (stop-start)/double(CLOCKS_PER_SEC)*1000 << endl;

    return 0;
}
