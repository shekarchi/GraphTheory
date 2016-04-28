#include <iostream>
#include <vector>

#define MYINF 2147483647

using namespace std;

double graph_centrality(vector<int> degrees, int max_deg, int n)
{
	double sum = 0;
	for(int i=0; i<n; i++)
	{
		sum += (double)(max_deg - degrees[i]);
	}
	return sum/(double)((n-1)*(n-2));
}

int main()
{
	int m,n;
        cin >> n >> m;
        vector< vector<int> > graph;
	vector<int> degrees(n);
        for(int i=0; i<n; i++)
                graph.push_back(vector<int>(n));
        int max_deg = -1;
	for (int i=0; i<n; i++)
	{
		int deg = 0;
                for(int j=0; j<n; j++)
                {
			cin >> graph[i][j];
			if(graph[i][j] == -1)
				graph[i][j] = MYINF;
			else if(graph[i][j] == 0)
				;
			else
				deg++;
		}
		degrees[i] = deg;
		if(deg > max_deg)
			max_deg = deg;
        }
	int q;
        cin >> q;
        for (int i=0; i<q; i++)
        {
		int in;
		cin >> in;
		cout << degrees[in-1]<<endl;
	}
	cout << graph_centrality(degrees, max_deg, n) << endl;
}
