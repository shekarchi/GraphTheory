import java.util.ArrayList;
import java.util.HashSet;
import java.util.Scanner;


public class ChromaticPolynomial {

	public static MyNode getInstance (HashSet<MyNode> graph, int x) {
		for (MyNode m : graph) {
			if (m.id == x)
				return m;
		}
		MyNode res = new MyNode(x);
		graph.add(res);
		return res;
	}
	
	public static void printGraph(HashSet<MyNode> graph) {
		System.out.println("--->");
		for (MyNode node : graph) {
			System.out.print(node.id + ": ");
			for (MyNode a : node.adjacents) {
				System.out.print(a.id + ", ");
			}
			System.out.println();
		}
		System.out.println("<---");
	}
	
	public static void getInput(HashSet<MyNode> graph, ArrayList<Edge> allEdges, Integer edgeNumber) {
		Scanner reader = new Scanner(System.in);
		int n = reader.nextInt();
		int m = reader.nextInt();
		edgeNumber = new Integer(m);
		for (int i=0; i<n; i++) {
			MyNode temp = new MyNode(i);
			graph.add(temp);
		}
		int x, y;
		for (int t=0; t<m;t++) {
			x = reader.nextInt();
			y = reader.nextInt();
			MyNode r = getInstance(graph, x);
			MyNode s = getInstance(graph, y);
			r.addAdj(s);
			s.addAdj(r);
			allEdges.add(new Edge(x, y));
		}
		reader.close();
		
	}
	
	public static Edge takeAnEdge (HashSet<MyNode> graph) {
		MyNode temp;
		for (MyNode n : graph) {
			if (!n.adjacents.isEmpty()) {
				MyNode[] adjArr = n.adjacents.toArray(new MyNode[graph.size()]);
				temp = adjArr[0];
				//System.out.print("\nchosen edge: " + n.id + " " + temp.id + " for graph: ");
				//for (MyNode zz : graph)
					//System.out.print(zz.id+ ", ");
				//System.out.println();
				return new Edge(n.id, temp.id);
			}
		}
		return null;
	}
	
	public static void deleteEdge(HashSet<MyNode> graphd, Edge tempEdge) {
		int x = tempEdge.from;
		int y = tempEdge.to;
		MyNode m = getInstance(graphd, x);
		MyNode n = getInstance(graphd, y);
		m.removeAdj(n);
		n.removeAdj(m);
	}
	
	public static void contractEdge (HashSet<MyNode> graphc, Edge tempEdge) {
		int x = tempEdge.from;
		int y = tempEdge.to;
		MyNode m = getInstance(graphc, x);
		MyNode n = getInstance(graphc, y);
		for (MyNode s : n.adjacents) {
			s.removeAdj(n);
			if(s.id != m.id) {
				if(!m.hasThisNeighbor(s))
					m.addAdj(s);
				if(!s.hasThisNeighbor(m))
					s.addAdj(m);
			}
		}
		m.adjacents.remove(n);
		graphc.remove(n);
	}
	
	public static Polynomial computeChromaticPolynomial (HashSet<MyNode> graph, Integer edgeNumber) {
		
		if (edgeNumber == 0) {
			Polynomial p1   = new Polynomial(1, 1);//k
			Polynomial p2   = new Polynomial(1, 0);//1
			for (int i=0; i<graph.size(); i++)
				p2 = p2.times(p1);
			return p2;
		}
		/*if (allEdges.size() == graph.size()-1) {
			System.out.println("tree");
			//Polynomial p   = new Polynomial(4, 3);//4x^3
			Polynomial p1   = new Polynomial(1, 1);//k
			Polynomial p2   = new Polynomial(1, 0);//1
			Polynomial p3 = new Polynomial(1, 1);//k
			p3 = p3.minus(p2);//k-1
			for(int i=1; i<graph.size()-1; i++)
				p3 = p3.times(p3);//(k-1)^(n-1)
			return p3.times(p1);//(k-1)^(n-1)*k
		}*/
		
		HashSet<MyNode> graphd = new HashSet<MyNode>();
		HashSet<MyNode> graphc = new HashSet<MyNode>();
		for (MyNode zz : graph) {
			MyNode newNode = getInstance(graphd, zz.id);
			for (MyNode ad : zz.adjacents) {
				MyNode nn = getInstance(graphd, ad.id);
				newNode.adjacents.add(nn);
			}
		}
		for (MyNode zz : graph) {
			MyNode newNode = getInstance(graphc, zz.id);
			for (MyNode ad : zz.adjacents) {
				MyNode nn = getInstance(graphc, ad.id);
				newNode.adjacents.add(nn);
			}
		}
		//printGraph(graphc);
		Edge tempEdge = takeAnEdge(graph);
		//System.out.println("before delete edge, number of edges: " + edgeNumber);
		if (tempEdge == null) {
			Polynomial p1   = new Polynomial(1, 1);//k
			Polynomial p2   = new Polynomial(1, 0);//1
			for (int i=0; i<graph.size(); i++)
				p2 = p2.times(p1);
			return p2;
		}
		deleteEdge(graphd, tempEdge);
		//System.out.println("graph is:");
		//printGraph(graph);
		//System.out.println("graphd is:");
		//printGraph(graphd);
		contractEdge(graphc, tempEdge);
		//System.out.println("graphc is:");
		//printGraph(graphc);
		
		Polynomial pd = computeChromaticPolynomial(graphd, new Integer(edgeNumber-1));
		Polynomial pc = computeChromaticPolynomial(graphc, new Integer(edgeNumber-1));
		return pd.minus(pc);
	}
	
	public static void main(String[] args) {
		HashSet<MyNode> graph = new HashSet<MyNode>();
		ArrayList<Edge> allEdges = new ArrayList<Edge>();
		Integer edgeNumber = new Integer(0);
		Scanner reader = new Scanner(System.in);
		int n = reader.nextInt();
		int m = reader.nextInt();
		edgeNumber = new Integer(m);
		for (int i=0; i<n; i++) {
			MyNode temp = new MyNode(i);
			graph.add(temp);
		}
		int x, y;
		for (int t=0; t<m;t++) {
			x = reader.nextInt();
			y = reader.nextInt();
			MyNode r = getInstance(graph, x);
			MyNode s = getInstance(graph, y);
			r.addAdj(s);
			s.addAdj(r);
			allEdges.add(new Edge(x, y));
		}
		reader.close();
//		getInput(graph, allEdges, edgeNumber);
		System.out.println(computeChromaticPolynomial(graph, edgeNumber).toString());
	}
}

class MyNode {
	public int id;
	public HashSet<MyNode> adjacents;
	public MyNode (int i) {
		this.id = i;
		this.adjacents = new HashSet<MyNode>();
	}
	public MyNode () {
		this.adjacents = new HashSet<MyNode>();
	}
	public void addAdj (MyNode adj) {
		adjacents.add(adj);
	}
	public void removeAdj (MyNode adj) {
		adjacents.remove(adj);
	}
	public boolean hasThisNeighbor(MyNode m) {
		for (MyNode a : this.adjacents) {
			if (a.id == m.id)
				return true;
		}
		return false;
	}
}

class Edge {
	public int from;
	public int to;
	public Edge (int f, int t) {
		this.from = f;
		this.to = t;
	}
}
