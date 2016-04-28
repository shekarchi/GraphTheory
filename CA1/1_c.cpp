#include <iostream>
#include <vector>

#define MYINF 2147483647

using namespace std;

int min_distance(vector<int> *dist, vector<bool> spt_set)
{
	int n = (*dist).size();
	int min = MYINF;
	int min_index = -1;
	for(int v=0; v<n; v++)
		if(spt_set[v] == false && (*dist)[v] <= min)
		{			
			min = (*dist)[v];
			min_index = v;
		}
	return min_index;
}

void dijkstra(vector< vector<int> > graph, int source, vector<int> *dist)
{
	int n = graph.size();
	vector<bool> spt_set(n);
	for(int i=0; i<n; i++)
		(*dist)[i] = MYINF;
	(*dist)[source] = 0;
	for(int count=0; count<n-1; count++)
	{
		int u = min_distance(dist, spt_set);
		spt_set[u] = true;
		for(int v=0; v<n; v++)
			if(!spt_set[v] && graph[u][v] > 0 && (*dist)[u]!=MYINF && (*dist)[u]+graph[u][v]<(*dist)[v])
				(*dist)[v] = (*dist)[u] + graph[u][v];
	}
}

void harmonic_centrality(vector< vector<int> > graph, int source)
{
	int n = graph.size();
	vector<int> dist(n);
	dijkstra(graph, source, &dist);
	double sum = 0;
        for(int j=0; j<dist.size(); j++)
                if(source != j)
                        sum += (double)1/(double)dist[j];
        cout << sum << endl;
}

int main()
{
	int m,n;
        cin >> n >> m;
        vector< vector<int> > graph;
        for(int i=0; i<n; i++)
                graph.push_back(vector<int>(n));
        for (int i=0; i<n; i++)
        {
                for(int j=0; j<n; j++)
                {
                        cin >> graph[i][j];
                        //if(graph[i][j] == -1)
                          //      graph[i][j] = MYINF;
                }
        }
        int q;
        cin >> q;
	vector<int> qs(q);
        for (int i=0; i<q; i++)
        {        
                int in;
                cin >> in;
		harmonic_centrality(graph, in-1);
        }	
}
