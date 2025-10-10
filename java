import java.util.*;

public class Graph {
    private int V; // число вершин
    private LinkedList<Integer>[] adj; // список соседей

    public Graph(int v) {
        V = v;
        adj = new LinkedList[V];
        for (int i = 0; i < V; i++) {
            adj[i] = new LinkedList<>();
        }
    }

    public void addEdge(int u, int v) {
        adj[u].add(v);
        adj[v].add(u); // для неориентированного графа
    }

    private void DFSUtil(int v, boolean[] visited) {
        visited[v] = true;
        System.out.print(v + " ");

        for (int neighbor : adj[v]) {
            if (!visited[neighbor]) {
                DFSUtil(neighbor, visited);
            }
        }
    }

    public void DFS(int start) {
        boolean[] visited = new boolean[V];
        System.out.println("Обход в глубину, начиная с вершины " + start + ":");
        DFSUtil(start, visited);
        System.out.println();
    }

    public static void main(String[] args) {
        Graph g = new Graph(5);

        g.addEdge(0, 1);
        g.addEdge(0, 4);
        g.addEdge(1, 2);
        g.addEdge(1, 3);
        g.addEdge(1, 4);
        g.addEdge(2, 3);
        g.addEdge(3, 4);

        g.DFS(0);
    }
}
