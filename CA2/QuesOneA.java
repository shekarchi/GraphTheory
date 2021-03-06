import java.util.ArrayList;
import java.util.HashSet;
import java.util.Scanner;

class BiNode {
	public int id;
	public HashSet <BiNode> neighbours;
	public BiNode (int _id) {
		id = _id;
		neighbours = new HashSet<>();
	}
}

class MyGraph {
	public HashSet<BiNode> U;
	public HashSet<BiNode> V;
	public MyGraph() {
		U = new HashSet<BiNode>();
		V = new HashSet<BiNode>();
	}
}

public class QuesOneA {

	public static void main(String[] args) {
		
		int a, b, m;
		
		Scanner sc = new Scanner(System.in);
		a = sc.nextInt();
		b = sc.nextInt();
		m = sc.nextInt();
		
		MyGraph graph = new MyGraph();
		
		int tmpf = -1;
		int tmpt = -1;
		for(int i=0; i<m; i++) {
			tmpf = sc.nextInt();
			tmpt = sc.nextInt();
			BiNode f = new BiNode(tmpf);
			BiNode t = new BiNode(tmpt);
			f.neighbours.add(t);
			t.neighbours.add(f);
			graph.U.add(f);
			graph.V.add(t);
		}
	}
	
}
