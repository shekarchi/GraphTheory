/**
 * Created by zahra on 5/2/16.
 */

import java.util.*;

class BiNode implements Comparable<BiNode>{
    public Integer id;
    public HashSet <BiNode> neighbours;
    public BiNode (int _id) {
        id = _id;
        neighbours = new HashSet<>();
    }

    @Override
    public String toString() {
        return id.toString();
    }

    @Override
    public int compareTo(BiNode biNode) {
        return BiNodeComparator.getInstance().compare(this, biNode);
    }

    public int commonNeighborhoodSize(HashSet<BiNode> l) {
        int result=0;
        for(BiNode n: neighbours)
            if(l.contains(n))
                ++result;
        return result;
    }
}

class BiNodeComparator implements Comparator<BiNode> {
    private static BiNodeComparator instance = new BiNodeComparator();
    private HashSet<BiNode> l;
    private BiNodeComparator() {
        l=new HashSet<>();
    }
    public static BiNodeComparator getInstance() {
        return instance;
    }
    public void setL(HashSet<BiNode> l) {
        this.l = l;
    }
    public int compare(BiNode n1, BiNode n2) {
        if(n1.commonNeighborhoodSize(l)>n2.commonNeighborhoodSize(l))
            return 1;
        return -1;
    }
}

class BiGraph {
    public HashSet<BiNode> U;
    public HashSet<BiNode> V;
    public BiGraph() {
        U = new HashSet<>();
        V = new HashSet<>();
    }
}

/*for this, I made use of:
http://stackoverflow.com/questions/4903611/java-list-sorting-is-there-a-way-to-keep-a-list-permantly-sorted-automatically,
also I got Comparable part from A. Moez
*/
class MySortedArrayList <T extends Comparable<? super T>> extends ArrayList<T> {
    @Override
    public boolean add(T inserting) {
        int index=Collections.binarySearch(this, inserting);
        if (index < 0) index = ~index;
        super.add(index, inserting);
        return true;
    }
}


public class A {
    public static int maxVertexSize;

    public static void parseInput(BiGraph graph, MySortedArrayList<BiNode> sortedP) {
        int a, b, m;
        Scanner sc = new Scanner(System.in);
        a = sc.nextInt();
        b = sc.nextInt();
        m = sc.nextInt();

        ArrayList<BiNode> u = new ArrayList<>();
        for(int i=0; i<a; i++)
            u.add(new BiNode(i));
        ArrayList<BiNode> v = new ArrayList<>();
        for(int i=0; i<b; i++)
            v.add(new BiNode(i));
        int tmpf;
        int tmpt;
        for(int i=0; i<m; i++) {
            tmpf = sc.nextInt();
            tmpt = sc.nextInt();
            u.get(tmpf).id = tmpf;
            v.get(tmpt).id = tmpt;
            u.get(tmpf).neighbours.add(v.get(tmpt));
            v.get(tmpt).neighbours.add(u.get(tmpf));
        }

        graph.U = new HashSet<>(u);
        graph.V = new HashSet<>(v);
        if(graph.U.size() < graph.V.size()) {
            HashSet<BiNode> temp = new HashSet<>(graph.U);
            graph.U = graph.V;
            graph.V = temp;

        }
        BiNodeComparator.getInstance().setL(graph.U);

        for (BiNode n: graph.V)
            sortedP.add(n);
    }

    /*a function which is implemented from a paper, introduced in report*/
    public static void bicliqueFind(BiGraph G, HashSet<BiNode> L, HashSet<BiNode> R, MySortedArrayList<BiNode> P, HashSet<BiNode> Q) {
        BiNodeComparator.getInstance().setL(L);
        int i = 0; //position of selected candidate in P
        while(!P.isEmpty()) {
            BiNode x = P.get(0);//select next candidate from P in order
            HashSet<BiNode> Rp = new HashSet<>(R);
            Rp.add(x);
            HashSet<BiNode> Lp = new HashSet<>();
            HashSet<BiNode> LpBar = new HashSet<>();

            for (BiNode u : L) {
                if (x.neighbours.contains(u))
                    Lp.add(u);
                else
                    LpBar.add(u);
            }
            //observation 1: extend biclique
            //LpBar <- L\Lp has been done above
            HashSet<BiNode> C = new HashSet<>();
            C.add(x);
            MySortedArrayList<BiNode> Pp = new MySortedArrayList<>();
            HashSet<BiNode> Qp = new HashSet<>();

            //observation 2: check maximality
            boolean is_maximal = true;
            for(BiNode v : Q) {
                HashSet<BiNode> Nv = new HashSet<>();
                for (BiNode u : Lp) {
                    if(v.neighbours.contains(u)) {
                        Nv.add(u);
                    }
                }
                //observation 4: end of branch
                if(Nv.size() == Lp.size()) {
                    is_maximal = false;
                    break;
                }
                else if(Nv.size() > 0)
                    Qp.add(v);
            }
            if(is_maximal) {
                for(BiNode v : P)
                    if(v != x) {
                        HashSet<BiNode> Nv = new HashSet<>();//get the neighbours of v in Lp
                        for(BiNode u : Lp)
                            if(v.neighbours.contains(u))
                                Nv.add(u);
                        if(Nv.size() == Lp.size()) {
                            Rp.add(v);
                            //observation 3: expand to maximal
                            HashSet<BiNode> S = new HashSet<>();
                            for(BiNode u : LpBar)
                                if(v.neighbours.contains(u))
                                    S.add(u);
                            if(S.size() == 0)
                                C.add(v);
                            //observation 5: further pruning
                        }
                        else if(Nv.size() > 0) {
                            Pp.add(v);//insert v into Pp in non-decreasing order of common neighbourhood size
                        }
                    }
                //report maximal biclique
                //System.out.println("Lp and Rp Are:");
                //System.out.println("Lp:\t" + Lp.toString());
                //System.out.println("Rp:\t" + Rp.toString());
                if(Lp.size()+Rp.size() > maxVertexSize)
                    maxVertexSize = Lp.size()+Rp.size();
                if(!Pp.isEmpty()) {
                    bicliqueFind(G, Lp, Rp, Pp, Qp);
                    BiNodeComparator.getInstance().setL(L);
                }
            }
            Q.addAll(C);
            P.removeAll(C);
        }
    }

    public static void main(String[] args) {
        maxVertexSize = -1;
        BiGraph graph = new BiGraph();
        MySortedArrayList<BiNode> sortedP = new MySortedArrayList<BiNode>();
        parseInput(graph, sortedP);
        bicliqueFind(graph, graph.U, new HashSet<BiNode>(), sortedP, new HashSet<BiNode>());
        System.out.println(maxVertexSize);
    }
}
