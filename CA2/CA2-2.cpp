/*
**
**for this implementation, I assume that index value is from 0 to n-1
*/

#include <iostream>
#include <vector>
#include <limits.h>
using namespace std;

class MyFraction {
public:
	int n;//n/d
	int d;
	MyFraction(int _n, int _d)
	{
		n = _n;
		d = _d;
	}
	string print() 
	{
		cout << " " << n << "/" << d << " ";
	}
	double toDouble()
	{
		return (d==0)?0.0:(double)n/(double)d;
	}
};

double doubleOf(int n, int d)
{
	return (d==0)?0.0:(double)n/(double)d;
}

unsigned GCD(int u, int v) {
    while ( v != 0) {
        unsigned r = u % v;
        u = v;
        v = r;
    }
    return u;
}

int main() 
{
	cout << GCD (0,0) << endl;
	// return 0;


	//get input
	int n, m, k, index, x, y;
	cin >> n >> m >> k;
	vector< vector<bool> > graph;
	for (int i=0; i<n; i++)
	{
		vector<bool> tmp(n, false);
		graph.push_back(tmp);
	}
	vector<int> value(n, 0);
	vector<bool> deleted(n, false);
	vector<int> Nv(n, 0);
	vector<bool> isInU(n, false);
	vector <int> VminusU;
	for (int i=0; i<k; i++)
	{
		cin >> index;
		isInU[index] = true;
	}
	for(int i=0; i<m; i++) 
	{
		cin >> x >> y;
		graph[x][y] = true;
		graph[y][x] = true;
		Nv[x]++;
		Nv[y]++;
	}
	//END of get input

	// print graph
	// for (int i=0; i<n; i++)
	// {
	// 	for(int j=0; j<n; j++)
	// 		cout << graph[i][j];
	// 	cout << endl;
	// }

	//initialize S = V-U
	MyFraction globalMaxS(0, 0);
	MyFraction minS1(INT_MAX, 1);
	for(int i=0; i<n; i++)
	{
		if(!isInU[i])
		{
			VminusU.push_back(i);
			int sum = 0;
			for(int j=0; j<n ; j++)
			{
				if(!isInU[j] && graph[i][j])
					sum++;
			}
			value[i] = sum;//(Nv[i]==0)?0.0:(double)sum/(double)Nv[i];

			if(doubleOf(value[i], Nv[i]) < minS1.toDouble())
			{
				minS1.n = value[i]; //= value[i];
				minS1.d = Nv[i];
			}
		}
	}
	globalMaxS.n = minS1.n;
	globalMaxS.d = minS1.d;
	cerr << "initial globalMaxS: " << globalMaxS.n << "/" << globalMaxS.d << endl<<endl;
	//END of init

	//print values
	// for (int i=0; i<n; i++)
	// 	cout << value[i] << "/" << Nv[i] << ",\t";
	// cout << endl;

	//update S to upper value
	for(int i=0; i<VminusU.size(); i++)
	{
		int min = 0;
		for (int m=1; m<VminusU.size(); m++)
			if(!deleted[VminusU[m]] && 
				(doubleOf(value[VminusU[m]], Nv[VminusU[m]]))<(doubleOf(value[VminusU[min]], Nv[VminusU[min]])))
				min = m;

		cerr << "\nfound min is: " << VminusU[min] << endl;

		int j = VminusU[min];//node index should be removed
		deleted[j] = true;
		if(value[j] == 0)//means Nv[j]=0 or has no nghbr out of U
		{	
			cerr << "--> a node _" << j << "_ with Nv=0 is found: " << endl;
			int t;
			for(t=0; t<n; t++)
				if(!deleted[t] && !isInU[t] && !deleted[t])
				{
					if(value[t] != 0)
					{
						globalMaxS.n = value[t];
						globalMaxS.d = Nv[t];
						cerr << endl<< "--> new value is assigned to globalMaxS - " << globalMaxS.n << "/" << globalMaxS.d << endl;
						break;
					}
				}
			for(int s=t; s<n; s++)
				if(!deleted[s] && !isInU[s])
				{
					cerr << "--> other value for S could be? " <<value[s] << " cmp " << globalMaxS.n << "/" << globalMaxS.d << endl;
					if((double)value[s]/(double)Nv[s] < globalMaxS.toDouble())
					{
						globalMaxS.n = value[s];
						globalMaxS.d = Nv[s];
					}
				}
			cerr << "updated value for globalMaxS after  removing iso node is " << globalMaxS.n << "/" << globalMaxS.d << endl<< endl;
			continue;
		}
		MyFraction minS(INT_MAX, 1);
		for(int t=0; t<n; t++)
			if(graph[j][t] && !isInU[t])//&& !deleted[t]
			{
				cerr << endl<< "loop for updating globalMaxS and found nghbr in V-U" << endl;
				cerr << "before any update for t="<<t<<" new value is " << value[t] << "/" << Nv[t] << endl;
				value[t] -= 1;
				cerr << "because of "<<j<< " for t="<<t<<" new value is " << value[t] << "/" << Nv[t]<< endl;
				if((double)value[t]/(double)Nv[t] < minS.toDouble())
				{
					minS.n = value[t];
					minS.d = Nv[t];
				}
				cerr << "and so minS is: " << minS.n << "/" << minS.d << endl;
			}
		if(minS.toDouble() > globalMaxS.toDouble())
		{
			globalMaxS.n = minS.n;
			globalMaxS.d = minS.d;
		}
		cerr << "and so globalMaxS is:: " << globalMaxS.n << "/" << globalMaxS.d << endl<< endl;
	}
	cout <<endl<< "finally: " << globalMaxS.n/GCD(globalMaxS.n, globalMaxS.d) << "/" << globalMaxS.d/GCD(globalMaxS.n, globalMaxS.d) << endl;
}
