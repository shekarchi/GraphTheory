import java.util.*;

public class Main {
	
	public static int GCD(int u, int v) {
	    while ( v != 0) {
	        int r = u % v;
	        u = v;
	        v = r;
	    }
	    return u;
	}
	
	public static void main(String[] args) {
		
		int n, m, k;
		
		Scanner sc = new Scanner(System.in);
		n = sc.nextInt();
		m = sc.nextInt();
		k = sc.nextInt();
		
		HashSet<Node> V, U, S;
		ArrayList<Node> graph = new ArrayList<>();
		for(int i=0; i<n; i++) 
			graph.add(new Node());
		V = new HashSet<>(graph);
		U = new HashSet<Node>();
		for(int i=0; i<k; i++) {
			int tmp;
			tmp = sc.nextInt();
			U.add(graph.get(tmp));
		}
		S = new HashSet<>(V);
		S.removeAll(U);
		
		int x, y;
		for(int i=0; i<m; i++) {
			x = sc.nextInt();
			y = sc.nextInt();
			graph.get(x).neighbours.add(graph.get(y));
			graph.get(y).neighbours.add(graph.get(x));
		}
		//end of getting input
		
		for(Node nn: S)
		{
			nn.computeNs(S);
		}
		
		ArrayList<Node> Sarray;
		
		double bestValue = 0.0;
		int bestN = 0;
		int bestD = 1;
		
		while(!S.isEmpty()) {
			Sarray = new ArrayList<Node>(S);
			Node min = Sarray.get(0);
			for(Node t : Sarray) {
				if(t.value() < min.value())
					min = t;
			}
			//bestValue = Math.max(min.value(), bestValue);
			if(min.value() > bestValue) {
				bestValue = min.value();
				bestN = min.SNeighbours.size();
				bestD = min.neighbours.size();
			}
			for(Node nn : min.neighbours) {
				nn.SNeighbours.remove(min);
			}
			S.remove(min);
		}
		if(bestValue==0) {
			System.out.println("0/1");
			return;
		}
		System.out.println(new Integer(bestN/GCD(bestN, bestD)).toString() + "/" + new Integer(bestD/GCD(bestN, bestD)).toString());
	}
}

class Node {
	public HashSet <Node> neighbours;
	public HashSet<Node> SNeighbours;
	public Node () {
		neighbours = new HashSet<>();
		SNeighbours = new HashSet<>();
	}
	
	public void computeNs(HashSet<Node> S) {
		SNeighbours = new HashSet<>(S);
		SNeighbours.retainAll(neighbours);
	}
	
	public double value() {
		double Snum = SNeighbours.size();
		double VNum = neighbours.size();
		return (VNum==0)?0.0:Snum/VNum;
	}
}

class MyFraction {
	public int n;
	public int d;
	public MyFraction (int _n, int _d) {
		n = _n;
		d = _d;
	}
	public double toDouble() {
		double nt = n;
		double dt = d;
		return (d==0)?0.0:nt/dt; 
	}
}



