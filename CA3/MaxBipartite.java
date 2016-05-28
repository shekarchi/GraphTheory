import java.util.ArrayList;
import java.util.HashSet;
import java.util.Scanner;


public class MaxBipartite {
	public static int m = 6;
	public static int n = 6;
	
	public static boolean makeBipartiteMatch (ArrayList< ArrayList<Boolean> > bipartiteGraph, int u, ArrayList<Boolean> seen, ArrayList<Integer> match) {
		for (int v=0; v<n; v++) {
			if (bipartiteGraph.get(u).get(v) && !seen.get(v)) {
				seen.set(v, new Boolean(true));
				if(match.get(v) < 0 || makeBipartiteMatch(bipartiteGraph, match.get(v), seen, match)) {
					match.set(v, new Integer(u));
					return true;
				}
			}
		}
		
		return false;
	}
	
	public static int maxBipartiteMatching(ArrayList< ArrayList<Boolean> > bipartiteGraph) {
		int result = 0;
		
		ArrayList<Integer> match = new ArrayList<>();
		for (int i=0; i<n; i++)
			match.add(-1);
		
		for (int u=0; u<m; u++) {
			ArrayList<Boolean> seen = new ArrayList<Boolean>();
			for (int i=0; i<n; i++) 
				seen.add(false);
			if (makeBipartiteMatch(bipartiteGraph, u, seen, match))
				result++;
		}
		
		return result;
	}
	
	public static void main (String[] args) {
		ArrayList< ArrayList<Boolean> > bipartiteGraph = new ArrayList<>();
		/*ArrayList<Boolean> t1 = new ArrayList<Boolean>();
		t1.add(false);
		t1.add(false);
		t1.add(false);
		t1.add(false);
		t1.add(false);
		t1.add(true);
		bipartiteGraph.add(t1);
		ArrayList<Boolean> t2 = new ArrayList<Boolean>();
		t2.add(false);
		t2.add(false);
		t2.add(false);
		t2.add(false);
		t2.add(true);
		t2.add(false);
		bipartiteGraph.add(t2);
		ArrayList<Boolean> t3 = new ArrayList<Boolean>();
		t3.add(false);
		t3.add(false);
		t3.add(false);
		t3.add(true);
		t3.add(false);
		t3.add(false);
		bipartiteGraph.add(t3);
		ArrayList<Boolean> t4 = new ArrayList<Boolean>();
		t4.add(false);
		t4.add(false);
		t4.add(true);
		t4.add(false);
		t4.add(false);
		t4.add(false);
		bipartiteGraph.add(t4);
		ArrayList<Boolean> t5 = new ArrayList<Boolean>();
		t5.add(false);
		t5.add(false);
		t5.add(false);
		t5.add(false);
		t5.add(false);
		t5.add(false);
		bipartiteGraph.add(t5);
		ArrayList<Boolean> t6 = new ArrayList<Boolean>();
		t6.add(false);
		t6.add(false);
		t6.add(false);
		t6.add(false);
		t6.add(false);
		t6.add(false);
		bipartiteGraph.add(t6);
		for (int i=0; i<6; i++) {
			for(int j=0; j<6; j++) {
				System.out.print(bipartiteGraph.get(i).get(j) + " ");
			}
			System.out.println();
		}*/
		
		ArrayList<String> pairs = new ArrayList<String>();
		HashSet<Integer> threeRes = new HashSet<Integer>();
		
		Scanner reader = new Scanner(System.in);
		n = reader.nextInt();
		int x, y, plus, minus, mult;
		for (int i=0; i<n; i++) {
			x = reader.nextInt();
			y = reader.nextInt();
			pairs.add(String.valueOf(x)+"&"+String.valueOf(y));
			plus = x + y;
			minus = x - y;
			mult = x * y;
			threeRes.add(plus);
			threeRes.add(minus);
			threeRes.add(mult);
		}
		
		ArrayList<Integer> threeResArr = new ArrayList<Integer>(threeRes);
		m = threeResArr.size();
		for(int i=0; i<m+n; i++) {
			ArrayList<Boolean> temp = new ArrayList<Boolean>();
			for (int j=0; j<m+n; j++) {
				temp.add(false);
			}
			bipartiteGraph.add(temp);
		}
		
		for (int j=0; j<n; j++) {
			String pair = pairs.get(j);
			String[] each = pair.split("&");
			x = Integer.valueOf(each[0]);
			y = Integer.valueOf(each[1]);
			for(int i=0; i<threeResArr.size(); i++) {
				if(threeResArr.get(i)==x+y || threeResArr.get(i)==x-y || threeResArr.get(i)==x*y) {
					bipartiteGraph.get(i).set(j, true);
				}
			}
		}
		/*System.out.print("  \t");
		for (int i=0; i<threeResArr.size(); i++)
			System.out.print(threeResArr.get(i)+ "   ");
		System.out.println();
		for(int i=0; i<pairs.size(); i++) {
			System.out.print(pairs.get(i));
			for (int j=0; j<threeResArr.size(); j++)
				System.out.print(bipartiteGraph.get(i).get(j) + " ");
			System.out.println();
		}*/
		
		int mbpmSize = MaxBipartite.maxBipartiteMatching(bipartiteGraph);
		//System.out.println(mbpmSize);
		System.out.println((mbpmSize == n)?"Possible":"Impossible");
	}
}

