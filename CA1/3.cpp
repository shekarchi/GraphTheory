#include <limits.h>
#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

class Adj {
public:
	int src;
	int dest;
	int weight;
	int a;
	Adj(int s, int d, int w)
	{
		src = s;
		dest = d;
		weight = w;
	}
};

int count_child(vector< vector<Adj> > adj_list, vector<int> *child_num, int from)
{
	if((*child_num)[from] > -1)
		return (*child_num)[from];
	if(adj_list[from].size() == 0)
	{	
		(*child_num)[from] = 1;
		return 1;
	}
	
	(*child_num)[from] = 1;
	for(int j=0; j<adj_list[from].size(); j++)
	{
		(*child_num)[from] += count_child(adj_list, child_num, adj_list[from][j].dest);
	}

	return (*child_num)[from];
}

int main()
{
	int n;
	cin >> n;
	vector< vector<Adj> > adj_list(n);
	vector<Adj> edges;
	int si, ti, li;
	for(int i=0; i<n-1; i++)
	{
		cin >> si >> ti >> li;
		Adj a = Adj(si-1, ti-1, li);
		adj_list[si-1].push_back(a);
		edges.push_back(a);
	}

	vector<int> child_num(n, -1);
	count_child(adj_list, &child_num, 0);

	for(int i=0; i<edges.size(); i++)
	{
		edges[i].a = child_num[edges[i].dest];
	}

	int q;
	cin >> q;
	double sum = 0;
	for(int i=0; i<n; i++)
	{
		for(int j=0; j<adj_list[i].size(); j++)
		{
			int a = child_num[adj_list[i][j].dest];
			adj_list[i][j].a = adj_list[i][j].weight*(n-2)*(a)*(n-a);
			sum += adj_list[i][j].a;
		}
	}
	sum /= (double)(n*(n-1)*(n-2)/6);
	//cout << sum << endl;

	for(int qs=0; qs<q; qs++)
	{
		int edge_num, new_w;
		cin >> edge_num >> new_w;
		int diff = edges[edge_num-1].weight - new_w;
		sum -= ((double)(diff*edges[edge_num-1].a*(n-2)*(n-edges[edge_num-1].a))/(double)(n*(n-1)*(n-2)/6));
		edges[edge_num-1].weight = new_w;
		cout << setiosflags(ios::fixed) << std::setprecision(6) << sum << endl;
	}

}