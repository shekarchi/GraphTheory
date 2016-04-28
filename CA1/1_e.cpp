#include <iostream>
#include <vector>
#include <cmath>

#define INF 2147483647

using namespace std;

void floyd_warshall(vector< vector<int> > graph, vector< vector<int> > *dist)
{
	int n = graph.size();
	for(int i=0; i<n; i++)
		for(int j=0; j<n; j++)
			(*dist)[i][j] = graph[i][j];
	for(int k=0; k<n; k++)
		for(int i=0; i<n; i++)
			for(int j=0; j<n; j++)
				if((*dist)[i][k]+(*dist)[k][j] < (*dist)[i][j])
					(*dist)[i][j] = (*dist)[i][k] + (*dist)[k][j];
}

void augmented_floyd_warshall(vector< vector<int> > graph, vector< vector<int> > sigma, vector<int> qs)
{
	int n = graph.size();
	vector< vector<int> > dist;
	for(int i=0; i<n; i++)
		dist.push_back(vector<int>(n));
	for(int i=0; i<n; i++)
		for(int j=0; j<n; j++)
			dist[i][j] = graph[i][j];
	vector< vector< vector<int> > > sigv;//from i to j through k
	for(int k=0; k<n; k++)
	{
		vector< vector<int> > temp;
		for(int i=0; i<n; i++)
			temp.push_back(vector<int>(n));
		sigv.push_back(temp);
	}
			
	for(int k=0; k<n; k++)
		for(int i=0; i<n; i++)
		{
			for(int j=0; j<n; j++)
			{
				if(dist[i][k]+dist[k][j] <= dist[i][j])
				{
					dist[i][j] = dist[i][k] + dist[k][j];
					sigv[i][j][k] = sigma[i][k]*sigma[k][j];
					
				}
				
			}
		}

	//for(int i=0; i<n; i++)
	//{
	//	for(int j=0; j<n; j++)
	//	{
	//		for(int k=0; k<n; k++)
	//			cerr << sigv[k][j][i];
	//		cerr<<endl;}
	//		cerr<<endl;}

	for(int i=0; i<qs.size(); i++)	
	{
		double sum = 0.0;
		for(int s=0; s<n; s++)
			for(int t=0; t<n; t++)
			{
				//cerr<<"s: "<<s<<" t: "<<t<<" v: "<<i<<" "<<sigv[s][t][i]<<" "<<sigma[s][t]<<endl;
				sum += (sigv[s][t][i]==0&&sigma[s][t]==0)?0:(double)sigv[s][t][i]/(double)sigma[s][t];
			}
		cout << sum << endl;
	}
}

void dfs_visit(vector< vector<int> > graph, int s, int u, vector<int>* count, vector< vector<int> > dist)
{
	int n = graph.size();
	for(int v=0; v<n; v++)
		if(graph[u][v] == 1)//adj with u eqivalent: graph[v][u]==0
		{
			if(dist[s][v]==dist[s][u]+1)
			{
				if(u==s)
					(*count)[v] = 1;
				else
					(*count)[v] += 1;
				dfs_visit(graph, s, v, count, dist);
			}
		}
}

void shortest_path_count(vector< vector<int> > graph, vector< vector<int> >dist, vector< vector<int> > *count)
{
	int n = graph.size();
	for(int i=0; i<n; i++)
	{
		vector <int> tmp_count(n, 0);
		dfs_visit(graph, i, i, &tmp_count, dist);
		(*count).push_back(tmp_count);
	}
}

int main()
{
	int m,n;
	cin >> n >> m;
	vector< vector<int> > graph;
	for(int i=0; i<n; i++)
		graph.push_back(vector<int>(n));
	for (int i=0; i<n; i++)	
		for(int j=0; j<n; j++)
			cin >> graph[i][j];
	vector< vector<int> > dist;
	for(int i=0; i<n; i++)
		dist.push_back(vector<int>(n));
	int q;
	cin >> q;
	vector <int> qs(q);
	for (int i=0; i<q; i++)
		cin >> qs[i];
	floyd_warshall(graph, &dist);

	vector< vector<int> > count;
	shortest_path_count(graph, dist, &count);
	vector< vector<int> > sigma;
	augmented_floyd_warshall(graph, count, qs);

}
